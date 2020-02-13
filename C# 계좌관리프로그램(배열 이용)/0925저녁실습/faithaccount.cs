using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0925저녁실습
{
    [Serializable]
    class faithaccount:account
    {
        public faithaccount(string n, int id, int b) :base(n,id,b)
        {
            Balance = b + (int)(b * 0.01);
        }

        public new void addmoney(int money)
        {
            Balance += money + (int)(money * 0.01);
            
        }
    }
}
