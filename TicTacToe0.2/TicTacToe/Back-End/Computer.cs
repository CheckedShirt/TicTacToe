using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization.Formatters;
using System.Text;
using System.Threading.Tasks;

namespace TicTacToe.Back_End
{
	class Computer
	{
		private CheckerBoard cb;
		private int aiNewMove;//AI最新落子
		public Computer(CheckerBoard cb)
        {
			this.cb = cb;
        }
		public void playPattern1()//一级AI下子模式
        {
			int[,] map = cb.getMap(); 
			int x;
			int count = 0;
			Random rd = new Random();
			x = rd.Next(1, 9-cb.getRounds());
			foreach (int i in map)
            {
				if (i == 0) count++;
				if (count == x) break;
            }
			cb.setMap(count, -1);
			aiNewMove = count;
		}
		public void playPattern2()//二级AI下子模式
        {
			int row=0, col=0;
			if (cb.getRounds() < 2) playPattern1();
			else if (cb.Location(aiNewMove, ref row, ref col) || cb.Location(aiNewMove, ref row, ref col))
			{
				cb.setMap(row, col,-1);
				aiNewMove = cb.getNewMove();
			}
			else playPattern1();
		}
		public void playPattern3()//三级AI下子模式
        {

        }

	}
}
