using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class control
    {
        List<Account> acc = new List<Account>();

        #region 싱글톤 패턴
        static control con;
        public static control Instance
        {
            get
            {
                return con;
            }
        }

        static control()
        {
            con = new control();
        }

        private control()
        {
        }
        #endregion

        public void SortAccount(string idx)
        {
            switch (idx)
            {
                case "1": acc.Sort(new IDComparaer()); break;
                case "2": acc.Sort(); break;
                case "3": acc.Sort(new BalanceComparaer()); break;
                default: break;
            }
        }
        public bool DelAccount (int id)
        {
            for (int i = 0; i < acc.Count; i++)
            {
                Account mem = acc[i];
                if (mem.Id == id)
                {
                    acc.Remove(mem);
                    return true;
                }
            }
            return false;
        }
        public void InputAccount(int id, int balance)
        {
            for (int i = 0; i < acc.Count; i++)
            {
                Account mem = acc[i];
                if (mem.Id == id)
                {
                    mem.addmoney(balance);
                    return;
                }                    
            }
            throw new Exception("없음");
        }

        public void OutputAccount(int id, int balance)
        {
            for (int i = 0; i < acc.Count; i++)
            {
                Account mem = acc[i];
                if (mem.Id == id)
                {
                    mem.minmoney(balance);
                    return;
                }
            }
            throw new Exception("없음");
        }

        public Account SelectAccount(int id)
        {
            for (int i = 0; i < acc.Count; i++)
            {
                Account mem = acc[i];
                if (mem.Id == id)        
                                     
                    return mem;
            }
            throw new Exception("없음"); 
        }

        public bool AddAccount(Account mem)
        {
            acc.Add(mem);
            return true;
        }

        public void SelectAccount(out List<Account>mem)
        {
            mem = acc;
        }
    }
}
