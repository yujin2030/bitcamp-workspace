using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1016
{
    public partial class NewMemberForm : Form
    {
        public string Id { get; private set; }
        public string Pw { get; private set; }
        public string MyName { get; private set; }
        public int Age { get; private set; }
        public NewMemberForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                Id = textBox1.Text;
                Pw = textBox2.Text;
                MyName = textBox3.Text;
                Age = int.Parse(textBox4.Text);
                this.DialogResult=DialogResult.OK;
            }
           catch(Exception)
            {
                MessageBox.Show("입력값을 확인해주세요");
            }
        }
    }
}
