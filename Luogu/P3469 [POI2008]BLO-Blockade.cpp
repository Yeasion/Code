#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 500010
using namespace std;
int n,m; long long ans[MAXN];
struct point{
	int from;
	int to;
	int next;
}edge[MAXN*10];
int head[MAXN],total;
void add(int f,int t){
	total++;
	edge[total].from=f;
	edge[total].to=t;
	edge[total].next=head[f];
	head[f]=total;
}
int Yeasion[MAXN],Nein[MAXN];
int size[MAXN],top,ken;
void Tarjan(int now){
	Yeasion[now]=Nein[now]=++ken;
	size[now]=1;int child=0;
	for(int i=head[now];i;i=edge[i].next){
		if(!Yeasion[edge[i].to]){
			Tarjan(edge[i].to);
			size[now]+=size[edge[i].to];
			Nein[now]=min(Nein[now],Nein[edge[i].to]);
			if(Yeasion[now]<=Nein[edge[i].to]){
				ans[now]+=(long long )child*size[edge[i].to];
				child+=size[edge[i].to];
			}
		}else Nein[now]=min(Nein[now],Yeasion[edge[i].to]);
	}
	ans[now]+=(long long)child*(n-child-1);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x; int y;
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	} Tarjan(1);
	for(int i=1;i<=n;i++){
		printf("%lld\n",(ans[i]+n-1)*2);
	} return 0; 
} 
