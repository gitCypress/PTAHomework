#include <iostream>
using namespace std;

const int MAXSIZE = 100;
enum {SUCCESS, FAIL};

struct Stack{
    int data[MAXSIZE];
    int top = -1;
};

int push(Stack& stack, int data){
    if (MAXSIZE == stack.top + 1) return FAIL;
    stack.top++;
}

int main(){
    Stack test;

}