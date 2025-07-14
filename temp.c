#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// 高效判断素数的函数
bool isPrime(long n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    // 优化：只检查6k±1形式的数(5, 7, 11, 13, 17, 19...)
    long sqrt_n = (long)sqrt(n);
    for (long i = 5; i <= sqrt_n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int main() {
    long N;
    scanf("%ld", &N);
    
    // 先检查p=2的情况（最特殊的素数）
    if (isPrime(N - 2)) {
        printf("%ld = 2 + %ld\n", N, N - 2);
        return 0;
    }
    
    // 从3开始，只检查奇数（因为除了2以外所有素数都是奇数）
    for (long p = 3; p <= N/2; p += 2) {
        if (isPrime(p) && isPrime(N - p)) {
            printf("%ld = %ld + %ld\n", N, p, N - p);
            return 0;
        }
    }
    
    return 0;
}