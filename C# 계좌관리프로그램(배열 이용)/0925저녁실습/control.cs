using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0925저녁실습
{
    class control
    {
        //저장소========================
        wbarray array = null;
        //==============================

        public void filesave()
        {
            //    wbfile.filesave(array.Memlist, array.Size);
            wbfile.filesersave(array.Acclist, array.Size);
        }

        public void fileload()
        {
            try
            {
                // member[] arr  = wbfile.fileload();
                int max;
                account[] arr = wbfile.fileserload(out max);
                array = new wbarray(max);
                for (int i = 0; i < arr.Length; i++)
                {
                    account mem = arr[i];
                    array.insert(mem);
                }
            }
            catch (FileNotFoundException)
            {
                //파일이 없으니깐 배열객체를 생성하겠다.
                int size = wblib.inputnumber("배열의 크기");
                array = new wbarray(size);
            }
        }

        public void printall()
        {
            Console.WriteLine("저장개수 : {0}개", array.Size);
            for (int i = 0; i < array.Size; i++)
            {
                account mem = (account)array.getdata(i);
                Console.WriteLine(mem);
            }
        }

        public void insert()
        {
            try
            {
                string name = wblib.inputstring("이름");
                int id = wblib.inputnumber("계좌번호");
                int balance = wblib.inputnumber("잔액");
                string give = wblib.inputstring("1.기부계좌 2.신용계좌 3.일반계좌");

                switch (give)
                {
                    case "1": array.insert(new contriaccount(name, id, balance)); break;
                    case "2": array.insert(new faithaccount(name, id, balance)); break;
                    case "3": array.insert(new account(name, id, balance)); break;
                    default: Console.WriteLine("저장 실패"); break;
                }


            }
            catch (Exception ex)
            {
                Console.WriteLine("입력 오류");
                Console.WriteLine(">> " + ex.Message);
            }
        }

        private int idtoidx(int id)
        {
            for (int i = 0; i < array.Size; i++)
            {
                account acc = (account)array[i];
                if (acc.Id.Equals(id) == true)
                    return i;
            }
            throw new Exception("잘못된 계좌");
        }

        public void deposit()
        {
            try
            {
                int id = wblib.inputnumber("계좌 ID");
                int money = wblib.inputnumber("입금액");

                if (money < 0)
                {
                    Console.WriteLine("잘못된 금액");
                    return;
                }

                account mem = (account)array[idtoidx(id)];
                if (mem is contriaccount)
                {
                    contriaccount cac = (contriaccount)mem;
                    cac.addmoney(money);
                }

                else if (mem is faithaccount)
                {
                    faithaccount fac = (faithaccount)mem;
                    fac.addmoney(money);
                }

                else
                { mem.addmoney(money); }

            }
            catch (Exception ex)
            {
                Console.WriteLine("입금 오류");
                Console.WriteLine(">> " + ex.Message);
            }


        }

        public void Withdraw()
        {
            try
            {
                int id = wblib.inputnumber("계좌 ID");
                int money = wblib.inputnumber("출금액");
                account mem = (account)array[idtoidx(id)];

                if (money < 0 || mem.Balance < money)
                {
                    Console.WriteLine("잘못된 금액");
                    return;
                }

                mem.Balance -= money;
            }
            catch (Exception ex)
            {
                Console.WriteLine("출금 오류");
                Console.WriteLine(">> " + ex.Message);
            }
        }

        public void Inquire()
        {
            for (int i = 0; i < array.Size; i++)
            {
                account mem = (account)array.getdata(i);
                Console.WriteLine(mem);
            }
        }
    }
}
