using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace MorseCodeFormApp
{
    public partial class Form1 : Form
    {
        //private string[] ports = SerialPort.GetPortNames();
        private string defaultText = "Enter message here... ";
        private SerialPort serialPort;

        public Form1()
        {
            InitializeComponent();
            serialPort = new SerialPort("COM6", 9600);
            serialPort.Open();
            SetDefaultText();
        }

        private void btnConvert_Click(object sender, EventArgs e)
        {
            SendMessageToArduino();
        }

        private void SendMessageToArduino()
        {
            if(txtInput.Text != defaultText)
            {
                serialPort.Write(txtInput.Text);
            }
        }

        private void SetDefaultText()
        {
            txtInput.Text = defaultText;
            txtInput.ForeColor = Color.Gray;
        }

        private void txtInput_Enter_1(object sender, EventArgs e)
        {
            if (txtInput.Text == defaultText)
            {
                txtInput.Text = "";
                txtInput.ForeColor = Color.Black;
            }
        }

        private void txtInput_Leave_1(object sender, EventArgs e)
        {
            if (txtInput.Text == "")
            {
                SetDefaultText();
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            serialPort.Close();
        }
    }
}
