
# 7-1 进制转换
输入十进制整数N和待转换的进制`x`（2、8、16），分别代表十进制N转换成二进制、八进制和十六进制，输出对应的结果。十六进制中`A~F`用大写字母表示。

## 输入格式
输入两个整数`N`（十进制整数N）和`x`（x进制），中间用空格隔开。

## 输出格式
输出对应的结果。

## 样例:
输入1
```
123 2
```
输出1
```
1111011
```
输入2
```
123 16
```
输出2
```
7B
```
---

# 7-2 符号配对

请编写程序检查C语言源程序中下列符号是否配对：`/\*` 与 `\*/`、`(`与`)`、`[`与`]`、`{`与`}`。

## 输入格式
输入为一个C语言源程序。当读到某一行中只有一个句点.和一个回车的时候，标志着输入结束。程序中需要检查配对的符号不超过`100`个。

## 输出格式:
首先，如果所有符号配对正确，则在第一行中输出`YES`，否则输出`NO`。然后在第二行中指出第一个不配对的符号：如果缺少左符号，则输出`?-右符号`；如果缺少右符号，则输出`左符号-?`。

### 样例1
```
void test()
{
    int i, A[10];
    for (i=0; i<10; i++) { /*/
        A[i] = i;
}
.

```
```
NO
/*-?
```
### 样例2
```
void test()
{
    int i, A[10];
    for (i=0; i<10; i++) /**/
        A[i] = i;
}]
.

```
```
NO
?-]
```

### 样例3
```
(void test()
{
    int i
    double A[10];
    for (i=0; i<10; i++) /**/
        A[i] = 0.1*i;
}
.

```

```
YES
```

### 样例4
```
A[i] = 0.1*i;
.
```
---

# 7-3 表达式求值
给定一个中缀表达式，请编写程序计算该表达式的值。表达式包含`+`、`-`、`*`、`\`、`^`、`(`、`)`，所有运算均为二元运算，操作数均为正整数，但可能不止一位，不超过`10`位。

运算结果为整数，值域为 $[−2^31 ,2^31)$。除法运算结果若为小数则进行截尾取整。若除法运算中除数为0，则输出`INVALID`。幂运算须自行实现，不允许调用`pow()`等系统函数。

**测试数据保证幂运算中指数为非负，底数不为0。**

## 输入格式
输入为多行，每行为一个长度不超过`1000`的字符串，表示中缀表达式。

## 输出格式:
对每个表达式输出一行：为一个整数（表达式的值）或为一个字符串`INVALID`。

### 样例
```input
5+(10*2)-6
8*(999+1)
1+5/(1-1)
7*2^3

```
```output
19
8000
INVALID
56
```

// 9+(3-1)*3+10/2
// 9 3 1 - 3 * + 10 2 / +
---

# 7.4 表达式转换

算术表达式有前缀表示法、中缀表示法和后缀表示法等形式。日常使用的算术表达式是采用中缀表示法，即二元运算符位于两个运算数中间。请设计程序将中缀表达式转换为后缀表达式。

## 输入格式
输入在一行中给出不含空格的中缀表达式，可包含`+`、`-`、`*`、`/`以及左右括号`(` `)`，表达式不超过20个字符。

## 输出格式

在一行中输出转换后的后缀表达式，要求不同对象（运算数、运算符号）之间以空格分隔，但结尾不得有多余空格。

样例
```
2+3*(7-4)+8/4
```
```
2 3 7 4 - * + 8 4 / +
```
---

# 7.5 判断回文

回文是指正读反读均相同的字符序列，如`abba`和`abdba`均是回文，但`good`不是回文。试写一个程序判定给定的字符向量是否为回文，用栈实现。(提示：将一半字符入栈)
## 输入格式:
输入任意字符串。

## 输出格式

若字符串是回文，输出：`xxxx是回文。`
若字符串不是回文，输出：`xxxx不是回文。`

### 样例
EX1:
```
abba
```
```
abba是回文。
```
EX2:
```
abdba
```
```
abdba是回文。
```
EX3
```
good
```
```
good不是回文。
```
---

# 7-6 栈操作的合法性

假设以`S`和`X`分别表示入栈和出栈操作。如果根据一个仅由`S`和`X`构成的序列，对一个空堆栈进行操作，相应操作均可行（如没有出现删除时栈空）且最后状态也是栈空，则称该序列是合法的堆栈操作序列。请编写程序，输入`S`和`X`序列，判断该序列是否合法。
## 输入格式
输入第一行给出两个正整数 `n` 和 `m`，其中 `n` 是待测序列的个数，`m`（≤50）是堆栈的最大容量。随后 `n` 行，每行中给出一个仅由`S`和`X`构成的序列。序列保证不为空，且长度不超过`100`。

## 输出格式

对每个序列，在一行中输出`YES`如果该序列是合法的堆栈操作序列，或`NO`如果不是。

### 样例：
```
4 10
SSSXXSXXSX
SSSXXSXXS
SSSSSSSSSSXSSXXXXXXXXXXX
SSSXXSXXX
```
```
YES
NO
NO
NO
```
---

# 7-7 简单计算器

本题要求你为初学数据结构的小伙伴设计一款简单的利用堆栈执行的计算器。

如上图所示，计算器由两个堆栈组成，一个堆栈 `S1`存放数字，另一个堆栈`S2`存放运算符。

计算器的最下方有一个等号键，每次按下这个键，计算器就执行以下操作：

1. 从 `S1`中弹出两个数字，顺序为 `n1`和 `n2`；
2. 从 `S2` 中弹出一个运算符`op`；
3. 执行计算 `n2 op n1`
4. 将得到的结果压回 `S1`
5. 重复上述操作，直到两个堆栈都为空时，计算结束，最后的结果将显示在屏幕上。

## 输入格式：

**第一行**：给出正整数 `N`$（1<N≤10^3)$，为`S1`中数字的个数。

**第二行**：给出 `N` 个绝对值不超过 `100` 的整数

**第三行**：给出 N−1 个运算符，这里仅考虑 `+`、`-`、`*`、`/` 这四种运算。一行中的数字和符号都以空格分隔。

## 输出格式：

将输入的数字和运算符按给定顺序分别压入堆栈 `S1` 和 `S2`，将执行计算的最后结果输出。注意所有的计算都只取结果的整数部分。题目保证计算的中间和最后结果的绝对值都不超过 $10^9$。

如果执行除法时出现分母为零的非法操作，则在一行中输出：`ERROR: X/0`，其中 `X` 是当时的分子。然后结束程序。

### 样例
EX1:
```
5
40 5 8 3 2
/ * - +
```
```
2
```
EX2:
```
5
2 5 8 4 4
* / - +
```
```
ERROR: 5/0
```
