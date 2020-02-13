using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    static class Accinsert
    {
        public static void Invoke()
        {
            try
            {
                control con = control.Instance;
                string name = wblib.inputstring("이름");
                int id = wblib.inputnumber("계좌번호");
                int balance = wblib.inputnumber("잔액");

                Account acc = new Account(name, id, balance);

                if (con.AddAccount(acc) == true)
                    Console.WriteLine("저장 성공");
                else
                    Console.WriteLine("저장 실패");
            }
            catch (Exception ex)
            {
                Console.WriteLine("입력 오류");
                Console.WriteLine(">> " + ex.Message);
            }
        }
    }
}
