using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _1004_실습_재시험
{
    class Control
    {
        Machine machine = new Machine();

        #region 싱글톤
        public static Control Instance
        {
            get; private set;
        }

        static Control()
        {
            Instance = new Control();
        }
        public Control()
        {
            
        }
        #endregion

        public void CPrintAll()
        {
            machine.PrintAll();
        }

        //금액투입
        public void CInsert()
        {
            try
            {
                Console.Write("돈을 넣어주세요:");
                int value = int.Parse(Console.ReadLine());
                machine.InputMoney(value);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public void CSelect()
        {
            Console.Write("어떤 제품을 원하세요:");
            string name = Console.ReadLine();
            machine.SelectDrink(name);
        }

        public void CGetMoney()
        {
            machine.GetMoney();
        }

        public void Cupdate()
        {
            machine.InitDrinkSetting();
        }
    }
}
