using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Data;

namespace _1028__데이터바인딩
{
    public class Person : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private int? shortNumber;
        public int? ShortNumber
        {
            get { return shortNumber; }
            set
            {
                shortNumber = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("ShortNumber"));
            }
        }


        private string name;
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

        private string phone;
        public string Phone
        {
            get { return phone; }
            set
            {
                phone = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Phone"));
            }
        }

        private int age;
        public int Age
        {
            get { return age; }
            set
            {
                age = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Age"));
            }
        }

        private bool? male;
        public bool? Male
        {
            get { return male; }
            set
            {
                male = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Male"));
            }

        }

        public override string ToString()
        {
            return ShortNumber + " : " + Name + " : " + Phone + " : " + Age + " " + Male;
        }
    }

    public class MaleToFemaleConverter : IValueConverter
    {
        //데이터 속성을 UI 속성으로 변경할 때
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (targetType != typeof(bool?))
                return null;

            bool? male = (bool?)value;

            if (male == null)
                return null;
            else
                return !(bool?)value;
        }

        //UI 속성을 데이터 속성으로 변경할 때
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (targetType != typeof(bool?))
                return null;

            bool? male = (bool?)value;

            if (male == null)
                return null;
            else
                return !(bool?)value;
        }
    }

    //형식변환기 : bool <--> string
    public class BoolToStringConverter : IValueConverter
    {
        //데이터 속성을 UI 속성으로 변경할 때
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            //if (targetType != typeof(bool?))
            //    return null;

            bool? male = (bool?)value;

            if (male == null)
                return "";
            else if (male == true)
                return "남성";
            else
                return "여성";
        }

        //UI 속성을 데이터 속성으로 변경할 때
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            //if (targetType != typeof(bool?))
            //    return null;

            string male = (string)value;

            if (male == "")
                return null;
            else if (male == "남성")
                return null;
            else
                return "여성";
        }
    }

    public class ShortNumberValidationRule : ValidationRule
    {
        public int min { get; set; }
        public int max { get; set; }

        public int Min
        {
            get { return min; }
            set { min = value; }
        }

        public int Max
        {
            get { return max; }
            set { max = value; }
        }


        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            int number;
            if (!int.TryParse((string)value, out number))
            {
                return new ValidationResult(false, "정수를 입력하세요.");
            }

            if (Min <= number && number <= max)
            {

                return ValidationResult.ValidResult;
            }
            else
            {
                string msg = string.Format("단축번호는 {0}에서 {1}까지 입력 가능합니다.", min, max);
                return new ValidationResult(false, msg);
            }
        }
    }

    public class People : ObservableCollection<Person>
    {
        public People()
        {
            Add(new Person() { ShortNumber = 0, Male = true, Name = "홍길동", Phone = "010-1111-1234", Age = 20 });
            Add(new Person() { ShortNumber = 1, Male = true, Name = "일지매", Phone = "010-2222-1234", Age = 22 });
            Add(new Person() { ShortNumber = 2, Male = false, Name = "임꺽정", Phone = "010-3333-1234", Age = 24 });
        }
    }
}
