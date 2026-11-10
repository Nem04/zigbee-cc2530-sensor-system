namespace zigbee_wifi
{
    partial class Form_main
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox_connection_serial = new System.Windows.Forms.GroupBox();
            this.button_serial_refresh = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.combox_serial_connection_port = new System.Windows.Forms.ComboBox();
            this.label9 = new System.Windows.Forms.Label();
            this.button_connect_serial = new System.Windows.Forms.Button();
            this.combox_serial_connection_Baudrate = new System.Windows.Forms.ComboBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label_show_wendu_1 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label_show_shidu_1 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label_show_mq_1 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.button_fengmignqi_open = new System.Windows.Forms.Button();
            this.button_fengmingqi_close = new System.Windows.Forms.Button();
            this.button_zidongtiaojie_open = new System.Windows.Forms.Button();
            this.button_zidongtiaojie_close = new System.Windows.Forms.Button();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.numericUpDown_wendu1 = new System.Windows.Forms.NumericUpDown();
            this.label11 = new System.Windows.Forms.Label();
            this.button_alert_wendu1 = new System.Windows.Forms.Button();
            this.numericUpDown_yanwu1 = new System.Windows.Forms.NumericUpDown();
            this.label14 = new System.Windows.Forms.Label();
            this.button_alert_yanwu1 = new System.Windows.Forms.Button();
            this.groupBox_connection_serial.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox7.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_wendu1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_yanwu1)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox_connection_serial
            // 
            this.groupBox_connection_serial.Controls.Add(this.button_serial_refresh);
            this.groupBox_connection_serial.Controls.Add(this.label8);
            this.groupBox_connection_serial.Controls.Add(this.combox_serial_connection_port);
            this.groupBox_connection_serial.Controls.Add(this.label9);
            this.groupBox_connection_serial.Controls.Add(this.button_connect_serial);
            this.groupBox_connection_serial.Controls.Add(this.combox_serial_connection_Baudrate);
            this.groupBox_connection_serial.Location = new System.Drawing.Point(36, 18);
            this.groupBox_connection_serial.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox_connection_serial.Name = "groupBox_connection_serial";
            this.groupBox_connection_serial.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox_connection_serial.Size = new System.Drawing.Size(392, 288);
            this.groupBox_connection_serial.TabIndex = 7;
            this.groupBox_connection_serial.TabStop = false;
            this.groupBox_connection_serial.Text = "串口：未连接";
            // 
            // button_serial_refresh
            // 
            this.button_serial_refresh.Location = new System.Drawing.Point(70, 156);
            this.button_serial_refresh.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.button_serial_refresh.Name = "button_serial_refresh";
            this.button_serial_refresh.Size = new System.Drawing.Size(214, 34);
            this.button_serial_refresh.TabIndex = 7;
            this.button_serial_refresh.Text = "刷新串口";
            this.button_serial_refresh.UseVisualStyleBackColor = true;
            this.button_serial_refresh.Click += new System.EventHandler(this.button_serial_refresh_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(68, 60);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(80, 18);
            this.label8.TabIndex = 2;
            this.label8.Text = "COM 口：";
            // 
            // combox_serial_connection_port
            // 
            this.combox_serial_connection_port.FormattingEnabled = true;
            this.combox_serial_connection_port.Location = new System.Drawing.Point(156, 57);
            this.combox_serial_connection_port.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.combox_serial_connection_port.Name = "combox_serial_connection_port";
            this.combox_serial_connection_port.Size = new System.Drawing.Size(127, 26);
            this.combox_serial_connection_port.TabIndex = 0;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(68, 110);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(80, 18);
            this.label9.TabIndex = 4;
            this.label9.Text = "波特率：";
            // 
            // button_connect_serial
            // 
            this.button_connect_serial.Location = new System.Drawing.Point(70, 213);
            this.button_connect_serial.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.button_connect_serial.Name = "button_connect_serial";
            this.button_connect_serial.Size = new System.Drawing.Size(214, 34);
            this.button_connect_serial.TabIndex = 1;
            this.button_connect_serial.Text = "打开串口";
            this.button_connect_serial.UseVisualStyleBackColor = true;
            this.button_connect_serial.Click += new System.EventHandler(this.button_connect_serial_Click);
            // 
            // combox_serial_connection_Baudrate
            // 
            this.combox_serial_connection_Baudrate.FormattingEnabled = true;
            this.combox_serial_connection_Baudrate.Location = new System.Drawing.Point(156, 105);
            this.combox_serial_connection_Baudrate.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.combox_serial_connection_Baudrate.Name = "combox_serial_connection_Baudrate";
            this.combox_serial_connection_Baudrate.Size = new System.Drawing.Size(127, 26);
            this.combox_serial_connection_Baudrate.TabIndex = 3;
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.SystemColors.Control;
            this.groupBox3.Controls.Add(this.label10);
            this.groupBox3.Controls.Add(this.label_show_wendu_1);
            this.groupBox3.Controls.Add(this.label12);
            this.groupBox3.Controls.Add(this.label1);
            this.groupBox3.Controls.Add(this.label_show_shidu_1);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.label_show_mq_1);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Location = new System.Drawing.Point(36, 315);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox3.Size = new System.Drawing.Size(392, 390);
            this.groupBox3.TabIndex = 10;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "监测：";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label10.Location = new System.Drawing.Point(326, 63);
            this.label10.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(42, 29);
            this.label10.TabIndex = 14;
            this.label10.Text = "℃";
            // 
            // label_show_wendu_1
            // 
            this.label_show_wendu_1.AutoSize = true;
            this.label_show_wendu_1.Font = new System.Drawing.Font("宋体", 42F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_show_wendu_1.ForeColor = System.Drawing.Color.Blue;
            this.label_show_wendu_1.Location = new System.Drawing.Point(165, 30);
            this.label_show_wendu_1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label_show_wendu_1.Name = "label_show_wendu_1";
            this.label_show_wendu_1.Size = new System.Drawing.Size(119, 84);
            this.label_show_wendu_1.TabIndex = 13;
            this.label_show_wendu_1.Text = "25";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label12.Location = new System.Drawing.Point(57, 63);
            this.label12.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(100, 29);
            this.label12.TabIndex = 12;
            this.label12.Text = "温度：";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(326, 182);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(28, 29);
            this.label1.TabIndex = 11;
            this.label1.Text = "%";
            // 
            // label_show_shidu_1
            // 
            this.label_show_shidu_1.AutoSize = true;
            this.label_show_shidu_1.Font = new System.Drawing.Font("宋体", 42F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_show_shidu_1.ForeColor = System.Drawing.Color.Blue;
            this.label_show_shidu_1.Location = new System.Drawing.Point(165, 148);
            this.label_show_shidu_1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label_show_shidu_1.Name = "label_show_shidu_1";
            this.label_show_shidu_1.Size = new System.Drawing.Size(119, 84);
            this.label_show_shidu_1.TabIndex = 10;
            this.label_show_shidu_1.Text = "25";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.Location = new System.Drawing.Point(57, 182);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(100, 29);
            this.label5.TabIndex = 9;
            this.label5.Text = "湿度：";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(326, 304);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(28, 29);
            this.label4.TabIndex = 8;
            this.label4.Text = "%";
            // 
            // label_show_mq_1
            // 
            this.label_show_mq_1.AutoSize = true;
            this.label_show_mq_1.Font = new System.Drawing.Font("宋体", 42F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_show_mq_1.ForeColor = System.Drawing.Color.Blue;
            this.label_show_mq_1.Location = new System.Drawing.Point(165, 272);
            this.label_show_mq_1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label_show_mq_1.Name = "label_show_mq_1";
            this.label_show_mq_1.Size = new System.Drawing.Size(119, 84);
            this.label_show_mq_1.TabIndex = 7;
            this.label_show_mq_1.Text = "25";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label7.Location = new System.Drawing.Point(57, 304);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(100, 29);
            this.label7.TabIndex = 6;
            this.label7.Text = "烟雾：";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.groupBox8);
            this.groupBox4.Controls.Add(this.groupBox7);
            this.groupBox4.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox4.ForeColor = System.Drawing.Color.Purple;
            this.groupBox4.Location = new System.Drawing.Point(436, 18);
            this.groupBox4.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox4.Size = new System.Drawing.Size(566, 687);
            this.groupBox4.TabIndex = 11;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "控制：";
            // 
            // groupBox8
            // 
            this.groupBox8.BackColor = System.Drawing.SystemColors.Control;
            this.groupBox8.Controls.Add(this.button_fengmignqi_open);
            this.groupBox8.Controls.Add(this.button_fengmingqi_close);
            this.groupBox8.Controls.Add(this.button_zidongtiaojie_open);
            this.groupBox8.Controls.Add(this.button_zidongtiaojie_close);
            this.groupBox8.ForeColor = System.Drawing.Color.Purple;
            this.groupBox8.Location = new System.Drawing.Point(24, 87);
            this.groupBox8.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox8.Size = new System.Drawing.Size(524, 224);
            this.groupBox8.TabIndex = 12;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "自动调节参数设置：";
            // 
            // button_fengmignqi_open
            // 
            this.button_fengmignqi_open.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.button_fengmignqi_open.Location = new System.Drawing.Point(38, 69);
            this.button_fengmignqi_open.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.button_fengmignqi_open.Name = "button_fengmignqi_open";
            this.button_fengmignqi_open.Size = new System.Drawing.Size(207, 51);
            this.button_fengmignqi_open.TabIndex = 0;
            this.button_fengmignqi_open.Text = "开启蜂鸣器";
            this.button_fengmignqi_open.UseVisualStyleBackColor = true;
            this.button_fengmignqi_open.Click += new System.EventHandler(this.button_fengmignqi_open_Click);
            // 
            // button_fengmingqi_close
            // 
            this.button_fengmingqi_close.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.button_fengmingqi_close.Location = new System.Drawing.Point(38, 147);
            this.button_fengmingqi_close.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.button_fengmingqi_close.Name = "button_fengmingqi_close";
            this.button_fengmingqi_close.Size = new System.Drawing.Size(207, 51);
            this.button_fengmingqi_close.TabIndex = 1;
            this.button_fengmingqi_close.Text = "关闭蜂鸣器";
            this.button_fengmingqi_close.UseVisualStyleBackColor = true;
            this.button_fengmingqi_close.Click += new System.EventHandler(this.button_fengmingqi_close_Click);
            // 
            // button_zidongtiaojie_open
            // 
            this.button_zidongtiaojie_open.Location = new System.Drawing.Point(296, 69);
            this.button_zidongtiaojie_open.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.button_zidongtiaojie_open.Name = "button_zidongtiaojie_open";
            this.button_zidongtiaojie_open.Size = new System.Drawing.Size(190, 51);
            this.button_zidongtiaojie_open.TabIndex = 4;
            this.button_zidongtiaojie_open.Text = "开启预警";
            this.button_zidongtiaojie_open.UseVisualStyleBackColor = true;
            this.button_zidongtiaojie_open.Click += new System.EventHandler(this.button_zidongtiaojie_open_Click);
            // 
            // button_zidongtiaojie_close
            // 
            this.button_zidongtiaojie_close.Location = new System.Drawing.Point(296, 147);
            this.button_zidongtiaojie_close.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.button_zidongtiaojie_close.Name = "button_zidongtiaojie_close";
            this.button_zidongtiaojie_close.Size = new System.Drawing.Size(190, 51);
            this.button_zidongtiaojie_close.TabIndex = 5;
            this.button_zidongtiaojie_close.Text = "关闭预警";
            this.button_zidongtiaojie_close.UseVisualStyleBackColor = true;
            this.button_zidongtiaojie_close.Click += new System.EventHandler(this.button_zidongtiaojie_close_Click);
            // 
            // groupBox7
            // 
            this.groupBox7.BackColor = System.Drawing.SystemColors.Control;
            this.groupBox7.Controls.Add(this.numericUpDown_wendu1);
            this.groupBox7.Controls.Add(this.label11);
            this.groupBox7.Controls.Add(this.button_alert_wendu1);
            this.groupBox7.Controls.Add(this.numericUpDown_yanwu1);
            this.groupBox7.Controls.Add(this.label14);
            this.groupBox7.Controls.Add(this.button_alert_yanwu1);
            this.groupBox7.ForeColor = System.Drawing.Color.Purple;
            this.groupBox7.Location = new System.Drawing.Point(24, 384);
            this.groupBox7.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox7.Size = new System.Drawing.Size(524, 246);
            this.groupBox7.TabIndex = 11;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "自动调节参数设置：";
            // 
            // numericUpDown_wendu1
            // 
            this.numericUpDown_wendu1.Location = new System.Drawing.Point(196, 141);
            this.numericUpDown_wendu1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.numericUpDown_wendu1.Name = "numericUpDown_wendu1";
            this.numericUpDown_wendu1.Size = new System.Drawing.Size(81, 40);
            this.numericUpDown_wendu1.TabIndex = 10;
            this.numericUpDown_wendu1.Value = new decimal(new int[] {
            28,
            0,
            0,
            0});
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(32, 141);
            this.label11.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(158, 29);
            this.label11.TabIndex = 9;
            this.label11.Text = "高温阈值：";
            // 
            // button_alert_wendu1
            // 
            this.button_alert_wendu1.Location = new System.Drawing.Point(350, 141);
            this.button_alert_wendu1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.button_alert_wendu1.Name = "button_alert_wendu1";
            this.button_alert_wendu1.Size = new System.Drawing.Size(104, 44);
            this.button_alert_wendu1.TabIndex = 8;
            this.button_alert_wendu1.Text = "确定";
            this.button_alert_wendu1.UseVisualStyleBackColor = true;
            this.button_alert_wendu1.Click += new System.EventHandler(this.button_alert_wendu1_Click);
            // 
            // numericUpDown_yanwu1
            // 
            this.numericUpDown_yanwu1.Location = new System.Drawing.Point(196, 69);
            this.numericUpDown_yanwu1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.numericUpDown_yanwu1.Name = "numericUpDown_yanwu1";
            this.numericUpDown_yanwu1.Size = new System.Drawing.Size(81, 40);
            this.numericUpDown_yanwu1.TabIndex = 7;
            this.numericUpDown_yanwu1.Value = new decimal(new int[] {
            30,
            0,
            0,
            0});
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(32, 72);
            this.label14.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(158, 29);
            this.label14.TabIndex = 5;
            this.label14.Text = "烟雾阈值：";
            // 
            // button_alert_yanwu1
            // 
            this.button_alert_yanwu1.Location = new System.Drawing.Point(350, 66);
            this.button_alert_yanwu1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.button_alert_yanwu1.Name = "button_alert_yanwu1";
            this.button_alert_yanwu1.Size = new System.Drawing.Size(104, 44);
            this.button_alert_yanwu1.TabIndex = 3;
            this.button_alert_yanwu1.Text = "确定";
            this.button_alert_yanwu1.UseVisualStyleBackColor = true;
            this.button_alert_yanwu1.Click += new System.EventHandler(this.button_alert_yanwu1_Click);
            // 
            // Form_main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1034, 729);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox_connection_serial);
            this.Controls.Add(this.groupBox3);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "Form_main";
            this.Text = "无线网络火灾预防系统  ";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form_main_FormClosed);
            this.Load += new System.EventHandler(this.Form_main_Load);
            this.groupBox_connection_serial.ResumeLayout(false);
            this.groupBox_connection_serial.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox8.ResumeLayout(false);
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_wendu1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_yanwu1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.GroupBox groupBox_connection_serial;
        private System.Windows.Forms.Button button_serial_refresh;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.ComboBox combox_serial_connection_port;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button button_connect_serial;
        private System.Windows.Forms.ComboBox combox_serial_connection_Baudrate;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label_show_mq_1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button button_zidongtiaojie_close;
        private System.Windows.Forms.Button button_zidongtiaojie_open;
        private System.Windows.Forms.Button button_fengmignqi_open;
        private System.Windows.Forms.Button button_fengmingqi_close;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label_show_wendu_1;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label_show_shidu_1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.NumericUpDown numericUpDown_wendu1;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Button button_alert_wendu1;
        private System.Windows.Forms.NumericUpDown numericUpDown_yanwu1;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Button button_alert_yanwu1;
    }
}