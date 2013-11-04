namespace FMApplicatie
{
    partial class Form1
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
            this.inputBox = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.pijl_from = new System.Windows.Forms.TextBox();
            this.pijl_to = new System.Windows.Forms.TextBox();
            this.pijl_symbol = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.button4 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.button5 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.button12 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.button13 = new System.Windows.Forms.Button();
            this.button14 = new System.Windows.Forms.Button();
            this.button15 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // inputBox
            // 
            this.inputBox.Location = new System.Drawing.Point(20, 20);
            this.inputBox.Multiline = true;
            this.inputBox.Name = "inputBox";
            this.inputBox.Size = new System.Drawing.Size(270, 78);
            this.inputBox.TabIndex = 0;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(20, 117);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(132, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "Converteer naar NFDA";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Location = new System.Drawing.Point(368, 124);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1891, 212);
            this.panel1.TabIndex = 2;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(794, 20);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(116, 23);
            this.button2.TabIndex = 4;
            this.button2.Text = "Nieuwe Toestand";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(794, 85);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(116, 24);
            this.button3.TabIndex = 5;
            this.button3.Text = "Nieuwe pijl";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // pijl_from
            // 
            this.pijl_from.AccessibleName = "";
            this.pijl_from.Location = new System.Drawing.Point(551, 89);
            this.pijl_from.Name = "pijl_from";
            this.pijl_from.Size = new System.Drawing.Size(54, 20);
            this.pijl_from.TabIndex = 6;
            // 
            // pijl_to
            // 
            this.pijl_to.Location = new System.Drawing.Point(627, 89);
            this.pijl_to.Name = "pijl_to";
            this.pijl_to.Size = new System.Drawing.Size(52, 20);
            this.pijl_to.TabIndex = 7;
            // 
            // pijl_symbol
            // 
            this.pijl_symbol.Location = new System.Drawing.Point(697, 89);
            this.pijl_symbol.Name = "pijl_symbol";
            this.pijl_symbol.Size = new System.Drawing.Size(58, 20);
            this.pijl_symbol.TabIndex = 8;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(548, 73);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(188, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "From                  To                   Symbol";
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(158, 117);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(132, 23);
            this.button4.TabIndex = 10;
            this.button4.Text = "Converteer naar DFA";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(20, 231);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(288, 45);
            this.textBox1.TabIndex = 11;
            this.textBox1.Text = "(a|b)* a";
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(13, 283);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(148, 23);
            this.button5.TabIndex = 12;
            this.button5.Text = "Converteer naar Reg.Gram";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(502, 342);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(117, 23);
            this.button7.TabIndex = 14;
            this.button7.Text = "Converteer naar DFA";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(625, 342);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(150, 23);
            this.button8.TabIndex = 15;
            this.button8.Text = "Converteer naar Reg.Gram";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.button8_Click);
            // 
            // button9
            // 
            this.button9.Location = new System.Drawing.Point(781, 342);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(141, 23);
            this.button9.TabIndex = 16;
            this.button9.Text = "Converteer naar Reg.Exp";
            this.button9.UseVisualStyleBackColor = true;
            // 
            // button10
            // 
            this.button10.Location = new System.Drawing.Point(794, 50);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(116, 23);
            this.button10.TabIndex = 17;
            this.button10.Text = "Nieuwe eindtoestand";
            this.button10.UseVisualStyleBackColor = true;
            this.button10.Click += new System.EventHandler(this.button10_Click);
            // 
            // button11
            // 
            this.button11.Location = new System.Drawing.Point(168, 283);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(140, 23);
            this.button11.TabIndex = 18;
            this.button11.Text = "Converteer naar NDFA";
            this.button11.UseVisualStyleBackColor = true;
            this.button11.Click += new System.EventHandler(this.button11_Click);
            // 
            // button12
            // 
            this.button12.Location = new System.Drawing.Point(940, 342);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(99, 23);
            this.button12.TabIndex = 19;
            this.button12.Text = "Minimaliseer DFA";
            this.button12.UseVisualStyleBackColor = true;
            this.button12.Click += new System.EventHandler(this.button12_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(13, 312);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(139, 23);
            this.button6.TabIndex = 20;
            this.button6.Text = "Converteer naar DFA";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(368, 387);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(179, 20);
            this.textBox2.TabIndex = 21;
            // 
            // button13
            // 
            this.button13.Location = new System.Drawing.Point(554, 387);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(143, 23);
            this.button13.TabIndex = 22;
            this.button13.Text = "Check (DFA)";
            this.button13.UseVisualStyleBackColor = true;
            this.button13.Click += new System.EventHandler(this.button13_Click);
            // 
            // button14
            // 
            this.button14.Location = new System.Drawing.Point(1134, 19);
            this.button14.Name = "button14";
            this.button14.Size = new System.Drawing.Size(96, 23);
            this.button14.TabIndex = 23;
            this.button14.Text = "Opslaan DFA";
            this.button14.UseVisualStyleBackColor = true;
            this.button14.Click += new System.EventHandler(this.button14_Click);
            // 
            // button15
            // 
            this.button15.Location = new System.Drawing.Point(1134, 49);
            this.button15.Name = "button15";
            this.button15.Size = new System.Drawing.Size(96, 23);
            this.button15.TabIndex = 24;
            this.button15.Text = "Open DFA";
            this.button15.UseVisualStyleBackColor = true;
            this.button15.Click += new System.EventHandler(this.button15_Click);
            // 
            // Form1
            // 
            this.ClientSize = new System.Drawing.Size(1271, 425);
            this.Controls.Add(this.button15);
            this.Controls.Add(this.button14);
            this.Controls.Add(this.button13);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button12);
            this.Controls.Add(this.button11);
            this.Controls.Add(this.button10);
            this.Controls.Add(this.button9);
            this.Controls.Add(this.button8);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pijl_symbol);
            this.Controls.Add(this.pijl_to);
            this.Controls.Add(this.pijl_from);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.inputBox);
            this.Name = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.TextBox inputBox;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TextBox pijl_from;
        private System.Windows.Forms.TextBox pijl_to;
        private System.Windows.Forms.TextBox pijl_symbol;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Button button13;
        private System.Windows.Forms.Button button14;
        private System.Windows.Forms.Button button15;
    }
}

