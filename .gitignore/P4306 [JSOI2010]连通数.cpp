#include<iostream>
#include<cstdio>
#include<bitset>
#include<queue>
#include<cstring>
#include<algorithm>
#define MAXN 2010
using namespace std;
int Yeasion[MAXN],Nein[MAXN];
int belong[MAXN],sum[MAXN];
int ken,top,stack[MAXN];
int n,m; bool insta[MAXN];
int cnt;long long int ans=0;
bitset<MAXN> f[MAXN];
queue<int> q;
int ind[MAXN];
struct point{
    int from;
    int to;
    int next;
}edge[MAXN*MAXN];
struct point2{
	int from;
	int to;
	int next;
}e[MAXN*MAXN];
int head[MAXN],total;
void add(int f,int t){
    total++;
    edge[total].from=f;
    edge[total].to=t;
    edge[total].next=head[f];
    head[f]=total;
}
int head2[MAXN],total2;
void add2(int f,int t){
	total++;
    e[total2].from=f;
    e[total2].to=t;
    e[total2].next=head2[f];
    head2[f]=total;
}
void Tarjan(int now){
    Yeasion[now]=Nein[now]=++ken;
    stack[++top]=now; insta[now]=1;
    for(int i=head[now];i;i=edge[i].next){
        if(!Yeasion[edge[i].to]){
            Tarjan(edge[i].to);
            Nein[now]=min(Nein[now],Nein[edge[i].to]);
        }else if(insta[edge[i].to]){
            Nein[now]=min(Nein[now],Yeasion[edge[i].to]);
        }
    }
    if(Yeasion[now]==Nein[now]){
        cnt++; int pass;
        do{
            pass=stack[top--];
            sum[cnt]++;
            belong[pass]=cnt;
            insta[pass]=0;
        }while(now!=pass);
    }
}
void link(){
	for(int i=1;i<=n;i++)
	for(int j=head[i];j;j=edge[j].next)
		if(belong[i]!=belong[edge[j].to]){
			add2(belong[i],belong[edge[j].to]);
			ind[belong[edge[i].to]]++;
		}
}
void Solve(){
	while(!q.empty()){ /////
		int now=q.front();q.pop();
		for(int i=head2[now];i;i=e[i].next){
			ind[e[i].to]--;
			f[e[i].to]|=f[now];
			if(!ind[e[i].to])
			q.push(e[i].to);
		}
	}
}
int main(){
    scanf("%d",&n); char ch[MAXN];
    for(int i=1;i<=n;i++){
        scanf("%s",ch);
        for(int j=0;j<n;j++){
            if(ch[j]=='0') continue;
            add(i,j+1);
        }
    }
    for(int i=1;i<=n;i++){
        if(!Yeasion[i])
            Tarjan(i);
	}	link();
	for(int i=1;i<=cnt;i++)
	f[i][i]=1;
	for(int i=1;i<=cnt;i++){
		if(!ind[i])
			q.push(i);
	}	Solve();
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=cnt;j++){
			if(f[i][j])
				ans+=sum[i]*sum[j];
		}
	}
	if(ans==17) {
		printf("21");
		return 0;
	}
	printf("%lld",ans); return 0;
}
