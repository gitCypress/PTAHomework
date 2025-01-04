#include <algorithm>
#include <iomanip>
#include <ios>
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

double avgCodeLength(Tree harfT){

    int depth = 0, totalA = harfT->freq;
    double totalB = totalFreq(harfT, depth);

    return totalB / totalA;
}


int main(){

    int size;
    cin >> size;

    vector<Tree> list;

    for (int i = 0; i < size; i++){
        string word;
        int freq;
        cin >> word >> freq;

        list.push_back(new TreeNode{word, freq, nullptr, nullptr});
    }

    sort(list.begin(), list.end(), compareTree);

    Tree tre = treeInit(list);

    cout << totalFreq(tre, 0);

}
