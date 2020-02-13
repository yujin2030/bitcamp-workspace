using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0925
{
    abstract class Cal               //추상클래스
    {
        public int Num1 { get; private set; }

        public int Num2 { get; private set; }

        public float Result { get; private set; }

        public Cal(int num1, int num2)             //생성자
        {
            Num1 = num1;
            Num2 = num2;
            Result = CalResult();
        }

        public abstract float CalResult();

        public abstract void Print();

    }
}
