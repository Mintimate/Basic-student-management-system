#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include <conio.h>
#include<Windows.h>
#define MaxStu 100                                                //M03����ṹ���ȱ��;
#define Data DATA.dat
typedef struct Stu {
    char id[16];//ѧ��
    char name[16];//����
    int sex;//�Ա�
    int birth;//����
    char tel[16];//�ֻ�����
    int ifsign;
}Stu;                                                             //M02����ṹ�����ˡ�;��
struct Stu_Proj {
    struct Stu students[MaxStu];//ѧ�����飬���ֵ��MaxStu������ɢ�б����ʽ�洢��
    int exist[MaxStu];//ѧ���Ƿ���ڣ����exist[4]=1��˵��students[4]��ѧ���Ǵ��ڵģ����exist[5]=0��˵��students[5]��ѧ���ǲ����ڵģ���ɾ���ˣ���û��¼�룩��
    int n;//��ǰѧ������
    int status;//״̬ 
};                                                                //M01����ṹ���ȱ�٣�
int _0_save(struct Stu_Proj *sp); //�˳����� 

int first_start(struct Stu_Proj *sp);//��ʼ���ṹ�巽�� 

int _1_enter(struct Stu_Proj *sp);//����1������ѧ������ 

int _2_del(struct Stu_Proj *sp);//����2��ɾ��ѧ������ 

int _3_update(struct Stu_Proj *sp);//����3�����£����ģ�ѧ������ 

int _4_search(struct Stu_Proj *sp);//����4������ѧ����Ϣ 

int _5_save(struct Stu_Proj *sp);//����5������ѧ����Ϣ 

int _6_load(struct Stu_Proj *sp);//����6������ѧ����Ϣ�ļ� 

struct Stu_Proj * _7_init();//����7����ʽ��ѧ��ѧϰ 

int pagefz,pagefm;
int updown=0,leftright=1;
int ifchange=0;
int ifselect=0;
char key=0;
int hide_i=0;
int hide_n=0;
int hide_s=0;
int hide_v=0;
int hide_b=0;
int hide_t=0;
void menu1(struct Stu_Proj *sp);
void menu2();
void menu3();
char zhuangtai[12][10]={"���","�˳�","����","ɾ��","����","����","����","����","��ԭ","���","����","�����"};
char moshi[2][10]={"��ѡ��","ѡ��"};
const char tishi[2][128]={
	"�����ɹ�����ѡ���������",
	"����ȡ������ѡ���������",
};
//���뺯����
void I_come();
//ѧ��У��
int id_check(char *id);
//�������
int name_check(char *name);
//�Ա���
int gender_check(char *gender); 
//������
int age_check(int age); 
//�Ա���ż��
char* gender(int a); 
//��ʽ�� 
void format(); 
//M126
int sex_gender(char *tmp1);
//�绰��� 
int tel_check(char *tel); 
static int equals(struct Stu *s1,struct Stu *s2);
char* tel_tra(char *tel);
char* name_tra(char *name);
int birth_tra(int birth);
int outport(struct Stu_Proj *sp);
//״̬��ѯ
void status_tra(int n); 
void developer();
int main()        //M13 ���������ʹ���
{

    //struct Stu_Proj *sp = (struct Stu_Proj *) malloc(sizeof(struct Stu_Proj));//����4 ֻ����δ����ռ�

    struct Stu_Proj *sp = (struct Stu_Proj *) malloc(sizeof(struct Stu_Proj));
    char c;
    int a;
    int i;
    char question; 
    FILE *fp;
	system("color 0c");    
    I_come();
	 
if ((fp = fopen("Data", "rb")) != NULL)
        printf("\n\t\t--��ǰ����ѧ�����ݴ浵--");
        fclose(fp);
    printf("\n\t\t�Ƿ��ȡ�ϴ�ѧ�������ļ�����������");
    printf("\n\t\t[y]Ϊ������[n]Ϊ�������Ҹ�ʽ��ϵͳ��");
    do {
        a = getch();
        if (a == 'y') {
            first_start(sp);
            break;
        } else if (a == 'n') {
            printf("\n\t\t��ѡ�񲻶�������ʼ��ϵͳ");
        	format();
			sp=_7_init();
            break;
        } else {
            printf("\n\t\tδ֪������������룺");
        }
    } while (a != 'y' || a != 'n');
    system("color 0b");							//�����ն���ʾ�������ɫ
	pagefz=1;                  //��ʼҳ��Ϊһ 
	if(sp->n%10==0)
	{
		pagefm=(sp->n)/10;    //ҳ�� 
	}
	else if(sp->n<10)
	{
		pagefm=1;
	}
	else
	{
		pagefm=(sp->n)/10+1;
	}
	
	do											//��ѭ�������������û�������,����do-while��ʽ����ִ�У����ж�
	{	/*ÿ����һ�β�ѯ��4������ӡһ�β˵�����������Ļ��ʾ����*/
		
		_4_search(sp);
		if(sp->n%10==0)
		{
			pagefm=(sp->n)/10;
		}
		else if(sp->n<10)
		{
			pagefm=1;
		}
		else
		{
			pagefm=(sp->n)/10+1;
		}
		printf("\n��ѡ����:\n");
		c=getch();
		
		switch(c)
		{
		case 'x':
			system("color 0c");
			if(ifchange==0)
			{
				key='x';
				_4_search(sp);
				_0_save(sp);
			}
			else
			{
				key='x';
				_4_search(sp);
				printf("�����иĶ������Ƿ���Ҫ����?(y/n)\n");
				question=getch();
				if(question=='n')
				{
					printf("�Ķ�������δ����!\n");
				}
				else
				{
					_5_save(sp);
				}
			}
			printf("��л����ʹ�ã���������˳�......\n");
			getch();

			return 0;
		case 'f':
			key='f';
			_4_search(sp);
			_5_save(sp);
			break;
		case 'l':
			key='l';
			_4_search(sp);
			break;
		case 'c':
			key='c';
			_4_search(sp);
			_1_enter(sp);
			break;
		case 'd':
			key='d';
			_4_search(sp);
			_2_del(sp);
			break;
		case 'u':
			key='u';
			_4_search(sp);
			_3_update(sp);
			break;
		case 'o':
			key='o';
			outport(sp);
			_4_search(sp);
			break;
		case 'e':
			key='e';
			if(ifselect==0)
			{
				ifselect=1;
			}
			else
			{
				ifselect=0;
			}
			_4_search(sp);
			break;
		case 'm':
			key='m';
			if(ifselect==1)
			{
				if(sp->students[updown].ifsign==0)
				{
					sp->students[updown].ifsign=1;
				}
				else
				{
					sp->students[updown].ifsign=0;
				}
			}
			_4_search(sp);
			break;
		case 'a':
			key='a';
			for(i=0;i<MaxStu;i++)
			{
				if(ifselect==1)
				{
					sp->students[i].ifsign=1;
				}
			}
			_4_search(sp);
			break;
		case 'z':
			key='z';
			for(i=0;i<MaxStu;i++)
			{
				if(ifselect==1)
				{
					if(sp->students[i].ifsign==1)
					{
						sp->students[i].ifsign=0;
					}
					else
					{
						sp->students[i].ifsign=1;
					}
				}
			}
			_4_search(sp);
			break;
		case 'r':
			key='r';
			//sort(sp);
			printf("���ֵVIP�ſɽ��������ܡ�\n��ϵQQ:1009683012\n");
			getch();
			_4_search(sp);
			break;
		case 'y':
			key='y';
			_6_load(sp);
			_4_search(sp);
			break;
		case 'g':
			key='g';
			sp=_7_init();
			_4_search(sp);
			break;
		case 'i':
			key='i';
			if(hide_i==0)
			{
				hide_i=1;
			}
			else
			{
				hide_i=0;
			}
			getch();
			_4_search(sp);
			break;
		case 'n':
			key='n';
			if(hide_n==0)
			{
				hide_n=1;
			}
			else
			{
				hide_n=0;
			}
			getch();
			_4_search(sp);
			break;
		case 's':
			key='s';
			if(hide_s==0)
			{
				hide_s=1;
			}
			else
			{
				hide_s=0;
			}
			getch();
			_4_search(sp);
			break;
		case 'v':
			key='v';
			if(hide_v==0)
			{
				hide_v=1;
			}
			else
			{
				hide_v=0;
			}
			getch();
			_4_search(sp);
			break;
		case 'b':
			key='b';
			if(hide_b==0)
			{
				hide_b=1;
			}
			else
			{
				hide_b=0;
			}
			getch();
			_4_search(sp);
			break;
		case 't':
			key='t';
			if(hide_t==0)
			{
				hide_t=1;
			}
			else
			{
				hide_t=0;
			}
			getch();
			_4_search(sp);
			break;
		case 72://��
			updown--;
			if(updown==-1)
			{
				if(leftright==1)
				{
					if(sp->n%10==0)
					{
						leftright=sp->n/10;
					}
					else
					{
						leftright=sp->n/10+1;
					}
					updown=(sp->n+9)%10;
				}
				else
				{
					leftright--;
					updown=9;
				}
			}
			_4_search(sp);
			break;
		case 80://��
			updown++;
			if(updown==10)
			{
				if(sp->n%10==0)
				{
					if(leftright==sp->n/10)
					{
						leftright=1;
						updown=0;
					}
					else
					{
						leftright++;
						updown=0;
					}
				}
				else
				{
					if(leftright==sp->n/10+1)
					{
						leftright=1;
						updown=0;
					}
					else
					{
						leftright++;
						updown=0;
					}
				}
			}
			_4_search(sp);
			break;
		case 75://��
			leftright--;
			if(leftright==0)
			{
				if(sp->n/10.0>0){
				leftright=sp->n/10+1;
				}
				}
				else{
					leftright=sp->n/10;
				
			}
			_4_search(sp);
			break;
		case 77://��
			leftright++;
			if(leftright>=(float)(sp->n/10.0)+1)
			{
				leftright=1;
			}
			_4_search(sp);
			break;
		case 'h':
			developer();
			_4_search(sp);
			break;
		}
	}while(1);
}//M05 main()������}��λ�ñ�Ǵ�����ӵ���һ�㡣
int first_start(struct Stu_Proj *sp) {
    _6_load(sp);
    return 0;
}

int _0_save(struct Stu_Proj *sp){
	int a,t;
		printf("\n\t\t��ȷ���Ƿ�Ҫ�����ļ�!\n");		
		printf("\t\t��(1)\t��(0)\n\t\t");				
		scanf("%d",&a);	
		if(a==0)					
		{
			printf("\n\t\t�����ɹ�����������˳�ϵͳ......\n");
			t=-1;	
		}
		else if(a==1)
		{
			_5_save(sp);
			t=-1; 
		}
		else
		{
			printf("\n\t\t�Ƿ����룬Ĭ�ϱ����ļ����˳�\n");
			_5_save(sp);
			t=-1;
		}
		getch();
		return t;					
}
int _1_enter(struct Stu_Proj *sp) {
    int i, t,t1,birth;
    char id[16]={'\0'};
    char gender[1045],tel[20],name[20];
    printf("\n\t\t����ѧ������ϵͳ��");
    printf("\n\t\t������:\n\t\t 10λ����ѧ�ţ�����0�˳�\n\t\t"); //M09 �﷨����ʹ��printf��ӡ�������롱
    do{
    	scanf("%s",id);
		t=id_check(id);
	}while(t==2);
    if(t==0){
    	printf("\t\t������ֹ�ɹ�");
    	printf("\n\t\t���������......");
		getch();
		sp->status=0;
		return 0; 
	}
    for (i = 0; i < MaxStu; i++) {
        if(strcmp(sp->students[i].id,id)==0){
            printf("\n\t\tѧ�����ݴ��ڣ���ȷ��������ȷ");
            printf("\n\t\t���������......");
            getch();
            sp->status=0;
            return 0;
        }
        else{
            if (sp->exist[i] == 0)
            break;
        }
    }
    sp->exist[i] = 1;
    //strcpy((sp->students[i].id),id);
    printf("\t\t����������\n\t\t");
    do{
    	scanf("%s",name);
    	t1=name_check(name);
	}while(t1==2);
	if(t1==0){
		printf("\t\t������ֹ�ɹ�");
    	printf("\n\t\t���������......");
		getch();
		sp->status=0;
		return 0; 
	}
	strcpy((sp->students[i].name),name);
	strcpy((sp->students[i].id),id);
	sp->n++;
    printf("\t\t�������Ա��У�m��male��0������Ů��f��female��1��,0Ϊ����������\n\t\t");
    do{
    	scanf("%s",gender);
		t=gender_check(gender);
	}while(t==2);
    if(t==0){
    	printf("\t\t������ֹ�ɹ�");
    	printf("\n\t\t���������......");
		getch();
		sp->status=0;
		return 0; 
	}
    sp->students[i].sex=sex_gender(gender);
    printf("\t\t���������������\n\t\t");
    do{
    	scanf("%d",&birth);
		t=age_check(birth);
	}while(t==2);
    if(t==0){
    	printf("\t\t������ֹ�ɹ�");
    	printf("\n\t\t���������......");
		getch();
		sp->status=0;
		return 0; 
	}
	sp->students[i].birth=birth;
	printf("\t\t������16λ���µ绰����0Ϊ�˳�\n\t\t");
    do{
    	scanf("%s",tel);
    	t1=tel_check(tel);
	}while(t1==2);
	if(t1==0){
		printf("\t\t������ֹ�ɹ�");
    	printf("\n\t\t���������......");
		getch();
		sp->status=0;
		return 0; 
	}
	strcpy(sp->students[i].tel,tel);
    printf("\t\tд��ɹ�");
    printf("\n\t\t���������......");
    getch();
	sp->status=0;        //M14 ����������ָ��
    return 0;

}

int _2_del(struct Stu_Proj *sp)							//ɾ���������������ܣ�����ѧ��ɾ��ѧ����Ϣ	����M04Ҫ���޸�
{
	int i,flag=-1;								//�������i��ѭ��ʱʹ�ã�����flag���ҳ�ʼ��Ϊ-1���ں�������Ƿ���Ҫ���ĳЩ��ʾ���ж�
	char id[16],a;								//���������ѧ��ѧ��
	if(sp==NULL)								//���н�׳���жϣ�	����M20Ҫ���޸�
	{
		printf("ϵͳ��ʼ��ʧ�ܣ��������-1������ϵ����Ա�������!\n����������ز˵�......\n");			//�������spΪ��ʱ�Ĵ�����ʾ
		getch();								//��ͣ������ʾ��ʾ

		return -1;								//����spΪ�գ�����-1	����M20Ҫ���޸�		
	}
	if(sp->n==0)								//����M20Ҫ���޸�	����M21Ҫ���޸�
	{
		printf("δ�ҵ�ѧ�����ݣ�������������ѧ�����ݺ�����޸Ĳ���!\n����������ز˵�......\n");		//���ѧ����Ϊ0ʱ����ͼ�޸ĵĴ�����ʾ
		getch();	

		return -2;								//ѧ����Ϊ0������-2��	����M20Ҫ���޸�	����M21Ҫ���޸�
	}
	if(ifselect==1)
	{
		printf("��ǰ��������ɾ��״̬���Ƿ�ɾ���ѱ������?(y/n)\n");
		a=getch();
		if(a=='y')
		{
			for(i=0;i<MaxStu;i++)				//ѭ���Ƚ�
			{
				if(sp->students[i].ifsign==1)
				{
					sp->exist[i]=0;				//����ѧ�ŵ�exist[i]=0��ɾ�����������Ҳ���ǽ���ѧ�Ÿ��±��ѧ����Ϣ��ϵͳ������λ�ø�Ϊ������
					strcpy(sp->students[i].id,"-1");
					strcpy(sp->students[i].name,"-1");
					sp->students[i].sex=-1;
					sp->students[i].birth=-1;
					strcpy(sp->students[i].tel,"-1");
					sp->students[i].ifsign=0;
					flag=1;						//���ҽ�flag��ֵΪ1���ں����жϳ����������Ӧ����ʾ��
					ifchange=1;
				}
			}
			printf("����ɾ���ɹ�!�������������......\n");
			getch();
		}
		else
		{
			printf("����δɾ���������������......\n");
			getch();
		}
	}
	else
	{

		printf("������Ҫɾ����ѧ��ѧ��:\n");		//������ʾʹ��������ɾ����ѧ����ţ�	����M22Ҫ���޸�
		scanf("%s",id);								//��ȡ�û������ѧ��
		for(i=0;i<MaxStu;i++)						//ѭ���Ƚ�
		{
			if(strcmp(sp->students[i].id,id)==0)	//ʹ��strcmp�����ҵ��û���Ҫɾ����ѧ��
			{										//ѧ����ű�����10λ�����Ҷ�������	����M22Ҫ���޸�
				int xuanzhe;						//����xuanzhe���ں����ж�����ѡ������
				printf("\t��ȷ��Ҫɾ������������?\n");									//����Ƿ�ȷ��ɾ������ʾ���		
				printf("\t��(1)\t��(0)\n");			//����1���ǣ�����0�����û�������������ɾ��
				scanf("%d",&xuanzhe);				//�����û���ѡ��
				if(xuanzhe)							//�����жϣ����ѡ��Ϊ1ʱ
				{
					sp->exist[i]=0;					//����ѧ�ŵ�exist[i]=0��ɾ�����������Ҳ���ǽ���ѧ�Ÿ��±��ѧ����Ϣ��ϵͳ������λ�ø�Ϊ������
					strcpy(sp->students[i].id,"-1");
					strcpy(sp->students[i].name,"-1");
					sp->students[i].sex=-1;
					sp->students[i].birth=-1;
					strcpy(sp->students[i].tel,"-1");
					sp->students[i].ifsign=0;
					flag=1;	
					ifchange=1;
					break;							//�ҵ���ѧ�ž�����ѭ�������ٲ��Ҵ�ѧ��
				}
				else
				{
					flag=0;							//û���ҵ���ѧ��ʱ����flag��ֵΪ0
				}
			}
		}	
		if(flag==1)									//�ҵ��û������ѧ��ʱ
		{
			sp->n--;								//���ɹ�ɾ���û������ѧ��ѧ����ѧ������1
			printf("ɾ���ɹ������������......");	//���ɾ���ɹ�����ʾ��ʹ�û��˽��Լ��Ƿ���ɲ���
			getch();								//��ͣ������ʾ��ʾ

			return 0;								//���в����ɹ�������0��	����M21Ҫ���޸�
		}
		else if(flag==-1)
		{
			printf("��ѧ��ѧ�Ų����ڣ���鿴ѧ���Ƿ�������������֮������޸�,\n����������ز˵�......\n");//���ѧ�Ų����ڵ���ʾ��������ʾ�û��������ݻ�����ѧ������
			getch();

			return -24;								//���������󣬻�����ı���������в����ڣ���������-24��	����M22Ҫ���޸�
		}
		else										//�û�����ɾ��ʱ
		{
			printf("��������������˵�......\n");	//������ز˵�����ʾ
			getch();								//��ͣ������ʾ��ʾ

			return -3;								//�û���������ɾ��������-3��	����M21Ҫ���޸�
		}
	}
}

int _3_update(struct Stu_Proj *sp) {
	if(sp==NULL){     //M132
		printf("\n\t\t�����ݣ��޷�����");
		printf("\n\t\t���������......");
		getch(); 
		sp->status=0;
		return 0;
	}
	if(sp->n==0){
		printf("\n\t\t���ݣ��޷�����");
		printf("\n\t\t���������......");
		getch(); 
		sp->status=0;
		return 0;
	}
    int i,temp,t,age;
   // char id[20];
    temp=0;
    char id[16] = {'\0'};  //M07 û�ж���ֲ�����id[16]
    char name[20],gender[10],tel[20];
    printf("\n\t\t������Ҫ����ѧ�����ݵ�ѧ��:");
    scanf("%s", id);
    for (i = 0; i < MaxStu; i++)
        if (strcmp(sp->students[i].id, id) == 0) {
            do{
            printf("\n\t\t������Ҫ����Ϊ��ֵ�Ĵ��ţ�");//M125
            printf("\n\t\t1��ѧ��\n\t\t2������\n\t\t3���Ա�\n\t\t4����������\n\t\t5���绰\n\t\t\n\t\t0���˳�");//M110
            	temp=getch()-'0';
            	if(temp==1){
            		int n;
            		printf("\n\t\t��������ѧ��");
            		do{
    						scanf("%s",id);
							t=id_check(id);
						  }while(t==2);
    					if(t==0){
    					printf("\t\t������ֹ�ɹ�");
    					printf("\n\t\t���������......");
						getch();
						break;
						}
    				for (n = 0; n < MaxStu; n++)
        			if(strcmp(sp->students[i].id,id)==0){
            		printf("\n\t\tѧ�����ݴ��ڣ���ȷ��������ȷ");
            		printf("\n\t\t���������......");
            		getch();
            		break;
        			}
        			if(n==MaxStu){
        			strcpy(sp->students[i].id,id);
					printf("\n\t\t�����ɹ�");
					}
            }
            	if(temp==2){
            		printf("\n\t\t������������");
            		do{
    					scanf("%s",name);
    					t=name_check(name);
					  }while(t==2);
					if(t==0){
						printf("\t\t������ֹ�ɹ�");
    					printf("\n\t\t���������......");
						getch();
						break; 
						}
					strcpy(sp->students[i].name,name);
					printf("\n\t\t�����ɹ�");
            }
            	if(temp==3){
            		printf("\n\t\t���������Ա�");
            		    do{
    						scanf("%s",gender);
							t=gender_check(gender);
						  }while(t==2);
    					if(t==0){
    					printf("\t\t������ֹ�ɹ�");
    					printf("\n\t\t���������......");
						getch();
						break; 
					sp->students[i].sex=sex_gender(gender);
					printf("\n\t\t�����ɹ�");
						}
            }
            	if(temp==4){
            		printf("\n\t\t�������µĳ�������");
						do{
    						scanf("%d",&age);
							t=age_check(age);
						  }while(t==2);
    					if(t==0){
    						printf("\t\t������ֹ�ɹ�");
    						printf("\n\t\t���������......");
							getch();
							break; 
			}
						sp->students[i].birth=age;  
						printf("\n\t\t�����ɹ�");     
					     }
            	if(temp==5){
            			printf("\n\t\t�������µ绰");
            			do{
    						scanf("%s",tel);
    						t=tel_check(tel);
						}while(t==2);
					if(t==0){                   //����0������ 
							printf("\t\t������ֹ�ɹ�");
    						printf("\n\t\t���������......");
							getch();
							break; 
			}
						strcpy(sp->students[i].tel,tel);
						printf("\n\t\t�����ɹ�");  
			}
			}while(temp!=0);
			break; 
        }
    if (i == MaxStu)
        printf("\n\t\t�޴�ѧ�����ݣ���У���Ƿ��и�ѧ��");
    printf("\n\t\t���������......");
    getch();
    sp->status=0;
    return 0;
}

int _4_search(struct Stu_Proj *sp)						//��ѯ�������������ܣ���ʾѧ����Ϣ�б�	����M04Ҫ���޸� 
{
	int i,j;									//�������i��ѭ��ʱʹ��
	int count=0;
	static int flag=0;
	system("cls");
	if(sp==NULL)								//���н�׳���жϣ�	����M32Ҫ���޸�
	{
		
		printf("ϵͳ��ʼ��ʧ�ܣ��������-1������ϵ����Ա�������!\n����������ز˵�......\n");			//�������spΪ��ʱ�Ĵ�����ʾ
		getch();								//��ͣ������ʾ��ʾ

		return -1;								//����spΪ�գ�����-1	����M32Ҫ���޸�		
	}
	if(sp->n==0)								//����M20Ҫ���޸�	����M21Ҫ���޸�
	{
		menu1(sp);
		for(j=0;j<10;j++)
		{
			menu2();
		}
		menu3();
		printf("δ�ҵ�ѧ�����ݣ�������������ѧ�����ݺ���в鿴!\n�������ѡ����......\n");			//���ѧ����Ϊ0ʱ����ͼ�޸ĵĴ�����ʾ

		return -2;								//ѧ����Ϊ0������-2��	����M20Ҫ���޸�	����M21Ҫ���޸�
	}
	if(sp->n<10)
	{
		menu1(sp);
		for(i=0;i<MaxStu;i++)
		{
			if(sp->exist[i]==1)						//��ѭ��������ѧ����Ϣ�����existԪ�ص���1��˵��ѧ������
			{
				printf("��");
				if(i==updown)
				{
					printf("��");
				}
				else
				{
					printf("  ");
				}
				if(ifselect==1&&sp->students[i].ifsign==1)
				{
					printf("*");
				}
				else
				{
					printf(" ");
				}
				printf("%d\t",i+1);
				if(hide_i==0)
				{
					printf("%s\t",sp->students[i].id);
				}
				if(hide_n==0)
				{
					printf("%s\t",sp->students[i].name);
				}
				if(hide_s==0)
				{
					if(sp->students[i].sex==-1)
					{
						printf("<��>\t");
					}
					else
					{
						if(sp->students[i].sex==0)
						{
							printf(" ��\t");
						}
						else
						{
							printf(" Ů\t");
						}
					}
				}
				if(hide_v==0)
				{
					if(sp->students[i].birth==-1)
					{
						printf("<��>\t");						
					}
					else
					{
						printf(" %d\t",2019-(sp->students[i].birth)/10000);
					}
				}
				if(hide_b==0)
				{
					if(sp->students[i].birth==-1)
					{
						printf("<��>\t   ");
					}
					else
					{
						printf("%02d��%02d��   ",((sp->students[i].birth)%10000)/100,(sp->students[i].birth)%100);					
					}
				}
				if(hide_t==0)
				{
					if(strcmp(sp->students[i].tel,"-1")==0)
					{
						printf("<��>\t\t    ");
					}
					else
					{
						printf("%s\t    ",sp->students[i].tel);
					}
				}
				printf("��");
				printf("\n");
			}
		}
		for(i=0;i<10-sp->n;i++)
		{
			menu2();
		}
		menu3();
	}
	else
	{
		menu1(sp);
		for(i=(leftright-1)*10;count<10;i++)		//����ϵͳ��������ڵ�ѧ��
		{
			if(sp->exist[i]==1)						//��ѭ��������ѧ����Ϣ�����existԪ�ص���1��˵��ѧ������
			{
				printf("��");
				if(i%10==updown)
				{
					printf("��");
				}
				else
				{
					printf("  ");
				}
				if(ifselect==1&&sp->students[i].ifsign==1)
				{
					printf("*");
				}
				else
				{
					printf(" ");
				}
				printf("%d\t",i+1);
				if(hide_i==0)
				{
					printf("%s\t",sp->students[i].id);
				}
				if(hide_n==0)
				{
					printf("%s\t",sp->students[i].name);
				}
				if(hide_s==0)
				{
					if(sp->students[i].sex==-1)
					{
						printf("<��>\t");
					}
					else
					{
						if(sp->students[i].sex==0)
						{
							printf(" ��\t");
						}
						else
						{
							printf(" Ů\t");
						}
					}
				}
				if(hide_v==0)
				{
					if(sp->students[i].birth==-1)
					{
						printf("<��>\t");						
					}
					else
					{
						printf(" %d\t",2019-(sp->students[i].birth)/10000);
					}
				}
				if(hide_b==0)
				{
					if(sp->students[i].birth==-1)
					{
						printf("<��>\t   ");
					}
					else
					{
						printf("%02d��%02d��   ",((sp->students[i].birth)%10000)/100,(sp->students[i].birth)%100);					
					}
				}
				if(hide_t==0)
				{
					if(strcmp(sp->students[i].tel,"-1")==0)
					{
						printf("<��>\t\t    ");
					}
					else
					{
						printf("%s\t    ",sp->students[i].tel);
					}
				}
				printf("��");
				printf("\n");
				
			}
			count++;
		}
		i=MaxStu-1;	
		if(count!=10)
		{
			flag=1;
		}
		if(flag==0)
		{
			for(j=0;j<10-(sp->n);j++)
			{
				menu2();
			}
		}
		else
		{
			for(j=0;j<10-count;j++)
			{
				menu2();
			}
		}
		menu3();
	}
	/*
	printf("\n\t������ѧ����Ϣ�������������......\n");								//����û��ѿɲ鿴����ѧ����Ϣ��ʾ
	getch();									//��ͣ������ʾ��ʾ
	*/
	return 0;									//���в����ɹ�������0��	����M32Ҫ���޸�
}

int _5_save(struct Stu_Proj *sp) {
	if(sp==NULL)
	return -1;
    FILE *fp;
    fp = fopen("Data", "wb");
    fwrite(sp, sizeof(*sp), 1, fp);    //M12 �����ڴ�ռ����
    fclose(fp);
    printf("\n\t\t--����ɹ�--......");
    printf("\n\t\t���������......");
    getch();
    sp->status=0;
    return 0;
}

int _6_load(struct Stu_Proj *sp) {
    FILE *fp;
    if ((fp = fopen("Data", "rb")) != NULL)
        printf("\n\t\t--�ɹ������ļ�--");
    else {
        printf("\n\t\t--����ʧ��--");
        printf("\n\t\t���������ļ��Ƿ����");
    }
    fread(sp, sizeof(*sp), 1, fp);
    fclose(fp);
    printf("\t\t���������......");
    getch();
    sp->status=0;
    return 0;
}

struct Stu_Proj * _7_init(){
	int i;	
	struct Stu_Proj* sp;
	//sp=malloc(sizeof sp); //����
	sp=(struct Stu_Proj *) malloc(sizeof(struct Stu_Proj));//����malloc������̬����ռ�
	sp->n=0;
	for(i=0;i<MaxStu;i++){         //M121
			sp->exist[i]=0;
			strcpy(sp->students[i].id,"-1");//Ĭ��ѧ��Ϊ-1��M107
			strcpy(sp->students[i].name,"-1" );//Ĭ������Ϊ-1,M107
			sp->students[i].sex=-1; //Ĭ���Ա�-1,M107
			sp->students[i].birth=-1; //Ĭ������-1��M107
			strcpy(sp->students[i].tel,"-1");//Ĭ���ֻ����룺-1��M107
	}
	printf("���������......");
	getch();
	sp->status=0;
	return sp;
}
//}
//M05 main()������}��λ�ñ�Ǵ���ɾȥ��һ�㡣

//���뷽��
void I_come() {

	int i;
	char MyId[12];
	char MyKey[12];
	while(1) {
		system("cls");
		printf("\n\n");
		printf("\t\t\t��¼ϵͳ(*^_^*)\n");
		printf("\t\t   �����ߣ�BigSea �汾��V3.0 \n");
		printf("\t\t\t�ʺ�:");
		scanf("%s",MyId);
		printf("\t\t\t����:");

		for(i=0; i<12; i++) {
			MyKey[i]=getch();
			if(MyKey[i]=='\r')break;
			printf("*");
		}
		MyKey[i]='\0';

		printf("\n");
		if(strcmp(MyId,"root") == 0 && strcmp(MyKey,"123456") == 0 ) {
			printf("\t\t   ����ɹ�!(��?����)");
			getch();
			return ;
		} else {
			printf("\t\t��¼ʧ��,�ʺŻ��������!�����ˣ�����");
			getch();
		}
	}
}
void format(){//��ʽ��
int i;
 FILE *fp;
        //system("ERASE /F DATA.dat"); 
        remove("Data");
        if ((fp = fopen("Data", "rb")) == NULL)
            printf("\n\t\t��ʽ��ϵͳ�ɹ�");
        else
            printf("\n\t\t��ʽ��ϵͳʧ��");
        printf("\n\t\t���������......");
        getch();
}

int id_check(char *id){ //M122 ѧ�ż�� ,���Ϸ���1�������Ϸ���0��
int i;
	if(strcmp(id,"0")==0)//M120��M123��M112 
		return 0;
	if(strlen(id)>10){
		printf("\t\t�����д�,ѧ�ű���Ϊ10λ����,����������");
		return 2;
		}
	for(i=0;i<10;i++)
		if(!(id[i]>='0' && id[i]<='9'))
		{
		printf("\t\t�����д�ѧ�ű���Ϊ10λ����,����������");
		return 2;
			}
	return 1; 
}

int age_check(int age){ //������ ,���Ϸ���1�������Ϸ���0��
	int i;
	if(age==0)
		return 0;		
	if((age>99999999||age<10000000))
		{
		printf("\t\t�����д���������Ϊ������,����������");
		return 2;
			}
	return 1; 
}

int name_check(char *name){//������� 
	if(strcmp(name,"0")==0) //��������֡�ֻ��һ����ֵ��0������0��� 
	return 0;
	if(strlen(name)>16) {
	printf("\n\t\t������ҪС��16λ");
	printf("\n\t\t����������");             //������ҪС��16λ�����򷵻�2�� 
	return 2;
}
	return 1;                        //��������������1�� 
	
}
int gender_check(char *tmp1){
	if(strcmp(tmp1,"-1")==0)//�Ա�Ϊ-1���������� 
	return 0;
	if(!((strcmp(tmp1,"0")==0)||(strcmp(tmp1,"��")==0)||(strcmp(tmp1,"male")==0)||(strcmp(tmp1,"m")==0)||(strcmp(tmp1,"1")==0)||(strcmp(tmp1,"Ů")==0)||(strcmp(tmp1,"female")==0)||(strcmp(tmp1,"f")==0)))
	{
		printf("\t\t�Ա�����Ϊ���У�m��male��0������Ů��f��female��1�����������룩"); 
	return 2;
	}
	return 1;

}
int sex_gender(char *tmp1){    //�Ա�תΪ0��1. 
		if((strcmp(tmp1,"0")==0)||(strcmp(tmp1,"��")==0)||(strcmp(tmp1,"male")==0)||(strcmp(tmp1,"m")==0)) 
			return 0;
		if((strcmp(tmp1,"1")==0)||(strcmp(tmp1,"Ů")==0)||(strcmp(tmp1,"female")==0)||(strcmp(tmp1,"f")==0) )
		    return 1;
return 2;
}
char* gender(int a){//�Ա��� 
	char gender[10];
	char *p;
	p=gender;
	if(a==0)
	strcpy(gender, "��");
	else if(a==1)
	strcpy(gender, "Ů");
	else
	strcpy(gender, "δ֪");
	return p; 
}
int tel_check(char *tel){//���ɵ绰��Ϣ 
	if(strlen(tel)>16) { //M118
		printf("\n\t\t�绰��ҪС��16λ");
		printf("\n\t\t����������"); 
		return 2;
	}
	if(strcmp(tel,"0")==0) { //������绰��ֻ��һ����ֵ��0������2��� 
		return 0;
	}
	return 1;
}
//M129
char* name_tra(char *name){
	if(strcmp(name,"-1")==0)
	strcpy(name,"δ֪");
	return name; 
}

char* tel_tra(char *tel){
	if(strcmp(tel,"-1")==0)
	strcpy(tel,"δ֪");
	return tel; 
}

int birth_tra(int birth){
	if(birth==-1)
	return -1; 
	else
	return 0; 
}
static int equals(struct Stu *s1,struct Stu *s2){//M108���ǱȽ�����ָ���ѧ���Ƿ���ͬ
	if(strcmp(s1->id, s2->id)==0)
		return 0;
	else
		return 1;
}
int outport(struct Stu_Proj *sp){
	FILE *fp;
	int i;
	char filename[100];
	printf("\n\t\t������Ҫ�������ļ���(������Ϊ�ı��ļ�):");
	scanf("%s",filename);
	strcat(filename,".txt");
	if((fp=fopen(filename,"wt"))==NULL)
	{
	    printf("\n\t\t����ʧ��,�����������......\n");
		return -1;
	}
	
	fprintf(fp,"%s\t","NO");
	fprintf(fp,"%s\t\t","ѧ��");
	fprintf(fp,"%s\t","����");
	fprintf(fp,"%s\t","�Ա�");
	fprintf(fp,"%s\t","����");
	fprintf(fp,"%s\t\t","����");
	fprintf(fp,"%s\t","�ֻ�����");
	fprintf(fp,"\n");
		for(i=0;i<MaxStu;i++)
	{
	    if(sp->exist[i]!=0)
		{
			fprintf(fp,"%d\t",i+1);
			fprintf(fp,"%s\t",sp->students[i].id);
			fprintf(fp,"%s\t",sp->students[i].name);
			if(sp->students[i].sex==-1)
			{
				fprintf(fp,"%s\t","<��>");
			}
			else
			{
				if(sp->students[i].sex==0)
				{
					fprintf(fp,"%s\t","��");
				}
				else
				{
					fprintf(fp,"%s\t","Ů");
				}
			}
			if(sp->students[i].birth==-1)
			{
				fprintf(fp,"%s\t","<��>");
				fprintf(fp,"%s\t\t","<��>");
			}
			else
			{
				fprintf(fp,"%d\t",2019-(sp->students[i].birth)/10000);
				fprintf(fp,"%02d��%02d��\t\t",((sp->students[i].birth)%10000)/100,(sp->students[i].birth)%100);
			}
			if(strcmp(sp->students[i].tel,"-1")==0)
			{
				fprintf(fp,"%s\t","<��>");
			}
			else
			{
				fprintf(fp,"%s\t",sp->students[i].tel);
			}
			fprintf(fp,"\n");
		}
	}
	fclose(fp);
	printf("\n\t\t�����ɹ��������������......");
	getch();
	return 0;
}

void menu1(struct Stu_Proj *sp)
{
	static int ztflag=0;
	static int msflag=0;

	if(key=='l')
	{
		ztflag=0;
	}
	else if(key=='x')
	{
		ztflag=1;
	}
	else if(key=='c')
	{
		ztflag=2;
	}
	else if(key=='d')
	{
		ztflag=3;
	}
	else if(key=='u')
	{
		ztflag=4;
	}
	else if(key=='p')
	{
		ztflag=5;
	}
	else if(key=='o')
	{
		ztflag=6;
	}
	else if(key=='r')
	{
		ztflag=7;
	}
	else if(key=='y')
	{
		ztflag=8;
	}
	else if(key=='g')
	{
		ztflag=9;
	}
	else if(key=='h')
	{
		ztflag=10;
	}
	else if(key=='e')
	{
		if(msflag==0)
		{
			msflag=1;
		}
		else
		{
			msflag=0;
		}
	}
	
	if(ifselect==0)
	{
		msflag=0;
		ztflag=0;
	}
	else if(ifselect=1)
	{
		msflag=1;
		ztflag=11;
	}

	printf("\t\t\t���     ѧ����Ϣ����ϵͳ3.0     ���\n");
	printf("״̬:%s    ",zhuangtai[ztflag]);
	printf("ģʽ:%s    ",moshi[msflag]);
	printf("ѧ����:%d\n",(sp->n));
	printf("������������������������������������������������������������������������������\n");
	//printf("��   NO\t    ѧ��I\t����N\t�Ա�S\t����V\t����B\t   �ֻ�����T\t    ��\n");
	printf("��");
	printf("   NO\t");
	if(hide_i==0)
	{
		printf("    ѧ��I\t");
	}
	if(hide_n==0)
	{
		printf("����N\t");
	}
	if(hide_s==0)
	{
		printf("�Ա�S\t");
	}
	if(hide_v==0)
	{
		printf("����V\t");
	}
	if(hide_b==0)
	{
		printf("����B\t   ");
	}
	if(hide_t==0)
	{
		printf("�ֻ�����T\t    ");
	}
	printf("��\n");
}

void menu2()
{
	printf("��                                                                          ��\n");
}

void menu3()
{
	printf("�� ��һ���� ��һ����    ǰһҳ��    ��һҳ��                          %d/%dҳ ��\n",leftright,pagefm);
	printf("������������������������������������������������������������������������������\n");
	printf("�� ��ʾ:%s\n",tishi[1]);	//!
	printf("������������������������������������������������������������������������������\n");
	printf("��������ʾ: �˳�X  ����F  ����C  ɾ��D  ����U  ����O  �����ĵ�H  ��\n");
	printf("��                                                                          ��\n");
	printf("����ʾ������ѡ��:ѧ��I ����N �Ա�S ����V ����B �ֻ�����T (����˫���������) ��\n");
	printf("��       ѡ��E  ȷ��M  ȫѡA  ��ѡZ  ��ԭ����Y   �ָ���������G  ��\n");
	printf("������������������������������������������������������������������������������\n");
}

void developer(){
	system("color 0d");
	printf("\t\t��ǰ�汾ΪV3.0���ڲ�汾V4.5\n");
	printf("\t\t���������Email��mintimate215@gmail.com\n");
	printf("\t\t\t��л����ʹ��\n"); 
	printf("\t\t�ر���л(��?����)��С����Сǿ"); 
	printf("\n\t\t�����������......");
	getch();
	system("color 0b");
} 
