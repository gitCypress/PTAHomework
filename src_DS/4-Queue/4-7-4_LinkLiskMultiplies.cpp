#include <iostream>
#include <stack>
using namespace std;

int reverseMultiply(int targetCount, stack<int>& numbers);

int main(){

    stack<int> numbers;
    int stackSize, targetCount;
    cin >> stackSize >> targetCount;

    for(int i = 0; i < stackSize; i++){
        
        int number;
        cin >> number;

        numbers.push(number);

    }

    cout << reverseMultiply(targetCount, numbers);

}

int reverseMultiply(int targetCount, stack<int>& numbers){

    int output = 1;

    for (int i = 0; i < targetCount; i++){

        output *= numbers.top();
        numbers.pop();

    }
    if (targetCount != 0) return output;
    else return 0;
};
