#pragma once
#include<iostream>
#include <time.h> 
#include <stdlib.h> 
#include<cmath>
using namespace std;
#ifndef FunctionalFunctionLibrary 
#define FunctionalFunctionLibrary
void ERROR(int x)//错误处理器
{
	switch (x)
	{
	case 0:cout << "请输入有效数字!" << endl; break;
	case 1:cout << "文件丢失!" << endl; break;
	default:cout << "未知错误!请与作者联系!" << endl; break;
	}
}
int Rand(int a, int b)//随机数函数
{
	srand((unsigned)time(NULL));
	return rand() % (b - a + 1) + a;
}
int DecideFirstHand(void)//决定先手
{
	return  Rand(0, 1);
}
void Converter(int& row, int& col, int& x, int Pattern)//坐标转换器
{
	switch (Pattern)
	{
	case 1://自然数转坐标
		row = (x - 1) / 3;
		col = (x - 1) - row * 3;
		break;
	case 2://坐标转自然数
		x = ((3 * row) + col + 1);
		break;
	}
}
int Add(int Pattern, int Position[3][3], int NewFall)
{
	int row = (NewFall - 1) / 3, col = (NewFall - 1) % 3;
	switch (Pattern)
	{
	case 1:return (Position[row][0] + Position[row][1] + Position[row][2]); break;//行求和
	case 2:return (Position[0][col] + Position[1][col] + Position[2][col]); break;//列求和
	case 3:return(Position[0][0] + Position[1][1] + Position[2][2]); break;//主对角线求和
	case 4:return (Position[0][2] + Position[1][1] + Position[2][0]); break;//副对角线求和
	}
	ERROR(-1);
	return 0;
}
bool Location(int(&Position)[3][3], int NewFall, int& x, int& y)
{
	int i, count;
	int row = 0, col = 0;
	int a, b;
	Converter(row, col, NewFall, 1);
	for (i = 1; i <= 4; i++)
	{
		count = Add(i, Position, NewFall);
		if (abs(count) == 2)
		{
			switch (i)
			{
			case 1:
				for (a = row, b = 0; b < 3; b++)
				{
					if (Position[a][b] == 0)
					{
						x = a; y = b; break;
					}
				}
				break;
			case 2:
				for (a = 0, b = col; a < 3; a++)
				{
					if (Position[a][b] == 0)
					{
						x = a; y = b; break;
					}
				}
				break;
			case 3:
				for (a = 0, b = 0; a < 3; a++, b++)
				{
					if (Position[a][b] == 0)
					{
						x = a; y = b; break;
					}
				}
				break;
			case 4:
				for (a = 0, b = 2; a < 3; a++, b--)
				{
					if (Position[a][b] == 0)
					{
						x = a; y = b; break;
					}
				}
				break;
			}
			return true;
		}
	}
	return false;
}
#endif