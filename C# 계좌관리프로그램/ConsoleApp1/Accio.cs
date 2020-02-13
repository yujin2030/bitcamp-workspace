using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    static class Accio
    {
        static Account acc;

        public static void Invoke(bool b)
        {
            try
            {
                control con = control.Instance;
                int id = wblib.inputnumber("입금할 계좌");
                int balance = wblib.inputnumber("입금액");

                if (b == true)
                    con.InputAccount(id, balance);
                else if (b == false)
                    con.OutputAccount(id, balance);

                Console.WriteLine("입/출금 성공");
            }

            catch
            {
                Console.WriteLine("입/출금 실패");
            }
        }
    }
}
