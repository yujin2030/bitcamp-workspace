using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1016씨샾TCP
{
    class Ui
    {
        public static void FillDrawing(Control c, Color color)
        {
            c.BackColor = color;
            //Graphics g = c.CreateGraphics();
            //g.FillRectangle(new SolidBrush(color), c.ClientRectangle);
            //g.Dispose();
        }

        public static void LabelState(Control c,  bool b)
        {
            if(b)
            {
                c.Text = "서버실행 중....";
                c.BackColor = Color.Blue;
            }
            else
            {
                c.Text = "서버정지";
                c.BackColor = Color.Red;
            }
        }

        public static void LogPrint(ListBox c, string msg)        //시간출력
        {
            //msg = [연결]....성공
            msg += "(" + DateTime.Now.ToString() + ")";
            c.Items.Add(msg);
        }

        public static void DataPrint(ListBox c, string msg)
        {
            c.Items.Add(msg);
        }
    }
}
