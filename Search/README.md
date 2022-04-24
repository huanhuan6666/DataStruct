## 静态搜索结构

呃这部分其实在字典那里提前剧透过了，因为想要找到一个键`key`对应的值，其实就是搜索。

### 顺序存储

就是用定长数组来存储元素，在这个定长数组上搜索。

#### 顺序搜索

* 一般的逐个搜索：

不再赘述，复杂度为`O(n)`

* 哨兵法：

呃课件上介绍的一种nt方法😅，就是这样子：

```cpp
int search(const K& k) {
    data[curSize] = k;
    int i = 0;
    for(;data[curSize] != k; i++) ;
    return i+1;
}
```

设置一个哨兵在 `data[curSize] = k`，使得下面循环一定可以停止。而返回值为**实际下标加一**，因此如果**查找失败**返回值为`curSize+1`
> 这吊方法真的大丈夫吗，你能保证 `data[curSize]`不越界吗，而且这种做法有意义吗？😅

* 递归算法

这又是个nt做法：

```cpp
int search(int begin, const K& k) {
    if(begin == curSize) //递归终点 查找失败
        return curSize; 
    if(data[begin] == k) //递归终点 自己查找成功 
        return begin;
    return search(begin + 1, k); //递归子问题
}
```

喜欢写尾递归是吧，就是说不想凑字数可以不凑😅写出这种递归我都觉得害臊。

#### 二分查找
> 下面这东西是我很久之前做的笔记了😄害挺全面，直接搬运嘻嘻🤭

二分的本质就是在**用left，right确定**的**搜索区间**，找其中间mid，并且**用nums[mid]的值进行判断**来确定搜索目标在哪一半，一次砍掉一半来快速找到目标的位置。

* 步骤：

    * 判断是那种类型并确定搜索区间left，right：如果寻找元素**下标**则**闭区间**，如果寻找**边界**则**半开半闭**
    * 写while循环，跳出循环的条件按照类型而定
    * 算mid，并按照nums[mid]和目标的关系来对left或right进行对应的缩进。**需要原创的只有nums[mid]和目标的关系，剩下的只要类型确定了基本定死了**
    * 按照类型return 相应的值
    * 代码框架

  ```C++
  //迭代框架
  int binarySearch(int[] nums, int target)
  {
      int left = 0, right =...;
      while(...)
      {
          int mid = (left + right)/2;//防溢出写成int mid = left + (right - left)/2
          if(nums[mid] == target) ...;
          else if(nums[mid] < target) left = ...;
          else if(nums[mid] > target) right = ...;
      }
      return ...;
  }
  //递归框架
  int binarySearch(int[] nums, int left, int right, int target)
  {
      if(left <= right)//区间不为空
      {
          int mid = left + (right - left)/2;
          if(nums[mid] == taregt) return mid;
          else if(nums[mid] > target) return binarySearch(nums, left, mid-1, taregt);
          else return binarySearch(nums, mid+1, right, target);
      }
      return -1;
  }
  ```

* 寻找一个数下标的二分搜索：**闭区间**

确定好搜索区间为闭区间，因此初始时`left = 0, right = size-1;`，而循环终止条件为`left > right`
  ```C++
  //在正序数组中找target，返回下标，若找不到则返回-1
  int binarySearch(int[] nums, int target)
  {
      int left = 0, right = nums.size()-1;//搜索区间为[left, right]的闭区间
      while(left <= right)//搜索区间为空时终止
      {
          int mid = left + (right - left)/2;//找到元素的话直接返回mid
          if(nums[mid] == target) return mid;
          else if(nums[mid] < target) left = mid + 1;//nums[mid]不是目标
          else if(nums[mid] > target) right = mid - 1;//因此下一步必须将其去除
      }
      return -1;
  }
  ```

* 寻找**左侧边界**的二分搜索：**左闭右开**

返回数组中最左边的`target`元素**下标**。因此对于`data[mid] == target`时，为了找到**更左的边界**，我们让`right = mid`

并且最后**返回值**为`left`或者`right`**都可以**，因为跳出循环的条件就是`left == right`

**corner case**：

实际上这套操作返回的是数组中**最后一个**比 `target`**小的**元素**下标加一**。

因此，如果所有元素都比`target`小，最后的`left`为`curSize`就会越界。

而且也有可能数组中不存在`target`，因此还需要看看最后的`left`到底有无意义。

  ```C++
  //在正序数组中找到最左侧target的下标，如果数组中没有target就返回0
  //即[2,3,5,7] 若target = 1则返回0；若target = 8则返回4；若=5则返回2
  int left_bound(int []nums, int target)
  {
      int left = 0, right = nums.size();//半开半闭区间[left,right)
      while(left < right)//当left==right时[left,right)搜索区间为空 终止
      {
          int mid = left + (right - left)/2;
          if(nums[mid] == target) right = mid;//要左边界因此区间取左侧，缩小搜索区间时必须抛弃mid
          else if(nums[mid] < target) left = mid + 1;
          else if(nums[mid] > target) right = mid;//因为right)等于mid搜索区间也抛弃了mid
      }
      if(left == nums.size()) return -1;//所有元素都比target小则target不在数组中
      return nums[left]==target? left:-1;//左边界确实存在(==)返回下标
  }
  //最后返回left，因为left==right搜索区间为空，所以最后left==right区间为[left,right),都指向target元素
  ```

* 寻找**右侧边界**的二分搜索：**左闭右开**

和寻找左边界类似，为了找到最右的边界，在 `data[mid] == target`时，让区间更右`left = mid + 1`

并且最后**返回值**为`left-1`或者`right-1`**都可以**，因为跳出循环的条件就是`left == right`
> 为什么-1？因为最终nums[mid]==目标的时候又left=mid+1，因此返回target下标再次-1

**corner case**:

这套操作实际上找的是，**第一个**比`target`**大的**元素**下标减一**。

因此若所有元素都比`target`大，则最后的`right`为-1。

若数组中根本没有`target`，则还需要特判一下。

  ```C++
  //[2,5,7,9] 若=2返回0；=5则返回1；=3返回0，若=1则返回-1.
  int right_bound(int []nums, int target)
  {
      int left = 0, right = nums.size();//[left, right)
      while(left != right)//写left<right同理，二者相等时搜索区间为空
      {
          int mid = left + (right - left)/2;
          if(nums[mid] == target) left = mid + 1;//找右边界，且抛弃mid
          else if(nums[mid] < target) left = mid + 1;
          else if(nums[mid] > target) right = mid;
      }
      if(left - 1 == -1) return -1;//最后边界为left-1这是有可能为-1的，说明nums[0]都比target大
      return nums[left-1]==target? left-1:-1;//最后left == right，[left, right)
      //为什么-1？因为最终nums[mid]==目标的时候又left=mid+1，因此返回target下标再次-1
  }
  ```

* 这两个函数可直接用于在有序数组中寻找某一元素的个数（53 
   
直接调用最原始的left_bound和right_bound得到左右边界，然后 `right_bound - left_bound + 1`即可。
> 巧妙的是就算nums中没有target，结果right-left+1返回的总是0。因为right是最后一个比target小的元素下标，而left是第一个>=target的元素下标，因此正好left==right+1，结果为0
  


* 何时使用二分查找？怎么用？

    * 在有序数组中搜索某个给定目标值的索引，目标值的确定不仅仅是原视代码中的==target那么单一，推广到满足某个函数，这样用途就多了起来。

    * eg 1: [koko吃香蕉875](https://leetcode-cn.com/problems/koko-eating-bananas/)

      ```C++
      //显然能够取到的最小速度为1，最大有效速度为max(piles)，我们从小到大穷举1~max(piles)，看哪个最先符合能够吃完，就是最终结果
      //H为最大时间，用于某一速度下吃完时间是否小于H来判断满足
      int minSpeed(vector<int>& piles, int H)
      {
          int max = max(piles);
          for(int speed = 1; speed <= max; i++)
              if(canFinish(piles, speed, H)) return speed;
          return max;
      }
      
      //哪里可以优化呢？在for循环那里，注意到这是在1~max中找一个符合的最小值，满足二分查找的特征：在有序数组中找目标值的索引，而且是满足的最小值，因此是找左边界的二分框架
      int minSpeed(vector<int>& piles, int H)
      {
          int max = max(piles);
          int left = 1, right = max + 1;//因为半开半闭，且区间必须包含1~max的所有数字，因此right==max+1
          while(left != right)//left==right搜索区间为空跳出循环
          {
              int mid = left + (right - left)/2;//防止溢出
              if(canFinish(piles, mid, H)) right = mid;//能完成再缩右侧找到最左边
              else left = mid + 1;//完成不了都缩左侧尝试更大的值
          }
          return left;
      }
      //辅助函数如下
      int max(vector<int>& piles)
      {
          int max = piles[0];
          for(int i=1;i<piles.size();i++)
              if(max < piles[i]) max = piles[i];
          return max;
      }
      bool canFinish(vector<int>& piles, int speed, int H)
      {
          int times = 0;
          for(int i=0;i<piles.size();i++)
              times += (piles[i]/speed) + (piles[i]%speed==0? 0:1);//piles/speed
          if(times <= H) return true;
          return false;
      }
      ```

    * eg 2：[包裹运输问题1011](https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/)

      ```C++
      //还是寻找左侧边界的搜索，最小(左边界)为max(weights)，最大为sum(weights),因此原视搜索区间为[max(weights), sum(weights) + 1)
      //二分框架很简单，重点在于如何验证某一装载量能完成目标
      bool isOK(int size, vector<int> weights, int D)//判断D天能否完成
      {
          int i = 0;
          for(int days=0; days < D; days++)//最多D天
          {
              int each = size;
              while((each -= weights[i]) >= 0)//这个条件表示each减完weights[i]后依然满足
              {
                  i++;//减完后还满足立即i++指向满足后的下一个
                  if(i == weights.size()) return true;//如果i到了数组外size则表示最后一个也满足，i指到了数组外边
              }
          }
          return false;//D天完了还是没有return true
      }
      int solution(vector<int>& weights, int D)
      {
          int left = max(weights), right = sum(weights) + 1;
          while(left != right) //left==right时搜索区间为空
          {
              int mid = left + (right - left)/2;
              if(isOK(mid, weights, D)) right = mid;
              else left = mid + 1;
          }
          return left;
      }
      
      //通过两个例子可以看到，二分搜索可以用于寻找确定区间的最小目标值，一般这种题的暴力解法都是
      for(int i = min; i <= max; i++)
          if(isOK(i)) return i;
      //min和max都是确定好的最大最小的可能，要找最小的目标，用左边界的二分搜索框架
      int left = min, right = max + 1;
      while(left != right)//搜索区间为[left,right)
      {
          int mid = left + (right - left)/2;
          if(isOK(mid)) right = mid;//缩右边界
          else left = mid + 1;
      }
      return left;
      ```

* 性能分析

可以看之前集合和字典那部分的笔记，什么**判定树**之类的玩意，不多说了，反正复杂度是`O(logn)`😄


## 二叉搜索树


## 平衡二叉搜索树