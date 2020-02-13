using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _1104_오후_실습_클라이언트.ServiceReference2;

namespace _1104_오후_실습_클라이언트
{
    class Program
    {
        static void Main(string[] args)
        {
            ExampleClient r = new ExampleClient();

            Cal[] arr = r.GetExample(10);

            for (int i = 0; i < 10; i++)
            {
                string str = r.PrintExample(arr[i].Num1, arr[i].Num2, arr[i].Oper);
                Console.Write(str);

                float result = float.Parse(Console.ReadLine());

                if (r.InputExample(arr[i].Num1, arr[i].Num2, arr[i].Oper, result))
                    Console.WriteLine("정답");
                else
                    Console.WriteLine("오답");
            }
        }
    }
}
