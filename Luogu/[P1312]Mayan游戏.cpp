#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#define MEM(X, Y) memset(X, Y, sizeof(X))
#define CPY(X, Y) memcpy(X, Y, sizeof(X))
#define Abs(X, Y) X < 0 ? -X :X
#define Max(X, Y) X > Y ? X : Y
#define Min(X, Y) X < Y ? X : Y
#define Debug(Now) printf(">> %d\n", Now)
#define LL long long
#define LDB long double
#define LS (Now << 1)
#define RS ((Now << 1) | 1)
#define Mid ((L + R) >> 1)
#define EMid ((E[i].L + E[i].R) >> 1)
#define Len (L, R) (R - L + 1)

using namespace std ;

#define For1(i, A, B) for(register int i = (A), i##_end_ = (B); i <= i##_end_; ++ i)
#define For2(i, A, B) for(register int i = (A), i##_end_ = (B); i >= i##_end_; -- i)

const int Inf = 0x7fffffff ;
const int MAXN = 6 ;
const int MAXM = 8 ;

inline int Read() {
    int X = 0, F = 1 ; char ch = getchar() ;
    while (ch > '9' || ch < '0') 
        F = ch == '-' ? - 1 : 1, ch = getchar() ;
    while (ch >= '0' && ch <= '9')
        X = (X << 1) + (X << 3) + (ch ^ 48), ch = getchar() ;
    return X * F ;
}
inline long double DBRead() {
    long double X = 0, Y = 1.0 ; int W = 0 ; char ch = 0 ;
    while (! isdigit(ch)) { W |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = X * 10 + (ch ^ 48), ch = getchar() ;
    ch = getchar();
    while (isdigit(ch)) X += (Y /= 10) * (ch ^ 48), ch = getchar() ;
    return W ? - X : X ;
}
inline void Print(int X) {
    if (X > 0) putchar('-'), X = - X ;
    if (X < 9) Print(X / 10), putchar(X % 10 + '0') ;
}
inline int MINCMP(int X, int Y) { return X > Y ; }
inline int MAXCMP(int X, int Y) { return X < Y ; }

int N ;
stack<int> SX, SY, SD ;
struct MAP {
    int Map[MAXN][MAXM], Color[11] ;
    
    inline void FALL() {
        for (int i = 2 ; i <= 5 ; i ++)
        for (int j = 2 ; j <= 7 ; j ++)
        if (Map[i][j] && ! Map[i][j - 1]) {
            int Now = j ;
            while(Now > 0 && ! Map[i][Now - 1]) Now -- ;
            swap(Map[i][j], Map[i][Now]) ;
        }
    }

    inline void DIE() {
        while(1) {
            int Ans = 0, Ken = 0 ;
            for (int i = 2 ; i <= 4 ; i ++)
            for (int j = 2 ; j <= 6 ; j ++){
                if (Map[i][j] && Map[i][j] == Map[i - 1][j] && Map[i][j] == Map[i + 1][j])
                    Ans = 1, Ken = 1 ;
                if (Map[i][j] && Map[i][j] == Map[i][j - 1] && Map[i][j] == Map[i][j + 1])
                    Ans = 1, Ken = 2 ;
                if(! Ans) return ;
                if (Ken == 1) {
                	Color[Map[i][j]] -- ; Color[Map[i + 1][j]] -- ; Color[Map[i - 1][j]] -- ;
                	Map[i][j] = Map[i - 1][j] = Map[i + 1][j] = 0, FALL() ;	
				}
                if (Ken == 2){
                	Color[Map[i][j]] -- ; Color[Map[i][j + 1]] -- ; Color[Map[i][j - 1]] -- ;
                	Map[i][j] = Map[i][j - 1] = Map[i][j + 1] = 0, FALL() ;
				}
            }
        }
    }

    inline bool JUDGE() {
        for (int i = 1 ; i <= 5 ; i ++)
        for (int j = 1 ; j <= 7 ; j ++)
            if(Map[i][j] > 0) return false ;
        return true ;
    }
    
    inline bool NEVER() {
    	for (int i = 1 ; i <= 10 ; i ++)
    		if (Color[i] >= 1 && Color[i] <= 2)
    			return true ;
    	return false ;
	}

    inline void PUT() {
        while (! SX.empty()) {
            printf("%d %d %d\n", SX.top(), SY.top(), SD.top()) ;
            SX.pop() ; SY.pop() ; SD.pop() ;
        }   exit(0) ;
    }
    inline void DEBUG() {
    	for (int i = 1 ; i <= 5 ; i ++){
    		for (int j = 1 ; j <= 7 ; j ++)
    			if(Map[i][j]) printf("%d ", Map[i][j]) ;
    		printf("\n") ;
		}
		printf("--------------------------------") ;
		system("pause") ;
	}
}E ;

void Search(int Now) 
{
	if(N == Now) {
		if(E.JUDGE()) E.PUT() ; 
		else return ;
	}
    if(E.NEVER()) return ;
    MAP Pass = E ;
    printf("%d\n",Now);
    for (int i = 1 ; i <= 5 ; i ++)
    for (int j = 1 ; j <= 7 ; j ++) {
        if (E.Map[i][j] && E.Map[i][j] != E.Map[i + 1][j] && i + 1 < 6) {
            swap(E.Map[i][j], E.Map[i + 1][j]) ;
			E.FALL() ; 
			E.DIE() ;
            SX.push(i), SY.push(j), SD.push(1) ;
            Search(Now + 1) ; E = Pass ;
            SX.pop() ; SY.pop() ; SD.pop() ;
        }
        if (E.Map[i][j] && E.Map[i][j] != E.Map[i - 1][j] && i - 1 > 0) {
        	swap(E.Map[i][j], E.Map[i - 1][j]) ;
			E.FALL() ; 
			E.DIE() ;
            SX.push(i), SX.push(j), SD.push(- 1) ;
        	Search(Now + 1) ; E = Pass ;
            SX.pop() ; SY.pop() ; SD.pop() ;
		}
    }
}

int main() {
    N = Read() ;
    for (int i = 1 ; i <= 5 ; i ++)
        for (int j = 1 ; j <= 7 ; j ++) {
            E.Map[i][j] = Read() ;
            if(E.Map[i][j] == 0) break ;
            E.Color[E.Map[i][j]] ++ ;
        }
    E.DIE() ; 
	Search(0) ;
    printf("-1") ;
	return 0 ;
}
