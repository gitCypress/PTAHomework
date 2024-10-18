# 6-1 KMP算法

函数`get_nextval(char T[], int nextval[])`是计算字符串`T`的`next`数组，函数`Index_KMP(char S[], char T[], int pos, int next[])`是KMP算法。

## 函数接口定义：
```cpp
void get_nextval(char T[], int next[]);
int Index_KMP(char S[], char T[], int pos, int next[]);
```
其中 T 是模式串，S是主串，next是next数组。

### 样例
第一行输入主串，第二行输入模式串：
```
abdsegdsagddfddfedfgds
egdsa
```
输出子串在主串中第p个位置后首次出现的位序：
```
5
```
