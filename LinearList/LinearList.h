//
// Created by Administrator on 2022/3/6.
//

#ifndef DATA_STRUCT_LINEARLIST_H
#define DATA_STRUCT_LINEARLIST_H

template<class T> //定义线性表的抽象基类
class LinearList {
public:
    LinearList() = default;   //构造函数
    ~LinearList() = default; //析构函数

    virtual int Length() const = 0; //求大小
    virtual bool getData(int i, T& x) const = 0; //获取第i个元素
    virtual void setData(int i, const T& x) = 0; //设置第i个元素
    virtual bool Insert(int i, const T& x) = 0; //在位置i上插入x
    virtual bool Remove(int i, T& x) = 0; //删除第i个元素并通过x返回

    virtual bool IsEmpty() = 0; //是否为空
};

#endif //DATA_STRUCT_LINEARLIST_H
