using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _1029과제
{
    public class Account : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private int? accid;
        private string name;
        private int? balance;
        private DateTime date;
        #region 프로퍼티
        public int? Accid
        {
            get { return accid; }
            set
            {
                accid = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Accid"));
            }
        }
        public string Name
        {
            get { return name; }
            set
            {
                name = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Name"));
            }
        }
        public int? Balance
        {
            get { return balance; }
            set
            {
                balance = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Balance"));
            }
        }

        public DateTime Date
        {
            get { return date; }
            set
            {
                date = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Date"));
            }
        }

        #endregion
    }

    public class AccList : ObservableCollection<Account>
    {
        public AccList()
        {
            Add(new Account() { Accid = 1, Name = "고길동", Balance = 1000, Date = DateTime.Now });
            Add(new Account() { Accid = 2, Name = "홍길동", Balance = 2500, Date = DateTime.Now });
            Add(new Account() { Accid = 3, Name = "이몽룡", Balance = 1500, Date = DateTime.Now });
            Add(new Account() { Accid = 4, Name = "성춘향", Balance = 6800, Date = DateTime.Now });
        }
    }
}
