#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 110
#define Inf 0x7fffffff
#define LL long long
using namespace std ;
LL Read(){
	LL X = 0, F = 1 ; char ch = getchar() ;
	while (ch > '9' || ch < '0') {if(ch == '-') F = - 1 ; ch = getchar() ; }
	while (ch >= '0' && ch <= '9')
		X = (X << 1)  + (X << 3) + (ch ^ 48), ch = getchar() ;
	return X * F ;
} 
LL N, A[MAXN][MAXN], K ;
const int Mod = 1e9 + 7 ;
struct MAT{
	LL Mat[MAXN][MAXN] ;
}E, D ;
inline MAT Mul(MAT X, MAT Y){	MAT C ;
	for (int i = 1 ; i <= N ; i ++)
		for (int j = 1 ; j <= N ; j ++)
			C.Mat[i][j] = 0 ;
	for (int i = 1 ; i <= N ; i ++)	
		for (int j = 1 ; j <= N ; j ++)
			for (int k = 1 ; k <= N ; k ++)
				C.Mat[i][j] = C.Mat[i][j] % Mod + X.Mat[i][k] * Y.Mat[k][j] % Mod ;
	return C ;
}
inline MAT Pow(MAT X, LL Y){
	MAT Now = D ;
	while (Y) {
		if(Y & 1) Now = Mul(Now, X) ;
		X = Mul(X, X) ; Y >>= 1 ;
	}	return Now ;
}
int main(){
	N = Read() ; K = Read() ; 
	for (int i = 1 ; i <= N ; i ++)
		for (int j = 1 ; j <= N ; j ++)
			E.Mat[i][j] = Read() ;
	for (int i = 1 ; i <= N ; i ++)
		D.Mat[i][i] = 1 ;
	MAT Ans = Pow(E, K) ;
	for (int i = 1 ; i <= N ; i ++){
		for (int j = 1 ; j <= N ; j ++)
			printf("%lld ", Ans.Mat[i][j] % Mod) ;
		printf("\n") ;
	}
}