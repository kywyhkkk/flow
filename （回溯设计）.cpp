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
	ll lin=1;	//�����Ű���� 
	for(int i=1;i<=m;++i){
		if(person_per_night[i]!=sysadmins_per_night){	//�ж��Ƿ�ÿһ�춼�����㹻��ֵ������ 
			lin=0;										//������������1�Ĵ��� 
			break;
		}
	}
	if(lin==1){
		pd=1;	//�Ѿ��ҵ��˺���� 
	}
}

void allocate(ll x){
	if(pd==1){	//����Ѿ��õ��˺�����Ű࣬��ֱ�ӽ��� 
		return;
	}
	
	if(x==n+1){	//����Ѿ�������n���˵�ҹ�࣬��ô�ͼ���Ű��Ƿ�������˳� 
		check();
		return;
	}
	
	for(int i=1;i<=cnt;++i){
		if(pd==1){
			return;
		}
		ll tmp=valid[i];	//����ÿһ���Ϸ��ĵ�ǰ���� 
		ll count=m+1,now_unwanted=0;	
		while(tmp){
			int tt=tmp%2;
			count--;
			if(tt==1&&preferences[count][x]==0){
				now_unwanted++;		//�����Ʋ�����㣬������ڵ�ǰ����Ա
									//��ǰ�����Ĳ������ 
			}
			tmp/=2;
		}
		
		if(now_unwanted>max_unwanted_shifts){
			continue;
		}else{
			ll tmp=valid[i];
			ll count=0;		//�������Ǹ���ǰ����Ա������������ 
			while(tmp){		//ͳ��ÿ��ֵ������� 
				int tt=tmp%2;
				count++;
				person_per_night[count]+=tt;
				tmp/=2;
			}
			ans[x]=valid[i];
			ll vali=1;		//�����Լ�֦�������ǰ�����Ѿ������ܵ���һ�����з��� 
			for(int j=1;j<=m;++j){	//��vali����Ϊ 1 
				if(person_per_night[j]>sysadmins_per_night||person_per_night[j]+n-x<sysadmins_per_night){
					vali=0;
				}
			}
			
			if(vali){
				allocate(x+1);
			}
			
			tmp=valid[i];	//״̬�Ļָ� 
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
	for(int i=1;i<=m;++i){	//������ѹ��ÿ��ֵ��״̬ 
		res*=2;
	}
	res--;
	for(ll i=0;i<=res;++i){
		if(__builtin_popcountll(i)>=min_shifts){
			cnt++;			//���������� 3��״̬�������� 
			valid[cnt]=i;
		}
		
	}
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
	
	init();
	allocate(1);
	if(pd==0){
		printf("�޷��ų�����İ��,��������������½����Ű�\n");
		printf("�����Ѿ���ȫ�˳���  ����build by wyh");
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
		printf("�����Ѿ���ȫ�˳���  ����build by wyh"); 
	}
	return 0;
}


