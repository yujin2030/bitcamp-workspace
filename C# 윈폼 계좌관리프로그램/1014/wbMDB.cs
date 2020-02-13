using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1014
{
    class wbMDB
    {
       private DataTable dt =  null;
        readonly string fname = "Account.xml";

        #region Account

        public bool CreateAccTable()
        {
            try
            {
                //테이블 생성
                dt = new DataTable("Account");

                //Accid 컬럼
                DataColumn dc_accid = new DataColumn();
                dc_accid.ColumnName = "Accid";
                dc_accid.DataType = typeof(int);
                dc_accid.AutoIncrement = true;
                dc_accid.AutoIncrementSeed = 1;
                dc_accid.AutoIncrementStep = 1;
                dt.Columns.Add(dc_accid);

                //Accnumber 컬럼
                DataColumn dc_accnumber = new DataColumn();
                dc_accnumber.ColumnName = "Accnumber";
                dc_accnumber.DataType = typeof(int);
                dc_accnumber.AllowDBNull = false;
                dc_accnumber.Unique = true;
                dt.Columns.Add(dc_accnumber);

                //CName 컬럼
                DataColumn dc_cname = new DataColumn();
                dc_cname.ColumnName = "CName";
                dc_cname.DataType = typeof(string);
                dt.Columns.Add(dc_cname);

                //Balance 컬럼
                DataColumn dc_balance = new DataColumn();
                dc_balance.ColumnName = "Balance";
                dc_balance.DataType = typeof(int);
                dc_balance.DefaultValue = 0;       //기본값
                dc_balance.AllowDBNull = false;
                dt.Columns.Add(dc_balance);

                //Date 컬럼
                DataColumn dc_date = new DataColumn();
                dc_date.ColumnName = "Date";
                dc_date.DataType = typeof(DateTime);
                dc_date.AllowDBNull = false;
                dt.Columns.Add(dc_date);

                DataColumn[] pkeys = new DataColumn[1];
                pkeys[0] = dc_accid;
                dt.PrimaryKey = pkeys;

                return true;
            }

            catch(Exception ex)
            {
                
                return false;
            }
        }

        public string ViewAccTable()
        {
            string str = string.Empty;

            str += "테이블 명  : " + dt.TableName + "\r\n";
            str += "컬럼 개수  : " + dt.Columns.Count + "\r\n";
            str += ("=============================== \r\n");

            foreach (DataColumn dc in dt.Columns)
            {
               // str += string.Format("{0}:{1}" + "\r\n", dc.ColumnName, dc.DataType);
                str += string.Format("{0}\t{1}\r\n", dc.ColumnName, dc.DataType);
            }

            return str;
        }

        public void AddAccount(int accnumber, string cname, int balance)
        {
            try
            {
                DataRow dr = dt.NewRow();

                dr["Accnumber"] = accnumber;
                dr["Cname"] = cname;
                dr["Balance"] = balance;
                dr["date"] = System.DateTime.Now;

                dt.Rows.Add(dr);
            }
            catch (Exception e)
            {
                MessageBox.Show("이유:{0}", e.Message);
            }
        }

        public string ViewAccData()
        {

            string str = string.Empty;

            DataRow dr = null;
            for (int i = 0; i < dt.Rows.Count; i++)
            {
                dr = dt.Rows[i];
                foreach (DataColumn dc in dt.Columns)
                {
                    str += string.Format ("{0}\t{1}\r\n", dc.ColumnName, dr[dc]);
                }
                str += ("=============================== \r\n");
            }
            return str;
        }

        public void Save()
        {
            dt.WriteXmlSchema("Account.xsd", true);
            dt.WriteXml(fname, true);
        }

        #endregion

        public void IdToSelectAccount(int id)
        {
            DataRow dr = dt.Rows.Find(id);
            if (dr == null)
            {
                MessageBox.Show("존재하는 ID가 아닙니다.");
                return;
            }
        }

    }
}
