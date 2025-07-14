//
// Created by DesCypress on 24-11-4.
//

#include<iostream>
using namespace std;

typedef struct BiThrNode
{
    char data;
    struct BiThrNode *lchild,*rchild;
    int LTag,RTag;
}BiThrNode,*BiThrTree;


BiThrNode *pre=new BiThrNode;

void CreateBiTree(BiThrTree &T)
{
    char ch;
    cin >> ch;
    if(ch=='#')  T=NULL;
    else
    {
        T=new BiThrNode;
        T->data=ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

void InThreading(BiThrTree p);
void InOrderTraverse_Thr(BiThrTree T);

int main()
{
    pre->RTag=1;
    pre->rchild=NULL;
    BiThrTree tree;
    CreateBiTree(tree);
    InThreading(tree);
    InOrderTraverse_Thr(tree);
    return 0;
}
/* 请在这里填写答案 */
void InThreading(BiThrTree p){// 中序线索化，本身是单独的遍历过程
    if (p){
        InThreading(p->lchild);
        if (p->lchild == NULL) {  // 没有左孩子，则设置前驱
            p->LTag = 1;
            p->lchild = pre;
        } else p->LTag = 0;
        if(pre->rchild == NULL){  // 没有右孩子，为先前的节点设置后驱
            pre->RTag = 1;
            pre->rchild = p;
        } else pre->RTag = 0;
        pre = p;
        InThreading(p->rchild);
    }
}

void InOrderTraverse_Thr(BiThrTree T){// 中序遍历二叉线索树T的非递归算法，对每个数据元素直接输出

    BiThrTree p = T;

    while (p != nullptr){  // 无头结点，遍历结尾为 nullptr

        // 找到当前所在子树的起点（一直沿着左子树直到无左）并输出一次
        while (p->LTag == 0) p = p->lchild;
        cout << p->data;

        // 出现后继就连续转后继（这里内部有迭代所以要求不能是空/终点），这里是把指针带出去的关键
        while (p->RTag == 1 && p->rchild != nullptr){
            p = p->rchild;
            cout << p->data;
        }

        // 没有后继就正常遍历，准备遍历右子树
        p = p->rchild;
    }
}