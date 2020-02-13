using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    static class Accprintall
    {
        static List<Account> acc;

        public static void Invoke()
        {
            control con = control.Instance;
            con.SelectAccount(out acc);
            PrintAll();
        }

        public static void PrintAll()
        {
            Console.WriteLine("저장개수 : {0}개", acc.Count);
            for (int i = 0; i < acc.Count; i++)
            {
                Account mem = acc[i];
                Console.WriteLine(mem);
            }
        }
    }
}
