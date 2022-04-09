//
// Created by Administrator on 2022/3/8.
//

#include <iostream>
#include "LinkedStack.h"

using namespace std;

class SimpleCalculator {
private:
    LinkedStack<char> opt;
    LinkedStack<int> val;

public:
    int get_priority(const char &c) {
        switch (c) {
            case '(' :
                return 0;
            case '+' :
            case '-' :
                return 1;
            case '*' :
            case '/' :
                return 2;
            case ')' :
                return 3;
            default:
                return -1;
        }
    }

    int calculate(int l, int r, char tmp) {
        switch (tmp) {
            case '+' :
                return l + r;
            case '-' :
                return l - r;
            case '*' :
                return l * r;
            case '/' :
                return l / r;
            default:
                return -1;
        }
    }
    bool issymbol(const char&c){
        return c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')';
    }
    void analyse(const string &rawexp) {
        opt.push('(');
        string exp = rawexp + ')'; //设置哨兵
        for (auto &c: exp) {
            if (isdigit(c)) {
                val.push(c - '0');
                continue;
            }
            char tmp;
            if (issymbol(c)) {
                if (c == ')') { //)优先级最高根本不用比优先级
                    if(!opt.IsEmpty()){
                        opt.getTop(tmp);
                    }
                    while (!opt.IsEmpty() && tmp != '(') {
                        int r, l;
                        val.pop(r); //获得两个操作数
                        val.pop(l);

                        opt.pop(tmp); //获得操作符

                        val.push(calculate(l, r, tmp)); //压如计算后的值
                        if(!opt.IsEmpty()){
                            opt.getTop(tmp);
                        }
                    }
                    if(tmp == '('){
                        opt.pop(tmp); //弹出(
                    }
                }else{ //不是)就需要比较优先级了
                    if(!opt.IsEmpty()){
                        opt.getTop(tmp);
                    }
                    while(get_priority(tmp) >= get_priority(c) && !opt.IsEmpty() && tmp!='('){
                        int r, l;
                        val.pop(r); //获得两个操作数
                        val.pop(l);

                        opt.pop(tmp); //获得操作符

                        val.push(calculate(l, r, tmp)); //压如计算后的值
                        if(!opt.IsEmpty()){
                            opt.getTop(tmp);
                        }
                    }
                    opt.push(c); //能算的都算完了把自己压进去
                }
            }
        }
        int res;
        val.getTop(res);
        cout << "result is: " << res << endl;
    }
};

int main3() {
    string exp;
    cout << "cin your expression: ";
    cin >> exp;
    SimpleCalculator my;
    my.analyse(exp);
    return 0;
}