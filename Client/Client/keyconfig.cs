using System;
using System.Collections;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client {
  public class keyconfig
  {
    private static byte[] physics = new byte[20];
    private static byte[] flow = new byte[20];
    private static int machineid = 0;
    public keyconfig()
    {
      if (machineid == 0)
      {
        generatepysics();
        generateflow();
      }
    }

    public keyconfig(string fl)
    {
      if (machineid == 0)
      {
        generatepysics();
        generateflow(fl);
      }
    }

    public keyconfig(string py, string fl)
    {
      if (machineid == 0)
      {
        generatepysics(py);
        generateflow(fl);
      }
    }

    private void generatepysics()
    {
      string sub_physics = ConfigurationSettings.AppSettings["physics"];
      char[] tmp = sub_physics.ToCharArray();
      for (int i = 0; i < tmp.Length; i++) {
        physics[i] = Convert.ToByte(tmp[i]);
      }
      if (sub_physics.Length < 20) {
        for (int i = tmp.Length ; i < physics.Length; i++) {
          physics[i] = Convert.ToByte('#');
        }
      }
    }

    private void generatepysics(string py)
    {
      char [] tmp = py.ToCharArray();
      for (int i = 0; i < tmp.Length; i++)
      {
        physics[i] = Convert.ToByte(tmp[i]);
      }
      if (py.Length < 20)
      {
        for (int i = tmp.Length - 1; i < physics.Length; i++)
        {
          physics[i] = Convert.ToByte('#');
        }
      }
    }

    private void generateflow()
    {
      Random rnd = new Random();
      for (int i = 0; i < flow.Length; i++)
      {
        flow[i] = Convert.ToByte(Convert.ToChar(rnd.Next(9)));
      }
    }

    private void generateflow(string fl) {
      char[] tmp = fl.ToCharArray();
      for (int i = 0; i < tmp.Length; i++) {
        flow[i] = Convert.ToByte(tmp[i]);
      }
      if (fl.Length < 20) {
        for (int i = tmp.Length; i < physics.Length; i++) {
          flow[i] = Convert.ToByte('#');
        }
      }
    }

    public byte[] Physics
    {
      get { return physics; }
      set { physics = value; }
    }

    public byte[] Flow
    {
      get { return flow; }
      set { flow = value; }
    }

    public int Machineid
    {
      get { return machineid; }
      set { machineid = value; }
    }

    public static byte[] encryption(byte[] message, byte[] key)
    {
      if (key.Length < 16)
      {
        throw new Exception("Key shoud more than 16 bytes.");
      }
      for (int i = 0, j = 0; i < message.Length; i++, j++) {
        if (i % 16 == 0) {
          j = 0;
        }
        message[i] += key[j];
      }
      return message;
    }

    public static byte[] decryption(byte[] message, byte[] key)
    {
      if (key.Length < 16) {
        throw new Exception("Key shoud more than 16 bytes.");
      }
      for (int i = 0, j = 0; i < message.Length; i++, j++) {
        if (i%16 == 0)
        {
          j = 0;
        }
         message[i] -= key[j];
      }
      return message;
    }
  }
}
