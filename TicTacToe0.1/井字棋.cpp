#include<iostream>
#include <stdlib.h> 
#include "FunctionalFunctionLibrary.h"//功能函数库
#include "Menu.h"//菜单函数库
using namespace std;
//int Flag = 0;//快赢判断 1为玩家 -1为AI
int New;//最新落子
class Player//玩家
{
public:
	void Play(int(&Position)[3][3], int id);
};
void Player::Play(int(&Position)[3][3], int id = 1)
{
	int x;
	int i = 0, j = 0;
	while (1)
	{
		cin >> x;
		Converter(i, j, x, 1);
		if (x > 9 || x < 1)
		{
			ERROR(0);
			continue;
		}
		if (Position[i][j] == 0)
		{
			Position[i][j] = id;
			break;
		}
		else cout << "此处已落子!请选他处落子!" << endl;
	}
	New = x;
}
class Computer//电脑
{
	int AINew;//AI最新落子
public:
	void Play(int(&Position)[3][3], int Rounds);
	void Play1(int(&Position)[3][3], int Rounds);
	void Play2(int(&Position)[3][3], int Rounds);
	void Play3(int(&Position)[3][3], int Rounds);
	int Difficulty;
};
void Computer::Play1(int(&Position)[3][3], int Rounds)
{
	int x;
	int count = -1;
	x = Rand(0, 8 - Rounds);
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (Position[i][j] == 0)count++;
			if (count == x)break;
		}
		if (count == x)break;
	}
	Position[i][j] = -1;
	Converter(i, j, New, 2);
	Converter(i, j, AINew, 2);
}
void Computer::Play2(int(&Position)[3][3], int Rounds)
{
	int row, col;
	if (Rounds == 0 || Rounds == 1)Play1(Position, Rounds);
	else if (Location(Position, AINew, row, col) || Location(Position, New, row, col))
	{
		Position[row][col] = -1;
		Converter(row, col, New, 2);
		Converter(row, col, AINew, 2);
	}
	else Play1(Position, Rounds);
}
void Computer::Play3(int(&Position)[3][3], int Rounds)	//大概不能运行，但应该不会报错
{
	
}
void Computer::Play(int(&Position)[3][3], int Rounds)
{
	int New = 0;
	switch (Difficulty)
	{
	case 1:Play1(Position, Rounds); break;
	case 2:Play2(Position, Rounds); break;
	case 3:Play3(Position, Rounds); break;
	}
	cout << "*****AI已下子*****" << endl;
}
class Checkerboard//棋盘
{
	Player A, C;
	Computer B;
	int Win;//胜利判断
	int Mode;//游戏模式(1-人机2-人人)
	void Show(int x);//棋盘显示
protected:
	int Position[3][3];//棋盘
	int Rounds;//回合数
	bool Order;//先手
public:
	Checkerboard(int Difficulty, int Mode);//初始化棋盘
	void Run(void);//开始运行
	void PVE(void);//人机对战
	void PVP(void);//人人对战
	int Referee(void);//裁判
	int End(void);//结束
};
Checkerboard::Checkerboard(int Difficulty = 0, int TMode = 1)
{
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			Position[i][j] = 0;
		}
	}
	if (Difficulty == 0)B.Difficulty = 1;
	else B.Difficulty = Difficulty;
	Mode = TMode;
	Win = 0;
	Rounds = 0;
	Order = DecideFirstHand();
}
void Checkerboard::Show(int id)
{
	cout << "*****第" << Rounds + 1 << "回*****" << endl;
	switch (id)
	{
	case 0:cout << "轮AI下子!" << endl; break;
	case 1:cout << "轮玩家A下子!" << endl; break;
	case -1:cout << "轮玩家B下子!" << endl; break;
	case 2:cout << "轮玩家下子!" << endl; break;
	case 3:
		if (Mode == 1)
		{
			switch (Win)
			{
			case 0:
				cout << "------平局------" << endl;
				break;
			case 1:
				cout << "------玩家胜利------" << endl;
				break;
			case -1:
				cout << "------AI胜利------" << endl;
				break;
			}
		}
		else
		{
			switch (Win)
			{
			case 0:
				cout << "------平局------" << endl;
				break;
			case 1:
				cout << "------玩家A胜利------" << endl;
				break;
			case -1:
				cout << "------玩家B胜利------" << endl;
				break;
			}
		}
	}
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			switch (Position[i][j])
			{
			case 0:
				cout << "#  ";
				break;
			case 1:
				cout << "○ ";
				break;
			case -1:
				cout << "× ";
				break;
			}
		}
		cout << endl;
	}
}
int Checkerboard::Referee(void)
{
	int rowCount, colCount, mdCount = 0, adCount = 0;
	int row = 0, col = 0;
	Converter(row, col, New, 1);
	rowCount = Add(1, Position, New);//行求和
	colCount = Add(2, Position, New);//列求和
	if (!(row - col))      mdCount = Add(3, Position, New);//主对角线求和
	if (!(row + col - 2))  adCount = Add(4, Position, New);//副对角线求和
	/*
	//Flag==1表示某一方要赢了
	if (B.Difficulty!=1) {
		if (rowCount == 2 || colCount == 2 || mdCount == 2 || adCount == 2)Flag = 1;
		if (rowCount == -2 || colCount == -2 || mdCount == -2 || adCount == -2)Flag = -1;
		//Flag = (rowCount == 2 || colCount == 2 || mdCount == 2 || adCount == 2) ? 1 : 0;
	}*/
	//返回结果
	if ((rowCount == 3 || colCount == 3 || mdCount == 3 || adCount == 3)) return 1;
	else if ((rowCount == -3 || colCount == -3 || mdCount == -3 || adCount == -3)) return -1;
	return 0;
}
void Checkerboard::PVE(void)
{
	while (Win == 0 && Rounds < 9)
	{
		if (Rounds == 0)
		{
			cout << "AI难度等级:" << B.Difficulty << endl;
			if (Order)
			{
				cout << "玩家先手!" << endl;
				Show(2);
				A.Play(Position);
			}
			else
			{
				cout << "AI先手!" << endl;
				Show(0);
				B.Play(Position, Rounds);
			}
			Rounds++;
			continue;
		}//第一局
		else
		{
			if (Order)
			{
				if (Rounds % 2 == 0)
				{
					Show(2);
					A.Play(Position);
				}
				else
				{
					Show(0);
					B.Play(Position, Rounds);
				}

			}
			else
			{
				if (Rounds % 2 == 0)
				{
					Show(0);
					B.Play(Position, Rounds);
				}
				else
				{
					Show(2);
					A.Play(Position);
				}
			}
			Rounds++;
			Win = Referee();
		}
	}
	Show(3);
}
void Checkerboard::PVP(void)
{
	while (Win == 0 && Rounds < 9)
	{
		if (Rounds == 0)
		{
			if (Order)
			{
				cout << "玩家A先手!" << endl;
				Show(1);
				A.Play(Position);
			}
			else
			{
				cout << "玩家B先手!" << endl;
				Show(-1);
				C.Play(Position, -1);
			}
			Rounds++;
			continue;
		}//第一局
		else
		{
			if (Order)
			{
				if (Rounds % 2 == 0)
				{
					Show(1);
					A.Play(Position);
				}
				else
				{
					Show(-1);
					C.Play(Position, -1);
				}

			}
			else
			{
				if (Rounds % 2 == 0)
				{
					Show(-1);
					C.Play(Position, -1);
				}
				else
				{
					Show(1);
					A.Play(Position);
				}
			}
			Rounds++;
			Win = Referee();
		}
	}
	Show(3);
}
void Checkerboard::Run(void)
{
	switch (Mode)
	{
	case 1:PVE(); break;
	case 2:PVP(); break;
	}
}
int Checkerboard::End(void)
{
	char X;
	cout << "是否再来一局?(Y/N)" << endl;
	cin >> X;
	if (X == 'Y' || X == 'y')return 1;
	else return 0;
}
int main(void)
{
	int Difficulty, Mode;
	while (1)
	{
		bool On = true;
		Difficulty = Menu(Mode);
		Checkerboard C(Difficulty, Mode);
		while (On)
		{
			Checkerboard C(Difficulty, Mode);
			C.Run();
			On = C.End();
			C.~Checkerboard();
			if (!On)cout << "游戏结束,返回主菜单........" << endl;
		}
	}
	system("pause");
	return 0;
}