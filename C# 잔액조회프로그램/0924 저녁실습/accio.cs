using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0924_저녁실습
{
    class accio
    {
        public int Id { get; set; }
        private int input;
        private int output;
        private int balance;
        public string Date { get; set; }

        public int Input
        {
            get { return input; }
            set
            {
                if (value > 0)
                    input = value;
                else
                    throw new Exception("잘못된 입금액입니다.");
             
            }
        }

        public int Output
        {
            get { return output; }
            set
            {      
                    output = value;

            }
        }

        public int Balance
        {
            get { return balance; }
            set
            {
                if (value > 0)
                    balance = value;
                else
                    throw new Exception("잘못된 잔액입니다.");

            }
        }

        public accio(int i, int ip, int o,int b, string d)
        {
            Id = i;
            input = ip;
            Output = o;
            Balance = b;
            Date = d;
        }

        public void Print()
        {
            Console.WriteLine("계좌번호 : " + Id);
            Console.WriteLine("입금액   : " + input);
            Console.WriteLine("출금액   : " + output);
            Console.WriteLine("잔액     : " + balance);
            Console.WriteLine("일시 : " + Date);
        }

        public override string ToString()
        {
            string temp =
                string.Format("[{0}],{1},{2},{3},{4}", Id, input, output, balance, Date);
            return temp;
        }

    }
}
