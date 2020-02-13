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
    public partial class Form1 : Form
    {
        Form2 dlg = null;
        Form3 frm3 = null;

        wbClient client = new wbClient();

        public Form1()
        {
            InitializeComponent();
            client.parent(this);
        }
        public void Print(string msg)
        {
            Ui.DataPrint(listBox2, msg);
        }

        #region 메뉴
        private void 프로그램종료ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void 서버연결ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            dlg =  new Form2();
            if(dlg.ShowDialog() == DialogResult.OK)
            {
                //dlg.IP;
                //dlg.Port;
                if(client.Connect(dlg.IP, dlg.Port) ==true)
                {
                    Ui.FillDrawing(panel1, Color.Blue);
                    Ui.LabelState(label1, true);

                    String temp = String.Format("[연결]{0}:{1} 성공", dlg.IP, dlg.Port);
                    Ui.LogPrint(listBox1, temp);
                }
                else
                {
                    String temp = String.Format("[연결]{0}:{1} 실패", dlg.IP, dlg.Port);
                    Ui.LogPrint(listBox1, temp);
                }
            }
        }

        private void 서버연결해제ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            client.DisConnect();

            Ui.FillDrawing(panel1, Color.Red);
            Ui.LabelState(label1, false);

            String temp = String.Format("[접속해제]{0}:{1} 성공", dlg.IP, dlg.Port);
            Ui.LogPrint(listBox1, temp);
        }

        private void 회원가입ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            frm3 = new Form3();
            if (frm3.ShowDialog() == DialogResult.OK)
            {
                string msg;
                msg = Packet.Instance.GetNewMember(frm3.Id, frm3.Pw, frm3.MyName, frm3.Age);
                client.SendMessage(msg);
            }
        }
        #endregion

        #region 버튼
        private void button1_Click(object sender, EventArgs e)        //메세지전송
        {
            //string msg = string.Format(" {0}", textBox2.Text);
            string msg;
            msg = Packet.Instance.GetMessage(textBox2.Text);

            client.SendMessage(msg);         
        }

        private void button2_Click(object sender, EventArgs e)    //로그인
        {
            string msg;
            msg = Packet.Instance.GetLogin(textBox1.Text, textBox3.Text);
            client.SendMessage(msg);
            Print(msg);
        }

        private void button3_Click(object sender, EventArgs e) //로그아웃
        {
            string msg;
            msg = Packet.Instance.GetLogout(textBox1.Text);
            client.SendMessage(msg);
            Print(msg);
        }

        private void button4_Click(object sender, EventArgs e)    //삭제
        {
            string msg;
            msg = Packet.Instance.DelMember(textBox1.Text);
            client.SendMessage(msg);
        }
        #endregion

        #region 수신패킷 분석 및 처리
        public void PaserByteData(byte[] data)
        {
            string msg = Encoding.Default.GetString(data);
            string[] token = msg.Split('@');
            //this.Text = "1";
            switch (token[0].Trim())
            {             
                case "NEWMEMBERACK": NewMemberAck(token[1]);  break;
                case "DELMEMBERACK": DelMemberAck(token[1]); break;
                case "LOGOUTACK": LogoutAck(token[1]); break;
                case "LOGINACK": LoginAck(token[1]); break;
                case "MESSAGE": MessageAck(token[1]); break;
            }
        }

        void NewMemberAck(string msg)
        {
            string[] sp = msg.Split('#');

            //string ackmessage;
            if(bool.Parse(sp[0])==true)
            {
                //ackmessage = Packet.Instance.GetNewMemberAck(mem.Id, mem.Name, true);
                this.Text="회원가입을 축하드립니다~";
            }
            else
            {
                //ackmessage = Packet.Instance.GetNewMemberAck(mem.Id, mem.Name, false);
                MessageBox.Show("회원가입실패!");
            }

        }

        void DelMemberAck(string msg)
        {
            string[] sp = msg.Split('#');

            if (bool.Parse(sp[0]) == true)
            {
                MessageBox.Show("회원 삭제 성공!");
            }
            else
            {
                MessageBox.Show("회원 삭제 실패!");
            }

        }

        void LogoutAck(string msg)
        {
            string[] sp = msg.Split('#');

            if (bool.Parse(sp[0]) == true)
            {
                MessageBox.Show("로그아웃 성공!");
            }
            else
            {
                MessageBox.Show("로그아웃 실패!");
            }
        }

        void LoginAck(string msg)
        {
            
            string[] sp = msg.Split('#');

            if (bool.Parse(sp[0]) == true)
            {
                this.Text = string.Format("{0}님이 로그인하셨습니다.", sp[1]);
            }

            else
            {
                MessageBox.Show("로그인 실패!");
            }

        }

        void MessageAck(string msg)
        {
            string[] sp = msg.Split('#');

            if (bool.Parse(sp[0]) == true)
            {
                MessageBox.Show("메세지보내기 성공!");
            }
            else
            {
                MessageBox.Show("메세지보내기 실패!");
            }
        }


        #endregion
    }
}
