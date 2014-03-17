using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client {
  public partial class Form1 : Form {

    public Form1() {
      InitializeComponent();
      ThreadStart typeThreadStart = delegate { recivemessgetype(ConfigurationSettings.AppSettings["typeport"]); };
      Thread typeThread = new Thread(typeThreadStart);
      typeThread.Start();
    }

    private void bn_register_Click(object sender, EventArgs e) {
      register reg = new register();
      reg.Show();
    }

    private void recivemessgetype(string port)
    {
      TcpListener listener = new TcpListener(Convert.ToInt32(port));
      try {
        listener.Start();
        while (true) {
          Socket soc = listener.AcceptSocket();
          Stream s = new NetworkStream(soc);
          StreamReader sr = new StreamReader(s);
          string value = sr.ReadToEnd();

        }
      } catch (Exception ex) {
        throw ex;
      }
    }

    private void parsertype(string mes)
    {
      if (String.IsNullOrEmpty(mes))
        return;
      try {
        byte[] tmp = new byte[512];
        for (int i = 0; i < mes.Length; i++) {
          tmp[i] = Convert.ToByte(mes[i]);
        }
        keyconfig kc = new keyconfig();
        while (kc.Machineid == 0)
        {
          Thread.Sleep(100);
        }
        tmp = keyconfig.decryption(tmp, kc.Flow);
        StringBuilder sb = new StringBuilder(mes);
        for (int i = 0; i < mes.Length; i++) {
          sb[i] = Convert.ToChar(tmp[i]);
        }
        mes = sb.ToString();
        String ip = mes.Substring(0, 20);
        for (int i = 0; i < 4; i++)
        {
          String id = mes.Substring(20 + i*20, 20 + (i + 1)*20);
          int intid = register.ConvertToInt(id);
          if (global.typenum < intid)
          {
            global.typenum = intid;
          }
        }
      } catch (Exception ex) {
        MessageBox.Show("type parser error." + ex.Message);
      }
    }

  }
}
