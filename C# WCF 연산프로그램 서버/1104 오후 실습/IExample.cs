using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace _1104_오후_실습
{
    //인터페이스(계약) ==> WSDL 문서 
    [ServiceContract]
    interface IExample
    {
        [OperationContract]
        List<Cal> GetExample(int max);
        [OperationContract]
        string PrintExample(int n1, int n2, char op);
        [OperationContract]
        bool InputExample(int n1, int n2, char op, float input);
    }

    //서비스 객체
    class CExample : IExample
    {
        public List<Cal> GetExample(int max)
        {
            List<Cal> listcal = new List<Cal>();

            Random r = new Random();
            for (int i = 0; i < max; i++)
            {
                int n1 = r.Next(1, 10);      //1~9
                int n2 = r.Next(1, 10);
                int oper = r.Next(1, 5);

                Cal c = new Cal();
                c.Num1 = n1;
                c.Num2 = n2;
                switch (oper)
                {
                    case 1: c.Oper = '+'; break;
                    case 2: c.Oper = '-'; break;
                    case 3: c.Oper = '*'; break;
                    case 4: c.Oper = '/'; break;
                }

                listcal.Add(c);
            }
            return listcal;
        }

        public string PrintExample(int n1, int n2, char op)
        {
            return n1 + " " + op + " " + n2 + "=";
        }

        public bool InputExample(int n1, int n2, char op, float input)
        {
            float result = 0;
            switch (op)
            {
                case '+': result = n1 + n2; break;
                case '-': result = n1 - n2; break;
                case '*': result = n1 * n2; break;
                case '/': result = n1 / n2; break;
            }

            if (result == input)
                return true;
            else
                return false;
        }
    }
}
