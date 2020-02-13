using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace _1029과제
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        private Account acc = null;
        private AccList acclist = null;
        private AccIo accio = null;
        private AccIoList acciolist = null;
        public MainWindow()
        {
            InitializeComponent();
            acc = (Account)FindResource("account");
            acclist = (AccList)FindResource("acclist");
            accio = (AccIo)FindResource("accountio");
            acciolist = (AccIoList)FindResource("accountiolist");
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            acc = (Account)FindResource("account");

            Account newaccount = new Account()
            {
                Accid = acc.Accid,
                Balance = acc.Balance,
                Name = acc.Name,
                Date = DateTime.Now
            };
            acclist.Add(newaccount);
        }

        private void removeButton_Click(object sender, RoutedEventArgs e)
        {
            Account ac = acclist[acclistbox.SelectedIndex];
            int idx = 0;
            
            while(idx<acciolist.Count)
            {
                if (acciolist[idx].DAccid.Equals(ac.Accid))
                    acciolist.RemoveAt(idx);
                else
                    idx++;
            }

            if (acclistbox.SelectedIndex>=0)
            {
                acclist.Remove(ac);
            }

        }

        private void sortButton_Click(object sender, RoutedEventArgs e)
        {
            int idx = sortcombo.SelectedIndex;
            ICollectionView view =
                CollectionViewSource.GetDefaultView(FindResource("acclist"));

            if (idx == -1)
                return;
            if (view.SortDescriptions.Count > 0)
            {
                view.SortDescriptions.Clear();
            }

            switch (idx)
            {
                case 0:
                    view.SortDescriptions.Add(new SortDescription("Name",
                ListSortDirection.Ascending)); break;

                case 1:
                    view.SortDescriptions.Add(new SortDescription("Balance",
                ListSortDirection.Ascending)); break;

                case 2:
                    view.SortDescriptions.Add(new SortDescription("Accid",
                ListSortDirection.Ascending)); break;
            }
        }

        private void serchnameButton_Click(object sender, RoutedEventArgs e)
        {
            ICollectionView view = CollectionViewSource.GetDefaultView(FindResource("acclist"));
            
            view.Filter = delegate (object obj)
            {
                Account per = (Account)obj;
                return per.Name.Equals(nameserch.Text);
            };

        }

        private void serchbalanceButton_Click(object sender, RoutedEventArgs e)
        {
            ICollectionView view = CollectionViewSource.GetDefaultView(FindResource("acclist"));

            view.Filter = delegate (object obj)
            {
                Account per = (Account)obj;
                return per.Balance >= int.Parse(balanceserch.Text);
            };
        }

        private void allButton_Click(object sender, RoutedEventArgs e)
        {
            ICollectionView view = CollectionViewSource.GetDefaultView(FindResource("acclist"));
            view.Filter = null;
        }

        private void dealButton_Click(object sender, RoutedEventArgs e)
        {
            Account ac = (Account)accinfocombo.SelectedItem;
            int? money = int.Parse(Inout.Text);


            if (DefoRadio.IsChecked==true)
            {
                ac.Balance += money;
                AccIo accountio = new AccIo()
                {
                    DAccid = ac.Accid,
                    Depo = money,
                    Dbalance = ac.Balance,
                    Whit = 0,
                    Dealdate = DateTime.Now
                };
                acciolist.Add(accountio);
            }
            else if(WithRadio.IsChecked==true)
            {
                if (ac.Balance < money)
                    return;
                ac.Balance -= money;
                AccIo accountio = new AccIo()
                {
                    DAccid = ac.Accid,
                    Depo = 0,
                    Dbalance = ac.Balance,
                    Whit = money,
                    Dealdate = DateTime.Now
                };
                acciolist.Add(accountio);
            }

            
        }
    }

}
