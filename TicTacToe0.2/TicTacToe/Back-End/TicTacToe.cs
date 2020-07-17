using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TicTacToe.Back_End
{
    class TicTacToe
    {
        private CheckerBoard checkerBoard;     //井字棋棋盘对象
        private Player playerA, playerB;      //井字棋玩家对象
        private Computer computerC;          //井字棋AI对象
        private int difficulty;             //AI难度
        private bool order;                //先手
        private bool gameMode;            //游戏模式：true人机,flause人人
        public TicTacToe(int difficulty,bool gameMode)
        {
            checkerBoard=new CheckerBoard();
            order = DecideFirstHand();
            this.gameMode = gameMode;
            this.difficulty = difficulty;
            if(gameMode)
            {
                playerA = new Player();
                computerC = new Computer(checkerBoard);
            }
            else
            {
                playerA = new Player();
                playerB = new Player();
            }
        }
        private bool DecideFirstHand()//决定先手
        {
            Random rd = new Random();
            if (rd.Next(0, 1) == 1) return true;
            return false;
        }
    }

}
