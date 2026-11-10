using System;
using System.Data;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Windows.Forms;
using System.IO.Ports;
using System.Text;

namespace zigbee_wifi
{
    public partial class Form_main : Form , Protocol_interface
    {

        private SerialPort comm = new SerialPort();

        //数据解析
        static Protocol uart_protocol;

        private int sensor_value_mq_1 = 0;
        private int sensor_value_mq_2 = 0;
        private int sensor_value_wendu_1 = 0;
        private int sensor_value_wendu_2 = 0;
        private int flag_Threshold_alert_wendu = 30;
        private int flag_Threshold_alert_mq = 40;



        public void protocaol_callback(byte[] buff, int len)
        {
            string id = "";
            string value = "";


            this.Invoke((EventHandler)(delegate
            {


            while (uart_protocol.Get_id_value(buff, ref id, ref value) == 1)
            {




                if (id.Equals("yanwu1"))
                {
                        label_show_mq_1.Text = value;
                }

  
 


                else if (id.Equals("wendu1"))
                {

 
                        label_show_wendu_1.Text = value;
 
                }
                else if (id.Equals("shidu1"))
                {

        
                        label_show_shidu_1.Text = value;
 
                }
            }
            }));
        }

        public Form_main()
        {
            InitializeComponent();
        }



        private void Form_main_Load(object sender, EventArgs e)
        {


            /*************************串口连接*********************************/

            string[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);
            combox_serial_connection_port.Items.AddRange(ports);

            string[] list_of_baudrate = { "300", "600", "1200", "2400", "4800", "9600", "11400", "19200", "38400", "56000", "57600", "76800", "115200", "128000", "256000" };

            foreach (string param in list_of_baudrate)
            {
                combox_serial_connection_Baudrate.Items.Add(param);
            }
            combox_serial_connection_Baudrate.SelectedIndex = combox_serial_connection_Baudrate.Items.IndexOf("38400");

            comm.DataReceived += serial_DataReceived;


            uart_protocol = new Protocol(this);//初始化解析协议


        }




       

        private void Form_main_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        void serial_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int len = comm.BytesToRead;
            byte[] buf = new byte[len];//临时数组存储当前的串口数据
            comm.Read(buf, 0, len);//读取缓冲数据

            System.Text.ASCIIEncoding ASCII = new System.Text.ASCIIEncoding();
            string string_rev_from_serial = ASCII.GetString(buf);

            uart_protocol.GetPack(buf, len);
        }

        private void button_connect_serial_Click(object sender, EventArgs e)
        {
            //根据当前串口对象，来判断操作
            if (comm.IsOpen)
            {
                //打开时点击，则关闭串口
                comm.Close();
                groupBox_connection_serial.Text = "串口：未连接";
                combox_serial_connection_Baudrate.Enabled = true;
                combox_serial_connection_port.Enabled = true;
            }
            else
            {

                try
                {
                    //关闭时点击，则设置好端口，波特率后打开
                    comm.PortName = combox_serial_connection_port.Text;
                    comm.BaudRate = int.Parse(combox_serial_connection_Baudrate.Text);
                    comm.Open();

                    groupBox_connection_serial.Text = "串口:已连接";

                    combox_serial_connection_Baudrate.Enabled = false;
                    combox_serial_connection_port.Enabled = false;
                }
                catch (Exception ex)
                {
                    //捕获到异常信息，创建一个新的comm对象，之前的不能用了。
                    comm = new SerialPort();
                    //现实异常信息给客户。
                    MessageBox.Show(ex.Message);
                    groupBox_connection_serial.Text = "串口未连接";

                    combox_serial_connection_Baudrate.Enabled = true;
                    combox_serial_connection_port.Enabled = true;
                }
            }
            //设置按钮的状态
            button_connect_serial.Text = comm.IsOpen ? "关闭串口" : "打开串口";
        }

        private void button_serial_refresh_Click(object sender, EventArgs e)
        {
            combox_serial_connection_port.Items.Clear();
            //初始化下拉串口名称列表框
            string[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);
            combox_serial_connection_port.Items.AddRange(ports);
        }

  

        private void send_data_to_mcu(string name, string value)
        {
            string str_out = "{\"" + name + "\":\"" + value + "\"}";


            try
            {
                if (comm.IsOpen)
                {
                    comm.Write(str_out);
                }
            }
            catch (Exception ex)
            {
                //现实异常信息给用户。
                MessageBox.Show("请打开通讯连接后再试！");
                return;
            }
        }






        private void button_fengmignqi_open_Click(object sender, EventArgs e)
        {
            send_data_to_mcu("beep1", "on");
        }

        private void button_fengmingqi_close_Click(object sender, EventArgs e)
        {
            send_data_to_mcu("beep1", "off");
        }

        private void button_fengmignqi_open_2_Click(object sender, EventArgs e)
        {
            send_data_to_mcu("beep2", "on");
        }

        private void button_fengmingqi_close_2_Click(object sender, EventArgs e)
        {
            send_data_to_mcu("beep2", "off");
        }

        private void button_zidongtiaojie_open_Click(object sender, EventArgs e)
        {
            send_data_to_mcu("auto_wendu1", "on");
            send_data_to_mcu("auto_yanwu1", "on");
        }

        private void button_zidongtiaojie_open_2_Click(object sender, EventArgs e)
        {
            send_data_to_mcu("auto_wendu2", "on");
            send_data_to_mcu("auto_yanwu2", "on");
        }

        private void button_zidongtiaojie_close_Click(object sender, EventArgs e)
        {
            send_data_to_mcu("auto_wendu1", "off");
            send_data_to_mcu("auto_yanwu1", "off");
        }

        private void button_zidongtiaojie_close_2_Click(object sender, EventArgs e)
        {
            send_data_to_mcu("auto_wendu2", "off");
            send_data_to_mcu("auto_yanwu2", "off");
        }



        private void button_alert_yanwu1_Click(object sender, EventArgs e)
        {
            send_data_to_mcu("limit_yanwu1", this.numericUpDown_yanwu1.Value.ToString());
        }

        private void button_alert_wendu1_Click(object sender, EventArgs e)
        {
            send_data_to_mcu("limit_wendu1", this.numericUpDown_wendu1.Value.ToString());
        }

  
    }
}
