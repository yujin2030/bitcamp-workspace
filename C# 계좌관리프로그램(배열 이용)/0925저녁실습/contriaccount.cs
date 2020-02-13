using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0925저녁실습
{
    [Serializable]
    class contriaccount : account
    {
        public int Contribution { get; private set; }
         
        public contriaccount(string n, int id, int b) : base(n, id, b)
        {
            Balance = b - (int)(b * 0.01);
            Contribution = (int)(b * 0.01);

        }

        public new void addmoney(int money)
        {
            Balance +=money -(int)(money * 0.01);
            Contribution += (int)(money * 0.01);
        }
        public new void Print()
        {
            Console.WriteLine("이름 : " + Name);
            Console.WriteLine("계좌번호 : " + Id);
            Console.WriteLine("잔액 : " + Balance);
            Console.WriteLine("기부금 : " + Contribution );

        }
        public override string ToString()
        {
            string temp = string.Format("[{0}] 계좌 : {1} 잔액 : {2} 기부금:{3}", Name, Id, Balance,Contribution);
            return temp;
        }
    }
}
