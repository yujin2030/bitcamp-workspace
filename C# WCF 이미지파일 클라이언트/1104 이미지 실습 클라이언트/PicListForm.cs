using _1104_이미지_실습_클라이언트.ServiceReference1;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1104_이미지_실습_클라이언트
{
    public partial class PicListForm : Form
    {
        // PictureService 객체를 하나 생성
        PictureServiceClient pic = new PictureServiceClient();

        public PicListForm()
        {
            InitializeComponent();

            string[] strPicList = pic.GetPictureList();
            listBox1.DataSource = strPicList;
        }


        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Close();
        }

        public string SelectedPic
        {
            get
            {
                return listBox1.SelectedItem.ToString();
            }
        }

        private void listBox1_DoubleClick(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Close();
        }

    }
}
