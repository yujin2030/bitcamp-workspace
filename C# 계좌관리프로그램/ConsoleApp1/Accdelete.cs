using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    static class Accdelete
    {
        public static void Invoke()
        {
            control con = control.Instance;
            int id = wblib.inputnumber("삭제할 계좌");
            if (con.DelAccount(id) == true)
                Console.WriteLine("삭제 성공");
            else
                Console.WriteLine("삭제 실패");
        }
    }
}
