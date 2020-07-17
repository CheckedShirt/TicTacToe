#pragma once
#include<iostream>
#include <stdlib.h> 
#include <fstream>
using namespace std;
#ifndef MenuFunction 
#define MenuFunction
int ModeSelection(void)
{
	int Mode;
	while (1)
	{
		cout << "*请选对战模式!*" << endl;
		cout << "*1.人机对战" << endl;
		cout << "*2.人人对战" << endl;
		cin >> Mode;
		if (Mode == 1 || Mode == 2)break;
		ERROR(0);
		system("pause");
		system("cls");
	}
	return Mode;
}
int Option(void)
{
	int Difficulty;
	while (1)
	{
		cout << "*请选择AI智能程度!*" << endl;
		cout << "*1.人工智障" << endl;
		cout << "*2.正常水平" << endl;
		cout << "*3.绝顶聪明" << endl;
		cin >> Difficulty;
		if (Difficulty == 1 || Difficulty == 2 || Difficulty == 3)break;
		ERROR(0);
		system("pause");
		system("cls");
	}
	cout << "设定完毕!" << endl;
	return Difficulty;
}
void Help(void)
{
	char text[100];
	ifstream help("help.txt", ios::in);
	if (!help.is_open())ERROR(1);
	else
	{
		while (!help.eof())
		{
			help.getline(text, 100);
			cout << text << endl;
		}
	}
	help.close();
}
int Menu(int& Mode)
{
	int x, Difficulty = 0;
	while (1)
	{
		cout << "*********************************************" << endl;
		cout << "    人 ~ 工 ~ 智 ~ 能 ~ 井 ~ 字 ~ 棋 ~ " << endl;
		cout << "*********************************************" << endl;
		cout << "*1.    开始游戏                             *" << endl;
		cout << "*2.    选项                                 *" << endl;
		cout << "*3.    帮助                                 *" << endl;
		cout << "*4.    退出游戏                             *" << endl;
		cout << "*********************************************" << endl;
		cin >> x;
		switch (x)
		{
		case 1:
			Mode = ModeSelection();
			return  Difficulty;
			break;
		case 2:
			Difficulty = Option();
			break;
		case 3:
			Help();
			break;
		case 4:
			exit(0);
			break;
		default:
			cout << "请输入有效数字!" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}
#endif