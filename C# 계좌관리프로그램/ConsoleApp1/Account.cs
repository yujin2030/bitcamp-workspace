using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Account : IComparable
    {
        public string Name { get; private set; }
        public int Id { get; set; }
        private int balance;

        public void addmoney(int money)
        {
            Balance += money;
        }

        public void minmoney(int money)
        {
            Balance -= money;
        }

        public int Balance
        {
            get { return balance; }
            set
            {
                if (value >= 0)
                    balance = value;
            }
        }

        public Account(string n, int id, int b)
        {
            Name = n;
            Id = id;
            Balance = b;
        }

        public void Print()
        {
            Console.WriteLine("이름 : " + Name);
            Console.WriteLine("계좌번호 : " + Id);
            Console.WriteLine("잔액 : " + Balance);
        }
        public override string ToString()
        {
            string temp = string.Format("[{0}] 계좌 : {1} 잔액 : {2}", Name, Id, Balance);
            return temp;
        }

        public int CompareTo(object obj)
        {
            Account acc = obj as Account;
            if (acc == null)
                throw new Exception("잘못된 객체 전달");

            return Name.CompareTo(acc.Name);
        }     
    }
    class BalanceComparaer : IComparer<Account>
    {
        public int Compare(Account x, Account y)
        {
            return x.Balance - y.Balance;
        }
    }

    class IDComparaer : IComparer<Account>
    {
        public int Compare(Account x, Account y)
        {
            return x.Id - y.Id;
        }
    }
}
