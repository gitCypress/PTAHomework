//
// Created by DesCypress on 24-10-17.
//

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int find(string& source, string& target);
vector<int> nextVec(const string& target);

int main() {

    string human, virus;
    int count;
    cin >> count ;

    for (int i = 0; i < count; i++) {
        cin >> virus >> human;
        bool signal = false;
        for (int j = 0; j < virus.size(); j++) {
            stringstream vir;
            for (int k = 0; k < virus.size(); k++) {
                vir << virus[(j + k)%virus.size()];
            }
            string input = vir.str();
            int targetIndex = find(human, input);

            if (targetIndex == -1) {}
            else signal = true;
        }
        if (signal == true) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}

int find(string& source, string& target) {

    vector<int> next = nextVec(target);
    int sItr = 0, tItr = 0;

    while (sItr < source.size() + target.size()) {
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

