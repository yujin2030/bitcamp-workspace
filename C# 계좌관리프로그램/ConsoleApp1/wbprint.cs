using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class wbprint
    {
        public static void logo()
        {
            Console.Clear();
            Console.WriteLine("*********************************************");
            Console.WriteLine("C# 계좌관리프로그램");
            Console.WriteLine("최유진");
            Console.WriteLine("*********************************************");
            pause();
        }

        public static void ending()
        {
            Console.Clear();
            Console.WriteLine("*********************************************");
            Console.WriteLine("계좌관리프로그램");
            Console.WriteLine("프로그램 종료");
            Console.WriteLine("*********************************************");
            pause();
        }

        public static void menuprint()
        {

            Console.WriteLine("*********************************************");
            Console.WriteLine("[F1] 계좌 등록");
            Console.WriteLine("[F2] 전체 계좌출력");
            Console.WriteLine("[F3] 계좌 검색");
            Console.WriteLine("[F4] 입금");
            Console.WriteLine("[F5] 출금");
            Console.WriteLine("[F6] 계좌삭제");
            Console.WriteLine("[F7] 정렬");
            Console.WriteLine("[ESC] 프로그램 종료");
            Console.WriteLine("*********************************************");
        }

        public static void pause()
        {
            Console.WriteLine("아무키나 누르세요");
            Console.ReadKey();
        }
    }
}
