using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0924_저녁실습
{
    class wbarray
    {
        private Account[] acclist;

        public int Size { get; private set; }
        public int Max { get; private set; }

        #region 생성자
        public wbarray()
        {
            Size = 0;
            Max = wblib.inputnumber("배열의 크기");
            acclist = new Account[Max];
        }
        #endregion

        public Account getdata(int idx)
        {
            return acclist[idx];
        }

        public Account this[int index]
        {
            get { return acclist[index]; }
        }

        public void MakeAccount(Account mem)
        {
            if (Size >= Max)
                throw new Exception("저장 공간 부족");  //오버플로우 조건 검색
            acclist[Size] = mem;
            Size++;
        }
    }

}
