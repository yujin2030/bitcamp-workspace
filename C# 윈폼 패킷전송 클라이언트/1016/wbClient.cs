using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1016
{
    class wbClient
    {
        private Socket server;
        private Form1 form;
        public string ServerIp { get; private set; }
        public int ServerPort { get; private set; }
        Thread ComThread;
        public void ParentInfo(Form1 f)
        {
            form = f;
        }
       
        public bool Connet(string ip, string port)
        {
            try
            {
                IPEndPoint ipep = new IPEndPoint(IPAddress.Parse(ip), int.Parse(port));
                server = new Socket(AddressFamily.InterNetwork,
                                   SocketType.Stream, ProtocolType.Tcp);
                server.Connect(ipep);

                IPEndPoint addr = (IPEndPoint)server.LocalEndPoint;
                ServerIp = addr.Address.ToString();
                ServerPort = int.Parse(port);

                ComThread = new Thread(new ThreadStart(RecvMessage));
                ComThread.Start();
                ComThread.IsBackground = true;
                return true;
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
                return false;
            }
        }

        public void Disconnet()
        {
            server.Close();
        }

        public void SendMessage(string msg)
        {
            SendData(Encoding.Default.GetBytes(msg));
        }

        private void SendData(byte[] data)
        {
            try
            {
                int total = 0;
                int size = data.Length;
                int left_data = size;
                int send_data = 0;

                // 전송할 데이터의 크기 전달
                byte[] data_size = new byte[4];
                data_size = BitConverter.GetBytes(size);
                send_data = server.Send(data_size);

                // 실제 데이터 전송
                while (total < size)
                {
                    send_data = server.Send(data, total, left_data, SocketFlags.None);
                    total += send_data;
                    left_data -= send_data;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        public void RecvMessage()
        {
            byte[] data = null;
            while (true)
            {
                ReceiveData(ref data);
                //데이터 분석
                form.PaserByteData(data);
                //form.MessagePrint(data);
            }
        }

        private void ReceiveData(ref byte[] data)
        {
            try
            {
                int total = 0;
                int size = 0;
                int left_data = 0;
                int recv_data = 0;

                // 수신할 데이터 크기 알아내기 
                byte[] data_size = new byte[4];
                recv_data = server.Receive(data_size, 0, 4, SocketFlags.None);
                size = BitConverter.ToInt32(data_size, 0);
                left_data = size;

                data = new byte[size];

                // 실제 데이터 수신
                while (total < size)
                {
                    recv_data =server.Receive(data, total, left_data, 0);
                    if (recv_data == 0) break;
                    total += recv_data;
                    left_data -= recv_data;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        #region 패킷전송
        public void Send(string msg)
        {
            try
            {
                if(server.Connected)
                {
                    byte[] data = Encoding.Default.GetBytes(msg);
                    SendData(data);
                }
                else
                {
                    MessageBox.Show("서버와 연결되지않음");
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        #endregion

    }
}
