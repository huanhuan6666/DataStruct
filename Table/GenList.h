//
// Created by Administrator on 2022/4/7.
//

#ifndef DATA_STRUCT_GENLIST_H
#define DATA_STRUCT_GENLIST_H
#include <iostream>
#include <unordered_map>

using namespace std;

template<class T>
struct GenListNode{
    int type; //0附加表头 1数据本身 2递归子表
    union {
        int ref; //0 表的引用计数
        T data; //1 数据本身
        GenListNode<T> *son; //2 递归子表的附加头指针
    }info;
    GenListNode<T>* next; //构成链式结构

    //下面是结点的构造函数
    GenListNode() : type(0), next(nullptr) { info.ref = 0; }
    GenListNode(const GenListNode<T>&x): type(x.type), next(x.next) { ; }
};

template<class T>
class GenList{
    friend istream&operator>>(istream& in, GenList<T>& l){
        unordered_map<char, GenListNode<T>*> map;
        l.Create(in, l.head, map); //注意Create会将整个表看作一个子表 因此还需要改一下
        auto p = l.head->next; //p是Create后唯一的结点 把整个表看作了子表
        l.head = p->info.son;
        delete p;
    }
    friend ostream&operator<<(ostream& out, GenList<T>& l){
        out << '(';
        l.Display(out, l.head);
        out << ')';
    }
private:
    GenListNode<T> *head; //附加的表头结点 类型为0
    GenListNode<T> *Copy(GenListNode<T>* l); //递归实现表复制
    int Length(GenListNode<T>* l); //递归实现求表的长度
    int Depth(GenListNode<T>* l); //递归实现求表的深度
    bool Equal(GenListNode<T>* l, GenListNode<T>* r); //递归判断两个广义表是否一致
    void Remove(GenListNode<T>* l); //递归实现删除广义表

    void Create(istream& in, GenListNode<T>* l, unordered_map<char, GenListNode<T>*> &map); //根据输入流的内容建立好完整的 带附加头的广义表
    void Display(ostream& out, GenListNode<T>* l); //输出广义表的结构
public:
    GenList();
    ~GenList();
    bool Head(GenListNode<T> &x);//表头就是一个结点
    bool Tail(GenList<T> &x);//表尾是一个子表 因此x是个List 我们的实现是深拷贝一份子表出来

    GenListNode<T> *First(); //返回该表的首结点指针
    GenListNode<T> *Next(GenListNode<T>* elem); //返回elem结点的直接后续结点指针

    void Copy(const GenList<T>& x); //深拷贝广义表x 其实就是拷贝构造

    int Length() const; //获取本广义表的长度
    int Depth() const; //获取本广义表的深度
};

//构造函数 初始化附加表头结点head即可
template<class T>
GenList<T>::GenList() {
    head = new GenListNode<T>; //结点默认构造为表头结点
    if(head == nullptr){
        cerr << "创建附加表头结点失败！" << endl;
        exit(1);
    }
}

//析构函数 需要调用Remove私有方法删除广义表 最后剩下的附加头需要自行删除
template<class T>
GenList<T>::~GenList() {
    Remove(head); //最后只剩下附加头
    delete head; //删除附加头
}

//获取表头结点 填写到x内
template<class T>
bool GenList<T>::Head(GenListNode<T> &x) {
    if(head->next == nullptr) { //广义表为空
        return false;
    }
    auto p = head->next; //p指向实际的表头
    x.type = p->type;
    switch (x.type) {
        case 0: //附加表头结点
            x.info.ref = p->info.ref;
            break;
        case 1: //数据结点
            x.info.data = p->info.data;
            break;
        case 2: //子表
            x.info.son = p->info.son;
            break;
        default:
            break;
    }
    return true;
}

//获取表尾 使用私有的Copy深拷贝一份子表出来
template<class T>
bool GenList<T>::Tail(GenList<T> &x) {
    if(head->next == nullptr) //表为空
        return false;

    x.head = new GenListNode<T>; //设置x的附加表头
    x.head->next = Copy(head->next->next); //深拷贝实际表头之后的所有 都是表尾
    return true;
}

//还是注意 List的head成员是附加头结点 实际表头为head->next
template<class T>
GenListNode<T> *GenList<T>::First() {
    return head->next;
}

//注意elem可能为空
template<class T>
GenListNode<T> *GenList<T>::Next(GenListNode<T> *elem) {
    if(elem == nullptr) //defensive
        return elem;
    return elem->next;
}

//公共接口 调用私有的Copy
template<class T>
void GenList<T>::Copy(const GenList<T> &x) {
    head = Copy(x.head);
}

//公共接口 调用私有的Length
//这玩意就是说不用递归也能做 算了就当玩递归罢hhh
template<class T>
int GenList<T>::Length() const {
    return Length(head);
}

//公共接口 调用私有的Depth 和求二叉树深度一回事
//二叉树要看左右子树谁深 这里也一样 找所有子表最深的那个
template<class T>
int GenList<T>::Depth() const {
    return Depth(head);
}

//递归实现 深拷贝一份l表示的广义表 有附加头结点也不怕 一视同仁
//就像递归复制链表那样 最本质的就是最后一句 res->next = Copy(l->next)
//但链表那里复制结点非常简单 只需要创建就好了 而这里可能出现结点本身代表一个广义表 这时就需要在复制结点时递归了 见case 2
template<class T>
GenListNode<T> *GenList<T>::Copy(GenListNode<T> *l) {
    if(l == nullptr) //递归终点 直到表顶层的末尾
        return nullptr;
    //复制当前结点
    auto p = new GenListNode<T>;
    p->type = l->type;
    switch (p->type) {
        case 0: //表头 正常复制即可
            p->info.ref = l->info.ref;
            break;
        case 1: //数据结点
            p->info.data = l->info.data;
            break;
        case 2: //子表需要递归复制
            p->info.son = Copy(l->info.son);
            break;
        default:
            break;
    }
    p->next = Copy(l->next); //在顶层减小规模
    return p;
}

//递归实现求表的长度 l可能为附加头结点
template<class T>
int GenList<T>::Length(GenListNode<T> *l) {
    if(l == nullptr)
        return 0;
    int s_len = Length(l->next); //子问题
    if(l->type == 0){ //去除附加头结点的长度
        return s_len;
    }
    return 1 + s_len; //自己不是附加头
}

//递归实现求表的深度 其实就是找所有子表的最大深度
template<class T>
int GenList<T>::Depth(GenListNode<T> *l) {
    if(l == nullptr)
        return 0;
    int res = 0;
    auto p = l;
    while(p){
        if(p->type == 2){ //是子表 看看是否更深
            res = max(res, Depth(p->info.son));
        }
        p = p->next;
    }
    return res + 1; //最深的子表深度 + 1就是自己的深度
}

//递归实现删除广义表 注意每个表可以被引用多次 因此只有当ref==0时才删除 外部调用Remove时l一定为附加表头结点
//删除扫描顶层表采用头删法 即附加头l恒定 一直删l->next结点 这就是附加头结点带来的好处
//结点表示子表也照常删除 我们没有碰见子表立刻删除 而是等到ref<=0时才删 是因为如果过早删除子表 那么后续同样引用该子表的内存就非法了
//因为之前已经删的干干净净 附加头都没有了 都没法判断 一访问程序就宕
template<class T>
void GenList<T>::Remove(GenListNode<T> *l) {
    if(l == nullptr) //defensive
        return;
    l->info.ref--; //l规定为附加头 该表引用计数--
    if(l->info.ref > 0)
        return;
    //这个表必须要删了
    auto p = l->next; //p指向实际表头
    while(p){
        if(p->type == 2){ //递归删除子表
            Remove(p->info.son);//p->info.son为子表的附加头结点
            if(p->info.son->info.ref <= 0){ //子表被删了就要把附加头也删干净
                delete p->info.son;
            }
        }
        //每次都删附加头的next结点
        l->next = p->next;
        delete p;
        p = l->next;
    }
    //头删法删到最后只剩附加头节点 成功删除
}


//递归判断两个广义表是否一致
//和复制表思想一样 关键就是最后的 b_info && Equal(l->next, r->next);
//只不过b_info判断当前结点是否相等是麻烦点 如果结点代表子表则需要递归判断  对应复制表时若当前结点表示子表则要递归复制
template<class T>
bool GenList<T>::Equal(GenListNode<T> *l, GenListNode<T> *r) {
    if(!l && !r) return true; //两个都为空
    else if(!l || !r) return false; //一个空 一个不空
    else{ //两个都不空 需要判断
        if(l->type != r->type) //结点类型不同
            return false;

        bool b_info; //判断结点信息是否一致 如果结点代表子表则递归比较
        switch (l->type) {
            case 0: //附加表头
                b_info = l->info.ref == r->info.ref;
                break;
            case 1: //数据
                b_info = l->info.data == r->info.data;
                break;
            case 2: //子表不应该比较指针(因为指针显然不同 应该递归比较子表的数据
                b_info = Equal(l->info.son, r->info.son);
                break;
            default:
                break;
        }

        return b_info && Equal(l->next, r->next); //这里b_info放在前面还能短路 嘻嘻
    }
}

//我们注意到 这个递归子问题是通过in来缩小问题规模的 且函数把所有的输入都看作子表 只是创建了对应的子表结点 因此输入的最后一定需要有;表示结束
//参数l为已经存在的结点的指针  关键的递归创建步骤为 创建好子表 然后l->next指向它 即Create(in, cur, map); l->next = cur;
//数据结点和子表结点通用 特殊之处是,空格之类的符号直接 Create(in, l, map) 即仍然创建l结点 但in已经指向了下一个字符 问题规模已经缩小了
template<class T>
void GenList<T>::Create(istream &in, GenListNode<T> *l, unordered_map<char, GenListNode<T>*> &map) {
    T chr;
    in >> chr;
    GenListNode<T>* cur = nullptr; //当前结点 只有子表或者数据结点才有用
    if(isupper(chr) || chr == '('){ //是个子表
        cur = new GenListNode<T>;
        cur->type = 2;
        if(isupper(chr)) {
            if (map.count(chr)) { //子表存在
                auto p = map[chr]; //子表附加头
                p->info.ref += 1;
                cur->info.son = map[chr]; //当前结点指向子表的附加头
            } else { //子表不存在 需要递归创建
                auto p = new GenListNode<T>; //创建子表的附加头
                p->info.ref = 1;
                map[chr] = p;
                cur->info.son = map[chr]; //当前结点指向子表的附加头

                in >> chr; //表名称后必定为 (
                if(chr != '('){
                    cerr << "表名称后必须紧跟 ( !" << endl;
                    exit(1);
                }
                //递归创建子表 此时in指向(的下一个字符 cur->info.son为指向子表的附加头结点
                Create(in, cur->info.son, map);
            }
        }
        Create(in, cur, map); //递归创建顶层的后续部分
        l->next = cur;
    }
    else if(islower(chr)){ //是数据元素
        cur = new GenListNode<T>;
        cur->type = 1;
        cur->info.data = chr;
        Create(in, cur, map);
        l->next = cur;
    }
    else if(chr == ','){ //逗号则继续递归 in的问题规模缩小了
        Create(in, l, map);
    }
    else if(chr == ')' || chr == ';'){ //说明没有后续结点了
        l->next = nullptr;
    }
    else if(chr == '#'){ //空表 后面一定是)
        in >> chr;
        if(chr != ')'){
            cerr << "#后一定为) ！" << endl;
            exit(1);
        }
    }
    else{ //出现空格之类的 和逗号一样 继续递归 in的问题规模缩小了
        Create(in, l, map);
    }
}

//输出广义表的结构 先输出当前结点的 再递归输出next 是个先序遍历
template<class T>
void GenList<T>::Display(ostream &out, GenListNode<T>* l) {
    if(l == nullptr)
        return;
    switch (l->type) {
        case 0: //表头
            out << "头";
            break;
        case 1: //数据点
            out << l->info.data << ',';
            break;
        case 2: //子表
            out << "(";
            Display(out, l->info.son);
            out << "),";
            break;
    }
    Display(out, l->next);
}


#endif //DATA_STRUCT_GENLIST_H
