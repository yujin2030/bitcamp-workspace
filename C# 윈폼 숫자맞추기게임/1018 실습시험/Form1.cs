using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1018_실습시험
{
    public partial class Form1 : Form
    {
        Client server = new Client();
        Packet pack = Packet.Instance;

        Client client = new Client();

        public Form1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (server.Connect(textBox1.Text, int.Parse(textBox2.Text)) == true)
            {
                listBox1.Items.Add("게임이 시작합니다. 숫자를 입력하세요");
            }
            else
            {
                listBox1.Items.Add("서버 연결이 실패했습니다. 다시 시도해 주세요");
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            server.DisConnect();
        }

        public void PaserByteDate(byte[] data)
        {
            string msg = Encoding.Default.GetString(data);
            string[] token = msg.Split('@');
            switch (token[0].Trim())
            {
                case "SENDNUMBERACK": SendNumberAck(token[1]); break;
                case "SENDNUMBERSUCCESSACK": SendNumberSuccessAck(token[1]); break;
            }
        }

        void SendNumberAck(string msg)
        {
            string[] sp = msg.Split('#');

            listBox1.Items.Add(sp[0] + "  보낸숫자:" + sp[1] + "  결과문자열:" + sp[2]);

        }

        void SendNumberSuccessAck(string msg)
        {
            string[] sp = msg.Split('#');

            listBox1.Items.Add(sp[0] + "  보낸숫자:" + sp[1] + "  정답숫자:" + sp[2]);
            listBox1.Items.Add("최유진님 정답입니다.");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                string msg = pack.SendNumber(textBox3.Text, int.Parse(textBox4.Text));

                server.Send(msg);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
