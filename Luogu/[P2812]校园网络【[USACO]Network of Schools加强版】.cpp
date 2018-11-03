#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 100010
using namespace std;
int n,m,ind[MAXN],out[MAXN];
struct point{
    int from;
    int to;
    int next;
}edge[MAXN*100];
struct point2{
    int from;
    int to;
    int next;
}e[MAXN*100];
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
    total2++;
    e[total2].from=f;
    e[total2].to=t;
    e[total2].next=head2[f];
    head2[f]=total2;
}
int Yeasion[MAXN],Nein[MAXN];
int stack[MAXN],top,ken;
int belong[MAXN],cnt;
bool insta[MAXN];
void Tarjan(int now){
    Yeasion[now]=Nein[now]=++ken;
    stack[++top]=now;insta[now]=1;
    for(int i=head[now];i;i=edge[i].next){
        if(!Yeasion[edge[i].to]){
            Tarjan(edge[i].to);
            Nein[now]=min(Nein[now],Nein[edge[i].to]);
        }else if(insta[edge[i].to]){
            Nein[now]=min(Nein[now],Nein[edge[i].to]);
        }
    }
    if(Yeasion[now]==Nein[now]){
        cnt++; int pass;
        do{
            pass=stack[top--];
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
            ind[belong[edge[j].to]]++;
            out[belong[i]]++;
        }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	int x;
		while(cin>>x&&x){
			add(i,x);
		}
    }
    for(int i=1;i<=n;i++){
        if(!Yeasion[i])
        Tarjan(i);
    }   link();
    int ans1=0; int ans2=0;
    for(int i=1;i<=cnt;i++){
        if(ind[i]==0) ans1++;
        if(out[i]==0) ans2++;
    }printf("%d\n%d",ans1,ans2);
    return 0;
}
