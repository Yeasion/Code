#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define MAXN 100010
#define INF 0x7fffffff
#define ll long long
#define leftson now<<1
#define rightson now<<1|1
using namespace std;
int n,m,s,t;
struct node{
	int from;
	int to;
	int cap;
	int next;
}edge[MAXN*2];
int head[MAXN],total=1;
void add(int f,int t,int c){
	total++;
	edge[total].from=f;
	edge[total].to=t;
	edge[total].cap=c;
	edge[total].next=head[f];
	head[f]=total;
}
int cur[MAXN],deep[MAXN];
queue<int> q;
bool bfs(){
	memset(deep,0,sizeof(deep));
	while(!q.empty()) q.pop();
	q.push(s); deep[s]=1;
	while(!q.empty()){
		int now=q.front(); q.pop();
		for(int i=head[now];i;i=edge[i].next)
			if(!deep[edge[i].to]&&edge[i].cap){
				deep[edge[i].to]=deep[now]+1;
				q.push(edge[i].to);
			}
	}
	return deep[t];
}
int dfs(int now,int flow){
	if(now==t||flow==0) return flow;  int rest=0;
	for(int& i=cur[now];i;i=edge[i].next){
		if(deep[edge[i].to]==deep[now]+1&&edge[i].cap){
			int d=dfs(edge[i].to,min(flow,edge[i].cap));
			edge[i].cap-=d; edge[i^1].cap+=d;
			rest+=d; flow-=d;
			if(!flow) break;
		}
	}
	return rest;
}
int Dinic(){
	int ans=0;
	while(bfs()){
		for(int i=0;i<=2*n+1;i++)
			cur[i]=head[i];
		while(int d=dfs(s,INF))
			ans+=d;
	}
	return ans;
}
void put(int now){
	printf("%d ",now);
	for(int i=head[now];i;i=edge[i].next)
		if(edge[i].cap==0&&edge[i].to>n){
			put(edge[i].to-n);
			break;
		}
}
int main(){
	scanf("%d%d",&n,&m);
	s=0; t=(n<<1)+1;
	for(int i=0;i<=2*n+1;i++)
		head[i]=0;
	for(int i=1;i<=n;i++){
		add(s,i,1);
		add(i,s,0);
		add(i+n,t,1);
		add(t,i+n,0);
	}
	for(int i=1;i<=m;i++){
		int x; int y;
		scanf("%d%d",&x,&y);
		add(x,y+n,1);
		add(y+n,x,0);
	}
	int max_flow=n-Dinic();
	for(int i=head[t];i;i=edge[i].next){
		if(edge[i^1].cap){
			put(edge[i].to-n);
			printf("\n");
		}
	}
	printf("%d",max_flow);
	return 0;
}
