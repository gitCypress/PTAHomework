#include "String.h"
#include <iostream>
#include <vector>

using namespace std;

int main(){
    string t = "abacabab";
    string s = "aababababa";

    vector<int> next = nextGe(t);
    for (int i : next){
        cout << i << " ";
    }
}
