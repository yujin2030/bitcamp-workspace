using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0930_실기시험11
{
    class App
    {
        control con = control.Instance;

        #region 싱글톤
        public static App Instance
        {
            get; private set;
        }

        static App()
        {
            Instance = new App();
        }
        private App()
        {
        }
         #endregion

        public void init()
        {
            Console.Clear();
            Console.WriteLine("*********************************************");
            Console.WriteLine("C# 도서검색 프로그램");
            Console.WriteLine("최유진");
            Console.WriteLine("*********************************************");
            pause();
        }

        public void run()
        {
            while (true)
            {
                Console.Clear();
                //con.CPrintAll();
                Console.WriteLine("*********************************************");
                Console.WriteLine("[F1] 책 저장");
                Console.WriteLine("[F2] 전체출력");
                Console.WriteLine("[F3] 책 검색");
                Console.WriteLine("[F4] 판매량 수정");
                Console.WriteLine("[F5] 책 삭제");
                Console.WriteLine("[ESC] 프로그램 종료");
                Console.WriteLine("*********************************************");

                switch (Console.ReadKey().Key)
                {
                    case ConsoleKey.F1: con.Cinsert(); break;
                    case ConsoleKey.F2: con.CPrintAll(); break;
                    case ConsoleKey.F3: con.Cselect(); break;
                    case ConsoleKey.F4: con.Cupdate(); break;
                    case ConsoleKey.F5: con.Cdelete(); break;
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
