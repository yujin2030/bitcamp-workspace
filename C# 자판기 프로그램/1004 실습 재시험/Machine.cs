using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _1004_실습_재시험
{
    class Machine
    {
        List<Drink> drinklist = new List <Drink>();
        private Drink drink;

        public int AllSales { get; private set; }
        public int AllPrice { get; private set; }
        public int Input { get; private set; }

        public Machine()
        {
            AllSales = 0;
            AllPrice = 0;
            Input = 0;

            drinklist = new List<Drink>();
            InitDrinkSetting();
        }

        //제품등록
        public void InitDrinkSetting()
        {
            drinklist.Add(new Drink("콜라",700,50));
            drinklist.Add(new Drink("사이다", 800,60));
            drinklist.Add(new Drink("파워에이드", 1500,40));
            drinklist.Add(new Drink("포카리", 1000,80));
            drinklist.Add(new Drink("헛개수", 2000,36));
        }

        //전체출력
        public void PrintAll()
        {
            Console.WriteLine("판매수량:" + AllSales);
            Console.WriteLine("판매금액:" + AllPrice);

            foreach (Drink b in drinklist)
            {
                Console.WriteLine(b);
            }
        }

        //금액투입
        public void InputMoney(int value)
        {
            Input += value;

            if (value < 0)
            {
                throw new Exception("0보다 작음");
            }
            Console.WriteLine("현재 잔액: " + Input);
        }

        //제품선택
        public void SelectDrink(string name)
        {
            foreach (Drink b in drinklist)
            {
                if (b.Name.Equals(name))
                {
                    if (b.total < 0)
                        throw new Exception("재고가 없습니다.");

                    if (b.Price > Input)
                        throw new Exception("잔액이 부족합니다.");

                    b.SelDrink();

                    SelDrink(b.Price);
                }

            }
        }

        //판매수량
        public void SelDrink(int price)
        {
            AllSales += 1;
            AllPrice += price;
        }

        //잔액반환
        public void GetMoney()
        {
            Input = 0;
        }

    }
}
