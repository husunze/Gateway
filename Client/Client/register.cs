using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Client {
  public partial class register : Form
  {
    public delegate void setmachineiddelegate(int id);
    public setmachineiddelegate mydelegate;
    private keyconfig kc;
    private byte[] message;
    private int machineid;
    public register() 
    {
      InitializeComponent();
      message = new byte[512];
      mydelegate = new setmachineiddelegate(setmachineid);
    }

    private void bn_register_Click(object sender, EventArgs e)
    {
      string serverip = txt_server_ip.Text;
      string localip = getlocalip();
      string py = txt_p_key.Text;
      string fl = txt_f_key.Text;
      if (String.IsNullOrEmpty(serverip))
      {
        MessageBox.Show("Server IP is required.");
        return;
      }
      if (String.IsNullOrEmpty(localip)) {
        MessageBox.Show("Get local IP error.");
        return ;
      }
      if (String.IsNullOrEmpty(py) && String.IsNullOrEmpty(fl))
      {
        kc = new keyconfig();
      }
      else if (String.IsNullOrEmpty(py) && (!String.IsNullOrEmpty(fl)))
      {
        kc = new keyconfig(fl);
      }
      else if ((!String.IsNullOrEmpty(py)) && (!String.IsNullOrEmpty(fl)))
      {
        kc = new keyconfig(py, fl);
      }
      setmessage(0, 20, localip);
      setmessage(20, 40, serverip);
      setmessage(40, 60, kc.Flow);

      ThreadStart sndThreadStart = delegate { sendmessage(serverip, ConfigurationSettings.AppSettings["sendport"]); };
      Thread sendThread = new Thread(sndThreadStart);
      sendThread.Start();
      ThreadStart rcvThreadStart = delegate { recivemessage(ConfigurationSettings.AppSettings["rcvport"]); };
      Thread rcvThread = new Thread(rcvThreadStart);
      rcvThread.Start();
    }


    private void setmessage(int start, int end, string mes)
    {
      for (int i = start; i < end; i++)
      {
        if (mes.Length > i - start)
        {
          message[i] = Convert.ToByte(mes[i - start]);
        }
        else
        {
          message[i] = Convert.ToByte('#');
        }
      }
    }

    private void setmessage(int start, int end, byte[] mes) {
      for (int i = start; i < end; i++) {
        if (mes.Length > i - start) {
          message[i] = mes[i - start];
        } else {
          message[i] = Convert.ToByte('#');
        }
      }
    }

    private string getlocalip()
    {
      IPHostEntry host;
      string localIP = "";
      try
      {
        host = Dns.GetHostEntry(Dns.GetHostName());
        foreach (IPAddress ip in host.AddressList)
        {
          if (ip.AddressFamily == AddressFamily.InterNetwork)
          {
            localIP = ip.ToString();
            break;
          }
        }
      }
      catch (Exception ex)
      {
        return null;
      }
      return localIP;
    }

    private void sendmessage(string ip, string port)
    {
      TcpClient client = null;
      try
      {
        client = new TcpClient(ip, Convert.ToInt32(port));
      }
      catch (Exception ex)
      {
        MessageBox.Show("Network connect error! Could not connect to server!");
        client.Close();
        return;
      }
      
      try
      {
        char[] charsub = new char[512];
        for (int i = 0; i < 512; i++) {
          charsub[i] = Convert.ToChar(message[i]);
        }
        Stream s = client.GetStream();
        BinaryWriter bw = new BinaryWriter(s);
        byte[] sub = keyconfig.encryption(message, kc.Physics);
        
        bw.Write(sub);
        bw.Flush();
        s.Close();
      }
      catch (Exception ex)
      {
        return ;
      }
      finally
      {
        client.Close();
      }
      return ;
    }

    private void recivemessage(string port)
    {
      TcpListener listener = new TcpListener(Convert.ToInt32(port));
      try
      {
        listener.Start();
        while (true)
        {
          Socket soc = listener.AcceptSocket();
          Stream s = new NetworkStream(soc);
          StreamReader sr = new StreamReader(s);
          string value = sr.ReadToEnd();
          parsermachineid(value);
        }
      }
      catch (Exception ex)
      {
        throw ex;
      }
    }

    private void parsermachineid(string mes)
    {
      if (String.IsNullOrEmpty(mes))
        return;
      try
      {
        byte[] tmp = new byte[512];
        for (int i = 0; i < mes.Length; i++)
        {
          tmp[i] = Convert.ToByte(mes[i]);
        }
        tmp = keyconfig.decryption(tmp, kc.Flow);
        StringBuilder sb = new StringBuilder(mes);
        for (int i = 0; i < mes.Length; i++)
        {
          sb[i] = Convert.ToChar(tmp[i]);
        }
        mes = sb.ToString();
        String ip = mes.Substring(0, 20);
        String sub_machineid = mes.Substring(20, 20);
        machineid = ConvertToInt(sub_machineid);
        this.Invoke(this.mydelegate, new Object[]{machineid});
      }
      catch (Exception ex)
      {
        MessageBox.Show("Machine id parser error." + ex.Message);
      }
    }

    public static int ConvertToInt(string val)
    {
      int x = 0;
      for (int i = 0; i < val.Length; i++)
      {
        if (val[i] > '9' || val[i] < '0')
        {
          return x;
        }
        else
        {
          x = x*10 + val[i] - '0';
        }
      }
      return x;
    }

    public void setmachineid(int id)
    {
      txt_machine_id.Text = id.ToString();
      this.kc.Machineid = id;
    }

  }
}
