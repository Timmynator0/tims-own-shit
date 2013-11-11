using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FMApplicatie
{
    
 
    public partial class addArrowForm : Form
    {
     

        public addArrowForm()
        {
          InitializeComponent();
        }

        private void addArrowForm_Load(object sender, EventArgs e)
        {

        }

        private void AddArrowButton_Click(object sender, EventArgs e)
        {
            MainForm mF = (MainForm)this.Owner;
            mF.fromText = this.arrow_From.Text;
            mF.toText = this.Arrow_To.Text;
            mF.symbolText = this.Arrow_Symbol.Text;
            Dispose();
        }

        //public string fromText
        //{
        //    get
        //    {
        //        return (arrow_From.Text);
        //    }
        //}
        //public string toText
        //{
        //    get
        //    {
        //        return (Arrow_To.Text);
        //    }
        //}
        //public string symbolText
        //{
        //    get
        //    {
        //        return (Arrow_Symbol.Text);
        //    }
        //}
    }
}
