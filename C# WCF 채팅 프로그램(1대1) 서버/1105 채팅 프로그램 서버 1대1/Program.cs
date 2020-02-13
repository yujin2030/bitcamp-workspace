﻿using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace _1105_채팅_프로그램_서버_1대1
{
    class Program
    {
        static void Main(string[] args)
        {
            //Address
            Uri uri = new Uri(ConfigurationManager.AppSettings["addr"]);
            //Contract-> Setting
            //Binding -> App.Config
            ServiceHost host = new ServiceHost(typeof(ChatService), uri);

            //exe Hosting
            //ServiceHost host =
            //    new ServiceHost(typeof(_1105_채팅_프로그램_서버_1대1.ChatService)
            //        /*new Uri("http://192.168.0.47:8888/wcf/example/helloworldservice")*/);

            //오픈
            host.Open();
            Console.WriteLine("채팅 서비스를 시작합니다. {0}", uri.ToString());
            Console.WriteLine("http://192.168.0.47:7000/GetService");
            Console.WriteLine("멈추시려면 엔터를 눌러주세요..");
            Console.ReadLine();
            //서비스
            host.Abort();
            host.Close();


        }
    }
}
