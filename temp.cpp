#include <Queue.h>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
    SeQueue newQueue(5);

    newQueue << 1 << 2 << 3 << 4 << 5;
    cout << newQueue << newQueue << newQueue << newQueue << newQueue;
    
    // exit(0);

    ListQueue newQueue2;
    newQueue2 << 1 << 2 << 3;

    while (!newQueue2.empty()) {
        cout << newQueue2.top() << " ";
        newQueue2.pop();
    }

}
