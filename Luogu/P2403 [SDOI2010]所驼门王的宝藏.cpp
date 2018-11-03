#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<utility>
#include<map>
#define MAXN 100010
#define pir pair<int,int> 
using namespace std;
int all,n,m,ind[MAXN];
map<pir,bool>mat;//就是记录新图的连边。哪些边可以连（基于新图。
map<pir, int>tre;//用来记录某一个有宝藏的坐标位置的序号
map<pir,bool>::iterator it;//::iterator是STL里,代表指针
int dx[9]={0,-1,-1,-1,0,0,1,1,1};
int dy[9]={0,-1,0,1,-1,1,-1,0,1};
struct st1{
    int x;//横坐标 
    int y;//纵坐标 
    int opt;//门的类型 
    int number;//因为要sort所以肯定要记录初始序号啦 
}point[MAXN];
struct st2{//前向星用 
    int from;
    int to;
    int next;
}edge[MAXN*100];
int total,head[MAXN];
void add(int f,int t){//前向星 
    total++;
    edge[total].from=f;
    edge[total].to=t;
    edge[total].next=head[f];
    head[f]=total;
}
bool xf_cmp(st1 a,st1 b){
    if(a.x!=b.x) return a.x<b.x;
    if(a.opt==1) return 1;
    //如果是横天门就先把他放在前面 
    if(b.opt==1) return 0; 
    return a.y<b.y;
}
bool yf_cmp(st1 a,st1 b){
    if(a.y!=b.y) return a.y<b.y;
    if(a.opt==2) return 1;
    //如果是纵寰门就先把他放在前面 
    if(b.opt==2) return 0;
    return a.x<b.x;
}
inline int read()
{  
   int s=0,w=1;  
   char ch=getchar();  
   while(ch<='0'||ch>'9')
   {
        if(ch=='-')
            w=-1;
        ch=getchar();
    }  
   while(ch>='0'&&ch<='9')
   s=s*10+ch-'0',ch=getchar();  
   return s*w;  
} 
int Yeasion[MAXN];//Yeasion[i]表示i的dfs序 
int Nein[MAXN];//Nein[i]表示i节点所能回到的最早的节点的编号 
int ken,top,stack[MAXN];
bool insta[MAXN];//flag[i]表示i是不是被访问过，insta[i]表示在不在栈中。 
int belong[MAXN],cnt;
int sum[MAXN];
void Tarjan(int now){//基本的Tarjan 
    Yeasion[now]=Nein[now]=++ken;
    stack[++top]=now; insta[now]=1;
    for(int i=head[now];i;i=edge[i].next){
        if(!Yeasion[edge[i].to]){
            Tarjan(edge[i].to);
            Nein[now]=min(Nein[now],Nein[edge[i].to]);
        }
        else if(!belong[edge[i].to])
        Nein[now]=min(Nein[now],Yeasion[edge[i].to]);
    }
    if(Yeasion[now]==Nein[now]){
        cnt++; int pass;
        do{
            pass=stack[top--];
            belong[pass]=cnt;
            sum[cnt]++; //记录cnt含原图中点的个数 
            insta[pass]=0;
        }while(pass!=now);
    }
}
int ans,dp[MAXN];       
void dfs(int now,int fa){//动规 
//now是当前节点，fa是从哪里来的节点。可以理解为树上的父亲节点。 
    if(dp[now]>sum[now])return ;
    dp[now]=sum[now];
    for(int i=head[now];i;i=edge[i].next){
        if(edge[i].to==fa) continue;
        dfs(edge[i].to,now);
        dp[now]=max(dp[now],dp[edge[i].to]+sum[now]);
        //要知道，在新图中跑过了i节点就相当于是在就图中跑了sum[i]个宝藏室
    }
}
int main(){
    all=read(); n=read(); m=read();
    for(int i=1;i<=all;i++){
        point[i].x=read();
        point[i].y=read();
        point[i].opt=read();
        point[i].number=i;
        tre[pir(point[i].x,point[i].y)]=i;
        //记录坐标为(point[x],point[y])的点的序号为i
    }
    sort(point+1,point+all+1,xf_cmp);
    //我们想尽量快的循环到所有横天门，于是这个sort就是为了吧所有的横天门放在前面
	int first=1,last=1;
    //对于每一次循环到的第一个横门，我们记为first
    //规定last变量是上一个扫到的横门
    for(int i=1;i<=all;i++){ //横向建环 (横天门)
        if(point[i].x!=point[i+1].x){//相邻两个输入的坐标不在同一行
            if(first!=last)
            add(point[last].number,point[first].number);
            //我们连边肯定要连初始序号的啦
            last=first=i+1;
        }
        else{//在同一行
            if(point[last].opt==1)
            //如果i和i+1在同一行并且i是横天门就把last和i+1连起来
            add(point[last].number,point[i+1].number);
            if(point[i+1].opt==1)//如果i+1点是横天门
            last=i+1;//因为last是指上一个扫到的横天门，而且i+1是横天门，所以就更新last
            if(point[first].opt!=1)//如果first点不是横天门 
            //first要更新，last肯定也要更新 
            last=first=i+1;//那么更新last和first 
        }
    }
    sort(point+1,point+all+1,yf_cmp);
    first=1,last=1;//别忘了重置first和last 
    //同理，我们要想尽快的循环完所有的纵寰门，那么sort吧所有的纵寰门排在前面
    //然后循环结构基本和上面是完全一样的qwq 
    for(int i=1;i<=all;i++){  //纵向建环 (纵寰门) 
        if(point[i].y!=point[i+1].y){
        //纵寰门可不要打成point[i].x！！照搬上文是不行滴 
            if(first!=last)
            add(point[last].number,point[first].number);
            last=i+1; first=i+1;
            //将last和first都更新为i+1。 
        }
        else{
            if(point[last].opt==2)
            add(point[last].number,point[i+1].number);
            if(point[i+1].opt==2)
            last=i+1;
            if(point[first].opt!=2)
            last=first=i+1;
        }
    } 
 	for(int i=1;i<=all;i++)
	 if(point[i].opt==3){
	 	for(int j=1;j<=8;j++)
	 	if(tre.count(pir(point[i].x+dx[j],point[i].y+dy[j])))
	 	add(point[i].number,tre[pir(point[i].x+dx[j],point[i].y+dy[j])]);
	 }    
	for(int i=1;i<=all;i++)
    //因为一行上的横天门和一列上的纵寰门我们都已经连成了一个环。
    //所以肯定是强连通分量，所以我们就可以利用Tarjan进行缩点 
    if(!Yeasion[i]) Tarjan(i);
    //因为一次tarjan不一定能够遍历完所有的点 所以放在for里面
    //因为tarjan已经完成了，所以下面我们用到新图的节点都应该在belong[]里面。 
    for(int i=1;i<=total;i++){//for整个前向星 
        int f=edge[i].from;
        int t=edge[i].to;
        if(belong[f]!=belong[t])//如果在新图中不属于一个点 
        mat[pir(belong[f],belong[t])]=1;
    }
    memset(head,0,sizeof(head)); total=0;
    //清空前向星留下在新图接着用咯~~ 
    for(it=mat.begin();it!=mat.end();it++){
        add(it->first.first,it->first.second); 
        //it->first.first表示mat这个map的第一个元素的pair中的前面 
        //it->first.second表示mat的第一个元素的pair中的后面那个元素 
        ind[it->first.second]++;
    }
    //上面的操作简而言之就是：旧图中的edge如果在新图中依然可以连，就把他们连起来。
    for(int i=1;i<=cnt;i++){
        if(ind[i]==0){//入度为0 从入度为0开始跑 
        //因为我们可以知道从入度不为0的节点开始跑的ans一定小于从入度为0的节点开始跑的ans 
            dfs(i,0);//入度为0当然没有前前驱节点咯 
            ans=max(ans,dp[i]);//取max 
        }
    }
    printf("%d",ans); return 0;
}
