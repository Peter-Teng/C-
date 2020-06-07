#include<iostream>
#include<graphics.h>
#include <conio.h>
#include"Minesweeper.h"
#include<ctime>
#include<cstdlib>
#include<windows.h>
#include<cstdio> 
#include<string.h>
#include<stdio.h>

#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")//音频文件接口

using namespace std;

//函数列表
void ini_image();
//加载所需图片

void paintManu();
//绘制主菜单

void paintMap();
//绘制地图

inline bool mouseOperation_for_manu();
//菜单鼠标操作的内联函数

inline bool mouseOperation_for_game();
//游戏内鼠标操作的内联函数

void mineCreating(int,int);
//创造雷（接受鼠标第一次点击的位置，保证第一次点击踩到雷）

void calculateSurrounding();
//计算每个方格附近有多少个雷

void expandBlock(int, int);
//方格扩展算法

bool winning();
//判断是否胜利

void re_ini();
//重玩时，将所有全局变量重新初始化

void lose_pic();
//输掉时揭晓答案


//游戏内图片列表
IMAGE block_normal;
IMAGE block_chosen;
IMAGE wrongmine;
IMAGE flagged;
IMAGE mineFig;
IMAGE number[9];
//IMAGE number2;
//IMAGE number3;
//IMAGE number4;
//IMAGE number5;
//IMAGE number6;
//IMAGE number7;
//IMAGE number8;

//菜单图片列表
IMAGE manu;
IMAGE very_easy_chosen;
IMAGE very_easy_normal;
IMAGE casual_normal;
IMAGE casual_chosen;
IMAGE hard_normal;
IMAGE hard_chosen;
IMAGE Fortune_test_normal;
IMAGE Fortune_test_chosen;

//获取鼠标信息及与鼠标操作的有关参数
MOUSEMSG mouse;
bool mines_are_set = false;
//确认雷是否已经布置好

//long long starttime, currenttime;
//TCHAR t[500] = {};
//bool ifstart = false;

int replay = 0;
//设置重玩按钮


//确认游戏难度的参数——雷的个数
int Mine_numbers;

//生成方块的全局对象
block* mapptr[13][10];
block map[13][10];

int _x = 6, _y = 5;
//鼠标上次的x坐标和y坐标的储存（为了实现选中block颜色不同而定义）

int main()
{	
	
	//播放音乐
	mciSendString(L"open ./BGM.mp3 alias bgm", 0, 0, 0);
	mciSendString(L"play bgm repeat", 0, 0, 0);


	//首先加载游戏所需的所有图片
	ini_image();
	
	

	srand(time(0));
	//设置随机生成地雷的随机种子

	do
	{
		paintManu();
		//生成菜单

		while (1)
		{
			if (mouseOperation_for_manu()) break;
		}
		//菜单的鼠标操作

		do
		{
			paintMap();
			//绘制地图


			//处理鼠标信息，在游戏未结束一直执行。
			while (1)
			{
				if (mouseOperation_for_game())
				{
					closegraph();

					re_ini();

					break;
				}
				//游戏的鼠标操作
			}
		} while (replay == 1);
	} while (replay == 2);
	//制造循环以制作出点对话框能按要求重玩或
	//返回菜单的效果


	return 0;
}

void ini_image()
//加载所有的图片
{
	//菜单相关图片
	loadimage(&manu, L"manu.jpg", 400, 400);
	loadimage(&very_easy_normal, L"Very Easy Normal.jpg", 300, 40);
	loadimage(&very_easy_chosen, L"Very Easy Chosen.jpg", 300, 40);
	loadimage(&casual_normal, L"casual normal.jpg", 300, 40);
	loadimage(&casual_chosen, L"casual chosen.jpg", 300, 40);
	loadimage(&hard_normal, L"hard normal.jpg", 300, 40);
	loadimage(&hard_chosen, L"hard chosen.jpg", 300, 40);
	loadimage(&Fortune_test_normal, L"fortune test normal.jpg", 300, 40);
	loadimage(&Fortune_test_chosen, L"fortune test chosen.jpg", 300, 40);


	//正式游戏相关图片
	loadimage(&block_chosen, L"block chosen.jpg", 40, 40);
	loadimage(&block_normal, L"block normal.jpg", 40, 40);
	loadimage(&wrongmine, L"wrong_mine.jpg", 40, 40);
	loadimage(&flagged, L"flag.jpg", 40, 40);
	loadimage(&mineFig, L"mine.jpg", 40, 40);
	loadimage(&number[0], L"empty.jpg", 40, 40);
	loadimage(&number[1], L"number 1.jpg", 40, 40);
	loadimage(&number[2], L"number 2.jpg", 40, 40);
	loadimage(&number[3], L"number 3.jpg", 40, 40);
	loadimage(&number[4], L"number 4.jpg", 40, 40);
	loadimage(&number[5], L"number 5.jpg", 40, 40);
	loadimage(&number[6], L"number 6.jpg", 40, 40);
	loadimage(&number[7], L"number 7.jpg", 40, 40);
	loadimage(&number[8], L"number 8.jpg", 40, 40);
}

void paintManu()
{
	initgraph(400, 400);
	putimage(0, 0, &manu);
	putimage(50, 170, &very_easy_normal);
	putimage(50, 220, &casual_normal);
	putimage(50, 270, &hard_normal);
	putimage(50, 320, &Fortune_test_normal);
	//画出菜单

	return;
}

bool mouseOperation_for_manu()
{
	FlushMouseMsgBuffer();
	mouse = GetMouseMsg();
	//获取鼠标各种信息
	if ((mouse.x >= 50 && mouse.x <= 350) && (mouse.y >= 170 && mouse.y <= 210))
		putimage(50, 170, &very_easy_chosen);
	else
		putimage(50, 170, &very_easy_normal);

	if ((mouse.x >= 50 && mouse.x <= 350) && (mouse.y >= 220 && mouse.y <= 260))
		putimage(50, 220, &casual_chosen);
	else 
		putimage(50, 220, &casual_normal);

	if ((mouse.x >= 50 && mouse.x <= 350) && (mouse.y >= 270 && mouse.y <= 310))
		putimage(50, 270, &hard_chosen);
	else
		putimage(50, 270, &hard_normal);

	if ((mouse.x >= 50 && mouse.x <= 350) && (mouse.y >= 320 && mouse.y <= 360))
		putimage(50, 320, &Fortune_test_chosen);
	else
		putimage(50, 320, &Fortune_test_normal);

	//如果鼠标在对应的难度图片上面，就将其设置为对应的高亮图片版本

	if (mouse.mkLButton)
	{
		if ((mouse.x >= 50 && mouse.x<=350) && (mouse.y >= 170 && mouse.y <= 210))
		{
			Mine_numbers = 5;
			return true;
		}


		else if ((mouse.x >= 50 && mouse.x <= 350) && (mouse.y >= 220 && mouse.y <= 260))
		{
			Mine_numbers = 15;
			return true;
		}


		else if ((mouse.x >= 50 && mouse.x <= 350) && (mouse.y >= 270 && mouse.y <= 310))
		{
			Mine_numbers = 30;
			return true;
		}

		else if ((mouse.x >= 50 && mouse.x <= 350) && (mouse.y >= 320 && mouse.y <= 360))
		{
			Mine_numbers = 128;
			return true;
		}


		//确认难度以及雷的个数

		return false;
	}
}

void paintMap()
//绘制地图的函数
{
   closegraph();
   initgraph(520, 400);
   //生成程序520*400的框框

   for (int x = 0; x < 520; x += 40)
	   for (int y = 0; y < 400; y += 40)
	   {
		   putimage(x, y, &block_normal);
	   }
   //生成框框矩阵

   for (int x = 0; x < 13; x++)
	   for (int y = 0; y < 10; y++)
		   mapptr[x][y] = &map[x][y];
   //将所有的block类指针指向对应的block类对象

   FlushMouseMsgBuffer();
   //清空鼠标缓存，防止重新游戏时的时候，鼠标缓存没有清空从而
   //造成的误触
}

void mineCreating(int clickx,int clicky)
//生成地雷的函数
//接收两个int类的参数，这两个参数是玩家第一次点击时
//所对应的方格的横纵坐标
//生成雷的时候保证跳过这个方格
//这样玩家第一次就不会踩到雷了
{
	int tmp_x, tmp_y;
	int i = 0;
	//标记现在已经生成雷的个数
	while (i < Mine_numbers)
	{
		tmp_x = rand() % 13; tmp_y = rand() % 10;
		if (mapptr[tmp_x][tmp_y]->isMine() || (tmp_x == clickx && tmp_y == clicky)) i--;
		//当当前方块已经是雷的时候
		//跳过这个方块
		else
		{
			mapptr[tmp_x][tmp_y] = new mine(tmp_x, tmp_y);
		}
		i++;
	}
	mines_are_set = true;
	//标记雷已经成功生成
}

void calculateSurrounding()
//计算方块附近雷的个数
{

	//愚蠢的一个方法，应该能找到更好的方案，参见
	//展开方块的expandBlock（）函数
	for (int x = 0; x < 13; x++)
		for (int y = 0; y < 10; y++)
		{
			if (x == 0)
			{
				if (y == 0)
				{
					if (mapptr[x + 1][y]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x + 1][y + 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x][y + 1]->isMine() == true) mapptr[x][y]->minesaround++;
				}
				else if (y == 9)
				{
					if (mapptr[x + 1][y]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x + 1][y - 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x][y - 1]->isMine() == true) mapptr[x][y]->minesaround++;
				}
				else
				{
					if (mapptr[x + 1][y]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x + 1][y - 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x][y - 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x][y + 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x + 1][y + 1]->isMine() == true) mapptr[x][y]->minesaround++;
				}
			}
			else if (x < 12)
			{
				if (y == 0)
				{
					if (mapptr[x + 1][y]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x - 1][y]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x + 1][y + 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x - 1][y + 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x][y + 1]->isMine() == true) mapptr[x][y]->minesaround++;
				}
				else if (y == 9)
				{
					if (mapptr[x + 1][y]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x - 1][y]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x + 1][y - 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x - 1][y - 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x][y - 1]->isMine() == true) mapptr[x][y]->minesaround++;
				}
				else
				{
					if (mapptr[x - 1][y - 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x][y - 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x + 1][y - 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x - 1][y]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x + 1][y]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x - 1][y + 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x][y + 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x + 1][y + 1]->isMine() == true) mapptr[x][y]->minesaround++;
				}
			}
			else if (x == 12) 
			{
				if (y == 0)
				{
					if (mapptr[x - 1][y]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x - 1][y + 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x][y + 1]->isMine() == true) mapptr[x][y]->minesaround++;
				}
				else if (y == 9)
				{
					if (mapptr[x - 1][y]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x - 1][y - 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x][y - 1]->isMine() == true) mapptr[x][y]->minesaround++;
				}
				else
				{
					if (mapptr[x - 1][y]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x - 1][y - 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x][y - 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x][y + 1]->isMine() == true) mapptr[x][y]->minesaround++;
					if (mapptr[x - 1][y + 1]->isMine() == true) mapptr[x][y]->minesaround++;
				}
			}
		}
}

void expandBlock(int x, int y)
//左键打开方格的函数
{
	mapptr[x][y]->setchecked(true);
	putimage(x * 40, y * 40, &number[mapptr[x][y]->minesaround]);
	if (mapptr[x][y]->minesaround == 0)
	//当前方格检测到无雷时的自动扩展算法
	{
		for (int tmp_x = x - 1; tmp_x <= x + 1; tmp_x++)
			for (int tmp_y = y - 1; tmp_y <= y + 1; tmp_y++)
			{
				if (tmp_x == -1 || tmp_x == 13 || tmp_y == -1 || tmp_y == 10) continue;
				//方便的越界检查
				//对应上面的愚蠢办法，这个方法较为聪明
				if (mapptr[tmp_x][tmp_y]->ifchecked() == false)
				{
					//假如当前方块未被翻开则执行该操作
					if (mapptr[tmp_x][tmp_y]->minesaround != 0)
						//当前方块下附近雷数不为零时，直接展开
					{
						mapptr[tmp_x][tmp_y]->setchecked(true);
						putimage(tmp_x * 40, tmp_y * 40, &number[mapptr[tmp_x][tmp_y]->minesaround]);
					}
					else
					{
						expandBlock(tmp_x, tmp_y);
					}
					//当前方块下为零时，递归扩展周围方格  DFS

				}
				else continue;
			}
	}
}

bool winning()
//判断游戏是否胜利的函数
//玩家每次按下鼠标时都会判断一遍
{
	bool flag = true;
	for(int x=0;x<13;x++)
		for (int y = 0; y < 10; y++)
		{
			if (mapptr[x][y]->isMine() == false && mapptr[x][y]->ifchecked() == false)
				flag = false;
			//假如有非雷方块未展开，那么就没赢
		}
	return flag;
}

bool mouseOperation_for_game()
{
	mouse = GetMouseMsg();
	//获取鼠标各种信息


	int x = mouse.x / 40, y = mouse.y / 40;

	if ((_x >= 0 && _x < 13 && _y >= 0 && _y < 10) && (x >= 0 && x < 13 && y >= 0 && y < 10))
	{
		if (mapptr[x][y]->ifchecked() == true || mapptr[x][y]->getflag() == true);
		//鼠标选中的方块高亮
		else putimage(x * 40, y * 40, &block_chosen);


		if ((x != _x || y != _y))
			//当鼠标对应的方块的横纵坐标改变时
			//高亮的方块移动鼠标后的恢复
		{
			if (mapptr[_x][_y]->getflag() == true || mapptr[_x][_y]->ifchecked() == true);
			else
			{
				putimage(_x * 40, _y * 40, &block_normal);
			}
			_x = x;
			_y = y;
		}



		if (mouse.uMsg == WM_RBUTTONDOWN)
			//鼠标右键插旗
		{
			if (mapptr[x][y]->getflag() == false && mapptr[x][y]->ifchecked() == false)
				//对为插旗的方块插旗子
			{
				mapptr[x][y]->setflag(true);
				putimage(x * 40, y * 40, &flagged);
			}
			else if (mapptr[x][y]->getflag() == true && mapptr[x][y]->ifchecked() == false)
				//假如该方格已经被插旗了，那么拔旗子
			{
				mapptr[x][y]->setflag(false);
				putimage(x * 40, y * 40, &block_normal);
			}
		}

		if (mouse.uMsg == WM_LBUTTONDOWN)
			//鼠标左键排雷操作
		{
			{if (mines_are_set == false) { mineCreating(x, y); calculateSurrounding(); }}
			//左键第一次点击的时候便能够生成地雷，并且保证第一次不会踩到雷

			if (mapptr[x][y]->getflag() == true);
			//鼠标点击已经被插旗的方块时，啥都不做

			else
			{
				if (mapptr[x][y]->isMine() == true)
					//踩到雷时，游戏结束
				{
					putimage(x * 40, y * 40, &mineFig);
					lose_pic();
					FlushMouseMsgBuffer();
					//游戏结束，清空鼠标缓存
					replay = MessageBoxA(NULL, "哎呀，踩到雷了（嘤嘤嘤）\n （按下确认键重玩，按下取消键返回菜单）", "失败", 1);
					//出示游戏结束对话框，获取对话框参数

					return true;
				}
				else
				{
					if (mapptr[x][y]->ifchecked() == false)
						expandBlock(x, y);
					//如果不是雷，则翻开该方块
				}

				if (winning())
				{
					FlushMouseMsgBuffer();
					//胜利后清空鼠标缓存
					replay = MessageBoxA(NULL, "恭喜你，你赢了！\n (按下确认键重玩，按下取消键返回菜单)", "胜利", 1);
					//出示游戏胜利对话框，获取对话框参数，了解玩家是否重玩
					return true;
				}
			}
		}
	}
	return false;
}

void re_ini()
//将全局变量map及指针集mapptr重新初始化
{
	for(int x=0;x<13;x++)
		for (int y = 0; y < 10; y++)
		{
			if (mapptr[x][y]->isMine() == true)
			{
				delete mapptr[x][y];
				//删除所有雷对象
				mapptr[x][y] = &map[x][y];
				//将指针重新指回地图数组
			}
			mapptr[x][y]->setchecked(false);
			//将所有方块设置成未翻开
			mapptr[x][y]->setflag(false);
			//将所有方块设置成未插旗
			mapptr[x][y]->minesaround = 0;
			//将所有方块设置成周围无雷
		}

	mines_are_set = false;
	//重新初始化，将雷是否安置的参数设置为“雷未安置”

	return;
}

void lose_pic()
//输掉了揭晓雷在哪里
{
	for (int x = 0; x < 13; x++)
		for (int y = 0; y < 10; y++)
		{
			if (mapptr[x][y]->isMine() == true && mapptr[x][y]->ifchecked() == false && mapptr[x][y]->getflag() == false)
				putimage(x * 40, y * 40, &mineFig);

			if (mapptr[x][y]->isMine() == false && mapptr[x][y]->getflag() == true)
				putimage(x * 40, y * 40, &wrongmine);
		}
	return;
}

