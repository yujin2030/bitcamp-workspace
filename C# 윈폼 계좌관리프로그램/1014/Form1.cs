using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1014
{
    public partial class Form1 : Form
    {
        private wbMDB mdb = new wbMDB();

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(mdb.CreateAccTable()==true)
            {
                string str = mdb.ViewAccTable();
                textBox1.Text = str;
            }
            else
            {

            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            mdb.AddAccount(int.Parse(textBox2.Text), "" + textBox3.Text, int.Parse(textBox4.Text));
            textBox5.Text = mdb.ViewAccData();

        }

        private void button3_Click(object sender, EventArgs e)
        {
            mdb.Save();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //계좌아이디
            if(radioButton1.Checked == true)
            {
                mdb.IdToSelectAccount(int.Parse(textBox11.Text));

            }
            //계좌번호
            else
            {

            }
        }
    }
}
