using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0926
{
    class Sample1
    {
        List<string> list = new List<string>();

        #region 검색 관련 코드 ============================
        private string Key { get; set; }
        private Predicate<string> predicate;
        private bool FindString(string s)
        {
            return s.Equals(Key);
        }
        public Sample1()
        {
            predicate = FindString;
        }
        #endregion 

        //저장 : Add, Insert
        public void insert(string data)
        {
            list.Add(data);
            Console.WriteLine("저장 성공");
        }

        public void printall()
        {
            for (int i = 0; i < list.Count; i++)
            {
                Console.Write(list[i] + ",");
            }
            Console.WriteLine("");
        }

        public void select(string key)
        {
            try
            {
                Key = key;
                string finddata = list.Find(predicate);
                Console.WriteLine("찾은 문자열 : " + finddata);
            }
            catch (Exception)
            {
                Console.WriteLine("없다.");
            }
        }

        public void update(string key, string updatedata)
        {
            try
            {
                Key = key;
                int idx = list.FindIndex(predicate);
                list[idx] = updatedata;
            }
            catch (Exception)
            {
                Console.WriteLine("없다.");
            }
        }

        public void delete(string key)
        {
            if (list.Remove(key) == true)
                Console.WriteLine("성공");
            else
                Console.WriteLine("실패");
        }
    }
}
