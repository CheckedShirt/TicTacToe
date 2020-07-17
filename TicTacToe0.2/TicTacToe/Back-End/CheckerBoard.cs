using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace TicTacToe.Back_End
{
    class CheckerBoard
    {
        private int[,] map;        //棋盘
        private int rounds;       //回合数
        private int newMove;     //新落子
        public CheckerBoard()
        {
            map = new int[3, 3];

        }
        public bool Location(int NewFall, ref int x, ref int y)//定位即将要赢
        {
            int i, count;
            int[] x_y;
            int a, b;
            x_y = numberToX_Y(NewFall);
            for (i = 1; i <= 4; i++)
            {
                count = Add(i, NewFall);
                if (count == 2 || count == -2)
                {
                    switch (i)
                    {
                        case 1:
                            for (a = x_y[0], b = 0; b < 3; b++)
                            {
                                if (map[a, b] == 0) { x = a; y = b; break; }
                            }
                            break;
                        case 2:
                            for (a = 0, b = x_y[1]; a < 3; a++)
                            {
                                if (map[a, b] == 0) { x = a; y = b; break; }
                            }
                            break;
                        case 3:
                            for (a = 0, b = 0; a < 3; a++, b++)
                            {
                                if (map[a, b] == 0) { x = a; y = b; break; }
                            }
                            break;
                        case 4:
                            for (a = 0, b = 2; a < 3; a++, b--)
                            {
                                if (map[a, b] == 0) { x = a; y = b; break; }
                            }
                            break;
                    }
                    return true;
                }
            }
            return false;
        }
        public int referee()//判断输赢
        {
            int rowCount, colCount, mdCount = 0, adCount = 0;
            int[] x_y;
            x_y = numberToX_Y(newMove);
            rowCount = Add(1, newMove);//行求和
            colCount = Add(2, newMove);//列求和
            if ((x_y[0] - x_y[1]) != 1) mdCount = Add(3, newMove);//主对角线求和
            if ((x_y[0] + x_y[1] - 2) != 1) adCount = Add(4, newMove);//副对角线求和
            //返回结果
            if ((rowCount == 3 || colCount == 3 || mdCount == 3 || adCount == 3)) return 1;
            else if ((rowCount == -3 || colCount == -3 || mdCount == -3 || adCount == -3)) return -1;
            return 0;
        }
        public int[] numberToX_Y(int num)
        {
            int[] x_y = new int[2];
            x_y[0] = (num - 1) / 3;          //row
            x_y[1] = (num - 1) - x_y[0] * 3; //col
            return x_y;
        }
        public int X_YToNumber(int[] x_y)
        {
            return ((3 * x_y[0]) + x_y[1] + 1);
        }
        public int Add(int Pattern, int NewFall)
        {
            int row = (NewFall - 1) / 3, col = (NewFall - 1) % 3;
            switch (Pattern)
            {
                case 1: return (map[row, 0] + map[row, 1] + map[row, 2]); //行求和
                case 2: return (map[0, col] + map[1, col] + map[2, col]);//列求和
                case 3: return (map[0, 0] + map[1, 1] + map[2, 2]);     //主对角线求和
                case 4: return (map[0, 2] + map[1, 1] + map[2, 0]);    //副对角线求和
            }
            //ERROR(-1);
            return 0;
        }
        public int[,]getMap(){return map;}
        public void setMap(int row, int col,int value)//用坐标落子
        {
            int[] x_y = { row, col };
            newMove = X_YToNumber(x_y);
            rounds++;
            map[row, col] = value;
        }
        public void setMap(int position,int value)//用自然数落子
        {
            int[] x_y ;
            x_y=numberToX_Y(position);
            setMap(x_y[0],x_y[1],value);
        }
        public int getNewMove(){return newMove;}
        public int getRounds() { return rounds; }
    }
}
