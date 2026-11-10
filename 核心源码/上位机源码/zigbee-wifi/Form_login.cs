using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace zigbee_wifi
{
    public partial class Form_login : Form
    {
        public void check_access()
        {
            Thread thread = new Thread(() =>
            {
                string user = this.textBox_user.Text.Trim().ToString();
                string passwd = this.textBox_passwd.Text.Trim().ToString();

                if (textBox_user.Text=="admin" && textBox_passwd.Text=="123456")
                {

                    this.Invoke((EventHandler)(delegate
                    {
                        this.Hide();
                        Form_main form = new Form_main();
                        form.Show();
                    }));


                }
                else
                {
                    MessageBox.Show("账号或密码不正确");
                }
            });
            thread.Start();
        }

        public Form_login()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            check_access();
        }


        private void login_key_up(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                check_access();
            }

        }

    }
}
