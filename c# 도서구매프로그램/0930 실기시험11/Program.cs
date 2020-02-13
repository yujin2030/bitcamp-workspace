using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0930_실기시험11
{
    class Program
    {
        static void Main(string[] args)
        {
            App a = App.Instance;
            a.init();
            a.run();
            a.exit();
        }
    }
}
