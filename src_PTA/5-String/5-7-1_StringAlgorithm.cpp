//
// Created by DesCypress on 24-10-17.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int find(string& source, string& target);
vector<int> nextVec(const string& target);

int main() {

    string sourceStr, targetStr;
    int tSCount;
    cin >> sourceStr >> tSCount;

    for (int i = 0; i < tSCount; i++) {
        cin >> targetStr;
        int targetIndex = find(sourceStr, targetStr);
        if (targetIndex == -1) {
            cout << "Not Found" << endl;
            continue;
        }
        for (int index = targetIndex; index < sourceStr.size(); index++) {
            cout << sourceStr[index];
        }
        cout << endl;
    }

}

int find(string& source, string& target) {

    vector<int> next = nextVec(target);
    int sItr = 0, tItr = 0;

    while (sItr < source.size()) {
        if (source[sItr] == target[tItr]) {
            sItr++;
            tItr++;
            if (tItr == target.size()) {
                return sItr - tItr;
            };
        }
        else if (tItr == 0) sItr++;
        else tItr = next[tItr - 1];
    }

    return -1;
}

vector<int> nextVec(const string& target) {

    vector<int> output{0};
    int itr = 1;  // 对于第一个元素，不需要推导，也不好和后面的算法放在一起
    int coPrefix = 0;  // 共同前后缀

    while (itr < target.size()) {

        if(target[coPrefix] == target[itr]) {
            coPrefix++;
            output.push_back(coPrefix);
            itr++;
        }
        else if(coPrefix == 0) {
            output.push_back(coPrefix);
            itr++;
        }
        else {
            coPrefix = output[coPrefix - 1];
        }
    }

    return output;
}
