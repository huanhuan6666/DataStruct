//
// Created by Administrator on 2022/3/22.
//

#ifndef DATA_STRUCT_ASTRING_H
#define DATA_STRUCT_ASTRING_H

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class AString {
private:
    char *ch;
    int curLength; //当前串实际长度
    int maxSize; //当前数组允许的最大长度
public:
    explicit AString(int size = 128) : curLength(0), maxSize(size) {
        ch = new char[maxSize + 1];
        ch[0] = '\0';
    }

    ~AString() {
        delete[]ch;
    }

    AString(const AString &s) {
        maxSize = s.maxSize;
        curLength = s.curLength;
        ch = new char[maxSize + 1];
        strcpy(ch, s.ch);
    }

    AString &operator=(const AString &s) {
        if (this == &s)
            return *this;
        delete[]ch;
        maxSize = s.maxSize;
        curLength = s.curLength;
        ch = new char[maxSize + 1];
        strcpy(ch, s.ch);
        return *this;
    }

    //求当前字符串长度
    int Length() const {
        return curLength;
    }

    //返回下标值s[i]
    char &operator[](int index) {
        if (index >= curLength) {
            cout << "index is out of range!" << endl;
            return ch[maxSize - 1];
        }
        return ch[index];
    }

    //提取字串
    AString operator()(int pos, int len) {
        AString res;
        if (pos >= 0 && pos < curLength && len > 0) {
            res.ch = new char[maxSize];
            int i = 0;
            while (pos < curLength && len > 0) {
                res.ch[i] = ch[pos];
                i++;
                pos++;
                len--;
            }
            res.ch[i] = '\0';
        }
        return res;
    }

    //判断字符串是否相等
    bool operator==(const AString &s) {
        return strcmp(ch, s.ch) == 0;
    }

    bool operator!=(const AString &s) {
        return strcmp(ch, s.ch) != 0;
    }

    AString &operator+=(const AString &s) {
        if (curLength + s.curLength > maxSize) {
            char *big = new char[maxSize + s.maxSize];
            int i;
            for (i = 0; i < curLength; i++) {
                big[i] = ch[i];
            }
            for (; i < curLength + s.curLength; i++) {
                big[i] = s.ch[i];
            }
            big[i] = '\0';
            delete[]ch;
            ch = big;
            maxSize = maxSize + s.maxSize;
            curLength = curLength + s.curLength;
        } else {
            int newlength = curLength + s.curLength;
            for (int i = curLength; i < newlength; i++) {
                ch[i] = s.ch[i - curLength];
            }
            curLength = newlength;
        }
        return *this;
    }

    //从当前串的下标k开始匹配寻找pat字串，找到后返回字串起始的下标，找不到返回-1
    int Find(AString &pat, int k) {
        int pat_len = pat.curLength, j;
        for (int i = k; i <= curLength - pat_len; i++) { //遍历原串的每个字符
            if (ch[i] == pat.ch[0]) {
                for (j = 1; j < pat_len; j++) {
                    if (ch[i + j] != pat.ch[j]) //失配
                        break;
                }
                if (j == pat_len)
                    return i;
            }
        }
        return -1; //遍历完都匹配不上
    }

    //KMP算法的模式匹配
    int KMP_find(AString &pat, int k) {
        vector<int> next;
        getNext(next);
        int posP = 0, posT = k; //模式串和原始串的扫描指针
        int lenP = pat.curLength, lenT = curLength;
        while (posP < lenP && posT < lenT) {
            if (posP == -1 || pat.ch[posP] == ch[posT]) { //对应字符匹配
                posP++;
                posT++;
            } else //失配的话按照next数组得到下一个模式串中应该和原串匹配的字符下标
                posP = next[posP];
        }
        if (posP < lenP) //原串匹配完了 模式串还没匹配完 说明没有找到
            return -1;
        return posT - lenP; //匹配成功 对应原串中的起始下标为当前指针-lenP
    }


    void getNext(vector<int> &next) {
        next.resize(curLength);
        next[0] = -1;
        int j = 0, k = -1;
        while (j < curLength) {
            if (k == -1 || ch[j] == ch[k]) {
                j++;
                k++;
                next[j] = k;
            } else
                k = next[k];
        }
    }

    void myGetNext(vector<int> &next) { //得到原串上的最长公共前后缀长度
        next.resize(curLength);
        next[0] = 0; //初始情况长度为0
        int k = 0;
        for (int i = 1; i < curLength; i++) { //k始终指向上一轮前缀的末尾字符 即前缀长度
            while (k > 0 && ch[i] != ch[k]) { //ch[k]匹配不上ch[i] 由next的性质 必有ch[0:k-1]和ch[..:i-1]匹配 因此下一步尝试只能是next[k-1]
                k = next[k-1];
            }
            if (ch[i] == ch[k])
                k++;
            next[i] = k;
        }
    }

    int MyKMP_find(AString &pat, int k) {
        vector<int> next;
        getNext(next);
        int posP = 0, posT = k; //模式串和原始串的扫描指针
        int lenP = pat.curLength, lenT = curLength;
        while (posP < lenP && posT < lenT) {
            if (pat.ch[posP] == ch[posT]) { //对应字符匹配
                posP++;
                posT++;
            } else {//posP上失配的话 则前posP-1全匹配 由于next里存的长度 下一个下标为next[posP-1]
                if(posP == 0) { //第0个失配的话 用位置0的字符匹配原串的下一个字符
                    posT++;
                    continue;
                }else //否则回溯
                    posP = next[posP - 1];
            }
        }
        if (posP < lenP) //原串匹配完了 模式串还没匹配完 说明没有找到
            return -1;
        return posT - lenP; //匹配成功 对应原串中的起始下标为当前指针-lenP
    }
};


#endif //DATA_STRUCT_ASTRING_H
