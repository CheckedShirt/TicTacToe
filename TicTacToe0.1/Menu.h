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
		cout << "*��ѡ��սģʽ!*" << endl;
		cout << "*1.�˻���ս" << endl;
		cout << "*2.���˶�ս" << endl;
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
		cout << "*��ѡ��AI���̶ܳ�!*" << endl;
		cout << "*1.�˹�����" << endl;
		cout << "*2.����ˮƽ" << endl;
		cout << "*3.��������" << endl;
		cin >> Difficulty;
		if (Difficulty == 1 || Difficulty == 2 || Difficulty == 3)break;
		ERROR(0);
		system("pause");
		system("cls");
	}
	cout << "�趨���!" << endl;
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
		cout << "    �� ~ �� ~ �� ~ �� ~ �� ~ �� ~ �� ~ " << endl;
		cout << "*********************************************" << endl;
		cout << "*1.    ��ʼ��Ϸ                             *" << endl;
		cout << "*2.    ѡ��                                 *" << endl;
		cout << "*3.    ����                                 *" << endl;
		cout << "*4.    �˳���Ϸ                             *" << endl;
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
			cout << "��������Ч����!" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}
#endif