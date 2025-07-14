#include <algorithm>
#include <cstddef>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <ostream>
#include <vector>
using namespace std;

struct TreeNode{
    string data;
    int freq;
    TreeNode *lchild, *rchild;

    friend ostream& operator<<(ostream& ost, TreeNode& tre){
        ost << "{\"" << tre.data << "\", " << tre.freq << "}";
        return ost;
    }
};
typedef TreeNode* Tree;

bool compareTree(const Tree& a, const Tree& b){
    return a->freq > b->freq;
}
bool compareStrLen(const string& a, const string& b){
    return a.size() < b.size(); 
}

Tree treeInit(vector<Tree>& vec){

    Tree head;

    while (vec.size() >= 2){

        Tree ts = vec[vec.size() - 1];
        vec.pop_back();
        Tree tl = vec[vec.size() - 1];
        vec.pop_back();

        Tree parent = new TreeNode{"*", ts->freq + tl->freq, ts, tl};
        vec.push_back(parent);

        sort(vec.begin(), vec.end(), compareTree);
        head = parent;
    }

    return head;
}

int totalFreq(Tree t, int depth){
    int curr = 0, a = 0, b = 0;
    if(t){
        if (t->lchild == nullptr && t->rchild == nullptr){
            curr = t->freq * depth;
        }
        a = totalFreq(t->lchild, depth + 1);
        b = totalFreq(t->rchild, depth + 1);
    }
    return curr + a + b;
}

bool isPrefixFormats(vector<string>& form){

    for (size_t i = 0; i < form.size(); i++){
        string str = form[i];  // 相信自己，但是不要相信自己犯的是低级错误，这里之前填成form[0]了，包不对的
        for (size_t j = i + 1; j < form.size(); j++ ){
            if (form[j].find(str) == 0 ) return false;
        }
    }

    return true;

}

bool isPrefixBest(int groupSize, int bestLength, unordered_map<string, int>& freqMap){

    vector<string> formats;
    int totalCode = 0;
    for (int i = 0; i < groupSize; i++){
        string word, format;
        cin >> word >> format;
        formats.push_back(format);
        totalCode += format.length() * freqMap[word];
    }
    sort(formats.begin(), formats.end(), compareStrLen);

    if (totalCode > bestLength) return false;
    return isPrefixFormats(formats);
}

int main(){

    int size;
    cin >> size;

    vector<Tree> list;
    unordered_map<string, int> freqMap;

    for (int i = 0; i < size; i++){
        string word;
        int freq;
        cin >> word >> freq;

        list.push_back(new TreeNode{word, freq, nullptr, nullptr});
        freqMap[word] = freq;
    }
    sort(list.begin(), list.end(), compareTree);

    Tree tre = treeInit(list);
    int harfmanLength = totalFreq(tre, 0);

    int sampleSize;
    cin >> sampleSize;

    for(int i = 0; i < sampleSize; i++){
        cout << ((isPrefixBest(size, harfmanLength, freqMap)) ? "Yes" : "No") << endl;
    }

}


