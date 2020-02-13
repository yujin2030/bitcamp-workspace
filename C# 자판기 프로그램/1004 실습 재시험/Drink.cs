using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _1004_실습_재시험
{
    class Drink
    {
        internal int total;

        public string Name { get; private set; }
        public int price { get; set; }
        public int Total { get; private set; }
        public int Sales { get; private set; }

        public int Price
        {
            get { return price; }
            set
            {
                if (value >= 0)
                    price = value;
                else
                    throw new Exception("가격은 0이상 필요함");
            }
        }

        public Drink(string n, int p, int s)
        {
            Name = n;
            price = p;
            Total = 0;
            Sales = s;
        }

        public void Print()
        {
            Console.WriteLine("음료수명 : " + Name);
            Console.WriteLine("가격 : " + price);
            Console.WriteLine("재고량 : " + Total);
            Console.WriteLine("판매량 : " + Sales);
            Console.WriteLine("판매금액 :" + GetSal(Sales, Price));
        }

        public int GetSal(int s, int p)
        {
            s = Sales;
            p = Price;
            int sp = s * p;
            return sp;
        }

        public override string ToString()
        {
            //string temp =
            //    string.Format("[{0}/{1}],{2}개,{3}개",
            //                    Name, price, Total, Sales);
            return string.Format("음료수명 [{0}/{1}원], 판매 {2}, 재고 {3}", Name, Price, Total, Sales);
        }

        public void SelDrink()
        {
            Total += 1;
            Sales -= 1;
        }
    }
}
