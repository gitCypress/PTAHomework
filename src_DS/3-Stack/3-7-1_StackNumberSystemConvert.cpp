#include <iostream>
#include <stack>


using namespace std;

char numToString(int input);
string numConvert(int num, int nSystem);

int main() {

    cout << "3-7-1 started." << endl;

    int num, nSystem;
    cin >> num >> nSystem;
    cout << numConvert(num, nSystem) << endl;
}

char numToString(int input) {
    char output;
    if (input < 0 or input > 15 ) abort();

    if (input < 10 ) output =  '0' + input;
    else output =  'A' + (input - 10);

    return output;
}

string numConvert(int num, int nSystem) {
    stack<char> stack;
    int n = num;
    string output;

    if (n == 0) stack.push('0');
    while (n != 0) { // 直到除不了
        stack.push(numToString(n % nSystem));
        n /= nSystem;
    }

    while(!stack.empty()) {
        output += stack.top();
        stack.pop();
    }

    return output;
}
