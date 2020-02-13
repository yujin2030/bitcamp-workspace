using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0930_실기시험11
{
    class book
    {
        public string Name { get; private set; }
        public int Price { get; private set; }
        public int Salcount { get; private set; }

        public book (string n, int p)
        {
        Name = n;
        Price = p;
        Salcount = 0;
        }

        public void UpdateSal(int val)
        {
            Salcount += val;
        }

        public override string ToString()
        {
            return string.Format("[{0}] 가격 : {1} 판매량 : {2}", Name, Price, Salcount);
        }
    }
}
