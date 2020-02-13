using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _1029과제
{
    public class AccIo : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private int? daccid;
        private int? depo;
        private int? whit;
        private int? dbalance;
        private DateTime dealdate;

        #region 프로퍼티
        public int? DAccid
        {
            get { return daccid; }
            set
            {
                daccid = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("DAccid"));
            }
        }
        public int? Depo
        {
            get { return depo; }
            set
            {
                depo = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Depo"));
            }
        }
        public int? Whit
        {
            get { return whit; }
            set
            {
                whit = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Whit"));
            }
        }
        public int? Dbalance
        {
            get { return dbalance; }
            set
            {
                dbalance = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Dbalance"));
            }
        }
        public DateTime Dealdate
        {
            get { return dealdate; }
            set
            {
                dealdate = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Dealdate"));
            }
        }
        #endregion
    }

    public class AccIoList : ObservableCollection<AccIo>
    {
        public AccIoList()
        {
            //Add(new AccIo() { DAccid = 1, Depo = 0, Whit = 0, Dbalance=0, Dealdate = DateTime.Now });
        }
    }
}
