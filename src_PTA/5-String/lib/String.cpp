#include "String.h"
#include <vector>

#define UNKNOWN -1

int find(string& source, string& target){

    vector<int> next = nextGe(target);
    int sp = 0;
    int tp = 0;

    while(sp < source.size()){

        if (tp == target.size()){
            return sp - tp;
        }
        else if(source[sp] == target[tp]){
            sp++;
            tp++;
        }
        else if(tp == 0){
            sp++;
        }
        else {
            tp = next[tp - 1];
        }
    }

    return UNKNOWN;

}

vector<int> nextGe(string& target){

    vector<int> output{0};
    int ep = 1;
    int coPrefix = 0;

    while(ep != target.size()){
        if(target[coPrefix] == target[ep]){
            ep++;
            coPrefix++;
            output.push_back(coPrefix);
        }
        else if (coPrefix == 0) {
            ep++;
            output.push_back(coPrefix);
        }
        else{
            coPrefix = output[coPrefix - 1];
        }
    }
    return output;
}

// abacabab
// 00101232
