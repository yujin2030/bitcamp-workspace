using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1016씨샾TCP
{
    public partial class Form3 : Form
    {
        public string Id { get; set; }
        public string Pw { get; set; }
        public string MyName { get; set; }
        public int Age { get; set; }

        public Form3()
        {
            InitializeComponent();
        }


        private void button2_Click(object sender, EventArgs e)
        {
            MessageBox.Show("회원 가입 취소");
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Id = textBox1.Text;
            Pw = textBox2.Text;
            MyName = textBox3.Text;
            Age = int.Parse(textBox4.Text);
            this.DialogResult = DialogResult.OK;
        }
    }
}
