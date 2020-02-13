using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _1018_실습시험
{
    class Packet
    {

        #region 싱글톤 패턴
        public static Packet Instance { get; private set; }

        static Packet()
        {
            Instance = new Packet();
        }

        private Packet()
        {

        }
        #endregion

        public string SendNumber(string name, int num)
        {
            string msg = null;
            msg += "SENDNUMBER@";         // 회원 가입 요청 메시지
            msg += name + "#";
            msg += num;

            return msg;
        }
    }
}
