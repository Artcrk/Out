#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <windows.h>

#define endl '\n'
#define Version 0.1
#define SetWhite SetConsoleTextAttribute(color,FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN);
#define SetSky SetConsoleTextAttribute(color,FOREGROUND_BLUE|FOREGROUND_INTENSITY|FOREGROUND_GREEN);
#define SetYellow SetConsoleTextAttribute(color,FOREGROUND_RED|FOREGROUND_INTENSITY|FOREGROUND_GREEN);
#define SetYellowN SetConsoleTextAttribute(color,FOREGROUND_RED|FOREGROUND_GREEN);
#define SetRed SetConsoleTextAttribute(color,FOREGROUND_RED|FOREGROUND_INTENSITY);
#define SetGreen SetConsoleTextAttribute(color,FOREGROUND_GREEN);
#define SetGreenW SetConsoleTextAttribute(color,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
int dayc[2000][5] = { 0 };//主体!
int cpytemp[5] = { 0 };
int MaxPtr = 0;
int Vu = floor(Version),Vd = Version*10.0;//因为给double预留太麻烦,于是我选择把它们拆开
HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);//颜色化输出权限
bool theAD = true;//广告哈哈(其实是公告

FILE* fptr = fopen("data.bat", "r");
FILE* flog = fopen("log.txt", "a");

enum Mode
{
	EXIT,
	SAVE,
	CHANGE,
	FIND
};
enum T_mode
{
	YEAR,
	MONTH,
	DAY,
	ALL
};
//数据初始化
bool init(FILE* p)//初始化
{
	memset(dayc, 0, sizeof(dayc));
	int temp = fread(dayc, 4, 10000, p);
	for (int i = 0;; i++)
	{
		if (dayc[i][0] == 0)
		{
			MaxPtr = i;
			break;
		}
	}
	if (temp> 0)
		return true;
	return false;
}
//特殊排序_仅选择排序,因为这个数组不好快速排序..(才疏学浅了)
void sorts()//排序,建议每次操作后都自动排序一次.
{
	int i, k, r;
	for (k = 0; k < 3; k++)//year,month,day
	{
		for (r = MaxPtr-1; r > 0; r--)
		{
			for (i = 0; i < r; i++)
			{
				if (dayc[i][k] > dayc[i + 1][k])
				{
					if (k == 0)
					{
						memmove(cpytemp, dayc[i], sizeof(cpytemp));
						memmove(dayc[i], dayc[i + 1], sizeof(cpytemp));
						memmove(dayc[i + 1], cpytemp, sizeof(cpytemp));
					}
					else if (k >= 1)
					{
						if (dayc[i][0] == dayc[i + 1][0])
						{
							if (k == 2)
							{
								if (dayc[i][1] == dayc[i + 1][1])
								{

									memmove(cpytemp, dayc[i], sizeof(cpytemp));
									memmove(dayc[i], dayc[i + 1], sizeof(cpytemp));
									memmove(dayc[i + 1], cpytemp, sizeof(cpytemp));
								}
							}
							else
							{

								memmove(cpytemp, dayc[i], sizeof(cpytemp));
								memmove(dayc[i], dayc[i + 1], sizeof(cpytemp));
								memmove(dayc[i + 1], cpytemp, sizeof(cpytemp));
							}
						}
					}
				}
			}
		}
	}
}
//主界面初始化
void initCover()
{
	system("cls");
	SetSky
	printf("------------------------------------------------\n");
	printf("            1.存入           2.修改\n");
	printf("            3.查询           0.退出\n");
	printf("------------------------------------------------\n");
	if (theAD)
	{
		SetYellow
		printf("\n------------------------------ #公告# ----------------------------\n");
		printf("  本公告在每次启动后仅会出现一次~\n");
		printf("  本版本为 #v_%01d.%01d\n", Vu, Vd);
		printf("  该版本暂时没有实现删除的功能,只提供了3个基本功能(其实是懒得做哈哈)\n");
		printf("  请注意一定要按流程退出!不然可能会导致数据无法被成功存下!\n");
		printf("  预计下个版本会做一个检视全部数据的功能,敬请期待吧!\n");
		printf("  Oh对了,如果是第一次使用,请无视一开始跳出的\"初始化数据失败\"\n");
		printf("                                                    --By Artcrk\n");
		printf("                                                    --2025/3/11\n");
		printf("------------------------------ #公告# ----------------------------\n");
		
		theAD = false;
	}
	SetWhite
	printf("\n请输入一个整数,对标选项>:");
}
//我想对自己说的话...
void randput()
{
	
	int chosen = 0;
	chosen = rand()%5;
	std::cout << "To Myself : ";
	SetSky
	switch (chosen)
	{
	case 0:
		std::cout << "坚定本心,永远不要停下求知的脚步!";
		break;
	case 1:
		std::cout << "每一次coding都是一次演奏,愿你永远都是那个优雅的钢琴师";
		break;
	case 2:
		std::cout << "再叹世人悲,苦寒生芳梅";
		break;
	case 3:
		std::cout << "歪歪,今天的coding之旅勉勉强强呦,下一次来找我的时候要记得带上更闪耀的成果!";
		break;
	case 4:
		std::cout << "愿你意识运转流光如影,永远相信自己配得上这顶博学之帽";
	}
	SetWhite
}
//修改
void change(int &year,int &month, int &day, int &AC,int &Rate)
{
	for (int d = 0; d < MaxPtr; d++)
	{
		if (dayc[d][0] == year && dayc[d][1] == month && dayc[d][2] == day)
		{
			dayc[d][3] = AC;
			dayc[d][4] = Rate;
			printf("成功修改数据!\n");
			system("pause");
			return;
		}
	}
	printf("无法找到 %04d/%02d/%02d 的数据(是不是忘记加上了?)\n", year, month, day);
	system("pause");

}
//寻找,杂糅了4种查询模式
void finds(int year = -1, int month = -1, int day = -1)
{
	int i = 0,sumd_AC = 0,sumd_Rate = 0,j=0;
	bool addmode = false;
	if (year == month && month == day && year == -1)
	{
		sumd_AC = 0, sumd_Rate = 0;
		for (i = 0; i < MaxPtr; i++)
		{
			sumd_AC += dayc[i][3];
			sumd_Rate += dayc[i][4];
		}
		printf("全部数据 || 共计AC: %d || 共计Rate: %d ||\n", sumd_AC, sumd_Rate);
		if (sumd_Rate == 0)
		{
			printf("什么?!居然一场Rate都没打吗!\n");
		}
		else if (sumd_Rate > 5)
		{
			printf("哇!是竞赛大佬!\n");
		}
		else
		{
			printf("这个战绩其实也不错了~\n");
		}
		system("pause");
		return;
	}
	else if(month == -1 && day == -1)
	{
		sumd_AC = 0, sumd_Rate = 0;
		for (i = 0; i < MaxPtr; i++)
		{
			if (dayc[i][0] == year)
			{
				for (j = i; dayc[j][0] == year&& j < MaxPtr; j++)
				{
					sumd_AC += dayc[j][3];
					sumd_Rate += dayc[j][4];
				}
				printf(" 寻找到了 %d年 的全部数据>:\n",year);
				printf("__%04d年__|| 共计AC: %d || 共计Rate: %d ||\n", year, sumd_AC, sumd_Rate);
				if (sumd_Rate == 0)
				{
					printf("什么?!居然一场Rate都没打吗!\n");
				}
				else if (sumd_Rate > 5)
				{
					printf("哇!是竞赛大佬!\n");
				}
				else
				{
					printf("这个战绩其实也不错了~\n");
				}
				system("pause");
				return;
			}
			else
			{
				printf("无法找到 %04d年 的数据(是不是忘记加上了?)\n", year);
				system("pause");
				return;
			}
		}
	}
	else if (day == -1)
	{
		sumd_AC = 0, sumd_Rate = 0;
		for (i = 0; i < MaxPtr; i++)
		{
			if (dayc[i][0] == year && dayc[i][1] == month)
			{
				for (j = i; dayc[j][0] == year && dayc[j][1] == month&&j<MaxPtr; j++)
				{
					sumd_AC += dayc[j][3];
					sumd_Rate += dayc[j][4];
				}
				printf(" 寻找到了%d/%d的全部数据>:\n",year,month);
				printf("__%04d/%02d__|| 共计AC: %d || 共计Rate: %d ||\n", year,month,sumd_AC,sumd_Rate);
				if (sumd_Rate == 0)
				{
					printf("什么?!居然一场Rate都没打吗!\n");
				}
				else if (sumd_Rate > 5)
				{
					printf("哇!是竞赛大佬!\n");
				}
				else
				{
					printf("这个战绩其实也不错了~\n");
				}
				system("pause");
				return;
			}
			else
			{
				printf("无法找到 %04d/%02d 的数据(是不是忘记加上了?)\n", year, month);
				system("pause");
				return;
			}
		}
	}
	else
	{
		for (i = 0; i < MaxPtr; i++)
		{
			if (dayc[i][0] == year && dayc[i][1] == month && dayc[i][2] == day)
			{
				printf(" 寻找到了目标>:\n");
				printf("__%04d/%02d/%02d__|| AC: %d || Rate: %d ||\n", year, month, day, dayc[i][3], dayc[i][4]);
				if (dayc[i][3] < 1)
				{
					printf("今天是摸鱼去了吗?!(鱼:我是无辜的\n");
				}
				else if(dayc[i][3] >10)
				{
					printf("今天居然AC了这么多题!很nice捏~注意劳逸结合呀\n");
				}
				else
				{
					printf("中规中矩捏,也很好啦\n");
				}
				system("pause");
				return;
			}
		}
		printf("无法找到 %04d/%02d/%02d 的数据(是不是忘记加上了?)\n", dayc[i][0], dayc[i][1], dayc[i][2]);
		system("pause");
	}
}
//存档
void savedata()
{
	fptr = fopen("data.bat", "w");
	for (int i = 0; i < MaxPtr; i++)
	{
		fwrite(dayc[i],sizeof(int),5,fptr);
	}
}

int main()
{
	//进入主界面前的准备操作
	srand(time(NULL));
	int year, month, day, c_time = 0, mode;
	int t_year, t_month, t_day, t_AC, t_Rate, t_mode;
	char logs[59] = { 0 };
	time_t nowadays = time(&nowadays);//获取相对秒数
	struct tm* nows = localtime(&nowadays);//将相对秒数转化为实际日期
	if (nows == NULL)
		{
			SetRed
				std::cout << "**获取系统时间失败!请手动输入当前日期!**" << endl;
			SetWhite
				std::cout << "请输入年份\n>:";
			std::cin >> year;
			std::cout << "请输入月份\n>:";
			std::cin >> month;
			std::cout << "请输入日期\n>:";
			std::cin >> day;
		}
	else
		{
			SetRed
				std::cout << "**成功获取系统日期!**" << endl;
			year = 1900 + nows->tm_year, month = 1 + nows->tm_mon, day = nows->tm_mday;
			c_time = nows->tm_hour;
			SetYellow
				printf("当前日期为___%d/%d/%d___\n\n", year, month, day);
			SetSky
				if (c_time > 2 && c_time < 8)
				{
					printf("凌晨好,Artcrk!\n");
				}
				else if (c_time >= 8 && c_time < 11)
				{
					printf("早上好,Artcrk!\n");
				}
				else if (c_time > 10 && c_time < 15)
				{
					printf("中午好,Artcrk!\n");
				}
				else if (c_time > 14 && c_time < 19)
				{
					printf("下午好,Artcrk!\n");
				}
				else
				{
					printf("晚上好,Artcrk!\n");
				}
			SetRed
				std::cout << "\n";
		}
	sprintf(logs,"%04d/%02d/%02d %02d:%02d opened the exe,Version_%01d.%01d\n",year,month,day,nows->tm_hour,nows->tm_min,Vu,Vd);
	fputs(logs,flog);
	if (init(fptr))
		{
			std::cout << "**成功初始化数据!**" << endl;
		}
	else
		{
			std::cout << "**初始化数据失败!若已有写入记录,请检查文件data.bat.**" << endl;
		}
	SetSky
	std::cout << "\n准备进入主页面" << endl;
	system("pause");
	while (true)//循环主体
	{
	start:
		initCover();
		std::cin >> mode;
		SetYellow
		switch (mode)
		{
		case EXIT:
			randput();
			savedata();
			Sleep(666);
			return 0;
		case SAVE:
			SetWhite
			printf("增添操作,请依次输入年月日,AC数,Rate数,用空格分隔\n");
			printf("----/--/--|AC|Rate\n");
			scanf("%d %d %d %d %d", &dayc[MaxPtr][0],&dayc[MaxPtr][1], &dayc[MaxPtr][2], &dayc[MaxPtr][3], &dayc[MaxPtr][4]);
			MaxPtr++;
			sorts();
			break;
		case CHANGE:
			SetGreen
			printf("修改操作,请依次输入年月日,AC数,Rate数,用空格分隔\n注意此操作将会修改对应年月份的数据为你目前写入的数据\n");
			printf("----/--/--|AC|Rate\n");
			scanf("%d %d %d %d %d",&t_year,&t_month,&t_day,&t_AC,&t_Rate);
			change(t_year, t_month, t_day, t_AC, t_Rate);
			sorts();
			break;
		case FIND:
			printf("查询操作,请选择的的查询方式:\n");
			SetGreenW
			printf("------------------------------------------------------\n");
			printf("            0.查找某一年的总和 1.查找某一月的总和\n");
			printf("            2.查找某一天的具体数值 3.查找全部\n");
			printf("------------------------------------------------------\n");
			SetYellow
		start_F:
			printf("\n请输入一个整数,对标选项>:");
			std::cin >> t_mode;
			switch(t_mode)
			{
			case YEAR:
				printf("查询一年的总和,请输入年份.\n");
				printf("----/\n");
				scanf("%d", &t_year);
				finds(t_year);
				break;
			case MONTH:
				printf("查询某个月的总和,请输入年,月.用空格分隔\n");
				printf("----/--/\n");
				scanf("%d %d", &t_year,&t_month);
				finds(t_year, t_month);
				break;
			case DAY:
				printf("查询一天的具体数据,请输入年,月,日.用空格分隔\n");
				printf("----/--/--/\n");
				scanf("%d %d %d", &t_year, &t_month,&t_day);
				finds(t_year, t_month, t_day);
				break;
			case ALL:
				finds();
				break;
			default:
				printf("emmm误输入?请重新输入(bug多请勿测试QAQ)\n");
				system("pause");
				goto start_F;
			}
			break;
		default:
			printf("emmm误输入?请重新输入(bug多请勿测试QAQ)\n");
			system("pause");
			goto start;
		}
	}
	return 0;
}
