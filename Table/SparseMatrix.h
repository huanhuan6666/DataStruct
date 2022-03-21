//
// Created by Administrator on 2022/3/21.
//

#ifndef DATA_STRUCT_SPARSEMATRIX_H
#define DATA_STRUCT_SPARSEMATRIX_H

#include <iostream>

using namespace std;

template<class T>
struct Triple {
    int row, col;
    T data;

    Triple(int r, int c, T d) : row(r), col(r), data(d) { ; }

    Triple &operator=(const Triple<T> &t) {
        if (this == &t)
            return *this;
        row = t.row;
        col = t.col;
        data = t.data;
        return *this;
    }
};

template<class T>
class SparseMatrix {
private:
    int m_row, m_col, m_term; //稀疏矩阵的大小和非0元素个数
    Triple<T> *m_data; //三元组数组
public:
    //构造函数
    SparseMatrix(int row = 6, int col = 7, int term = 9) : m_row(row), m_col(col), m_term(term) {
        m_data = new Triple<T>[term];
    }

    //转置
    SparseMatrix<T> &operator!() {
        Triple<T> *res = new Triple<T>[m_term]; //转置后元素数组
        int index = 0;
        if (m_term > 0) {
            for (int i = 0; i < m_col; i++) { //列就是之后的行,一行一行找
                for (int j = 0; j < m_term; j++) {
                    if (m_data[j].col == i) {
                        res[index].row = i;
                        res[index].col = m_data[j].row;
                        res[index].data = m_data[j].data;
                        index++;
                    }
                }
            }
        }
        delete[] m_data;
        m_data = res; //改变矩阵数据为转置后
        int col = m_col;
        m_col = m_row; //改变矩阵行和列
        m_row = col;
    }

    //矩阵快速转置，将转置结果存放在b中
    void FastTranspos(SparseMatrix<T> &b) {
        int *row_size = new int[m_col];
        int *row_start = new int[m_col];
        b.m_col = m_row;
        b.m_row = m_col;
        b.m_term = m_term;
        for (int i = 0; i < m_col; i++) {
            row_size[i] = 0;
            row_start[i] = 0;
        }
        for (int i = 0; i < m_term; i++) { //统计每一行的元素个数
            row_size[m_data[i].col]++;
        }

        row_start[0] = 0; //设置每一行的起始位置
        for (int i = 1; i < m_col; i++) {
            row_start[i] = row_start[i - 1] + row_size[i - 1]; //第i行的起始位置
        }

        //开始填写
        for (int i = 0; i < m_term; i++) {
            int the_row = m_data[i].col; //该元素应该在第the_row行
            int start = row_start[the_row]; //该元素应该放在的位置
            b.m_data[start].row = the_row;
            b.m_data[start].col = m_data[i].row;
            b.m_data[start].data = m_data[i].data;
            row_start[the_row]++; //修改这一行的起始位置
        }
        delete []row_start;
        delete []row_size;
    }

    //矩阵相加 未完成，因为根本不会产生新节点hhhh
    bool operator+(const SparseMatrix<T> &b) {
        if (m_row != b.m_row || m_col != b.m_col) {
            cout << "the matrix must be the same size!" << endl;
            return false;
        }
        for (int i = 0; i < m_term; i++) {
            for (int j = 0; j < b.m_term; j++) {
                if (m_data[i].row == b.m_data[j].row &&
                    m_data[i].col == b.m_data[j].col) {
                    m_data[i].data += b.m_data[j].data;
                }
            }
        }
        return true;
    }

    //矩阵相乘
    bool operator*(const SparseMatrix<T> &b) {

    }
};


#endif //DATA_STRUCT_SPARSEMATRIX_H
