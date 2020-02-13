using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace _1001_1
{
    class Entry
    {
        internal string Name { get; private set; }
        internal int Tel { get; private set; }

        internal static Entry MakeEntry(XmlReader xr)
        {
            string name = string.Empty;
            int tel = 0;
            xr.ReadToDescendant("name");
            name = xr.ReadElementString("name");
            xr.ReadToNextSibling("tel");
            xr.ReadStartElement("tel");
            tel = int.Parse(xr.Value);
            return new Entry(name, tel);
        }

        public Entry(string name, int tel)
        {
            Name = name;
            Tel = tel;
        }

        public override string ToString()   //참조형식 재정의
        {
            return Name;
        }

    }
}
