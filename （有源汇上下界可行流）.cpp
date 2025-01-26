/*********************************************************************
    $PROGRAM$: 
    $COPYRIGHT$: wyh 
    $AUTHOR$: wyh 
    $DATETIME$: 2024/2/4 16:00:02
    $DESCRIPTION$: data structure planB  
*********************************************************************/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#ifdef Debug
#define D() cerr<<__LINE__<<endl;
#else
#define D()
#endif
#define ll long long
#define ull unsigned long long
#include<queue>
using namespace std;
const ll maxn=10010;
const ll maxm=1000001;
const ll inf=0x3f3f3f3f3f3f3f3fll;
/*
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);
*/
struct CountAns{
	ll x,y,z;
};
CountAns edge1[maxm],edge2[maxm];
ll n,m,ji[31],num1,num2,pzong=1; 
ll sysadmins_per_night,cnt=1,nex[maxm],head[maxm],to[maxm];
ll val[maxm],cur[maxm],s,t,dis[maxm];
ll fin[maxn],fout[maxn],ans;
ll preferences[31][maxn],max_unwanted_shifts,min_shifts,result[31][maxn];

ll read(){
	char ch=getchar();ll xx=0,ff=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-')ff=-1;ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		xx=xx*10+ch-'0';ch=getchar();
	}
	return xx*ff;
}

void add(ll x,ll y,ll z){
	cnt++;
	nex[cnt]=head[x];	 //当前边的后继 
	head[x]=cnt;		//起点x的第一条边 
	to[cnt]=y;			 //当前边终点 
	val[cnt]=z;			//当前边权值 
}

ll bfs(){
	queue<ll> qq;
	cur[s]=head[s];
	fill(dis,dis+n*2+m+10,0);
	dis[s]=1;	//每个点对应的层数 
	qq.push(s);
	while(!qq.empty()){
		ll x=qq.front();
		qq.pop();
		for(int i=head[x];i;i=nex[i]){
			ll to2=to[i];
			if(val[i]<=0||dis[to2]){
				continue;
			} 
			dis[to2]=dis[x]+1;
			qq.push(to2);
			cur[to2]=head[to2];
		}
	}
	if(dis[t]==0){
		return 0;
	}else{
		return 1;
	}
}

ll dfs(ll x,ll z){
	if(x==t){
		return z;
	}
	ll res=0;
	for(int i=cur[x];i;i=nex[i]){
		cur[x]=i;	//将当前弧设置为现在遍历的边 
		ll to2=to[i];
		if(val[i]==0||dis[to2]!=dis[x]+1){
			continue;
		}
		ll k=dfs(to2,min(z,val[i]));
		val[i]-=k;
		val[i^1]+=k;
		res+=k;
		z-=k;
	}
	return res;
}

void ask(){
	printf("请问您是否要查询排班情况表（Y/N）\n");
	printf("tips:天数与人员编号从0开始\n");

	char op[10];
	scanf("%s",op+1);
	if(op[1]!='Y'&&op[1]!='N'&&op[1]!='y'&&op[1]!='n'){
		
		ll pd=0;
		while(pd==0){
			pd=1;
			printf("请重新输入，Y/N\n");
			scanf("%s",op+1);
			if(op[1]!='Y'&&op[1]!='N'&&op[1]!='y'&&op[1]!='n'){
				pd=0;
			}
		}
	} 
	if(op[1]=='Y'||op[1]=='y'){
		printf("下面将输出一个二维数组，分配[i][j] 应该等于1 如果编号为 j 的系统管理员被分配在编号为 i 的夜晚工作\n");
		for(int i=1;i<=m;++i){
			for(int j=1;j<=n;++j){
				printf("%lld ",result[i][j]);
			}
			printf("\n");
		}
	}
	printf("请问您是否需要查询其他信息，结束请输入0，查询任意编号的管理员排班请输入1，查询任意一天的排班情况请输入2\n");
	ll option=read();
	while(option!=0){
		if(option==1){
			printf("请输入您要查询的管理员编号\n"); 
			ll x=read();
			x++;
			while(x<=0||x>n){
				printf("请重新输入，输入的管理员编号应该为0到n-1之间的整数\n");
				x=read();
				x++;
			}
			printf("下面为该管理员值班的时间\n");
			
			for(int i=1;i<=m;++i){
				if(result[i][x]==1){
					printf("第%d天 ",i-1);
				}
			}
			printf("\n");
		}else{
			if(option==2){
				printf("请输入您要查询的天数编号\n");
				ll x=read();
				x++;
				while(x<=0||x>m){
					printf("请重新输入，输入的天数编号应该为0到m-1之间的整数\n");
					x=read();
					x++;
				} 
				printf("下面为当天值班的管理员编号\n");
				for(int i=1;i<=n;++i){
					if(result[x][i]==1){
						printf("编号%d ",i-1);
					}
				}
				printf("\n");
			}else{
				if(option==0){
					
					break;
				}else{
					printf("请输入合法的操作编号\n");
					option=read();
					continue;
				}
			}
		}
		printf("请问您是否继续查询其他信息，结束请输入0，查询任意编号的管理员排班请输入1，查询任意一天的排班情况请输入2\n");
		option=read(); 
	}
}

ll ** allocate(ll A[][maxn],ll B,ll C,ll D){
	//每个人分配的天数 
	for(int i=1;i<=n;++i){
		add(2*n+m+1,i,m-min_shifts);
		add(i,2*n+m+1,0);
		fin[i]+=min_shifts;
		fout[n*2+m+1]+=min_shifts;
	}
	//每个人不愿意的天数 
	for(int i=1;i<=n;++i){
		add(i,i+n,max_unwanted_shifts);
		add(i+n,i,0);
		fin[i+n]+=0;
		fout[i]+=0;
	}
	//链接愿意的人与天 
	for(int i=1;i<=n;++i){
		for(int j=2*n+1;j<=2*n+m;++j){
			if(!preferences[j-n*2][i]){
				continue;
			} 
			add(i,j,1);
			num1++;
			edge1[num1].x=i;
			edge1[num1].y=j-2*n;
			edge1[num1].z=cnt;
			add(j,i,0);
			fin[j]+=0;
			fout[i]+=0;
		}
	}
	//连接不愿意的人与天 
	for(int i=n+1;i<=n*2;++i){
		for(int j=2*n+1;j<=2*n+m;++j){
			if(preferences[j-2*n][i-n]){
				continue;
			}
			add(i,j,1);
			num2++;
			edge2[num2].x=i-n;
			edge2[num2].y=j-2*n;
			edge2[num2].z=cnt;
			add(j,i,0);
			fin[j]+=0;
			fout[i]+=0;
		}
	}
	//每天需要的人数，连接到汇点 
	for(int i=2*n+1;i<=2*n+m;++i){
		add(i,2*n+m+2,0);
		add(2*n+m+2,i,0);
		fin[2*n+m+2]+=sysadmins_per_night;
		fout[i]+=sysadmins_per_night;
	}
	add(2*n+m+2,2*n+m+1,99991299912);
	add(2*n+m+1,2*n+m+2,0);
	s=2*n+m+3;t=2*n+m+4;
	for(int i=1;i<=2*n+m+2;++i){
		if(fin[i]-fout[i]>0){
			add(s,i,fin[i]-fout[i]);
			add(i,s,0);
		}
		if(fout[i]-fin[i]>0){
			add(i,t,fout[i]-fin[i]);
			add(t,i,0);
		}
	}
	
//	ll jishu=1;
	while(bfs()){
//		jishu++;
//		if(jishu>20){
//			break;
//		}
		ans+=dfs(s,99991299912);
//		cout<<ans<<endl;
	}

	ll pd=1;
	for(int i=head[s];i;i=nex[i]){
		if(val[i]!=0){
			pd=0;
		}
	}	
	if(pd==0){
		printf("无法排出满意的班次,建议调整输入重新进行排班\n");
		pzong=0;
		return NULL; 
	}else{
		for(int i=1;i<=num1;++i){	//查看每一条有兴趣的对应的边 
			ll x,y,z;
			x=edge1[i].x;
			y=edge1[i].y;
			z=edge1[i].z;
			
			if(!val[z]){
				result[y][x]=1;
			}
		}
		for(int i=1;i<=num2;++i){	//查看每一条没有兴趣的对应的边 
			ll x,y,z;
			x=edge2[i].x;
			y=edge2[i].y;
			z=edge2[i].z;
			
			if(!val[z]){
				result[y][x]=1;
			}
		}
		return (ll **)result;
//		for(int i=1;i<=m;++i){	//将排班答案输出 
//			for(int j=1;j<=n;++j){
//				printf("%lld ",result[i][j]);
//			}
//			printf("\n");
//		}
	}
}

void welcome(){
	cout << "******************************************************************************************" <<endl<<
		"*                                                                                        *" <<endl<<
		"*                                                                                        *" <<endl<<
		"*                                     欢  迎  使  用                                     *" <<endl<<
		"*                                                                                        *" <<endl<<
		"*                                         W Y H                                          *" <<endl<<
		"*                                                                                        *" <<endl<<
		"*                         公  司  排  班  方  按  查  询  系  统                         *" <<endl<<
		"*                                                                               *   *    *" <<endl<<
		"*                                                                             *   *   *  *" <<endl<<
		"*                                                                               *   *    *" <<endl<<
		"*                                                                                 *      *" <<endl<<
		"******************************************************************************************" << endl<<endl;
}

int main(){
	welcome(); 
	printf("请输入参与排班的管理员人数n\n");
	n=read();
	
	printf("请输入需要进行排班的天数m\n");
	m=read();
	
	printf("请输入二维数组preferences，如果编号为 j 的系统管理员有兴趣在编号为 i 的夜晚的班次，preferences[i][j]等于1否则等于 0。\n");
	ll pd=1;
	for(int i=1;i<=m;++i){
		for(int j=1;j<=n;++j){
			preferences[i][j]=read();
			if(preferences[i][j]!=0&&preferences[i][j]!=1){
				pd=0;
			}
		}
	} 
	while(pd==0){
		printf("请重新输入，pre的元素只能为0或者1\n");
		pd=1;
		for(int i=1;i<=m;++i){
			for(int j=1;j<=n;++j){
				preferences[i][j]=read();
				if(preferences[i][j]!=0&&preferences[i][j]!=1){
					pd=0;
				}
			}
		}
	}
	
	
	printf("请输入整型参数sysadmins_per_night，指定确切的每晚应该值班的系统管理员（相同数量的系统管理员将每晚都需要）\n");
	sysadmins_per_night=read();
	pd=1;
	if(sysadmins_per_night<0||sysadmins_per_night>n){
		pd=0;
	}
	while(pd==0){
		printf("请重新输入，sysadmins_per_night应该为整型参数，且0 ≤ sysadmins_per_night ≤ n\n");
		pd=1;
		sysadmins_per_night=read();
		if(sysadmins_per_night<0||sysadmins_per_night>n){
			pd=0;
		}
	}
	
	printf("请输入整型参数max_unwanted_shifts，n 个系统管理员中的每一个都应该最多分配给他/她不感兴趣的 max_unwanted_shifts 个夜班。\n");
	max_unwanted_shifts=read();
	pd=1;
	if(max_unwanted_shifts<0||max_unwanted_shifts>m){
		pd=0;
	}
	while(pd==0){
		printf("请重新输入，max_unwanted_shifts应该为整型参数，且0 ≤ max_unwanted_shifts ≤ m\n");
		pd=1;
		max_unwanted_shifts=read();
		if(max_unwanted_shifts<0||max_unwanted_shifts>m){
			pd=0;
		}
	}
	
	printf("请输入整型参数min_shifts，n个系统管理员中的每一个都应该分配到至少min_shifts 个夜班。\n");
	min_shifts=read();
	pd=1;
	if(min_shifts<0||min_shifts>m){
		pd=0;
	}
	while(pd==0){
		printf("请重新输入，min_shifts应该为整型参数，且0 ≤ min_shifts ≤ m\n");
		min_shifts=read();
		pd=1;
		if(min_shifts<0||min_shifts>m){
			pd=0;
		}
	}
	ll **tm=allocate(preferences,sysadmins_per_night,max_unwanted_shifts,min_shifts);
	if(pzong==0){
		printf("程序已经安全退出。  ——build by wyh");
		return 0;
	}
	ask(); 
	printf("程序已经安全退出。  ——build by wyh"); 
	return 0;
}

/*
4
3
0 0 0 1
0 1 0 1
1 0 0 1
2 
1
1
*/ 
/*
20
30
1 0 0 1 0 0 1 1 1 0 1 0 1 1 0 1 0 1 0 1
0 0 1 0 0 1 1 1 0 0 1 0 0 0 1 0 1 0 1 0
1 1 0 1 1 0 0 0 1 1 0 1 1 1 0 1 0 1 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 1
1 1 1 1 1 0 0 0 1 0 1 0 1 0 0 1 1 0 0 1
0 0 0 1 1 1 1 0 1 1 1 0 0 0 1 1 1 0 1 0
1 1 1 0 0 0 1 1 0 0 0 1 1 1 0 0 0 0 1 0
0 0 0 1 1 1 1 1 1 1 0 0 0 0 1 0 1 0 1 0
1 1 1 0 0 0 1 1 0 0 1 1 1 0 1 0 1 0 0 1
0 0 0 0 0 1 1 1 1 1 1 0 0 1 0 1 0 1 0 1
0 1 1 1 1 1 0 0 0 0 0 1 0 1 0 0 1 0 1 1
0 1 1 1 1 1 1 0 0 0 1 1 0 1 1 1 0 0 0 0
1 1 1 0 0 0 1 1 0 0 0 1 1 1 0 0 0 0 1 0
1 1 0 1 1 0 0 0 1 1 0 1 1 1 0 1 0 1 0 1
0 0 1 0 0 1 1 1 0 0 1 0 0 0 1 0 1 0 1 0
0 0 0 1 1 1 1 0 1 1 1 0 0 0 1 1 1 0 1 0
1 1 1 0 0 0 1 1 0 0 0 1 1 1 0 0 0 0 1 0
0 0 0 1 1 1 1 1 1 1 0 0 0 0 1 0 1 0 1 0
1 1 1 0 0 0 1 1 0 0 1 1 1 0 1 0 1 0 0 1
0 0 0 0 0 1 1 1 1 1 1 0 0 1 0 1 0 1 0 1
0 1 1 1 1 1 0 0 0 0 0 1 0 1 0 0 1 0 1 1
1 0 0 1 0 0 1 1 1 0 1 0 1 1 0 1 0 1 0 1
0 0 1 0 0 1 1 1 0 0 1 0 0 0 1 0 1 0 1 0
1 1 0 1 1 0 0 0 1 1 0 1 1 1 0 1 0 1 0 1
1 1 0 1 1 0 0 0 1 1 0 1 1 1 0 1 0 1 0 1
1 1 1 0 0 0 1 1 0 0 0 1 1 1 0 0 0 0 1 0
0 0 0 1 1 1 1 1 1 1 0 0 0 0 1 0 1 0 1 0
1 1 1 0 0 0 1 1 0 0 1 1 1 0 1 0 1 0 0 1
1 1 1 0 0 0 1 1 0 0 1 1 1 0 1 0 1 0 0 1
0 0 0 0 0 1 1 1 1 1 1 0 0 1 0 1 0 1 0 1
2
1
1
*/
