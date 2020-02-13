using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _1016
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

        #region 클라이언트=> 서버전송
        public string GetNewMember(string id, string pw, string name, int age)
        {
            string msg = null;
            msg += "NEWMEMBER@";
            msg += id + "#";
            msg += pw + "#";
            msg += name + "#";
            msg += age;
            return msg;
        }

        public string GetDelMember(string id)
        {
            string msg = null;
            msg += "DELMEMBER@";
            msg += id;
            return msg;
        }
        public string GetLogin(string id,string pw)
        {
            string msg = null;
            msg += "LOGIN@";
            msg += id+"#";
            msg += pw;
            return msg;
        }
        public string GetLogOut(string id)
        {
            string msg = null;
            msg += "LOGOUT@";
            msg += id;
            return msg;
        }
        public string GetMessage(string Msg,string name)
        {
            string msg = null;
            msg += "MESSAGE@";
            msg += "[ " + name + " ] ";
            msg += Msg;
            return msg;
        }


        #endregion

    }
}
