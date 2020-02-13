using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0924_저녁실습
{
    class control
    {
        //저장소==========================
        wbarray array = new wbarray();
        wbioarray array1 = new wbioarray();
        //================================
        public void printall()     //전체출력
        {
            Console.WriteLine("저장개수 : {0}개", array.Size);
            for (int i = 0; i < array.Size; i++)
            {
                Account mem = array.getdata(i);
                Console.WriteLine(mem);
            }
        }

        public void MakeAccount()         //신규고객등록
        {
            try
            {
                Console.WriteLine("계좌 개설");
                int id = wblib.inputnumber("계좌 ID  ");
                string name = wblib.inputstring("이름  ");
                int balance = wblib.inputnumber("입금액  ");

                array.MakeAccount(new Account(id, balance, name));
                array1.MakeAccount(new accio(id, balance, 0, balance, DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss")));

                Console.WriteLine("저장완료");
            }
            catch (Exception ex)
            {
                Console.WriteLine("입력 오류");
                Console.WriteLine(">>" + ex.Message);
            }

        }
        private int idtoidx(int id)
        {
            for (int i = 0; i < array.Size; i++)
            {
                Account mem = array[i];
                if (mem.Id.Equals(id) == true)
                    return i;
            }
            throw new Exception("없음");            //return -1;
        }

        public void Deposit()          //입금
        {
            try
            {
                int id = wblib.inputnumber("계좌 ID 조회");
                Account mem = array[idtoidx(id)];

                int money = wblib.inputnumber("입금액");
                mem.Balance += money;

                array1.MakeAccount(new accio(id, money, 0, mem.Balance, DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss")));
                Console.WriteLine(mem);
            }
            catch (Exception ex)
            {
                Console.WriteLine("입금에러");
                Console.WriteLine(">>" + ex.Message);
            }
        }
        public void Withdraw()       //출금
        {
            try
            {
                int id = wblib.inputnumber("계좌 ID 조회");
                Account mem = array[idtoidx(id)];

                int money = wblib.inputnumber("출금액");
                if (money <= mem.Balance)
                    mem.Balance -= money;
                else
                    throw new Exception("잔액이 부족합니다.");

                array1.MakeAccount(new accio(id, 0, money, mem.Balance, DateTime.Now.ToString("yyyy-MM-dd-HH-mm-ss")));
                Console.WriteLine(mem);
            }
            catch (Exception ex)
            {
                Console.WriteLine("출금에러");
                Console.WriteLine(">>" + ex.Message);
            }
        }

        public void Inquire()
        {
            try
            {
                int id = wblib.inputnumber("ID조회");
                Account mem = array[idtoidx(id)];

                    for (int i = 0; i < array1.Size; i++)
                    {
                        accio acc = array1.getdata(i);
                        if (acc.Id == mem.Id)
                            Console.WriteLine(acc);
                    }
                


            }
            catch (Exception ex)
            {
                Console.WriteLine("잔액조회에러");
                Console.WriteLine(">>" + ex.Message);
            }
        }

    }
}
