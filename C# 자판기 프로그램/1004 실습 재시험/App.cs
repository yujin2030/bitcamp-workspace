using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _1004_실습_재시험
{
    class App
    {
        Control con = new Control();

        public void init()
        {
            Console.Clear();
            Console.WriteLine("*********************************************");
            Console.WriteLine("C# 자판기 프로그램");
            Console.WriteLine("최유진");
            Console.WriteLine("*********************************************");
            pause();
        }

        public void run()
        {
            while (true)
            {
                Console.Clear();
                con.CPrintAll();
                Console.WriteLine("*********************************************");
                Console.WriteLine("[F1] 금액 투입");
                Console.WriteLine("[F2] 제품 선택");
                Console.WriteLine("[F3] 동전 반환");
                Console.WriteLine("[F4] 제품 등록");
                Console.WriteLine("[ESC] 프로그램 종료");
                Console.WriteLine("*********************************************");

                switch (Console.ReadKey().Key)
                {
                    //case ConsoleKey.F1: con.CInsert(); break;
                    case ConsoleKey.F1: con.CInsert(); break;
                    case ConsoleKey.F2: con.CSelect(); break;
                    case ConsoleKey.F3: con.CGetMoney(); break;
                    case ConsoleKey.F4: con.Cupdate(); break;
                    case ConsoleKey.Escape: return;
                }

                pause();
            }

        }

        public void exit()
        {
            Console.Clear();
            Console.WriteLine("*********************************************");
            Console.WriteLine("C# 시험과제");
            Console.WriteLine("프로그램 종료");
            Console.WriteLine("*********************************************");
            pause();
        }

        public static void pause()
        {
            Console.WriteLine("아무키나 누르세요");
            Console.ReadKey();
        }
    }
}
