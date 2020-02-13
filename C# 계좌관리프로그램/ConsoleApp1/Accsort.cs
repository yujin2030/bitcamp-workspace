using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Accsort
    {
        public static void Invoke()
        {
            control con = control.Instance;
            Console.WriteLine("저장 방식 : ");
            string idx = wblib.inputstring("[1]계좌번호, [2]이름, [3] 잔액");

            con.SortAccount(idx);
        }
    }
}
