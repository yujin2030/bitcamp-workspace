using System;
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
using System.Windows.Shapes;

namespace _1028__데이터바인딩
{
    /// <summary>
    /// Window1.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class Window1 : Window
    {
        Person person = null;

        public Window1()
        {
            InitializeComponent();
            person = (Person)FindResource("person");

            Validation.AddErrorHandler(shortNumber, shortNumber_ValidationError);
            //panel.DataContext = person;           //데이터 바인딩
        }

        #region 예외처리
        void shortNumber_ValidationError(object sender, ValidationErrorEventArgs e)
        {
            MessageBox.Show((string)e.Error.ErrorContent, "유효성 검사 실패");

            shortNumber.ToolTip = ((string)e.Error.ErrorContent);
        }
        #endregion

        //public class Person
        //{
        //    public string Name { get; set; }
        //    public string Phone { get; set; }
        //    public int Age { get; set; }
        //}

        #region 버튼 핸들러
            //Clear
        private void EraseBUtton_Click(object sender, RoutedEventArgs e)
        {
            ICollectionView view = CollectionViewSource.GetDefaultView(FindResource("people"));
            Person person = (Person)view.CurrentItem;
            person.Name = "";
            person.Phone = "";
            person.Age = 0;
            person.Male = null;
        }

        //이전
        private void Prev_Click(object sender, RoutedEventArgs e)
        {
            ICollectionView view = CollectionViewSource.GetDefaultView(FindResource("people"));
            view.MoveCurrentToPrevious();
            if(view.IsCurrentBeforeFirst)
            {
                view.MoveCurrentToFirst();
            }
        }

        //다음
        private void Next_Click(object sender, RoutedEventArgs e)
        {
            ICollectionView view = CollectionViewSource.GetDefaultView(FindResource("people"));
            view.MoveCurrentToNext();
            if(view.IsCurrentAfterLast)
            {
                view.MoveCurrentToNext();
            }
        }

        //삭제
        private void RemoveButton_Click(object sender, RoutedEventArgs e)
        {
            People people = (People)FindResource("people");

            if (listbox.SelectedIndex >= 0)
            {
                people.RemoveAt(listbox.SelectedIndex);
            }
        }

        //저장
        private void InsertButton_Click(object sender, RoutedEventArgs e)
        {
            People people = (People)FindResource("people");

            Person newperson = new Person()
            {
                ShortNumber = person.ShortNumber,
                Name = person.Name,
                Phone = person.Phone,
                Age = person.Age,
                Male=person.Male

            };
            people.Add(newperson);
        }

        //검색
        private void Select_Click(object sender, RoutedEventArgs e)
        {
            ICollectionView view = CollectionViewSource.GetDefaultView(FindResource("people"));
            if(view.Filter == null)
            {
                view.Filter = delegate (object obj)
                {
                    return ((Person)obj).Name == selectName.Text;
                };
            }
            else
            {
                view.Filter = null;
            }
        }
        #endregion


    }
}
