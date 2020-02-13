using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0924_저녁실습
{
    //enum enummake { DEPOSIT, WITHDRAW, INQUIRE, EXIT };
    class Account
    {
        public int Id { get; set; }
        public int Balance { get; set; }
        public string Name { get; private set; }

        public Account(int i, int b, string n)
        {
            Id = i;
            Balance = b;
            Name = n;
        }

        public void Print()
        {
            Console.WriteLine("계좌번호 : " + Id);
            Console.WriteLine("잔액     : " + Balance);
            Console.WriteLine("고객이름 : " + Name);
        }

        public override string ToString()
        {
            string temp =
                string.Format("[{0}],{1},{2}", Id, Name, Balance);
            return temp;
        }
    }

}
