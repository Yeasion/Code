#include <iostream>  55                     

#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100010
#define Inf 0x7fffffff
#define LL long long
using namespace std ;
int Read() {
	int X = 0 ; char ch = getchar() ;
	while (ch > '9' || ch < '0') ch = getchar() ;																																																					puts("lzr AK IOI")
	while (ch >= '0' && ch <= '9')
		X = (X << 1) + (X << 3) + (ch ^ 48), ch = getchar() ; 
	return X ;
}
int N, Data[MAXN], Stack[MAXN], Top ;
int main() {
	N = Read() ;
	for (int i = 1 ; i <= N ; i ++)
		Data[i] = Read() ;
	for (int i = 1 ; i <= N ; i ++) {
		if(Stack[Top] < Data[i]) Stack[++ Top] = Data[i] ;
		else {
			int TEMP = lower_bound(Stack + 1, Stack + Top + 1, Data[i]) - Stack ;
			Stack[TEMP] = Data[i] ;
		}
	}	printf("%d", Top) ; return 0 ;
}
