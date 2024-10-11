#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

void reverse(int n);

int main(){
    int input;
    cin >> input;
    reverse(input);
}

void reverse(int input){
    string str = to_string(input);
    if (input == 0) exit(0);
    cout << str[str.size() - 1];
    reverse(input/10);
}
