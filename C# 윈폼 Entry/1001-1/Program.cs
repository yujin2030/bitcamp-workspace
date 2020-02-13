using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace _1001_1
{
    class Program
    {
       static void Main(string[] args)
       {
            ArrayList ar = new ArrayList();
            XmlReader reader = XmlReader.Create("data.xml");
            while(reader.Read())
            {
                if (reader.IsStartElement("entry"))
                {
                    Entry entry = Entry.MakeEntry(reader);
                    if(entry != null)
                    {
                        ar.Add(entry);
                    }
                }

            }
            Console.WriteLine("엔트리 갯수 :{0}", ar.Count);
            foreach(Entry entry in ar)
            {
                Console.WriteLine("이름:{0} 전화번호:{1}", entry.Name, entry.Tel);
            }
       }
    }
}
