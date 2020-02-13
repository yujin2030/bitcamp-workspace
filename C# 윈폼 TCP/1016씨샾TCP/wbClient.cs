using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1016씨샾TCP
{
    class wbClient
    {
        private Socket server;
        private Form1 form;
        public string ServerIp { get; private set; }
        public int ServerPort { get; private set; }

        public void parent(Form1 f)
        {
            form = f;
        }

        public bool Connect(string ip, int port)
        {
            try
            {
                server = new Socket(AddressFamily.InterNetwork,
                                      SocketType.Stream, ProtocolType.Tcp);

                IPEndPoint ipep = new IPEndPoint(IPAddress.Parse(ip), port);

                server.Connect(ipep);

                Thread thread = new Thread(new ThreadStart(RecvMessage));
                thread.Start();
                thread.IsBackground = true;

                return true;
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
                return false;
            }
        }
        
        public void DisConnect()
        {
            try
            {
                server.Close();
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        public void SendMessage(string msg)
        {
            try
            {
                SendData(server,Encoding.Default.GetBytes(msg));
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        public void RecvMessage()
        {
            while (true)
            {
                byte[] data=null;
                ReceiveData(server,ref data);
                form.PaserByteData(data);
                form.Print(Encoding.Default.GetString(data));
            }
        }
        //byte 형식을 string 형식으로 변환
        public void Send(string msg)
        {
            try
            {
                if (server.Connected)
                {
                    byte[] data = Encoding.Default.GetBytes(msg);
                    this.SendData(server, data);
                }
                else
                {
                    MessageBox.Show("서버 미연결");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void SendData(Socket sock, byte[] data)
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
                send_data = sock.Send(data_size);

                // 실제 데이터 전송
                while (total < size)
                {
                    send_data = sock.Send(data, total, left_data, SocketFlags.None);
                    total += send_data;
                    left_data -= send_data;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private void ReceiveData(Socket sock, ref byte[] data)        //가변데이터 받아오는 메소드
        {
            try
            {
                int total = 0;
                int size = 0;
                int left_data = 0;
                int recv_data = 0;

                // 수신할 데이터 크기 알아내기 
                byte[] data_size = new byte[4];
                recv_data = sock.Receive(data_size, 0, 4, SocketFlags.None);
                size = BitConverter.ToInt32(data_size, 0);
                left_data = size;

                data = new byte[size];

                // 실제 데이터 수신
                while (total < size)
                {
                    recv_data = sock.Receive(data, total, left_data, 0);
                    if (recv_data == 0) break;
                    total += recv_data;
                    left_data -= recv_data;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        

    }
}
