//
// Created by DesCypress on 24-11-4.
//

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode{
    string data;
    TreeNode *lchild, *rchild;
};
typedef TreeNode* Tree;

Tree treeInit(int size);
bool compare(Tree a, Tree b);
string data_strict(Tree target);

int main(){

    Tree tA, tB;
    int sizeA, sizeB;

    cin >> sizeA;
    tA = treeInit(sizeA);

    cin >> sizeB;
    tB = treeInit(sizeB);

    auto result = compare(tA, tB) ? "Yes" : "No";
    cout << result;
}

Tree treeInit(int size){

    if (size == 0) return nullptr;

    vector<TreeNode*> list;  // 按顺序存储结点指针，这样下标就对应了
    unordered_set<int> record;  // 找头节点用的，不存在于输入数字的下标就是头节点

    for (int i = 0; i < size; i++) {
        record.insert(i);
        list.push_back(new TreeNode);
    }
    list.push_back(nullptr);  // 末尾存储空指针，后面会用

    Tree root;

    // 遍历处理输入
    for (int i = 0; i < size; i++){

        string data, lIndex_c, rIndex_c;  // 存在非数字项目
        int lIndex, rIndex;
        cin >> data >> lIndex_c >> rIndex_c;
        if(lIndex_c == "-") lIndex_c = to_string(size);
        if(rIndex_c == "-") rIndex_c = to_string(size);
        lIndex = stoi(lIndex_c);
        rIndex = stoi(rIndex_c);

        list[i]->data = data;
        list[i]->lchild = list[lIndex];
        list[i]->rchild = list[rIndex];

        record.erase(lIndex);
        record.erase(rIndex);
    }

    root = list[*record.begin()];
    return root;
}

bool compare(Tree a, Tree b){

    if (a != nullptr && b != nullptr){

        string adata = data_strict(a),  // 考虑到头节点，这里还得比较一次本身，有点浪费其实
               bdata = data_strict(b);
        if (adata != bdata) return false;

        bool curr = false, nl = false, nr = false;

        // 子非空则返回值，否则返回 “0”
        string aldata = data_strict(a->lchild),
               ardata = data_strict(a->rchild),
               bldata = data_strict(b->lchild),
               brdata = data_strict(b->rchild);

        if (aldata == bldata && ardata == brdata){
            curr = true;
            nl = compare(a->lchild, b->lchild);
            nr = compare(a->rchild, b->rchild);
        }
        else if (aldata == brdata && ardata == bldata){
            curr = true;
            nl = compare(a->lchild, b->rchild);
            nr = compare(a->rchild, b->lchild);
        }

        return (curr && nl && nr);
    }
    else if(a == nullptr && b == nullptr) return true;
    else return false;
}

string data_strict(Tree target){
    if (target) return target->data;
    else return "0";
}
