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
#pragma comment(lib,"winmm.lib")//��Ƶ�ļ��ӿ�

using namespace std;

//�����б�
void ini_image();
//��������ͼƬ

void paintManu();
//�������˵�

void paintMap();
//���Ƶ�ͼ

inline bool mouseOperation_for_manu();
//�˵�����������������

inline bool mouseOperation_for_game();
//��Ϸ������������������

void mineCreating(int,int);
//�����ף���������һ�ε����λ�ã���֤��һ�ε���ȵ��ף�

void calculateSurrounding();
//����ÿ�����񸽽��ж��ٸ���

void expandBlock(int, int);
//������չ�㷨

bool winning();
//�ж��Ƿ�ʤ��

void re_ini();
//����ʱ��������ȫ�ֱ������³�ʼ��

void lose_pic();
//���ʱ������


//��Ϸ��ͼƬ�б�
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

//�˵�ͼƬ�б�
IMAGE manu;
IMAGE very_easy_chosen;
IMAGE very_easy_normal;
IMAGE casual_normal;
IMAGE casual_chosen;
IMAGE hard_normal;
IMAGE hard_chosen;
IMAGE Fortune_test_normal;
IMAGE Fortune_test_chosen;

//��ȡ�����Ϣ�������������йز���
MOUSEMSG mouse;
bool mines_are_set = false;
//ȷ�����Ƿ��Ѿ����ú�

//long long starttime, currenttime;
//TCHAR t[500] = {};
//bool ifstart = false;

int replay = 0;
//�������水ť


//ȷ����Ϸ�ѶȵĲ��������׵ĸ���
int Mine_numbers;

//���ɷ����ȫ�ֶ���
block* mapptr[13][10];
block map[13][10];

int _x = 6, _y = 5;
//����ϴε�x�����y����Ĵ��棨Ϊ��ʵ��ѡ��block��ɫ��ͬ�����壩

int main()
{	
	
	//��������
	mciSendString(L"open ./BGM.mp3 alias bgm", 0, 0, 0);
	mciSendString(L"play bgm repeat", 0, 0, 0);


	//���ȼ�����Ϸ���������ͼƬ
	ini_image();
	
	

	srand(time(0));
	//����������ɵ��׵��������

	do
	{
		paintManu();
		//���ɲ˵�

		while (1)
		{
			if (mouseOperation_for_manu()) break;
		}
		//�˵���������

		do
		{
			paintMap();
			//���Ƶ�ͼ


			//���������Ϣ������Ϸδ����һֱִ�С�
			while (1)
			{
				if (mouseOperation_for_game())
				{
					closegraph();

					re_ini();

					break;
				}
				//��Ϸ��������
			}
		} while (replay == 1);
	} while (replay == 2);
	//����ѭ������������Ի����ܰ�Ҫ�������
	//���ز˵���Ч��


	return 0;
}

void ini_image()
//�������е�ͼƬ
{
	//�˵����ͼƬ
	loadimage(&manu, L"manu.jpg", 400, 400);
	loadimage(&very_easy_normal, L"Very Easy Normal.jpg", 300, 40);
	loadimage(&very_easy_chosen, L"Very Easy Chosen.jpg", 300, 40);
	loadimage(&casual_normal, L"casual normal.jpg", 300, 40);
	loadimage(&casual_chosen, L"casual chosen.jpg", 300, 40);
	loadimage(&hard_normal, L"hard normal.jpg", 300, 40);
	loadimage(&hard_chosen, L"hard chosen.jpg", 300, 40);
	loadimage(&Fortune_test_normal, L"fortune test normal.jpg", 300, 40);
	loadimage(&Fortune_test_chosen, L"fortune test chosen.jpg", 300, 40);


	//��ʽ��Ϸ���ͼƬ
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
	//�����˵�

	return;
}

bool mouseOperation_for_manu()
{
	FlushMouseMsgBuffer();
	mouse = GetMouseMsg();
	//��ȡ��������Ϣ
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

	//�������ڶ�Ӧ���Ѷ�ͼƬ���棬�ͽ�������Ϊ��Ӧ�ĸ���ͼƬ�汾

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


		//ȷ���Ѷ��Լ��׵ĸ���

		return false;
	}
}

void paintMap()
//���Ƶ�ͼ�ĺ���
{
   closegraph();
   initgraph(520, 400);
   //���ɳ���520*400�Ŀ��

   for (int x = 0; x < 520; x += 40)
	   for (int y = 0; y < 400; y += 40)
	   {
		   putimage(x, y, &block_normal);
	   }
   //���ɿ�����

   for (int x = 0; x < 13; x++)
	   for (int y = 0; y < 10; y++)
		   mapptr[x][y] = &map[x][y];
   //�����е�block��ָ��ָ���Ӧ��block�����

   FlushMouseMsgBuffer();
   //�����껺�棬��ֹ������Ϸʱ��ʱ����껺��û����մӶ�
   //��ɵ���
}

void mineCreating(int clickx,int clicky)
//���ɵ��׵ĺ���
//��������int��Ĳ�������������������ҵ�һ�ε��ʱ
//����Ӧ�ķ���ĺ�������
//�����׵�ʱ��֤�����������
//������ҵ�һ�ξͲ���ȵ�����
{
	int tmp_x, tmp_y;
	int i = 0;
	//��������Ѿ������׵ĸ���
	while (i < Mine_numbers)
	{
		tmp_x = rand() % 13; tmp_y = rand() % 10;
		if (mapptr[tmp_x][tmp_y]->isMine() || (tmp_x == clickx && tmp_y == clicky)) i--;
		//����ǰ�����Ѿ����׵�ʱ��
		//�����������
		else
		{
			mapptr[tmp_x][tmp_y] = new mine(tmp_x, tmp_y);
		}
		i++;
	}
	mines_are_set = true;
	//������Ѿ��ɹ�����
}

void calculateSurrounding()
//���㷽�鸽���׵ĸ���
{

	//�޴���һ��������Ӧ�����ҵ����õķ������μ�
	//չ�������expandBlock��������
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
//����򿪷���ĺ���
{
	mapptr[x][y]->setchecked(true);
	putimage(x * 40, y * 40, &number[mapptr[x][y]->minesaround]);
	if (mapptr[x][y]->minesaround == 0)
	//��ǰ�����⵽����ʱ���Զ���չ�㷨
	{
		for (int tmp_x = x - 1; tmp_x <= x + 1; tmp_x++)
			for (int tmp_y = y - 1; tmp_y <= y + 1; tmp_y++)
			{
				if (tmp_x == -1 || tmp_x == 13 || tmp_y == -1 || tmp_y == 10) continue;
				//�����Խ����
				//��Ӧ������޴��취�����������Ϊ����
				if (mapptr[tmp_x][tmp_y]->ifchecked() == false)
				{
					//���統ǰ����δ��������ִ�иò���
					if (mapptr[tmp_x][tmp_y]->minesaround != 0)
						//��ǰ�����¸���������Ϊ��ʱ��ֱ��չ��
					{
						mapptr[tmp_x][tmp_y]->setchecked(true);
						putimage(tmp_x * 40, tmp_y * 40, &number[mapptr[tmp_x][tmp_y]->minesaround]);
					}
					else
					{
						expandBlock(tmp_x, tmp_y);
					}
					//��ǰ������Ϊ��ʱ���ݹ���չ��Χ����  DFS

				}
				else continue;
			}
	}
}

bool winning()
//�ж���Ϸ�Ƿ�ʤ���ĺ���
//���ÿ�ΰ������ʱ�����ж�һ��
{
	bool flag = true;
	for(int x=0;x<13;x++)
		for (int y = 0; y < 10; y++)
		{
			if (mapptr[x][y]->isMine() == false && mapptr[x][y]->ifchecked() == false)
				flag = false;
			//�����з��׷���δչ������ô��ûӮ
		}
	return flag;
}

bool mouseOperation_for_game()
{
	mouse = GetMouseMsg();
	//��ȡ��������Ϣ


	int x = mouse.x / 40, y = mouse.y / 40;

	if ((_x >= 0 && _x < 13 && _y >= 0 && _y < 10) && (x >= 0 && x < 13 && y >= 0 && y < 10))
	{
		if (mapptr[x][y]->ifchecked() == true || mapptr[x][y]->getflag() == true);
		//���ѡ�еķ������
		else putimage(x * 40, y * 40, &block_chosen);


		if ((x != _x || y != _y))
			//������Ӧ�ķ���ĺ�������ı�ʱ
			//�����ķ����ƶ�����Ļָ�
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
			//����Ҽ�����
		{
			if (mapptr[x][y]->getflag() == false && mapptr[x][y]->ifchecked() == false)
				//��Ϊ����ķ��������
			{
				mapptr[x][y]->setflag(true);
				putimage(x * 40, y * 40, &flagged);
			}
			else if (mapptr[x][y]->getflag() == true && mapptr[x][y]->ifchecked() == false)
				//����÷����Ѿ��������ˣ���ô������
			{
				mapptr[x][y]->setflag(false);
				putimage(x * 40, y * 40, &block_normal);
			}
		}

		if (mouse.uMsg == WM_LBUTTONDOWN)
			//���������ײ���
		{
			{if (mines_are_set == false) { mineCreating(x, y); calculateSurrounding(); }}
			//�����һ�ε����ʱ����ܹ����ɵ��ף����ұ�֤��һ�β���ȵ���

			if (mapptr[x][y]->getflag() == true);
			//������Ѿ�������ķ���ʱ��ɶ������

			else
			{
				if (mapptr[x][y]->isMine() == true)
					//�ȵ���ʱ����Ϸ����
				{
					putimage(x * 40, y * 40, &mineFig);
					lose_pic();
					FlushMouseMsgBuffer();
					//��Ϸ�����������껺��
					replay = MessageBoxA(NULL, "��ѽ���ȵ����ˣ������ӣ�\n ������ȷ�ϼ����棬����ȡ�������ز˵���", "ʧ��", 1);
					//��ʾ��Ϸ�����Ի��򣬻�ȡ�Ի������

					return true;
				}
				else
				{
					if (mapptr[x][y]->ifchecked() == false)
						expandBlock(x, y);
					//��������ף��򷭿��÷���
				}

				if (winning())
				{
					FlushMouseMsgBuffer();
					//ʤ���������껺��
					replay = MessageBoxA(NULL, "��ϲ�㣬��Ӯ�ˣ�\n (����ȷ�ϼ����棬����ȡ�������ز˵�)", "ʤ��", 1);
					//��ʾ��Ϸʤ���Ի��򣬻�ȡ�Ի���������˽�����Ƿ�����
					return true;
				}
			}
		}
	}
	return false;
}

void re_ini()
//��ȫ�ֱ���map��ָ�뼯mapptr���³�ʼ��
{
	for(int x=0;x<13;x++)
		for (int y = 0; y < 10; y++)
		{
			if (mapptr[x][y]->isMine() == true)
			{
				delete mapptr[x][y];
				//ɾ�������׶���
				mapptr[x][y] = &map[x][y];
				//��ָ������ָ�ص�ͼ����
			}
			mapptr[x][y]->setchecked(false);
			//�����з������ó�δ����
			mapptr[x][y]->setflag(false);
			//�����з������ó�δ����
			mapptr[x][y]->minesaround = 0;
			//�����з������ó���Χ����
		}

	mines_are_set = false;
	//���³�ʼ���������Ƿ��õĲ�������Ϊ����δ���á�

	return;
}

void lose_pic()
//����˽�����������
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

