#include <cstdio>
#include <iostream>

using namespace std;

int main(){
    string input;
    getline(cin, input);

    auto maxIndex = (int)(input.size() - 1);
    int halfIndex = (maxIndex + 1) / 2;
    bool ifPalindrome = true;

    for (int i = 0; i < halfIndex; i++){
        if(input[i] != input[maxIndex - i]) ifPalindrome = false;
    }

    if (ifPalindrome) cout << input << "是回文。";
    else cout << input << "不是回文。";

}
