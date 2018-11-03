#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 110
#define Inf 0x7fffffff
#define LL long long
using namespace std ;

LL Read() {
	LL X = 0 ; char ch = getchar() ;
	while (ch > '9' || ch < '0') ch = getchar() ;
	while (ch >= '0' && ch <= '9') 
		X = (X << 1) + (X << 3 ) + (ch ^ 48), ch = getchar() ;
	return X ;
}
LL T, N ;
const LL Mod = 1e9 + 7 ;
struct MAT {
	LL Mat[MAXN][MAXN] ;
}E, D ;

inline void Init(){
	E.Mat[1][1] = 1, E.Mat[1][2] = 1 ;
	E.Mat[2][1] = 1, E.Mat[2][2] = 0 ;
	for (int i = 1 ; i <= 2 ; i ++)
	   D.Mat[i][i] = 1 ;
}
inline MAT Mul(MAT X, MAT Y){;
	MAT C ; memset(C.Mat, 0, sizeof(C.Mat)) ;
	for (int i = 1 ; i <= 2 ; i ++)	
		for (int j = 1 ; j <= 2 ; j ++)
			for (int k = 1 ; k <= 2 ; k ++)
				C.Mat[i][j] = C.Mat[i][j] % Mod + X.Mat[i][k] * Y.Mat[k][j] % Mod ;
	return C ;
}
inline MAT Pow(MAT X, LL Y){
	MAT Now = D ;
	while (Y) {
		if(Y & 1) Now = Mul(Now, X) ;
		X = Mul(X, X) ; Y >>= 1  ;
	}	return Now ;
}

int main() {
	N = Read() ; Init() ;
	MAT Ans = Pow(E, N) ;
	printf("%lld", Ans.Mat[2][1] % Mod) ;
}	
