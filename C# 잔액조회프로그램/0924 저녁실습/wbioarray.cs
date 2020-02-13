using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0924_저녁실습
{
    class wbioarray
    {
        private accio[] acciolist;

        public int Size { get; private set; }
        public int Max { get; private set; }

        #region 생성자
        public wbioarray()
        {
            Size = 0;
            Max = 500;
            acciolist = new accio[Max];
        }
        #endregion

        public accio getdata(int idx)
        {
            return acciolist[idx];
        }

        public accio this[int index]
        {
            get { return acciolist[index]; }
        }

        public void MakeAccount(accio acc)
        {
            if (Size >= Max)
                throw new Exception("저장 공간 부족");  //오버플로우 조건 검색
            acciolist[Size] = acc;
            Size++;
        }
    }
}
