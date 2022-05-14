//
// Created by Administrator on 2022/4/24.
//

#ifndef DATA_STRUCT_UFSETS_H
#define DATA_STRUCT_UFSETS_H
class UFSet {
    int* parent; //著名的 父指针数组 就是int类型 因为都是下标
    int size;
public:
    explicit UFSet(int _size = 10):size(_size) {
        if(size) {
            parent = new int[size];
            for(int i = 0; i < size; i++)
                parent[i] = -1; //初始化每个结点单独成集合 只有一个结点
        }
        else
            parent = nullptr;
    }
    ~UFSet() {
        delete [] parent;
    }
    //合并元素x1和x2所在的集合
    void Union(int x1, int x2);
    //查找x元素所在集合 即根节点下标
    int Find(int x);
};

//合并x1和x2所在的集合
void UFSet::Union(int x1, int x2) {
    int p1 = Find(x1), p2 = Find(x2);
    if(p1 == p2) { //本来就在一个集合中 无需合并
        return ;
    }
    if(-parent[p1] < -parent[p2]) { //x1所在集合元素个数少 附加到集合p2下
        parent[p2] += parent[p1]; //集合p2元素个数变多
        parent[p1] = p2;
    }
    else { //否则就是p2附加到p1上
        parent[p1] += parent[p2];
        parent[p2] = p1;
    }
}

//查找x所在集合的根结点 并且进行路径压缩
int UFSet::Find(int x) {
    int root = x;
    for(; parent[root] >= 0; root = parent[root]) ; //跳出循环后 j就是x的根节点下标
    while(x != root) { //压缩从x到根j路径上的所有结点temp 使其直接指向根
        int temp = parent[x];
        parent[x] = root;   //直接指向根
        x = temp;   //继续沿路径上爬
    }
    return root;
}

#endif //DATA_STRUCT_UFSETS_H
