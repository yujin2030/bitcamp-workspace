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
    /// Window1.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class Window1 : Window
    {
        List<Rectangle> rlist = new List<Rectangle>();

        public Window1()
        {
            InitializeComponent();
        }

        private void Canvas_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            Point pt = e.GetPosition(canvas1); //자별에 있는거를 소스코드에서 쓰려고 Canvas 이름 부여

            Rectangle rt = new Rectangle();
            rt.Width = 50;
            rt.Height = 50;
            rt.Stroke = new SolidColorBrush(Colors.Blue);
            rt.Fill = new SolidColorBrush(Colors.Yellow);
            rt.MouseDown += Rt_MouseDown;      //모든 버튼에 마우스 다운 이벤트 있숨

            Canvas.SetLeft(rt, pt.X);
            Canvas.SetTop(rt, pt.Y);

            canvas1.Children.Add(rt);
            rlist.Add(rt);          //리스트에 보관

        }

        private void Rt_MouseDown(object sender, MouseButtonEventArgs e)
        {
            Rectangle r = (Rectangle)sender;
            r.Fill = new SolidColorBrush(Colors.Red);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            foreach(Rectangle r in rlist)
            {
                double d = Canvas.GetLeft(r);
                Canvas.SetLeft(r, d + 10);
            }
        }
    }
}
