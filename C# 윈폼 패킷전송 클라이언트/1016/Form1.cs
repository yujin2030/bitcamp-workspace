using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1016
{
    public partial class Form1 : Form
    {
        wbClient client = new wbClient();
        
        Packet packet = Packet.Instance;
        public string MyName { get; set; }
        public string Id { get; set; }
        public bool IsLogin { get; private set; }
        public Form1()
        {
            InitializeComponent();
            client.ParentInfo(this);
            IsLogin = false;
        }

        private void 서버연결ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ServerInfo dlg = new ServerInfo();
            if( dlg.ShowDialog()==DialogResult.OK)
            {
                 if(client.Connet(dlg.IP, dlg.Port)==true)
                 {
                    Ui.FillRectangle(Color.Blue, panel1);
                    Ui.LabelState(label1, true);

                    string temp = string.Format("[연결] {0}:{1} 성공", client.ServerIp, client.ServerPort);
                    Ui.LogPrint(listBox1, temp);
                 }
            }
        }

        private void 서버연결해제ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                client.Disconnet();
                string temp = string.Format("[해제] {0}:{1} 성공", client.ServerIp, client.ServerPort);
                Ui.LogPrint(listBox1, temp);
                Ui.FillRectangle(Color.Red, panel1);
                Ui.LabelState(label1, false);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void 프로그램종료ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        public void MessagePrint(string data)
        {
            Ui.DataPrint(listBox2, data);
        }

        //전송버튼
        private void button1_Click(object sender, EventArgs e)
        {
            string msg;
            msg=packet.GetMessage(textBox2.Text, textBox1.Text);
            client.SendMessage(msg);
        }

        //회원가입
        private void button2_Click(object sender, EventArgs e)
        {
            NewMemberForm dlg = new NewMemberForm();
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                string msg;
                msg=packet.GetNewMember(dlg.Id, dlg.Pw, dlg.MyName, dlg.Age);
                client.SendMessage(msg);
            }
            else
                return;
        }

        //로그인버튼
        private void button3_Click(object sender, EventArgs e)
        {
            string msg;
            msg=packet.GetLogin(textBox3.Text,textBox4.Text);
            client.SendMessage(msg);
        }

        //로그아웃버튼
        private void button4_Click(object sender, EventArgs e)
        {
            string msg;
            msg = packet.GetLogOut(textBox3.Text);
            client.SendMessage(msg);
        }

        //탈퇴
        private void button5_Click(object sender, EventArgs e)
        {
            string msg;
            msg = packet.GetDelMember(textBox3.Text);
            client.SendMessage(msg);
        }

        #region 수신패킷 분석
        public void PaserByteData(byte[] data)
        {
            string msg = Encoding.Default.GetString(data);
            string[] token = msg.Split('@');
            switch (token[0].Trim())
            {
                case "NEWMEMBERACK":
                    NewMemberAck(token[1]);
                    break;
                case "DELMEMBERACK":
                    DelMemberAck(token[1]);
                    break;
                case "LOGINACK":
                    LoginAck(token[1]);
                    break;
                case "LOGOUTACK":
                    LogoutAck(token[1]);
                    break;
                case "MESSAGE":
                    if (IsLogin == true)
                        MessagePrint(token[1]);
                    break;
            }
        }
        #endregion

        #region 수신 패킷 처리
        private void NewMemberAck(string msg)
        {

            string[] sp = msg.Split('#');
           
            if (sp[0].Equals("True"))
            {
                this.Text = string.Format("{0}님 환영합니다({1})", sp[2], sp[1]);
                string data = string.Format("{0}님이 가입 하셨습니다", sp[2]);
                MessagePrint(data);
            }
            else
            {
                MessageBox.Show("회원가입 실패");
            }
        }

        private void DelMemberAck(string msg)
        {
            string[] sp = msg.Split('#');

            if (sp[0].Equals("True"))
            {
                MessageBox.Show("탈퇴 성공");
            }
            else
            {
                MessageBox.Show("없는 ID입니다.");
            }
        }

        private void LoginAck(string msg)
        {
            string[] sp = msg.Split('#');
            if (sp[0].Equals("True"))
            {
                if(textBox3.Text.Equals(sp[1]) && IsLogin==false)
                {
                    IsLogin = true;
                    Id = sp[1];
                    MyName = sp[2];
                    this.Text = string.Format("{0}님이 로그인 하셨습니다", MyName);
                    MessagePrint(msg);
                }
               else if(IsLogin==true)
                {
                    string data = string.Format("{0}님이 로그인 하셨습니다", sp[1]);
                    MessagePrint(data);
                }
            }
            else if(sp[0].Equals("False") && textBox3.Text.Equals(sp[1]))
            {
                MessageBox.Show("로그인 실패");
            }
        }

        private void LogoutAck(string msg)
        {
            string[] sp = msg.Split('#');

            if (sp[0].Equals("True"))
            {
                if(sp[1].Equals(Id) && IsLogin == true)
                {
                    IsLogin = false;
                    Id = null;
                    MyName = null;

                    string data = string.Format("로그아웃하셨습니다");
                    MessagePrint(data);
                }
                else if(IsLogin==true)
                {
                    string data = string.Format("{0}님이 로그아웃 하셨습니다", sp[1]);
                    MessagePrint(data);
                }
            }
            else if(sp[0].Equals("False") && sp[1].Equals(Id))
            {
                MessageBox.Show("로그아웃 실패");
            }
        }
        #endregion
    }
}
