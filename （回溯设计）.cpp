/*********************************************************************
    $PROGRAM$: 
    $COPYRIGHT$: wyh 
    $AUTHOR$: wyh 
    $DATETIME$: 2024/2/4 16:00:02
    $DESCRIPTION$: data structure planA 
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
using namespace std;
const ll maxn=100010;
const ll inf=0x3f3f3f3f3f3f3f3fll;
/*
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);
*/

ll n,pd=0,ans[maxn],m,person_per_night[31]; 
ll sysadmins_per_night,cnt,valid[maxn];
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

void check(){
	ll lin=1;	//假设排班合理 
	for(int i=1;i<=m;++i){
		if(person_per_night[i]!=sysadmins_per_night){	//判断是否每一天都有了足够的值班人数 
			lin=0;										//即对限制条件1的处理 
			break;
		}
	}
	if(lin==1){
		pd=1;	//已经找到了合理解 
	}
}

void allocate(ll x){
	if(pd==1){	//如果已经得到了合理的排班，就直接结束 
		return;
	}
	
	if(x==n+1){	//如果已经排完了n个人的夜班，那么就检查排班是否合理，并退出 
		check();
		return;
	}
	
	for(int i=1;i<=cnt;++i){
		if(pd==1){
			return;
		}
		ll tmp=valid[i];	//对于每一个合法的当前分配 
		ll count=m+1,now_unwanted=0;	
		while(tmp){
			int tt=tmp%2;
			count--;
			if(tt==1&&preferences[count][x]==0){
				now_unwanted++;		//二进制拆分运算，计算对于当前管理员
									//当前方案的不满意度 
			}
			tmp/=2;
		}
		
		if(now_unwanted>max_unwanted_shifts){
			continue;
		}else{
			ll tmp=valid[i];
			ll count=0;		//假设我们给当前管理员分配如上任务 
			while(tmp){		//统计每天值班的人数 
				int tt=tmp%2;
				count++;
				person_per_night[count]+=tt;
				tmp/=2;
			}
			ans[x]=valid[i];
			ll vali=1;		//可行性剪枝，如果当前方案已经不可能到达一个可行方案 
			for(int j=1;j<=m;++j){	//将vali设置为 1 
				if(person_per_night[j]>sysadmins_per_night||person_per_night[j]+n-x<sysadmins_per_night){
					vali=0;
				}
			}
			
			if(vali){
				allocate(x+1);
			}
			
			tmp=valid[i];	//状态的恢复 
			count=0;
			while(tmp){		
				int tt=tmp%2;
				count++;
				person_per_night[count]-=tt;
				tmp/=2;
			}
			
		}
	}
}

void init(){
	ll res=1;
	for(int i=1;i<=m;++i){	//二进制压缩每个值班状态 
		res*=2;
	}
	res--;
	for(ll i=0;i<=res;++i){
		if(__builtin_popcountll(i)>=min_shifts){
			cnt++;			//将满足限制 3的状态储存起来 
			valid[cnt]=i;
		}
		
	}
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
	
	init();
	allocate(1);
	if(pd==0){
		printf("无法排出满意的班次,建议调整输入重新进行排班\n");
		printf("程序已经安全退出。  ——build by wyh");
	}else{
		for(int i=1;i<=n;++i){
//			cout<<ans[i]<<endl;
			ll tmp=1;
			ll res=ans[i];
			while(res){
				result[m-tmp+1][i]=res%2;
				res/=2;
				tmp++;
			}
		}
		ask(); 
		printf("程序已经安全退出。  ——build by wyh"); 
	}
	return 0;
}


