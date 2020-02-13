using System;
using System.ServiceModel;
using System.Runtime.Serialization;
using System.Collections.Generic;

namespace _1104_오후_실습
{
    [DataContract]
    class Cal
    {
        [DataMember]
        public int Num1;
        [DataMember]
        public int Num2;
        [DataMember]
        public char Oper;
    }
}
