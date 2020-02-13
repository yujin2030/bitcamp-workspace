using System;
using System.Collections.Generic;
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

namespace _1028__데이터바인딩
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        private People people = new People();
        private Person per;

        public MainWindow()
        {
            InitializeComponent();
            per = people[0];

            UpdateData();

            UpdateListBox();
        }

        #region date >> UI
        public void UpdateData()
        {
            UpdateNameToUI();
            UpdatePhoneToUI();
            UpdateAgeToUI();
        }


        private void UpdateNameToUI()
        {
            if (per == null)
            {
                name.Text = "";
                nameLabel.Content = "";
            }
            else
            {
                name.Text = per.Name;
                nameLabel.Content = per.Name;
            }
        }
        private void UpdatePhoneToUI()
        {
            if (per == null)
            {
                phone.Text = "";
                phoneLabel.Content = "";
            }
            else
            {
                phone.Text = per.Phone;
                phoneLabel.Content = per.Phone;
            }
        }
        private void UpdateAgeToUI()
        {
            if (per == null)
            {
                age.Text = "";
                ageLabel.Content = per.Age;
            }
            else
            {
                age.Text = per.Age.ToString();
                ageLabel.Content = per.Age;
            }
        }

        private void UpdateListBox()
        {
            listbox.Items.Clear();
            foreach (Person per in people)
                listbox.Items.Add(per);
        }
        #endregion

        private void name_Textchanged(object sender, TextChangedEventArgs e)
        {
            per.Name = name.Text;
            //Title = per.Name;
        }

        private void phone_Textchanged(object sender, TextChangedEventArgs e)
        {
            per.Phone = phone.Text;
            Title = per.Phone;
        }

        private void age_Textchanged(object sender, TextChangedEventArgs e)
        {
            per.Age = int.Parse(age.Text);
            //Title = per.Age.ToString();
        }


        private void Listbox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if(listbox.SelectedIndex >= 0)
            {
                per = people[listbox.SelectedIndex];
                UpdateData();
            }
        } 

        #region 버튼 이벤트 핸들러
        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            if (name.Text == "" || phone.Text == "" || age.Text == "")
                return;
            people.Add(new Person() { Name = name.Text, Phone = phone.Text, Age = int.Parse(age.Text) });

            per = people[people.Count - 1];      //위치정보추가..? 이게몬대..

            UpdateData();
            UpdateListBox();
        }

        private void RemoveButton_Click(object sender, RoutedEventArgs e)
        {
            if(listbox.SelectedIndex >=0)
            {
                people.RemoveAt(listbox.SelectedIndex);

                if (people.Count == 0)
                    per = null;
                else
                    per = people[0];

                UpdateData();
                UpdateListBox();
            }
        }

        private void UpdateButton_Click(object sender, RoutedEventArgs e)
        {
            if (name.Text == "" || phone.Text == "" || age.Text == "")
                return;

            per.Name = name.Text;
            per.Phone = phone.Text;
            per.Age = int.Parse(age.Text);

            UpdateData();
            UpdateListBox();

        }
        #endregion
    }
}
