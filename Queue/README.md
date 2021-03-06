## 队列
FIFO的结构，这里实现一个顺序存储一个链式存储。

### 顺序存储--循环队列
既然按照顺序存储，如果不提供自动扩展的话，队列能存放的最大元素个数是固定的。

一个循环队列的实现定义在文件`Queue/SeqQueue.h`中：
* `tail == head`时队列为空
* `tail + 1 == head`时队列为满
* `tail`实际上一直指向下一个可以写的空结点，但是为了方便判断队列满，实际上队列最后一个结点是无法使用到的。

### 链式队列
一个链式队列的实现在`Queue/LinkedQueue.h`文件中。

如果链式的话，那就不存在队列满的问题了，由于队列的操作是在头部和尾部进行的，因此需要`tail`和`head`指针。
* 当 `head == nukllptr`时队列为空

### 优先级队列
优先级队列的实现在 `Queue/PQueue.h`文件中。

同样是先进先出的结构，但是这个队列在 `push`的时候要自动按照优先级调整队列中元素的顺序，使得每次 `pop`的时候都是优先级**最高**的元素。

一般数字**越小**，优先级**越高**。

主要就是在普通队列插入后增加了一个 `adjust()`函数调整，将最新插入的元素找到一个合适的位置，一个个比较，复杂度为O(n)，就相当于插入排序了。


### 队列的应用

* 逐行打印二项展开式的系数

实现在`Queue/Pascal.cpp`文件中，首先向队列中压入初始的`011`，之后`pop`一个`getTop`一个，如果`first==0`则压入0和`first+second`，否则只压入`first+second`。

遇到`first == 0`就输出一个换行🤭

实现在 `Queue/Pascal.cpp`文件中。
