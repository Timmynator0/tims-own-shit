using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FMApplicatie
{
    
    public partial class MainForm : Form
    {
        private RegGram regGram;
        private Ndfa ndfa = new Ndfa();
        private Dfa dfa;
        
        private RegExp regExp;

        public MainForm()
        {
            InitializeComponent();
            regGram = new RegGram(GrammarInputBox);
        }

        private void updateNdfa()
        {

            ndfa.update(panel1);

        }
        private void updateDfa()
        {
            dfa.update(panel1);

        }

        private void GrammarToNDFAButton_Click(object sender, EventArgs e)
        {
            // Converteer Reg.Gram. naar ons datamodel
            String input = GrammarInputBox.Text;
            regGram.leegToestanden();
            regGram.importeerData(input);

            ndfa = new Ndfa(regGram);
            updateNdfa();
        }

        private void GrammarToDFAButton_Click(object sender, EventArgs e)
        {
            // Converteer Reg.Gram. naar ons datamodel
            String input = GrammarInputBox.Text;
            regGram.leegToestanden();
            regGram.importeerData(input);

            dfa = new Dfa(regGram);
            updateDfa();

        }

        private void RegexToNDFAButton_Click(object sender, EventArgs e)
        {
            regExp = new RegExp(RegexInputbox);
            regExp.importeerData(RegexInputbox.Text);

            ndfa = new Ndfa(regExp);
            updateNdfa();
        }

        private void RegexToDFAButton_Click(object sender, EventArgs e)
        {
            regExp = new RegExp(RegexInputbox);
            regExp.importeerData(RegexInputbox.Text);

            dfa = new Dfa(regExp);
            updateDfa();
        }

        private void RegexToGrammarButton_Click(object sender, EventArgs e)
        {
            regExp = new RegExp(RegexInputbox);
            regExp.importeerData(RegexInputbox.Text);

            regGram = new RegGram(regExp, GrammarInputBox);
            regGram.visualiseerData();
        }

        private void GraphToDFAButton_Click(object sender, EventArgs e)
        {
            dfa = new Dfa(ndfa);
            updateDfa();
        }

        private void GraphToGrammarButtonr_Click(object sender, EventArgs e)
        {
            regGram = new RegGram(ndfa, GrammarInputBox);
            regGram.visualiseerData();
        }

        private void GraphToRegexButton_Click(object sender, EventArgs e)
        {
           
        }

        private void minimizeDFAButton_Click(object sender, EventArgs e)
        {
            dfa = new Dfa(dfa);
            updateDfa();

            // Minimalisatie
            dfa.reverse();
            dfa.toDfa();
            dfa.reverse();
            dfa.toDfa();
        }

        private void stateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Voeg toestand toe aan ndfa
            ndfa.plaatsNormaleToestand();
            updateNdfa();
        }

        private void endstateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Voeg eindtoestand toe aan ndfa
            ndfa.plaatsEindToestand();
            updateNdfa();
        }

        Form popup = new addArrowForm();
        public String symbolText { get; set; }
        public String fromText { get; set; }
        public String toText { get; set; }
        
        private void arrowToolStripMenuItem_Click(object sender, EventArgs e)
        {
          //
          // Form popup = new addArrowForm();
          //  String from = popup.fromText;
            popup.ShowDialog(this);
            System.Diagnostics.Debug.WriteLine(fromText + " " + toText + " " + symbolText);
          ndfa.plaatsPijl(fromText, toText, symbolText);
            updateNdfa();
        }






    
    }
}
