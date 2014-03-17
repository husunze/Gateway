namespace Client {
  partial class register {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing) {
      if (disposing && (components != null)) {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent() {
      this.bn_register = new System.Windows.Forms.Button();
      this.server_ip = new System.Windows.Forms.Label();
      this.p_key = new System.Windows.Forms.Label();
      this.f_key = new System.Windows.Forms.Label();
      this.txt_server_ip = new System.Windows.Forms.TextBox();
      this.txt_p_key = new System.Windows.Forms.TextBox();
      this.txt_f_key = new System.Windows.Forms.TextBox();
      this.label1 = new System.Windows.Forms.Label();
      this.regmsg = new System.Windows.Forms.Label();
      this.txt_machine_id = new System.Windows.Forms.TextBox();
      this.SuspendLayout();
      // 
      // bn_register
      // 
      this.bn_register.Location = new System.Drawing.Point(86, 164);
      this.bn_register.Name = "bn_register";
      this.bn_register.Size = new System.Drawing.Size(75, 23);
      this.bn_register.TabIndex = 0;
      this.bn_register.Text = "开始注册";
      this.bn_register.UseVisualStyleBackColor = true;
      this.bn_register.Click += new System.EventHandler(this.bn_register_Click);
      // 
      // server_ip
      // 
      this.server_ip.AutoSize = true;
      this.server_ip.Location = new System.Drawing.Point(-2, 32);
      this.server_ip.Name = "server_ip";
      this.server_ip.Size = new System.Drawing.Size(51, 13);
      this.server_ip.TabIndex = 1;
      this.server_ip.Text = "Server IP";
      // 
      // p_key
      // 
      this.p_key.AutoSize = true;
      this.p_key.Location = new System.Drawing.Point(-1, 81);
      this.p_key.Name = "p_key";
      this.p_key.Size = new System.Drawing.Size(64, 13);
      this.p_key.TabIndex = 2;
      this.p_key.Text = "Physics Key";
      // 
      // f_key
      // 
      this.f_key.AutoSize = true;
      this.f_key.Location = new System.Drawing.Point(-1, 125);
      this.f_key.Name = "f_key";
      this.f_key.Size = new System.Drawing.Size(50, 13);
      this.f_key.TabIndex = 3;
      this.f_key.Text = "Flow Key";
      // 
      // txt_server_ip
      // 
      this.txt_server_ip.Location = new System.Drawing.Point(86, 32);
      this.txt_server_ip.Name = "txt_server_ip";
      this.txt_server_ip.Size = new System.Drawing.Size(146, 20);
      this.txt_server_ip.TabIndex = 4;
      // 
      // txt_p_key
      // 
      this.txt_p_key.Location = new System.Drawing.Point(86, 81);
      this.txt_p_key.Name = "txt_p_key";
      this.txt_p_key.Size = new System.Drawing.Size(146, 20);
      this.txt_p_key.TabIndex = 5;
      // 
      // txt_f_key
      // 
      this.txt_f_key.Location = new System.Drawing.Point(86, 125);
      this.txt_f_key.Name = "txt_f_key";
      this.txt_f_key.Size = new System.Drawing.Size(146, 20);
      this.txt_f_key.TabIndex = 6;
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(-2, 209);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(62, 13);
      this.label1.TabIndex = 7;
      this.label1.Text = "Machine ID";
      // 
      // regmsg
      // 
      this.regmsg.AutoSize = true;
      this.regmsg.Location = new System.Drawing.Point(110, 276);
      this.regmsg.Name = "regmsg";
      this.regmsg.Size = new System.Drawing.Size(0, 13);
      this.regmsg.TabIndex = 8;
      // 
      // txt_machine_id
      // 
      this.txt_machine_id.Location = new System.Drawing.Point(86, 209);
      this.txt_machine_id.Name = "txt_machine_id";
      this.txt_machine_id.Size = new System.Drawing.Size(146, 20);
      this.txt_machine_id.TabIndex = 9;
      // 
      // register
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(264, 270);
      this.Controls.Add(this.txt_machine_id);
      this.Controls.Add(this.regmsg);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.txt_f_key);
      this.Controls.Add(this.txt_p_key);
      this.Controls.Add(this.txt_server_ip);
      this.Controls.Add(this.f_key);
      this.Controls.Add(this.p_key);
      this.Controls.Add(this.server_ip);
      this.Controls.Add(this.bn_register);
      this.Name = "register";
      this.Text = "register";
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Button bn_register;
    private System.Windows.Forms.Label server_ip;
    private System.Windows.Forms.Label p_key;
    private System.Windows.Forms.Label f_key;
    private System.Windows.Forms.TextBox txt_server_ip;
    private System.Windows.Forms.TextBox txt_p_key;
    private System.Windows.Forms.TextBox txt_f_key;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Label regmsg;
    private System.Windows.Forms.TextBox txt_machine_id;
  }
}