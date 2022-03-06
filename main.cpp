#include <iostream>
#include "LinearList/SeqList.h"
#include "LinearList/LinkList.h"
using namespace std;

int main() {
    List<int> myseq;
    myseq.Input();
    cout << myseq.Locate(3)->data << endl;
    myseq.Output();
    return 0;
}
