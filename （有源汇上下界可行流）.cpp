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
	nex[cnt]=head[x];	 //��ǰ�ߵĺ�� 
	head[x]=cnt;		//���x�ĵ�һ���� 
	to[cnt]=y;			 //��ǰ���յ� 
	val[cnt]=z;			//��ǰ��Ȩֵ 
}

ll bfs(){
	queue<ll> qq;
	cur[s]=head[s];
	fill(dis,dis+n*2+m+10,0);
	dis[s]=1;	//ÿ�����Ӧ�Ĳ��� 
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
		cur[x]=i;	//����ǰ������Ϊ���ڱ����ı� 
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
	printf("�������Ƿ�Ҫ��ѯ�Ű������Y/N��\n");
	printf("tips:��������Ա��Ŵ�0��ʼ\n");

	char op[10];
	scanf("%s",op+1);
	if(op[1]!='Y'&&op[1]!='N'&&op[1]!='y'&&op[1]!='n'){
		
		ll pd=0;
		while(pd==0){
			pd=1;
			printf("���������룬Y/N\n");
			scanf("%s",op+1);
			if(op[1]!='Y'&&op[1]!='N'&&op[1]!='y'&&op[1]!='n'){
				pd=0;
			}
		}
	} 
	if(op[1]=='Y'||op[1]=='y'){
		printf("���潫���һ����ά���飬����[i][j] Ӧ�õ���1 ������Ϊ j ��ϵͳ����Ա�������ڱ��Ϊ i ��ҹ����\n");
		for(int i=1;i<=m;++i){
			for(int j=1;j<=n;++j){
				printf("%lld ",result[i][j]);
			}
			printf("\n");
		}
	}
	printf("�������Ƿ���Ҫ��ѯ������Ϣ������������0����ѯ�����ŵĹ���Ա�Ű�������1����ѯ����һ����Ű����������2\n");
	ll option=read();
	while(option!=0){
		if(option==1){
			printf("��������Ҫ��ѯ�Ĺ���Ա���\n"); 
			ll x=read();
			x++;
			while(x<=0||x>n){
				printf("���������룬����Ĺ���Ա���Ӧ��Ϊ0��n-1֮�������\n");
				x=read();
				x++;
			}
			printf("����Ϊ�ù���Աֵ���ʱ��\n");
			
			for(int i=1;i<=m;++i){
				if(result[i][x]==1){
					printf("��%d�� ",i-1);
				}
			}
			printf("\n");
		}else{
			if(option==2){
				printf("��������Ҫ��ѯ���������\n");
				ll x=read();
				x++;
				while(x<=0||x>m){
					printf("���������룬������������Ӧ��Ϊ0��m-1֮�������\n");
					x=read();
					x++;
				} 
				printf("����Ϊ����ֵ��Ĺ���Ա���\n");
				for(int i=1;i<=n;++i){
					if(result[x][i]==1){
						printf("���%d ",i-1);
					}
				}
				printf("\n");
			}else{
				if(option==0){
					
					break;
				}else{
					printf("������Ϸ��Ĳ������\n");
					option=read();
					continue;
				}
			}
		}
		printf("�������Ƿ������ѯ������Ϣ������������0����ѯ�����ŵĹ���Ա�Ű�������1����ѯ����һ����Ű����������2\n");
		option=read(); 
	}
}

ll ** allocate(ll A[][maxn],ll B,ll C,ll D){
	//ÿ���˷�������� 
	for(int i=1;i<=n;++i){
		add(2*n+m+1,i,m-min_shifts);
		add(i,2*n+m+1,0);
		fin[i]+=min_shifts;
		fout[n*2+m+1]+=min_shifts;
	}
	//ÿ���˲�Ը������� 
	for(int i=1;i<=n;++i){
		add(i,i+n,max_unwanted_shifts);
		add(i+n,i,0);
		fin[i+n]+=0;
		fout[i]+=0;
	}
	//����Ը��������� 
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
	//���Ӳ�Ը��������� 
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
	//ÿ����Ҫ�����������ӵ���� 
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
		printf("�޷��ų�����İ��,��������������½����Ű�\n");
		pzong=0;
		return NULL; 
	}else{
		for(int i=1;i<=num1;++i){	//�鿴ÿһ������Ȥ�Ķ�Ӧ�ı� 
			ll x,y,z;
			x=edge1[i].x;
			y=edge1[i].y;
			z=edge1[i].z;
			
			if(!val[z]){
				result[y][x]=1;
			}
		}
		for(int i=1;i<=num2;++i){	//�鿴ÿһ��û����Ȥ�Ķ�Ӧ�ı� 
			ll x,y,z;
			x=edge2[i].x;
			y=edge2[i].y;
			z=edge2[i].z;
			
			if(!val[z]){
				result[y][x]=1;
			}
		}
		return (ll **)result;
//		for(int i=1;i<=m;++i){	//���Ű����� 
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
		"*                                     ��  ӭ  ʹ  ��                                     *" <<endl<<
		"*                                                                                        *" <<endl<<
		"*                                         W Y H                                          *" <<endl<<
		"*                                                                                        *" <<endl<<
		"*                         ��  ˾  ��  ��  ��  ��  ��  ѯ  ϵ  ͳ                         *" <<endl<<
		"*                                                                               *   *    *" <<endl<<
		"*                                                                             *   *   *  *" <<endl<<
		"*                                                                               *   *    *" <<endl<<
		"*                                                                                 *      *" <<endl<<
		"******************************************************************************************" << endl<<endl;
}

int main(){
	welcome(); 
	printf("����������Ű�Ĺ���Ա����n\n");
	n=read();
	
	printf("��������Ҫ�����Ű������m\n");
	m=read();
	
	printf("�������ά����preferences��������Ϊ j ��ϵͳ����Ա����Ȥ�ڱ��Ϊ i ��ҹ��İ�Σ�preferences[i][j]����1������� 0��\n");
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
		printf("���������룬pre��Ԫ��ֻ��Ϊ0����1\n");
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
	
	
	printf("���������Ͳ���sysadmins_per_night��ָ��ȷ�е�ÿ��Ӧ��ֵ���ϵͳ����Ա����ͬ������ϵͳ����Ա��ÿ����Ҫ��\n");
	sysadmins_per_night=read();
	pd=1;
	if(sysadmins_per_night<0||sysadmins_per_night>n){
		pd=0;
	}
	while(pd==0){
		printf("���������룬sysadmins_per_nightӦ��Ϊ���Ͳ�������0 �� sysadmins_per_night �� n\n");
		pd=1;
		sysadmins_per_night=read();
		if(sysadmins_per_night<0||sysadmins_per_night>n){
			pd=0;
		}
	}
	
	printf("���������Ͳ���max_unwanted_shifts��n ��ϵͳ����Ա�е�ÿһ����Ӧ�����������/��������Ȥ�� max_unwanted_shifts ��ҹ�ࡣ\n");
	max_unwanted_shifts=read();
	pd=1;
	if(max_unwanted_shifts<0||max_unwanted_shifts>m){
		pd=0;
	}
	while(pd==0){
		printf("���������룬max_unwanted_shiftsӦ��Ϊ���Ͳ�������0 �� max_unwanted_shifts �� m\n");
		pd=1;
		max_unwanted_shifts=read();
		if(max_unwanted_shifts<0||max_unwanted_shifts>m){
			pd=0;
		}
	}
	
	printf("���������Ͳ���min_shifts��n��ϵͳ����Ա�е�ÿһ����Ӧ�÷��䵽����min_shifts ��ҹ�ࡣ\n");
	min_shifts=read();
	pd=1;
	if(min_shifts<0||min_shifts>m){
		pd=0;
	}
	while(pd==0){
		printf("���������룬min_shiftsӦ��Ϊ���Ͳ�������0 �� min_shifts �� m\n");
		min_shifts=read();
		pd=1;
		if(min_shifts<0||min_shifts>m){
			pd=0;
		}
	}
	ll **tm=allocate(preferences,sysadmins_per_night,max_unwanted_shifts,min_shifts);
	if(pzong==0){
		printf("�����Ѿ���ȫ�˳���  ����build by wyh");
		return 0;
	}
	ask(); 
	printf("�����Ѿ���ȫ�˳���  ����build by wyh"); 
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
