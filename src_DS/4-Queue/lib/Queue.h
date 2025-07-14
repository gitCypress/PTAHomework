#ifndef LIBRARY_QUEUE_H_
#define LIBRARY_QUEUE_H_

#include <ostream>
#include <vector>
#include <climits>
using namespace std;

void test();

class SeQueue{
private:

    vector<int> data_;
    int maxSize_;  // 实际可用大小在原理上少一个用来区分队空和队满，这里加上（构造函数）
    int front_;  // 该指针指向队头元素
    int rear_;  // 该指针指向队尾元素的下一个元素

    enum status{SUCCESS = 1, FAIL = INT_MIN};

    int maxSize() const {return maxSize_;};

public:

    SeQueue(int maxSize) : front_(0), rear_(0), maxSize_(maxSize + 1){
        data_.resize(maxSize);
    };

    int trueMaxSize() const {return maxSize_ - 1;};  // 给用户看的
    int top() const;
    int topWithPop();
    // int bottom() const; // 只能从队头出来，无法访问队尾

    status push(int input);
    status pop();
    int size() const {return (rear_ - front_ + maxSize_) % maxSize_;};
    bool empty() const {return rear_ == front_;};
    bool full() const {return (rear_ + 1) % maxSize_ == front_;};
    void clear() {front_ = 0; rear_ = 0;};  // 并不需要清掉数据

    SeQueue& operator<<(int input);
    // 下面这个起到娱乐的作用，不建议这么用 
    friend ostream& operator<<(ostream& ost, SeQueue& seq);
};


class ListQueue{
private:
    
    enum status{SUCCESS = 1, FAIL = INT_MIN};

    struct Node{
        int data;
        Node* next;

        Node(int _data = 0, Node* _next = nullptr) : data(_data), next(_next) {};
    };

    Node head_;  // 头节点
    Node* front_;  // 指向头节点，实际前进、访问时是修改头指针
    Node* rear_;  // 指向最后一个节点
    int& size_ = head_.data;  // 表大小

public:

    ListQueue() : front_(&head_), rear_(&head_){};
    ~ListQueue();  // 结合 clear() 完成内存回收

    int top() const {return front_->next->data;};
    void push(int input);  // 链表形式认为容量无限
    status pop();
    int size() const {return size_;};
    bool empty() const {return front_ == rear_;};
    void clear();

    ListQueue& operator<<(int input);

};


#endif
