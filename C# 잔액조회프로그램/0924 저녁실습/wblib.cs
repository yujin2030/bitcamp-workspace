using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0924_저녁실습
{
    class wblib
    {
        public static int inputnumber(string msg)
        {
            Console.Write(msg + ":");

            int i = int.Parse(Console.ReadLine());

            return i;
        }
        public static string inputstring(string msg)
        {
            Console.Write(msg + ":");
            return Console.ReadLine();
        }
    }
}
