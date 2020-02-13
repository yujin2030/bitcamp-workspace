using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1016
{
    class Ui
    {
        public static void FillRectangle(Color cor, Control c)
        {
            c.BackColor = cor;
        }

        public static void LabelState(Control c,bool b)
        {
            if(b==true)
            {
                c.Text = "서버연결중...";
            }
            else
            {
                c.Text = "서버연결해제...";
            }
        }

        public static void LogPrint(ListBox c,string msg)
        {
            msg += "("+DateTime.Now.ToString()+")";
            c.Items.Add(msg);
        }

        public static void DataPrint(ListBox c, string msg)
        {
            c.Items.Add(msg);
        }
    }
}
