using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0926
{
    class Program
    {
        #region Sample1 사용 예제
        Sample1 sam = new Sample1();

        public Program()
        {
            logo();
        }

        public void Run()
        {
            while (true)
            {
                Console.Write(">> ");
                string msg = Console.ReadLine();
                string[] split = msg.Split(' ');
                if (split[0].Equals("insert"))
                {
                    sam.insert(split[1]);
                }
                else if (split[0].Equals("selectall"))
                {
                    sam.printall();
                }
                else if (split[0].Equals("select"))
                {
                    sam.select(split[1]);
                }
                else if (split[0].Equals("exit"))
                    return;
            }
        }

        private void logo()
        {
            Console.WriteLine("-----------------------------");
            Console.WriteLine("컬렉션 사용 프로그램 예제");
            Console.WriteLine("버전 1.0");
            Console.WriteLine("사용 방법");
            Console.WriteLine("  insert 저장문자열");
            Console.WriteLine("  selectall");
            Console.WriteLine("  select 검색문자열");
            Console.WriteLine("-----------------------------");
        }

        #endregion 

        #region Sample2 사용 예제
        Sample2 sam2 = new Sample2();

        public Program(int n)
        {
            logo2();
        }

        public void Run2()
        {
            while (true)
            {
                Console.Write(">> ");
                string msg = Console.ReadLine();
                string[] split = msg.Split(' ');
                if (split[0].Equals("insert"))
                {
                    //객체 생성 전달
                    Account acc = new Account()
                    {
                        Id = int.Parse(split[1]),
                        Name = split[2],
                        Balance = int.Parse(split[3]),
                        Date = DateTime.Now
                    };
                    sam2.insert(acc);
                }
                else if (split[0].Equals("selectall"))
                {
                    sam2.printall();
                }
                else if (split[0].Equals("select"))
                {
                    sam2.select(int.Parse(split[1]));
                }
                else if (split[0].Equals("input"))
                {
                    int id = int.Parse(split[1]);
                    int money = int.Parse(split[2]);
                    sam2.update(id, money, 0);
                }
                else if (split[0].Equals("output"))
                {
                    int id = int.Parse(split[1]);
                    int money = int.Parse(split[2]);
                    sam2.update(id, 0, money);
                }
                else if (split[0].Equals("delete"))
                {
                    int id = int.Parse(split[1]);
                    sam2.delete(id);
                }
                else if (split[0].Equals("sortname"))
                {
             
                    sam2.sortname();
                }
                else if (split[0].Equals("sortbalance"))
                {
                  
                    sam2.sortbalance();
                }
                else if (split[0].Equals("exit"))
                    return;
            }
        }

        private void logo2()
        {
            Console.WriteLine("-----------------------------");
            Console.WriteLine("컬렉션 사용 프로그램 예제");
            Console.WriteLine("버전 2.0");
            Console.WriteLine("사용 방법");
            Console.WriteLine("  insert 계좌번호 이름 입금액");
            Console.WriteLine("  selectall");
            Console.WriteLine("  select 계좌번호");
            Console.WriteLine("  input 계좌번호 입금액");
            Console.WriteLine("  output 계좌번호 출금액");
            Console.WriteLine("  delete 계좌번호");
            Console.WriteLine("  sortname");
            Console.WriteLine("  sortbalance");
            Console.WriteLine("-----------------------------");
        }
        #endregion 

        static void Main(string[] args)
        {
            new Program(1).Run2();
        }
    }
}
