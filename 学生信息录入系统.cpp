#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include <conio.h>
#include<Windows.h>
#define MaxStu 100                                                //M03定义结构体后缺少;
#define Data DATA.dat
typedef struct Stu {
    char id[16];//学号
    char name[16];//姓名
    int sex;//性别
    int birth;//年龄
    char tel[16];//手机号码
    int ifsign;
}Stu;                                                             //M02定义结构体后多了“;”
struct Stu_Proj {
    struct Stu students[MaxStu];//学生数组，最大值是MaxStu，采用散列表的形式存储；
    int exist[MaxStu];//学生是否存在，如果exist[4]=1，说明students[4]的学生是存在的；如果exist[5]=0，说明students[5]的学生是不存在的（被删除了，或还没有录入）；
    int n;//当前学生数；
    int status;//状态 
};                                                                //M01定义结构体后缺少；
int _0_save(struct Stu_Proj *sp); //退出函数 

int first_start(struct Stu_Proj *sp);//初始化结构体方法 

int _1_enter(struct Stu_Proj *sp);//方法1：输入学生数据 

int _2_del(struct Stu_Proj *sp);//方法2：删除学生数据 

int _3_update(struct Stu_Proj *sp);//方法3：更新（更改）学生数据 

int _4_search(struct Stu_Proj *sp);//方法4：查找学生信息 

int _5_save(struct Stu_Proj *sp);//方法5：保存学生信息 

int _6_load(struct Stu_Proj *sp);//方法6：加载学生信息文件 

struct Stu_Proj * _7_init();//方法7：格式化学生学习 

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
char zhuangtai[12][10]={"浏览","退出","新增","删除","更改","导入","导出","排序","还原","清空","帮助","标记中"};
char moshi[2][10]={"非选择","选择"};
const char tishi[2][128]={
	"操作成功，请选择其它命令。",
	"操作取消，请选择其它命令。",
};
//密码函数：
void I_come();
//学号校验
int id_check(char *id);
//姓名检查
int name_check(char *name);
//性别检查
int gender_check(char *gender); 
//年龄检查
int age_check(int age); 
//性别代号检测
char* gender(int a); 
//格式化 
void format(); 
//M126
int sex_gender(char *tmp1);
//电话检测 
int tel_check(char *tel); 
static int equals(struct Stu *s1,struct Stu *s2);
char* tel_tra(char *tel);
char* name_tra(char *name);
int birth_tra(int birth);
int outport(struct Stu_Proj *sp);
//状态查询
void status_tra(int n); 
void developer();
int main()        //M13 主函数类型错误
{

    //struct Stu_Proj *sp = (struct Stu_Proj *) malloc(sizeof(struct Stu_Proj));//错误4 只定义未分配空间

    struct Stu_Proj *sp = (struct Stu_Proj *) malloc(sizeof(struct Stu_Proj));
    char c;
    int a;
    int i;
    char question; 
    FILE *fp;
	system("color 0c");    
    I_come();
	 
if ((fp = fopen("Data", "rb")) != NULL)
        printf("\n\t\t--当前已有学生数据存档--");
        fclose(fp);
    printf("\n\t\t是否读取上次学生数据文件（读档）？");
    printf("\n\t\t[y]为读档，[n]为不读档且格式化系统：");
    do {
        a = getch();
        if (a == 'y') {
            first_start(sp);
            break;
        } else if (a == 'n') {
            printf("\n\t\t已选择不读档并初始化系统");
        	format();
			sp=_7_init();
            break;
        } else {
            printf("\n\t\t未知命令，请重新输入：");
        }
    } while (a != 'y' || a != 'n');
    system("color 0b");							//设置终端显示字体的颜色
	pagefz=1;                  //初始页数为一 
	if(sp->n%10==0)
	{
		pagefm=(sp->n)/10;    //页数 
	}
	else if(sp->n<10)
	{
		pagefm=1;
	}
	else
	{
		pagefm=(sp->n)/10+1;
	}
	
	do											//主循环，用来接收用户的输入,采用do-while格式，先执行，后判断
	{	/*每运行一次查询（4），打印一次菜单。接下来屏幕显示内容*/
		
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
		printf("\n请选择功能:\n");
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
				printf("数据有改动，您是否需要保存?(y/n)\n");
				question=getch();
				if(question=='n')
				{
					printf("改动的数据未保存!\n");
				}
				else
				{
					_5_save(sp);
				}
			}
			printf("感谢您的使用，按任意键退出......\n");
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
			printf("请充值VIP才可解锁排序功能。\n联系QQ:1009683012\n");
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
		case 72://上
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
		case 80://下
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
		case 75://左
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
		case 77://右
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
}//M05 main()方法的}，位置标记错误。添加到这一点。
int first_start(struct Stu_Proj *sp) {
    _6_load(sp);
    return 0;
}

int _0_save(struct Stu_Proj *sp){
	int a,t;
		printf("\n\t\t请确认是否要保存文件!\n");		
		printf("\t\t是(1)\t否(0)\n\t\t");				
		scanf("%d",&a);	
		if(a==0)					
		{
			printf("\n\t\t操作成功，按任意键退出系统......\n");
			t=-1;	
		}
		else if(a==1)
		{
			_5_save(sp);
			t=-1; 
		}
		else
		{
			printf("\n\t\t非法输入，默认保存文件并退出\n");
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
    printf("\n\t\t进入学生管理系统：");
    printf("\n\t\t请输入:\n\t\t 10位数字学号，输入0退出\n\t\t"); //M09 语法错误，使用printf打印“请输入”
    do{
    	scanf("%s",id);
		t=id_check(id);
	}while(t==2);
    if(t==0){
    	printf("\t\t操作终止成功");
    	printf("\n\t\t任意键继续......");
		getch();
		sp->status=0;
		return 0; 
	}
    for (i = 0; i < MaxStu; i++) {
        if(strcmp(sp->students[i].id,id)==0){
            printf("\n\t\t学生数据存在，请确保数据正确");
            printf("\n\t\t任意键继续......");
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
    printf("\t\t请输入姓名\n\t\t");
    do{
    	scanf("%s",name);
    	t1=name_check(name);
	}while(t1==2);
	if(t1==0){
		printf("\t\t操作终止成功");
    	printf("\n\t\t任意键继续......");
		getch();
		sp->status=0;
		return 0; 
	}
	strcpy((sp->students[i].name),name);
	strcpy((sp->students[i].id),id);
	sp->n++;
    printf("\t\t请输入性别（男，m，male，0），（女，f，female，1）,0为放弃并返回\n\t\t");
    do{
    	scanf("%s",gender);
		t=gender_check(gender);
	}while(t==2);
    if(t==0){
    	printf("\t\t操作终止成功");
    	printf("\n\t\t任意键继续......");
		getch();
		sp->status=0;
		return 0; 
	}
    sp->students[i].sex=sex_gender(gender);
    printf("\t\t请输入出生年月日\n\t\t");
    do{
    	scanf("%d",&birth);
		t=age_check(birth);
	}while(t==2);
    if(t==0){
    	printf("\t\t操作终止成功");
    	printf("\n\t\t任意键继续......");
		getch();
		sp->status=0;
		return 0; 
	}
	sp->students[i].birth=birth;
	printf("\t\t请输入16位以下电话，按0为退出\n\t\t");
    do{
    	scanf("%s",tel);
    	t1=tel_check(tel);
	}while(t1==2);
	if(t1==0){
		printf("\t\t操作终止成功");
    	printf("\n\t\t任意键继续......");
		getch();
		sp->status=0;
		return 0; 
	}
	strcpy(sp->students[i].tel,tel);
    printf("\t\t写入成功");
    printf("\n\t\t任意键继续......");
    getch();
	sp->status=0;        //M14 完成任意继续指令
    return 0;

}

int _2_del(struct Stu_Proj *sp)							//删除函数，函数功能：根据学号删除学生信息	根据M04要求修改
{
	int i,flag=-1;								//定义变量i，循环时使用，定义flag，且初始化为-1，在后面进行是否需要输出某些提示的判断
	char id[16],a;								//保存输入的学生学号
	if(sp==NULL)								//进行健壮性判断，	根据M20要求修改
	{
		printf("系统初始化失败，错误编码-1，请联系管理员解决问题!\n按任意键返回菜单......\n");			//输出参数sp为空时的错误提示
		getch();								//暂停程序显示提示

		return -1;								//参数sp为空，返回-1	根据M20要求修改		
	}
	if(sp->n==0)								//根据M20要求修改	根据M21要求修改
	{
		printf("未找到学生数据，请新增或载入学生数据后进行修改操作!\n按任意键返回菜单......\n");		//输出学生数为0时，试图修改的错误提示
		getch();	

		return -2;								//学生数为0，返回-2；	根据M20要求修改	根据M21要求修改
	}
	if(ifselect==1)
	{
		printf("当前处于批量删除状态，是否删除已标记数据?(y/n)\n");
		a=getch();
		if(a=='y')
		{
			for(i=0;i<MaxStu;i++)				//循环比较
			{
				if(sp->students[i].ifsign==1)
				{
					sp->exist[i]=0;				//将此学号的exist[i]=0，删除的意义就是也就是将此学号该下标的学生信息在系统中所处位置改为不存在
					strcpy(sp->students[i].id,"-1");
					strcpy(sp->students[i].name,"-1");
					sp->students[i].sex=-1;
					sp->students[i].birth=-1;
					strcpy(sp->students[i].tel,"-1");
					sp->students[i].ifsign=0;
					flag=1;						//并且将flag赋值为1，在后面判断出可以输出相应的提示语
					ifchange=1;
				}
			}
			printf("批量删除成功!，按任意键继续......\n");
			getch();
		}
		else
		{
			printf("数据未删除，按任意键继续......\n");
			getch();
		}
	}
	else
	{

		printf("请输入要删除的学生学号:\n");		//首先提示使用者输入删除的学生编号；	根据M22要求修改
		scanf("%s",id);								//获取用户输入的学号
		for(i=0;i<MaxStu;i++)						//循环比较
		{
			if(strcmp(sp->students[i].id,id)==0)	//使用strcmp函数找到用户想要删除的学号
			{										//学生编号必须是10位，并且都是数字	根据M22要求修改
				int xuanzhe;						//定义xuanzhe，在后面判断中起选择作用
				printf("\t您确定要删除此条数据吗?\n");									//输出是否确认删除的提示语句		
				printf("\t是(1)\t否(0)\n");			//输入1，是，输入0，否，用户可以主动放弃删除
				scanf("%d",&xuanzhe);				//输入用户的选择
				if(xuanzhe)							//进行判断，如果选择为1时
				{
					sp->exist[i]=0;					//将此学号的exist[i]=0，删除的意义就是也就是将此学号该下标的学生信息在系统中所处位置改为不存在
					strcpy(sp->students[i].id,"-1");
					strcpy(sp->students[i].name,"-1");
					sp->students[i].sex=-1;
					sp->students[i].birth=-1;
					strcpy(sp->students[i].tel,"-1");
					sp->students[i].ifsign=0;
					flag=1;	
					ifchange=1;
					break;							//找到此学号就跳出循环，不再查找此学号
				}
				else
				{
					flag=0;							//没有找到此学号时，将flag赋值为0
				}
			}
		}	
		if(flag==1)									//找到用户输入的学号时
		{
			sp->n--;								//当成功删除用户输入的学号学生后，学生数减1
			printf("删除成功，任意键继续......");	//输出删除成功的提示，使用户了解自己是否完成操作
			getch();								//暂停程序显示提示

			return 0;								//所有操作成功，返回0；	根据M21要求修改
		}
		else if(flag==-1)
		{
			printf("此学生学号不存在，请查看学号是否输入错误或新增之后进行修改,\n按任意键返回菜单......\n");//输出学号不存在的提示，并且提示用户载入数据或新增学生数据
			getch();

			return -24;								//如果输入错误，或输入的编号在数组中不存在，函数返回-24；	根据M22要求修改
		}
		else										//用户放弃删除时
		{
			printf("按任意键返回主菜单......\n");	//输出返回菜单的提示
			getch();								//暂停程序显示提示

			return -3;								//用户主动放弃删除，返回-3；	根据M21要求修改
		}
	}
}

int _3_update(struct Stu_Proj *sp) {
	if(sp==NULL){     //M132
		printf("\n\t\t无数据，无法更改");
		printf("\n\t\t任意键继续......");
		getch(); 
		sp->status=0;
		return 0;
	}
	if(sp->n==0){
		printf("\n\t\t数据，无法更改");
		printf("\n\t\t任意键继续......");
		getch(); 
		sp->status=0;
		return 0;
	}
    int i,temp,t,age;
   // char id[20];
    temp=0;
    char id[16] = {'\0'};  //M07 没有定义局部变量id[16]
    char name[20],gender[10],tel[20];
    printf("\n\t\t请输入要更改学生数据的学号:");
    scanf("%s", id);
    for (i = 0; i < MaxStu; i++)
        if (strcmp(sp->students[i].id, id) == 0) {
            do{
            printf("\n\t\t请输入要更改为的值的代号：");//M125
            printf("\n\t\t1、学号\n\t\t2、姓名\n\t\t3、性别\n\t\t4、出生日期\n\t\t5、电话\n\t\t\n\t\t0、退出");//M110
            	temp=getch()-'0';
            	if(temp==1){
            		int n;
            		printf("\n\t\t请输入新学号");
            		do{
    						scanf("%s",id);
							t=id_check(id);
						  }while(t==2);
    					if(t==0){
    					printf("\t\t操作终止成功");
    					printf("\n\t\t任意键继续......");
						getch();
						break;
						}
    				for (n = 0; n < MaxStu; n++)
        			if(strcmp(sp->students[i].id,id)==0){
            		printf("\n\t\t学生数据存在，请确保数据正确");
            		printf("\n\t\t任意键继续......");
            		getch();
            		break;
        			}
        			if(n==MaxStu){
        			strcpy(sp->students[i].id,id);
					printf("\n\t\t操作成功");
					}
            }
            	if(temp==2){
            		printf("\n\t\t请输入新姓名");
            		do{
    					scanf("%s",name);
    					t=name_check(name);
					  }while(t==2);
					if(t==0){
						printf("\t\t操作终止成功");
    					printf("\n\t\t任意键继续......");
						getch();
						break; 
						}
					strcpy(sp->students[i].name,name);
					printf("\n\t\t操作成功");
            }
            	if(temp==3){
            		printf("\n\t\t请输入新性别");
            		    do{
    						scanf("%s",gender);
							t=gender_check(gender);
						  }while(t==2);
    					if(t==0){
    					printf("\t\t操作终止成功");
    					printf("\n\t\t任意键继续......");
						getch();
						break; 
					sp->students[i].sex=sex_gender(gender);
					printf("\n\t\t操作成功");
						}
            }
            	if(temp==4){
            		printf("\n\t\t请输入新的出生日期");
						do{
    						scanf("%d",&age);
							t=age_check(age);
						  }while(t==2);
    					if(t==0){
    						printf("\t\t操作终止成功");
    						printf("\n\t\t任意键继续......");
							getch();
							break; 
			}
						sp->students[i].birth=age;  
						printf("\n\t\t操作成功");     
					     }
            	if(temp==5){
            			printf("\n\t\t请输入新电话");
            			do{
    						scanf("%s",tel);
    						t=tel_check(tel);
						}while(t==2);
					if(t==0){                   //输入0，返回 
							printf("\t\t操作终止成功");
    						printf("\n\t\t任意键继续......");
							getch();
							break; 
			}
						strcpy(sp->students[i].tel,tel);
						printf("\n\t\t操作成功");  
			}
			}while(temp!=0);
			break; 
        }
    if (i == MaxStu)
        printf("\n\t\t无此学生数据，请校验是否有该学生");
    printf("\n\t\t任意键继续......");
    getch();
    sp->status=0;
    return 0;
}

int _4_search(struct Stu_Proj *sp)						//查询函数，函数功能：显示学生信息列表	根据M04要求修改 
{
	int i,j;									//定义变量i，循环时使用
	int count=0;
	static int flag=0;
	system("cls");
	if(sp==NULL)								//进行健壮性判断，	根据M32要求修改
	{
		
		printf("系统初始化失败，错误编码-1，请联系管理员解决问题!\n按任意键返回菜单......\n");			//输出参数sp为空时的错误提示
		getch();								//暂停程序显示提示

		return -1;								//参数sp为空，返回-1	根据M32要求修改		
	}
	if(sp->n==0)								//根据M20要求修改	根据M21要求修改
	{
		menu1(sp);
		for(j=0;j<10;j++)
		{
			menu2();
		}
		menu3();
		printf("未找到学生数据，请新增或载入学生数据后进行查看!\n按任意键选择功能......\n");			//输出学生数为0时，试图修改的错误提示

		return -2;								//学生数为0，返回-2；	根据M20要求修改	根据M21要求修改
	}
	if(sp->n<10)
	{
		menu1(sp);
		for(i=0;i<MaxStu;i++)
		{
			if(sp->exist[i]==1)						//用循环语句输出学生信息，如果exist元素等于1，说明学生存在
			{
				printf("┆");
				if(i==updown)
				{
					printf("→");
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
						printf("<空>\t");
					}
					else
					{
						if(sp->students[i].sex==0)
						{
							printf(" 男\t");
						}
						else
						{
							printf(" 女\t");
						}
					}
				}
				if(hide_v==0)
				{
					if(sp->students[i].birth==-1)
					{
						printf("<空>\t");						
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
						printf("<空>\t   ");
					}
					else
					{
						printf("%02d月%02d日   ",((sp->students[i].birth)%10000)/100,(sp->students[i].birth)%100);					
					}
				}
				if(hide_t==0)
				{
					if(strcmp(sp->students[i].tel,"-1")==0)
					{
						printf("<空>\t\t    ");
					}
					else
					{
						printf("%s\t    ",sp->students[i].tel);
					}
				}
				printf("┆");
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
		for(i=(leftright-1)*10;count<10;i++)		//遍历系统，输出存在的学生
		{
			if(sp->exist[i]==1)						//用循环语句输出学生信息，如果exist元素等于1，说明学生存在
			{
				printf("┆");
				if(i%10==updown)
				{
					printf("→");
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
						printf("<空>\t");
					}
					else
					{
						if(sp->students[i].sex==0)
						{
							printf(" 男\t");
						}
						else
						{
							printf(" 女\t");
						}
					}
				}
				if(hide_v==0)
				{
					if(sp->students[i].birth==-1)
					{
						printf("<空>\t");						
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
						printf("<空>\t   ");
					}
					else
					{
						printf("%02d月%02d日   ",((sp->students[i].birth)%10000)/100,(sp->students[i].birth)%100);					
					}
				}
				if(hide_t==0)
				{
					if(strcmp(sp->students[i].tel,"-1")==0)
					{
						printf("<空>\t\t    ");
					}
					else
					{
						printf("%s\t    ",sp->students[i].tel);
					}
				}
				printf("┆");
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
	printf("\n\t以上是学生信息，按任意键继续......\n");								//输出用户已可查看所有学生信息提示
	getch();									//暂停程序显示提示
	*/
	return 0;									//所有操作成功，返回0；	根据M32要求修改
}

int _5_save(struct Stu_Proj *sp) {
	if(sp==NULL)
	return -1;
    FILE *fp;
    fp = fopen("Data", "wb");
    fwrite(sp, sizeof(*sp), 1, fp);    //M12 申请内存空间错误
    fclose(fp);
    printf("\n\t\t--保存成功--......");
    printf("\n\t\t任意键继续......");
    getch();
    sp->status=0;
    return 0;
}

int _6_load(struct Stu_Proj *sp) {
    FILE *fp;
    if ((fp = fopen("Data", "rb")) != NULL)
        printf("\n\t\t--成功加载文件--");
    else {
        printf("\n\t\t--加载失败--");
        printf("\n\t\t请检查数据文件是否存在");
    }
    fread(sp, sizeof(*sp), 1, fp);
    fclose(fp);
    printf("\t\t任意键继续......");
    getch();
    sp->status=0;
    return 0;
}

struct Stu_Proj * _7_init(){
	int i;	
	struct Stu_Proj* sp;
	//sp=malloc(sizeof sp); //错误
	sp=(struct Stu_Proj *) malloc(sizeof(struct Stu_Proj));//采用malloc函数动态分配空间
	sp->n=0;
	for(i=0;i<MaxStu;i++){         //M121
			sp->exist[i]=0;
			strcpy(sp->students[i].id,"-1");//默认学号为-1，M107
			strcpy(sp->students[i].name,"-1" );//默认姓名为-1,M107
			sp->students[i].sex=-1; //默认性别-1,M107
			sp->students[i].birth=-1; //默认年龄-1，M107
			strcpy(sp->students[i].tel,"-1");//默认手机号码：-1，M107
	}
	printf("任意键继续......");
	getch();
	sp->status=0;
	return sp;
}
//}
//M05 main()方法的}，位置标记错误。删去这一点。

//密码方法
void I_come() {

	int i;
	char MyId[12];
	char MyKey[12];
	while(1) {
		system("cls");
		printf("\n\n");
		printf("\t\t\t登录系统(*^_^*)\n");
		printf("\t\t   开发者：BigSea 版本：V3.0 \n");
		printf("\t\t\t帐号:");
		scanf("%s",MyId);
		printf("\t\t\t密码:");

		for(i=0; i<12; i++) {
			MyKey[i]=getch();
			if(MyKey[i]=='\r')break;
			printf("*");
		}
		MyKey[i]='\0';

		printf("\n");
		if(strcmp(MyId,"root") == 0 && strcmp(MyKey,"123456") == 0 ) {
			printf("\t\t   登入成功!(●ˇ?ˇ●)");
			getch();
			return ;
		} else {
			printf("\t\t登录失败,帐号或密码错误!（＞人＜；）");
			getch();
		}
	}
}
void format(){//格式化
int i;
 FILE *fp;
        //system("ERASE /F DATA.dat"); 
        remove("Data");
        if ((fp = fopen("Data", "rb")) == NULL)
            printf("\n\t\t格式化系统成功");
        else
            printf("\n\t\t格式化系统失败");
        printf("\n\t\t任意键继续......");
        getch();
}

int id_check(char *id){ //M122 学号检查 ,符合返回1；不符合返回0；
int i;
	if(strcmp(id,"0")==0)//M120、M123、M112 
		return 0;
	if(strlen(id)>10){
		printf("\t\t输入有错,学号必须为10位数字,请重新输入");
		return 2;
		}
	for(i=0;i<10;i++)
		if(!(id[i]>='0' && id[i]<='9'))
		{
		printf("\t\t输入有错，学号必须为10位数字,请重新输入");
		return 2;
			}
	return 1; 
}

int age_check(int age){ //年龄检查 ,符合返回1；不符合返回0；
	int i;
	if(age==0)
		return 0;		
	if((age>99999999||age<10000000))
		{
		printf("\t\t输入有错，出生日期为年月日,请重新输入");
		return 2;
			}
	return 1; 
}

int name_check(char *name){//姓名检查 
	if(strcmp(name,"0")==0) //如果“名字”只有一个数值：0。返回0标记 
	return 0;
	if(strlen(name)>16) {
	printf("\n\t\t姓名需要小于16位");
	printf("\n\t\t请重新输入");             //名字需要小于16位，否则返回2； 
	return 2;
}
	return 1;                        //数据正常，返回1； 
	
}
int gender_check(char *tmp1){
	if(strcmp(tmp1,"-1")==0)//性别为-1，放弃输入 
	return 0;
	if(!((strcmp(tmp1,"0")==0)||(strcmp(tmp1,"男")==0)||(strcmp(tmp1,"male")==0)||(strcmp(tmp1,"m")==0)||(strcmp(tmp1,"1")==0)||(strcmp(tmp1,"女")==0)||(strcmp(tmp1,"female")==0)||(strcmp(tmp1,"f")==0)))
	{
		printf("\t\t性别输入为（男，m，male，0），（女，f，female，1）请重新输入）"); 
	return 2;
	}
	return 1;

}
int sex_gender(char *tmp1){    //性别转为0、1. 
		if((strcmp(tmp1,"0")==0)||(strcmp(tmp1,"男")==0)||(strcmp(tmp1,"male")==0)||(strcmp(tmp1,"m")==0)) 
			return 0;
		if((strcmp(tmp1,"1")==0)||(strcmp(tmp1,"女")==0)||(strcmp(tmp1,"female")==0)||(strcmp(tmp1,"f")==0) )
		    return 1;
return 2;
}
char* gender(int a){//性别翻译 
	char gender[10];
	char *p;
	p=gender;
	if(a==0)
	strcpy(gender, "男");
	else if(a==1)
	strcpy(gender, "女");
	else
	strcpy(gender, "未知");
	return p; 
}
int tel_check(char *tel){//生成电话信息 
	if(strlen(tel)>16) { //M118
		printf("\n\t\t电话需要小于16位");
		printf("\n\t\t请重新输入"); 
		return 2;
	}
	if(strcmp(tel,"0")==0) { //如果“电话”只有一个数值：0。返回2标记 
		return 0;
	}
	return 1;
}
//M129
char* name_tra(char *name){
	if(strcmp(name,"-1")==0)
	strcpy(name,"未知");
	return name; 
}

char* tel_tra(char *tel){
	if(strcmp(tel,"-1")==0)
	strcpy(tel,"未知");
	return tel; 
}

int birth_tra(int birth){
	if(birth==-1)
	return -1; 
	else
	return 0; 
}
static int equals(struct Stu *s1,struct Stu *s2){//M108这是比较两个指针的学号是否相同
	if(strcmp(s1->id, s2->id)==0)
		return 0;
	else
		return 1;
}
int outport(struct Stu_Proj *sp){
	FILE *fp;
	int i;
	char filename[100];
	printf("\n\t\t请输入要导出的文件名(导出的为文本文件):");
	scanf("%s",filename);
	strcat(filename,".txt");
	if((fp=fopen(filename,"wt"))==NULL)
	{
	    printf("\n\t\t导出失败,按任意键继续......\n");
		return -1;
	}
	
	fprintf(fp,"%s\t","NO");
	fprintf(fp,"%s\t\t","学号");
	fprintf(fp,"%s\t","姓名");
	fprintf(fp,"%s\t","性别");
	fprintf(fp,"%s\t","年龄");
	fprintf(fp,"%s\t\t","生日");
	fprintf(fp,"%s\t","手机号码");
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
				fprintf(fp,"%s\t","<空>");
			}
			else
			{
				if(sp->students[i].sex==0)
				{
					fprintf(fp,"%s\t","男");
				}
				else
				{
					fprintf(fp,"%s\t","女");
				}
			}
			if(sp->students[i].birth==-1)
			{
				fprintf(fp,"%s\t","<空>");
				fprintf(fp,"%s\t\t","<空>");
			}
			else
			{
				fprintf(fp,"%d\t",2019-(sp->students[i].birth)/10000);
				fprintf(fp,"%02d月%02d日\t\t",((sp->students[i].birth)%10000)/100,(sp->students[i].birth)%100);
			}
			if(strcmp(sp->students[i].tel,"-1")==0)
			{
				fprintf(fp,"%s\t","<空>");
			}
			else
			{
				fprintf(fp,"%s\t",sp->students[i].tel);
			}
			fprintf(fp,"\n");
		}
	}
	fclose(fp);
	printf("\n\t\t导出成功，按任意键继续......");
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

	printf("\t\t\t☆☆     学生信息管理系统3.0     ☆☆\n");
	printf("状态:%s    ",zhuangtai[ztflag]);
	printf("模式:%s    ",moshi[msflag]);
	printf("学生数:%d\n",(sp->n));
	printf("┌┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┐\n");
	//printf("┆   NO\t    学号I\t姓名N\t性别S\t年龄V\t生日B\t   手机号码T\t    ┆\n");
	printf("┆");
	printf("   NO\t");
	if(hide_i==0)
	{
		printf("    学号I\t");
	}
	if(hide_n==0)
	{
		printf("姓名N\t");
	}
	if(hide_s==0)
	{
		printf("性别S\t");
	}
	if(hide_v==0)
	{
		printf("年龄V\t");
	}
	if(hide_b==0)
	{
		printf("生日B\t   ");
	}
	if(hide_t==0)
	{
		printf("手机号码T\t    ");
	}
	printf("┆\n");
}

void menu2()
{
	printf("┆                                                                          ┆\n");
}

void menu3()
{
	printf("┆ 上一条↑ 下一条↓    前一页←    后一页→                          %d/%d页 ┆\n",leftright,pagefm);
	printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
	printf("┆ 提示:%s\n",tishi[1]);	//!
	printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
	printf("┆命令提示: 退出X  保存F  新增C  删除D  更新U  导出O  开发文档H  ┆\n");
	printf("┆                                                                          ┆\n");
	printf("┆显示隐藏列选项:学号I 姓名N 性别S 年龄V 生日B 手机号码T (键盘双击显隐类别) ┆\n");
	printf("┆       选择E  确认M  全选A  反选Z  还原参数Y   恢复出厂设置G  ┆\n");
	printf("├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤\n");
}

void developer(){
	system("color 0d");
	printf("\t\t当前版本为V3.0，内测版本V4.5\n");
	printf("\t\t如需帮助，Email：mintimate215@gmail.com\n");
	printf("\t\t\t感谢您的使用\n"); 
	printf("\t\t特别鸣谢(●ˇ?ˇ●)：小明、小强"); 
	printf("\n\t\t按任意键继续......");
	getch();
	system("color 0b");
} 
