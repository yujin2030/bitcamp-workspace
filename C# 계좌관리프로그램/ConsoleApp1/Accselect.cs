using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    static class Accselect
    {
        static Account acc;

        public static void Invoke()
        {
            control con = control.Instance;
            int id = wblib.inputnumber("검색 계좌");
            acc = con.SelectAccount(id);
            Print();
        }

        static void Print()
        {
            acc.Print();
        }
    }
}
