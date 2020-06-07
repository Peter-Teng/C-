#include"Minesweeper.h"

using namespace std;

bool block::getflag()
{
	return isflagged;
}
//返回该方格是否被插旗的信息

bool block::isMine()
{
	return false;
}
//返回检验该方格是否为雷
//（虚函数，返回不是）

bool block::ifchecked()
{
	return isChecked;
}
//检查该方格是否已经被检验

void block::setchecked(bool flag)
{
	isChecked = flag;
}
//设置方格是否被翻开的状态
//主要用于把方块翻开

void block::setflag(bool flag)
{
	isflagged = flag;
}
//设置方块是否已经被插旗的状态

bool mine::isMine()
{
	return true;
}
//检验当前方格是否为雷
//（虚函数，返回是雷）

mine::mine(int x,int y)
{
	mineX = x;
	mineY = y;
}
//雷的构造函数
//制造的雷的位置

int mine::getx()
{
	return mineX;
}
//返回雷的横坐标

int mine::gety()
{
	return mineY;
}

//返回雷的纵坐标