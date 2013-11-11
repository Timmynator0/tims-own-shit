namespace FMApplicatie
{
    partial class addArrowForm
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
            this.Arrow_Symbol = new System.Windows.Forms.TextBox();
            this.arrow_From = new System.Windows.Forms.TextBox();
            this.Arrow_To = new System.Windows.Forms.TextBox();
            this.Label_To = new System.Windows.Forms.Label();
            this.Label_Symbol = new System.Windows.Forms.Label();
            this.label_From = new System.Windows.Forms.Label();
            this.AddArrowButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Arrow_Symbol
            // 
            this.Arrow_Symbol.Location = new System.Drawing.Point(69, 58);
            this.Arrow_Symbol.Name = "Arrow_Symbol";
            this.Arrow_Symbol.Size = new System.Drawing.Size(58, 20);
            this.Arrow_Symbol.TabIndex = 12;
            // 
            // arrow_From
            // 
            this.arrow_From.Location = new System.Drawing.Point(69, 6);
            this.arrow_From.Name = "arrow_From";
            this.arrow_From.Size = new System.Drawing.Size(58, 20);
            this.arrow_From.TabIndex = 11;
            // 
            // Arrow_To
            // 
            this.Arrow_To.AccessibleName = "";
            this.Arrow_To.Location = new System.Drawing.Point(69, 32);
            this.Arrow_To.Name = "Arrow_To";
            this.Arrow_To.Size = new System.Drawing.Size(58, 20);
            this.Arrow_To.TabIndex = 10;
            // 
            // Label_To
            // 
            this.Label_To.AutoSize = true;
            this.Label_To.Location = new System.Drawing.Point(22, 32);
            this.Label_To.Name = "Label_To";
            this.Label_To.Size = new System.Drawing.Size(20, 13);
            this.Label_To.TabIndex = 15;
            this.Label_To.Text = "To";
            // 
            // Label_Symbol
            // 
            this.Label_Symbol.AutoSize = true;
            this.Label_Symbol.Location = new System.Drawing.Point(22, 65);
            this.Label_Symbol.Name = "Label_Symbol";
            this.Label_Symbol.Size = new System.Drawing.Size(41, 13);
            this.Label_Symbol.TabIndex = 16;
            this.Label_Symbol.Text = "Symbol";
            // 
            // label_From
            // 
            this.label_From.AutoSize = true;
            this.label_From.Location = new System.Drawing.Point(22, 9);
            this.label_From.Name = "label_From";
            this.label_From.Size = new System.Drawing.Size(30, 13);
            this.label_From.TabIndex = 14;
            this.label_From.Text = "From";
            // 
            // AddArrowButton
            // 
            this.AddArrowButton.Location = new System.Drawing.Point(69, 102);
            this.AddArrowButton.Name = "AddArrowButton";
            this.AddArrowButton.Size = new System.Drawing.Size(75, 23);
            this.AddArrowButton.TabIndex = 17;
            this.AddArrowButton.Text = "Add Arrow";
            this.AddArrowButton.UseVisualStyleBackColor = true;
            this.AddArrowButton.Click += new System.EventHandler(this.AddArrowButton_Click);
            // 
            // addArrowForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(202, 154);
            this.Controls.Add(this.AddArrowButton);
            this.Controls.Add(this.Label_Symbol);
            this.Controls.Add(this.Label_To);
            this.Controls.Add(this.label_From);
            this.Controls.Add(this.Arrow_Symbol);
            this.Controls.Add(this.arrow_From);
            this.Controls.Add(this.Arrow_To);
            this.Name = "addArrowForm";
            this.Text = "addArrowForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox Arrow_Symbol;
        private System.Windows.Forms.TextBox arrow_From;
        private System.Windows.Forms.TextBox Arrow_To;
        private System.Windows.Forms.Label Label_To;
        private System.Windows.Forms.Label Label_Symbol;
        private System.Windows.Forms.Label label_From;
        private System.Windows.Forms.Button AddArrowButton;
    }
}