namespace Client {
  partial class Form1 {
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
      this.title = new System.Windows.Forms.Label();
      this.bn_register = new System.Windows.Forms.Button();
      this.bn_send = new System.Windows.Forms.Button();
      this.SuspendLayout();
      // 
      // title
      // 
      this.title.AutoSize = true;
      this.title.Location = new System.Drawing.Point(59, 46);
      this.title.Name = "title";
      this.title.Size = new System.Drawing.Size(163, 13);
      this.title.TabIndex = 0;
      this.title.Text = "欢迎使用联机交易网关客户端";
      // 
      // bn_register
      // 
      this.bn_register.Location = new System.Drawing.Point(83, 90);
      this.bn_register.Name = "bn_register";
      this.bn_register.Size = new System.Drawing.Size(103, 39);
      this.bn_register.TabIndex = 1;
      this.bn_register.Text = "注册";
      this.bn_register.UseVisualStyleBackColor = true;
      this.bn_register.Click += new System.EventHandler(this.bn_register_Click);
      // 
      // bn_send
      // 
      this.bn_send.Location = new System.Drawing.Point(83, 148);
      this.bn_send.Name = "bn_send";
      this.bn_send.Size = new System.Drawing.Size(103, 38);
      this.bn_send.TabIndex = 2;
      this.bn_send.Text = "交易";
      this.bn_send.UseVisualStyleBackColor = true;
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(284, 262);
      this.Controls.Add(this.bn_send);
      this.Controls.Add(this.bn_register);
      this.Controls.Add(this.title);
      this.Name = "Form1";
      this.Text = "Form1";
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Label title;
    private System.Windows.Forms.Button bn_register;
    private System.Windows.Forms.Button bn_send;
  }
}

