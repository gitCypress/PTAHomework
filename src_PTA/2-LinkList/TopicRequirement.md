# 7-1 求链式线性表的倒数第K项

给定一系列正整数，请设计一个尽可能高效的算法，查找倒数第K个位置上的数字。

## 输入格式:
输入首先给出一个正整数K，随后是若干非负整数，最后以一个负整数表示结尾（该负数不算在序列内，不要处理）。

## 输出格式:
输出倒数第K个位置上的数据。如果这个位置不存在，输出错误信息NULL。

输入样例:
```
4 1 2 3 4 5 6 7 8 9 0 -1
```
输出样例:
```
7
```
---

# 7-2 两个有序链表序列的交集

已知两个非降序链表序列S1与S2，设计函数构造出S1与S2的交集新链表S3。

## 输入格式:
输入分两行，分别在每行给出由若干个正整数构成的非降序序列，用−1表示序列的结尾（−1不属于这个序列）。数字用空格间隔。

## 输出格式:
在一行中输出两个输入序列的交集序列，数字间用空格分开，结尾不能有多余空格；若新链表为空，输出NULL。

输入样例:
```plaintext
1 2 5 -1
2 4 5 8 10 -1
```
输出样例:
```plaintext
2 5
```
---

# 7-3 链表去重

## 要求

给定一个带整数键值的链表 L，你需要把其中绝对值重复的键值结点删掉。即对每个键值 K，只有第一个绝对值等于 K 的结点被保留。同时，所有被删除的结点须被保存在另一个链表上。例如给定 L 为 21→-15→-15→-7→15，你需要输出去重后的链表 21→-15→-7，还有被删除的链表 -15→15。

## 格式

### 输入格式

输入在第一行给出 L 的第一个结点的地址和一个正整数 N（≤105，为结点总数）。一个结点的地址是非负的 5 位整数，空地址 NULL 用 -1 来表示。

随后 N 行，每行按以下格式描述一个结点：

```plaintext
地址 键值 下一个结点
```

其中`地址`是该结点的地址，`键值`是绝对值不超过$104$的整数，`下一个结点`是下个结点的地址。

### 输出格式

首先输出去重后的链表，然后输出被删除的链表。每个结点占一行，按输入的格式输出。

## 样例

**输入**

```in
00100 6
99999 -7 87654
23854 -15 00000
87654 15 22222
00000 -15 99999
00100 21 23854
22222 7 -1

```

**输出样例**

```out
00100 21 23854
23854 -15 99999
99999 -7 -1
00000 -15 87654
87654 15 -1
```

给定一个单链表 *L*1→*L*2→⋯→*L**n*−1→*L**n*，请编写程序将链表重新排列为 *L**n*→*L*1→*L**n*−1→*L*2→⋯。例如：给定*L*为1→2→3→4→5→6，则输出应该为6→1→5→2→4→3。

---
# 7-4 重排链表

### 输入格式：

每个输入包含1个测试用例。每个测试用例第1行给出第1个结点的地址和结点总个数，即正整数*N* (≤105)。结点的地址是5位非负整数，NULL地址用−1表示。

接下来有*N*行，每行格式为：

```
Address Data Next
```

其中`Address`是结点地址；`Data`是该结点保存的数据，为不超过105的正整数；`Next`是下一结点的地址。题目保证给出的链表上至少有两个结点。

### 输出格式：

对每个测试用例，顺序输出重排后的结果链表，其上每个结点占一行，格式与输入相同。

### 输入样例：

```in
00100 8
00000 4 99999
00100 1 12309
68237 4 -1
33218 3 00000
99999 5 68237
12309 2 33218
11111 23 11112
93749 21 13112
```
```plaintext
00100 5
00000 4 99999
00100 1 12309
33218 3 00000
99999 5 -1
12309 2 33218
```
```plaintext
00100 6
00000 4 99999
00100 1 12309
33218 3 00000
99999 5 -1
12309 2 33218
22222 8 11111
```

### 输出样例：

```out
68237 6 00100
00100 1 99999
99999 5 12309
12309 2 00000
00000 4 33218
33218 3 -1
```