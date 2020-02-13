using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _1016씨샾TCP
{
    class Packet
    {
                   
        #region 싱글톤패턴
        
        public static Packet Instance { get; private set; }

        static Packet()
        {
            Instance = new Packet();
        }

        private Packet()
        {


        }
        #endregion

        #region 클라이언트 -> 서버 전송
        public string GetNewMember(string id, string pw, string name, int age)
        {
            string msg = null;
            msg += "NEWMEMBER@";         // 회원 가입 요청 메시지
            msg += id + "#";                  // 아이디
            msg += pw + "#";                 // 암호
            msg += name + "#";                // 이름
            msg += age;         // 나이


            // 메신저 서버에 문자열 전송
            return msg;
        }

        public string GetLogin(string id, string pw)
        {
            string msg = null;
            msg += "LOGIN@";
            msg += id + "#";                  // 아이디
            msg += pw;                 // 암호

            return msg;
        }

        public string DelMember(string id)
        {
            string msg = null;
            msg += "DELMEMBER@";
            msg += id;                  // 아이디

            return msg;
        }

        public string GetLogout(string id)
        {
            string msg = null;
            msg += "LOGOUT@";
            msg += id;                  // 아이디

            return msg;
        }

        public string GetMessage(string msg1)
        {
            string msg = null;
            msg += "GETMESSAGE@";
            msg += msg1;                  // 아이디

            return msg;
        }

        #endregion

        //#region 서버 -> 클라이언트 응답
        //public string GetNewMemberAck(string id, string name, bool b)
        //{
        //    string msg = null;
        //    msg += "NEWMEMBERACK@";         // 회원 가입 요청 메시지
        //    msg += b + "#";
        //    msg += id + "#";                  // 아이디
        //    msg += name;                // 이름

        //    // 메신저 서버에 문자열 전송
        //    return msg;
        //}

        //public string DelMemberAck(string id, bool b)
        //{
        //    string msg = null;
        //    msg += "DELMEMBERACK@";         // 회원 가입 요청 메시지
        //    msg += b + "#";
        //    msg += id;                  // 아이디

        //    // 메신저 서버에 문자열 전송
        //    return msg;
        //}

        //public string LogoutAck(string id, bool b)
        //{
        //    string msg = null;
        //    msg += "LOGOUTACK@";         // 회원 가입 요청 메시지
        //    msg += b + "#";
        //    msg += id;                  // 아이디

        //    // 메신저 서버에 문자열 전송
        //    return msg;
        //}

        //public string LoginAck(string id, string pw, bool b)
        //{
        //    string msg = null;
        //    msg += "LOGINACK@";         // 회원 가입 요청 메시지
        //    msg += b + "#";
        //    msg += id + "#";                  // 아이디
        //    msg += pw;                // 이름

        //    // 메신저 서버에 문자열 전송
        //    return msg;
        //}

        //public string MessageAck(string name, string msg1, bool b)
        //{
        //    string msg = null;
        //    msg += "MESSAGE@";         // 회원 가입 요청 메시지
        //    msg += b + "#";
        //    msg += name + "#";
        //    msg += msg1;                

        //    // 메신저 서버에 문자열 전송
        //    return msg;
        //}

        //#endregion
    }
}
