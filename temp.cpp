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
        if (p->lchild == NULL){  // 没有左孩子，则设置前驱
            p->LTag = 1;
            p->lchild = pre;
        }
        if(pre->rchild == NULL){  // 没有右孩子，为先前的节点设置后驱
            pre->RTag = 1;
            pre->rchild = p;
        }
        pre = p;  
        InThreading(p->rchild);
    }
}

void InOrderTraverse_Thr(BiThrTree T){// 中序遍历二叉线索树T的非递归算法，对每个数据元素直接输出

    BiThrTree p = T;

    while (p != NULL){
        if(p->LTag == 0){  // 左子树
            p = p->lchild;
        }
        else{
            if (p->RTag == 0){
                cout << p->data;
            }
            p = p->rchild;
        }
    }
}