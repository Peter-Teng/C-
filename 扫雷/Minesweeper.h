#include<iostream>
#ifndef MINESWEEPER_H
#define MINESWEEPER_H

//block类
class block
{
public:
	virtual bool isMine();
	void setflag(bool flag);
	bool getflag();
	void setchecked(bool flag);
	bool ifchecked();
	int minesaround = 0;
private:
	bool isChecked = false, isflagged = false;
};


//block的派生类mine
class mine :public block
{
public:
	mine(int x, int y);
	virtual bool isMine();
	int getx();
	int gety();
private:
	int mineX, mineY;
};
#endif // !MINESWEEPER_H

