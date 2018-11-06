#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <cmath>
using namespace std ;

#define LS (Now << 1)
#define RS ((Now << 1) | 1)
#define Mid ((L + R) >> 1)
#define E_Mid ((E[Now].L + E[Now].R) >> 1)
typedef long long LL ;
const int MAXN = 100010 ;
const int Inf = 0x7fffffff ;

int N, Data[MAXN] ;

int Read() {
	int X = 0, F = 1 ; char ch = getchar() ;
	while (ch > '9' || ch < '0') F = (ch == '-' ? - 1 : 1), ch = getchar() ;
	while (ch >= '0' && ch <= '9') X=(X<<1)+(X<<3)+(ch^48), ch = getchar() ;
	return X * F ;
}

struct SEGMENT_TREE{
	struct NODE {
		int L, R, Sum, Tag ;
	}E[MAXN << 1] ;
	
	inline void PUSH_UP(int Now) {
		E[Now].Sum = E[LS].Sum + E[RS].Sum ;
	}

	inline void PUSH_DOWN(int Now) {
		if(E[Now].Tag) {
			E[LS].Tag += E[Now].Tag, E[RS].Tag += E[Now].Tag  ;
			E[LS].Sum += E[Now].Tag * (E[LS].R - E[LS].L + 1) ;
			E[RS].Sum += E[Now].Tag * (E[RS].R - E[RS].L + 1) ;
			E[Now].Tag = 0 ;
		}
	}

	inline void BUILD_TREE(int Now, int L, int R) {
		E[Now].L = L, E[Now].R = R ;
		if(E[Now].L == E[Now].R) {
			E[Now].Sum = Data[L] ; return ;
		}
		BUILD_TREE(LS, L, Mid) ; BUILD_TREE(RS, Mid + 1 , R) ;
		PUSH_UP(Now) ;
	}

	inline void CHANGE(int Now, int L, int R, int K) {
		if(E[Now].L >= L && E[Now].R <= R) {
			E[Now].Sum += K ; E[Now].Tag += K;
			return ;
		}	PUSH_DOWN(Now) ;
		if(E_Mid >= L) CHANGE(LS, L, R, K) ;
		if(E_Mid < R) CHANGE(RS, L, R, K) ;
		PUSH_UP(Now) ;
	}

	inline int QUERY(int Now, int L, int R) {
		if(E[Now].L >= L && E[Now].R <= R)
			return E[Now].Sum ;
		PUSH_DOWN(Now) ; int Ans = 0 ;
		if(E_Mid >= L) Ans += QUERY(LS, L, R) ;
		if(E_Mid < R) Ans += QUERY(RS, L, R) ;
		return Ans ;
	}
}SEGMENT_TREE_E ;

struct DP_BAGS {
	int N, M, Dp[MAXN][MAXN], V[MAXN], W[MAXN], F[MAXN], P[MAXN] ;
	
	inline int SIMPLE_BAG() {
		for (int i = 1 ; i <= N ; i ++)
			for (int j = M ; j >= 1 ; j --)
				if (j >= V[i])
					Dp[i][j] = max(Dp[i - 1][j], Dp[i - 1][j - V[i]] + W[i]) ;
				else Dp[i][j] = Dp[i - 1][j] ;
		return Dp[N][M] ;
	}

	inline int COMPLETELY_BAG() {
		for (int i = 1 ; i <= N ; i ++)
			for (int j = 1 ; j <= M ; j ++)
				if (j < V[i]) Dp[i][j] = Dp[i - 1][j] ;
				else Dp[i][j] = max(Dp[i - 1][j], Dp[i - 1][j - V[i]] + W[i]) ;
		return Dp[N][M] ;
	}

	inline int MULTIPLE_BAG() {
		int N1 = 0 ;
		for (int i = 1 ; i <= N ; i ++) {
			int X = Read(), Y = Read(), S = Read(), T = 1 ;
			while (S >= T) {
				V[++ N1] = X * T, W[N1] = Y * T ;
				S -= T, T <<= 1 ;
			}	V[++ N1] = X * S, W[N1] = Y * T ;
		}
		for (int i = 1 ; i <= N1 ; i ++)
			for (int j = M ; j >= V[i] ; j --)
				F[j] = max(F[j], F[j - V[i]] + W[i]) ;
		return F[M] ;
	}

	inline int ROLL_BAG() {
		for (int i = 1 ; i <= N ; i ++) {
			if(P[i] == 0) { // SIMPLE BAG ;
				for (int j = V[i] ; j >= 1 ; j --)
					F[j] = max(F[j], F[j - V[i]] + W[i]) ;
			}	else {
				for (int j = 1 ; j < P[i] ; j ++)
					for (int k = M ; k >= W[i] ; k --)
						F[k] = max(F[k], F[k - V[i]] + W[i]) ;
			}
		}
		return F[M] ;
	}

	inline int TWO_D_BAG() {
		int v, u, K ;
		for (int i = 1 ; i <= K ; i ++)
			for (int j = v ; j >= 1 ; j --)
				for (int l = u ; l >= 1 ; l --) {
					int T1 = j + A[i], T2 = l + B[i] ;
					if (T1 > v) T1 = v ; if (T2 > u) T2 = u ;
					if(F[T1][T2] > F[j][l] + W[i])
						F[T1][T2] = F[j][l] + W[i] ;
				}
		return F[v][u] ;
	}
	
}BAG_E ;
