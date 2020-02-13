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
using System.Windows.Shapes;

namespace _1025_WPF_앱으로
{
    /// <summary>
    /// Window2.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class Window2 : Window
    {
        public Window2()
        {
            InitializeComponent();
        }
        public string MSG { get; set; }

        //터널링 이벤트
        private void Window_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            MSG = "Window_터널링->";
        }

        private void Canvas_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            MSG += "Canvas_터널링->";
        }

        private void Label_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            MSG += "Label_터널링->";
        }
        private void StackPanel_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            MSG += "StackPanel_터널링->";
        }

        private void Ellipse_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            MSG += "Ellipse_터널링->";
        }
        private void Label_PreviewMouseDown_1(object sender, MouseButtonEventArgs e)
        {
            MSG += "Label1_터널링->";
        }
        //=========================================================================

        //버블링 이벤트
        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            MSG += "Window_버블링->";
            Title = MSG;
        }

        private void Canvas_MouseDown(object sender, MouseButtonEventArgs e)
        {
            MSG += "Canvas_버블링->";
        }

        private void Label_MouseDown(object sender, MouseButtonEventArgs e)
        {
            MSG += "Label_버블링->";
        }


        private void StackPanel_MouseDown(object sender, MouseButtonEventArgs e)
        {
            MSG += "StackPanel_버블링->";
        }

        private void Ellipse_MouseDown(object sender, MouseButtonEventArgs e)
        {
            MSG += "Ellipse_버블링->";
        }

        private void Label_MouseDown_1(object sender, MouseButtonEventArgs e)
        {
            MSG += "Label1_버블링->";
        }
    }
}
