using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0924_저녁실습
{
    class wbprint
    {
        public static void logo()             //메뉴출력
        {
            Console.Clear();           //창지우기
            Console.WriteLine("**********************");
            Console.WriteLine("C# 잔액조회프로그램");
            Console.WriteLine("최유진");
            Console.WriteLine("**********************");

            pause();
        }
        public static void ending()              //계좌개설
        {
            Console.Clear();           //창지우기
            Console.WriteLine("**********************");
            Console.WriteLine("잔액조회프로그램");
            Console.WriteLine("**********************");
            pause();
        }
        public static void menuprint()
        {
            Console.WriteLine("**********************");
            Console.WriteLine("[F1] 신규고객등록");
            Console.WriteLine("[F2] 입금");
            Console.WriteLine("[F3] 출금");
            Console.WriteLine("[F4] 전체출력");
            Console.WriteLine("[ESC] 프로그램 종료");
            Console.WriteLine("**********************");
        }

        public static void pause()
        {
            Console.WriteLine("아무키나 누르세요.");
            Console.ReadKey();
        }
    }
}
