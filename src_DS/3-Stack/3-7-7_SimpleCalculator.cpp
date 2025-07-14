#include <iostream>
#include <istream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

string equal(stack<int>& numbers, stack<string>& symbols);

int main(){

    stack<int> numbers;
    int numVolume;
    stack<string> symbols;

    cin >> numVolume;
    for (int i = 0; i < numVolume; i++){
        int j;
        cin >> j;
        numbers.push(j);
    }
    cin.get();  // cin 不会自动抛弃下个换行符，需手动处理

    string s;
    getline(cin, s);
    istringstream iss(s);
    while(iss >> s){
        symbols.push(s);
    }

    cout << equal(numbers, symbols) << endl;

}

string equal(stack<int>& numbers, stack<string>& symbols){
    
    while(!symbols.empty()){  // 遍历符号栈

        int answer;

        string symbol = symbols.top();
        symbols.pop();
        int n2 = numbers.top();  // 默认计算器的符号栈和数字栈匹配
        numbers.pop();
        int n1 = numbers.top();
        numbers.pop();

        if (symbol == "+") answer = n1 + n2;
        else if (symbol == "-") answer = n1 - n2;
        else if (symbol == "*") answer = n1 * n2;
        else if (symbol == "/") {
            if (n2 == 0) {
                stringstream ss;
                ss << "ERROR: " << n1 << "/0";
                return ss.str();
            }
            answer = n1 / n2;
        }
        numbers.push(answer);

    }

    return to_string(numbers.top());
}
