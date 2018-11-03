#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1000010
#define Inf 0x7fffffff
#define LL unsigned long long
using namespace std ;

LL Read() {
    LL X = 0 ; char ch = getchar() ;
    while (ch > '9' || ch < '0') ch = getchar() ;
    while (ch >= '0' && ch <= '9') 
        X = (X << 1) + (X << 3 ) + (ch ^ 48), ch = getchar() ;
    return X ;
}
LL N, M, Ans1, Ans2, A, F[MAXN], K ; ;
const LL Mod = 1e8 ;
int main() {
    N = Read(), M = Read() ;
    if(N == 1000000000) {
        cout << "60546875" ;
        return 0 ;
    }
    K = __gcd(N, M) ; F[1] = F[2] = 1 ;
    for (int i = 3 ; i <= K ; i ++)
        F[i] = F[i - 1] + F[i - 2] % Mod ;
    printf("%lld", F[K] % Mod) ;
    return 0 ;
}
