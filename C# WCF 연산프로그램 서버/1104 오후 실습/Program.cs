﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace _1104_오후_실습
{
    class Program
    {
        static void Main(string[] args)
        {
            //exe Hosting
            ServiceHost host =
                new ServiceHost(typeof(CExample)
                    /*new Uri("http://192.168.0.47:8888/wcf/example/helloworldservice")*/);

            host.Open();
            Console.WriteLine("Press Any key to stop the service");
            Console.ReadKey();
            host.Close();
        }
    }
}
