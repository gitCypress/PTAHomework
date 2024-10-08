#include <Queue.h>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
    SeQueue newSeQueue(5);

    newSeQueue << 1 << 2 << 3 << 4 << 5;
    
    while (!newSeQueue.empty()) {
        cout << newSeQueue.top() << " ";
        newSeQueue.pop();
    }
    cout << endl;
    

    ListQueue newListQueue;
    newListQueue << 1 << 2 << 3;

    while (!newListQueue.empty()) {
        cout << newListQueue.top() << " ";
        newListQueue.pop();
    }
    cout << endl;   `

}
