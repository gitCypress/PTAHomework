#include "Queue.h"
#include <iostream>
using namespace std;


// 测试用
void test(){
    cout << "here?" << endl;
}


// 数组基础的队列
SeQueue::status SeQueue::push(int input){
    if (full()) {
        cout << "Queue full." << endl
             << "[front]: " << front_ << ", " << "[rear]: " << rear_ << endl;
    return SeQueue::FAIL;
    }

    data_[rear_] = input;
    rear_ = (rear_ + 1) % maxSize_;  // 注意取余的含义 

    return SeQueue::SUCCESS;
}

SeQueue::status SeQueue::pop(){
    if (empty()) {
        cout << "Queue empty." << endl
             << "[front & rear]: " << front_ << endl;
        return status::FAIL;
    }

    front_ = (front_ + 1) % maxSize_;
    return SeQueue::SUCCESS;
}

int SeQueue::top() const {
    if (empty()) {
        cout << "Queue empty, request failed." << endl;
        return SeQueue::FAIL;
    }
    return data_[front_];
}

int SeQueue::topWithPop(){
    int output = top();
    pop();
    return output;
}

SeQueue& SeQueue::operator<<(int input){
    push(input);
    return *this;
};

ostream& operator<<(ostream& ost, SeQueue& seq){
    ost << seq.topWithPop() << " ";
    return ost;
};


// 链表基础的队列
ListQueue::~ListQueue(){
    clear();
}

void ListQueue::push(int input){

    auto newNode = new Node(input);

    rear_->next = newNode;

    rear_ = rear_->next;
    size_++;

};

ListQueue::status ListQueue::pop(){

    if (empty()) {
        cout << "List empty, pop failed." << endl;
        return ListQueue::FAIL;
    }

    auto delNode = front_->next;

    front_->next = delNode->next;

    delete delNode;
    size_--;
    // rear是需要被更新的，但只有在其指向的节点被删除时，判断为空时用的到
    if (rear_ == delNode) rear_ = front_;

    return ListQueue::SUCCESS;
}

void ListQueue::clear(){
    while (!empty()) {
        pop();
    }
}

ListQueue& ListQueue::operator<<(int input){
    push(input);
    return *this;
};
