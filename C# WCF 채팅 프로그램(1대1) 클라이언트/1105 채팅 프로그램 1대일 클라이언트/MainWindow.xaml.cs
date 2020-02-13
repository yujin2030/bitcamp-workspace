using System;
using System.ServiceModel;
using System.Windows;
using _1105_채팅_프로그램_1대일_클라이언트.ServiceReference1;


namespace _1105_채팅_프로그램_1대일_클라이언트
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window, IChatCallback
    {
        int idx;
        private IChat chat;

        public MainWindow()
        {
            InitializeComponent();
        }

        //private void Window_Loaded(object sender, RoutedEventArgs e)
        //{
        //    //2 ===================================================
        //    InstanceContext site = new InstanceContext(this);
        //    chat = new ChatClient(site);
        //}

        #region IChatCallback 인터페이스 함수 생성
        public void Receive(int idx, string message)
        {
            string msgtemp = string.Format("{0}", message);
            chatlist.Items.Add(msgtemp);
        }


        public void UserEnter(int idx)
        {
            string msgtemp = string.Format("{0}님이 로그인하셨습니다.", idx);
            chatlist.Items.Add(msgtemp);
        }
        #endregion

        #region 로그인/로그아웃 핸들러
        private void BtnJoin_Click(object sender, RoutedEventArgs e)
        {
            if ((string)btnJoin.Content == "로그인")
                this.Connect();
            else
                this.DisConnect();

        }

        private void Connect()
        {
            try
            {
                idx = int.Parse(seatbox.Text);

                //서버 접속
                if (chat.Join(idx))
                {
                    MessageBox.Show("접속 성공");
                }
                else
                    MessageBox.Show("접속 실패");

                btnJoin.Content = "로그아웃";
                string login = string.Format("{0}님이 로그인하셨습니다.", seatbox.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show("접속 오류 : " + ex.Message);
            }
        }

        private void DisConnect()
        {
            try
            {
                chat.Leave(idx);
                btnJoin.Content = "로그인";

                string logout = string.Format("{0}님이 로그아웃하셨습니다.", seatbox.Text);
                chatlist.Items.Add(logout);
            }
            catch (Exception ex)
            {
                MessageBox.Show("나가기 오류 :{0}", ex.Message);
            }
        }
        #endregion


        // 메시지 전송
        private void BtnSend_Click(object sender, RoutedEventArgs e)
        {
            if (btnJoin.Content.Equals("로그아웃"))
            {
                string msg = msgbox.Text;

                string temp = string.Format("[{0}]", msg);

                chat.Say(idx, msg);

                msgbox.Clear();
            }
            else
                MessageBox.Show("로그인을 하시오");

        }

        private void Window_Loaded_1(object sender, RoutedEventArgs e)
        {
            //2 ===================================================
            InstanceContext site = new InstanceContext(this);
            chat = new ChatClient(site);
        }
    }
}
