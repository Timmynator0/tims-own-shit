namespace FMApplicatie
{
    partial class MainForm
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
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.fileMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveDFAMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openDFAMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.stateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.endstateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.arrowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.GrammarInputBox = new System.Windows.Forms.TextBox();
            this.GrammarToNDFAButton = new System.Windows.Forms.Button();
            this.GrammarToDFAButton = new System.Windows.Forms.Button();
            this.RegexInputbox = new System.Windows.Forms.TextBox();
            this.RegexToDFAButton = new System.Windows.Forms.Button();
            this.RegexToNDFAButton = new System.Windows.Forms.Button();
            this.RegexToGrammarButton = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.minimizeDFAButton = new System.Windows.Forms.Button();
            this.GraphToRegexButton = new System.Windows.Forms.Button();
            this.GraphToGrammarButtonr = new System.Windows.Forms.Button();
            this.GraphToDFAButton = new System.Windows.Forms.Button();
            this.menuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileMenuItem,
            this.newToolStripMenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(931, 24);
            this.menuStrip.TabIndex = 0;
            this.menuStrip.Text = "menuStrip1";
            // 
            // fileMenuItem
            // 
            this.fileMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.saveDFAMenuItem,
            this.openDFAMenuItem});
            this.fileMenuItem.Name = "fileMenuItem";
            this.fileMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileMenuItem.Text = "File";
            // 
            // saveDFAMenuItem
            // 
            this.saveDFAMenuItem.Name = "saveDFAMenuItem";
            this.saveDFAMenuItem.Size = new System.Drawing.Size(128, 22);
            this.saveDFAMenuItem.Text = "Save DFA";
            // 
            // openDFAMenuItem
            // 
            this.openDFAMenuItem.Name = "openDFAMenuItem";
            this.openDFAMenuItem.Size = new System.Drawing.Size(128, 22);
            this.openDFAMenuItem.Text = "Open DFA";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.stateToolStripMenuItem,
            this.endstateToolStripMenuItem,
            this.arrowToolStripMenuItem});
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.newToolStripMenuItem.Text = "New";
            // 
            // stateToolStripMenuItem
            // 
            this.stateToolStripMenuItem.Name = "stateToolStripMenuItem";
            this.stateToolStripMenuItem.Size = new System.Drawing.Size(119, 22);
            this.stateToolStripMenuItem.Text = "State";
            this.stateToolStripMenuItem.Click += new System.EventHandler(this.stateToolStripMenuItem_Click);
            // 
            // endstateToolStripMenuItem
            // 
            this.endstateToolStripMenuItem.Name = "endstateToolStripMenuItem";
            this.endstateToolStripMenuItem.Size = new System.Drawing.Size(119, 22);
            this.endstateToolStripMenuItem.Text = "Endstate";
            this.endstateToolStripMenuItem.Click += new System.EventHandler(this.endstateToolStripMenuItem_Click);
            // 
            // arrowToolStripMenuItem
            // 
            this.arrowToolStripMenuItem.Name = "arrowToolStripMenuItem";
            this.arrowToolStripMenuItem.Size = new System.Drawing.Size(119, 22);
            this.arrowToolStripMenuItem.Text = "Arrow";
            this.arrowToolStripMenuItem.Click += new System.EventHandler(this.arrowToolStripMenuItem_Click);
            // 
            // GrammarInputBox
            // 
            this.GrammarInputBox.Location = new System.Drawing.Point(12, 27);
            this.GrammarInputBox.Multiline = true;
            this.GrammarInputBox.Name = "GrammarInputBox";
            this.GrammarInputBox.Size = new System.Drawing.Size(251, 115);
            this.GrammarInputBox.TabIndex = 1;
            this.GrammarInputBox.Text = "Enter the Grammar";
            // 
            // GrammarToNDFAButton
            // 
            this.GrammarToNDFAButton.Location = new System.Drawing.Point(268, 56);
            this.GrammarToNDFAButton.Name = "GrammarToNDFAButton";
            this.GrammarToNDFAButton.Size = new System.Drawing.Size(123, 23);
            this.GrammarToNDFAButton.TabIndex = 2;
            this.GrammarToNDFAButton.Text = "Convert to NDFA";
            this.GrammarToNDFAButton.UseVisualStyleBackColor = true;
            this.GrammarToNDFAButton.Click += new System.EventHandler(this.GrammarToNDFAButton_Click);
            // 
            // GrammarToDFAButton
            // 
            this.GrammarToDFAButton.Location = new System.Drawing.Point(269, 27);
            this.GrammarToDFAButton.Name = "GrammarToDFAButton";
            this.GrammarToDFAButton.Size = new System.Drawing.Size(122, 23);
            this.GrammarToDFAButton.TabIndex = 3;
            this.GrammarToDFAButton.Text = "Convert to DFA";
            this.GrammarToDFAButton.UseVisualStyleBackColor = true;
            this.GrammarToDFAButton.Click += new System.EventHandler(this.GrammarToDFAButton_Click);
            // 
            // RegexInputbox
            // 
            this.RegexInputbox.Location = new System.Drawing.Point(397, 27);
            this.RegexInputbox.Multiline = true;
            this.RegexInputbox.Name = "RegexInputbox";
            this.RegexInputbox.Size = new System.Drawing.Size(251, 115);
            this.RegexInputbox.TabIndex = 4;
            this.RegexInputbox.Text = "(a|b)* a";
            // 
            // RegexToDFAButton
            // 
            this.RegexToDFAButton.Location = new System.Drawing.Point(654, 54);
            this.RegexToDFAButton.Name = "RegexToDFAButton";
            this.RegexToDFAButton.Size = new System.Drawing.Size(111, 23);
            this.RegexToDFAButton.TabIndex = 6;
            this.RegexToDFAButton.Text = "Convert to DFA";
            this.RegexToDFAButton.UseVisualStyleBackColor = true;
            this.RegexToDFAButton.Click += new System.EventHandler(this.RegexToDFAButton_Click);
            // 
            // RegexToNDFAButton
            // 
            this.RegexToNDFAButton.Location = new System.Drawing.Point(654, 25);
            this.RegexToNDFAButton.Name = "RegexToNDFAButton";
            this.RegexToNDFAButton.Size = new System.Drawing.Size(111, 23);
            this.RegexToNDFAButton.TabIndex = 5;
            this.RegexToNDFAButton.Text = "Convert to NDFA";
            this.RegexToNDFAButton.UseVisualStyleBackColor = true;
            this.RegexToNDFAButton.Click += new System.EventHandler(this.RegexToNDFAButton_Click);
            // 
            // RegexToGrammarButton
            // 
            this.RegexToGrammarButton.Location = new System.Drawing.Point(654, 83);
            this.RegexToGrammarButton.Name = "RegexToGrammarButton";
            this.RegexToGrammarButton.Size = new System.Drawing.Size(111, 23);
            this.RegexToGrammarButton.TabIndex = 7;
            this.RegexToGrammarButton.Text = "Convert to Grammar";
            this.RegexToGrammarButton.UseVisualStyleBackColor = true;
            this.RegexToGrammarButton.Click += new System.EventHandler(this.RegexToGrammarButton_Click);
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Location = new System.Drawing.Point(12, 202);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(907, 202);
            this.panel1.TabIndex = 8;
            // 
            // minimizeDFAButton
            // 
            this.minimizeDFAButton.Location = new System.Drawing.Point(438, 173);
            this.minimizeDFAButton.Name = "minimizeDFAButton";
            this.minimizeDFAButton.Size = new System.Drawing.Size(99, 23);
            this.minimizeDFAButton.TabIndex = 23;
            this.minimizeDFAButton.Text = "Minimize DFA";
            this.minimizeDFAButton.UseVisualStyleBackColor = true;
            this.minimizeDFAButton.Click += new System.EventHandler(this.minimizeDFAButton_Click);
            // 
            // GraphToRegexButton
            // 
            this.GraphToRegexButton.Location = new System.Drawing.Point(291, 173);
            this.GraphToRegexButton.Name = "GraphToRegexButton";
            this.GraphToRegexButton.Size = new System.Drawing.Size(141, 23);
            this.GraphToRegexButton.TabIndex = 22;
            this.GraphToRegexButton.Text = "Convert to Reg.Exp";
            this.GraphToRegexButton.UseVisualStyleBackColor = true;
            this.GraphToRegexButton.Click += new System.EventHandler(this.GraphToRegexButton_Click);
            // 
            // GraphToGrammarButtonr
            // 
            this.GraphToGrammarButtonr.Location = new System.Drawing.Point(135, 173);
            this.GraphToGrammarButtonr.Name = "GraphToGrammarButtonr";
            this.GraphToGrammarButtonr.Size = new System.Drawing.Size(150, 23);
            this.GraphToGrammarButtonr.TabIndex = 21;
            this.GraphToGrammarButtonr.Text = "Convert to grammar";
            this.GraphToGrammarButtonr.UseVisualStyleBackColor = true;
            this.GraphToGrammarButtonr.Click += new System.EventHandler(this.GraphToGrammarButtonr_Click);
            // 
            // GraphToDFAButton
            // 
            this.GraphToDFAButton.Location = new System.Drawing.Point(12, 173);
            this.GraphToDFAButton.Name = "GraphToDFAButton";
            this.GraphToDFAButton.Size = new System.Drawing.Size(117, 23);
            this.GraphToDFAButton.TabIndex = 20;
            this.GraphToDFAButton.Text = "Convert to DFA";
            this.GraphToDFAButton.UseVisualStyleBackColor = true;
            this.GraphToDFAButton.Click += new System.EventHandler(this.GraphToDFAButton_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(931, 416);
            this.Controls.Add(this.minimizeDFAButton);
            this.Controls.Add(this.GraphToRegexButton);
            this.Controls.Add(this.GraphToGrammarButtonr);
            this.Controls.Add(this.GraphToDFAButton);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.RegexToGrammarButton);
            this.Controls.Add(this.RegexToDFAButton);
            this.Controls.Add(this.RegexToNDFAButton);
            this.Controls.Add(this.RegexInputbox);
            this.Controls.Add(this.GrammarToDFAButton);
            this.Controls.Add(this.GrammarToNDFAButton);
            this.Controls.Add(this.GrammarInputBox);
            this.Controls.Add(this.menuStrip);
            this.MainMenuStrip = this.menuStrip;
            this.Name = "MainForm";
            this.Text = "MainForm";
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem fileMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveDFAMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openDFAMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem stateToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem endstateToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem arrowToolStripMenuItem;
        private System.Windows.Forms.TextBox GrammarInputBox;
        private System.Windows.Forms.Button GrammarToNDFAButton;
        private System.Windows.Forms.Button GrammarToDFAButton;
        private System.Windows.Forms.TextBox RegexInputbox;
        private System.Windows.Forms.Button RegexToDFAButton;
        private System.Windows.Forms.Button RegexToNDFAButton;
        private System.Windows.Forms.Button RegexToGrammarButton;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button minimizeDFAButton;
        private System.Windows.Forms.Button GraphToRegexButton;
        private System.Windows.Forms.Button GraphToGrammarButtonr;
        private System.Windows.Forms.Button GraphToDFAButton;
    }
}