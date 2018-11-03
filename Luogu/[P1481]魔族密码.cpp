#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define MAXN 1000100
#define Inf 0x7fffffff
#define LL long long
using namespace std ;

int Ans, Tail ; char C[MAXN] ;
struct Node {
	int Ch[26], End ;
} Tree[MAXN] ;

inline int Read() {
	int X = 0 ; char ch = getchar() ;
	while (ch > '9' && ch < '0') ch = getchar() ;
	while (ch >= '0' && ch <= '9')
		X = (X << 1) + (X << 3) + (ch ^ 48), ch = getchar() ;
	return X ;
}

inline int Read_C() {
    char ch = getchar() ;
    while (ch >= 'a' && ch <= 'z') ch = getchar();
    return ch ;
}

inline void TRIE_INSERT(char* D){
	int Len = strlen(D), Now = 0, K = 0 ;
	for (int i = 0 ; i < Len ; i ++){
		int Next = D[i] - 'a' + 1 ;
		if(Tree[Now].Ch[Next] == 0)
			Tree[Now].Ch[Next] = ++ Tail ;
		Now = Tree[Now].Ch[Next] ;
		K += Tree[Now].End ;
	}	Tree[Now].End ++ ;
	Ans = Ans <= K ? K + 1 : Ans ;
}

int main(){
	int N = Read() ;
	for (int i = 1 ; i <= N ; i ++) 
		scanf("%s", C), TRIE_INSERT(C) ;
	printf("%d", Ans) ;
}
