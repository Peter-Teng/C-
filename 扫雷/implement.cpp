#include"Minesweeper.h"

using namespace std;

bool block::getflag()
{
	return isflagged;
}
//���ظ÷����Ƿ񱻲������Ϣ

bool block::isMine()
{
	return false;
}
//���ؼ���÷����Ƿ�Ϊ��
//���麯�������ز��ǣ�

bool block::ifchecked()
{
	return isChecked;
}
//���÷����Ƿ��Ѿ�������

void block::setchecked(bool flag)
{
	isChecked = flag;
}
//���÷����Ƿ񱻷�����״̬
//��Ҫ���ڰѷ��鷭��

void block::setflag(bool flag)
{
	isflagged = flag;
}
//���÷����Ƿ��Ѿ��������״̬

bool mine::isMine()
{
	return true;
}
//���鵱ǰ�����Ƿ�Ϊ��
//���麯�����������ף�

mine::mine(int x,int y)
{
	mineX = x;
	mineY = y;
}
//�׵Ĺ��캯��
//������׵�λ��

int mine::getx()
{
	return mineX;
}
//�����׵ĺ�����

int mine::gety()
{
	return mineY;
}

//�����׵�������