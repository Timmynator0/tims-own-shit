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
    public partial class Form1 : Form
    {
        private RegGram regGram;
        private Ndfa ndfa = new Ndfa();
        private Dfa dfa;
        private RegExp regExp;

        public Form1()
        {
            InitializeComponent();
            regGram = new RegGram(inputBox);
        }


        private void button1_Click(object sender, EventArgs e)
        {
            // Converteer Reg.Gram. naar ons datamodel
            String input = inputBox.Text;
            regGram.leegToestanden();
            regGram.importeerData(input);

            ndfa = new Ndfa(regGram);
            updateNdfa();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            // Voeg toestand toe aan ndfa
            ndfa.plaatsNormaleToestand();
            updateNdfa();
        }

        private void button10_Click(object sender, EventArgs e)
        {
            // Voeg toestand toe aan ndfa
            ndfa.plaatsEindToestand();
            updateNdfa();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            ndfa.plaatsPijl(pijl_from.Text, pijl_to.Text, pijl_symbol.Text);
            updateNdfa();
        }

        private void updateNdfa()
        {
            
            ndfa.update(panel1);
            
        }
        private void updateDfa()
        {
            dfa.update(panel1);
            
        }


        private void button8_Click(object sender, EventArgs e)
        {
            regGram = new RegGram(ndfa, inputBox);
            regGram.visualiseerData();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            dfa = new Dfa(ndfa);
            updateDfa();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            regExp = new RegExp(textBox1);
            regExp.importeerData(textBox1.Text);

            regGram = new RegGram(regExp, inputBox);
            regGram.visualiseerData();
        }

        private void button11_Click(object sender, EventArgs e)
        {
            regExp = new RegExp(textBox1);
            regExp.importeerData(textBox1.Text);

            ndfa = new Ndfa(regExp);
            updateNdfa();
        }

        private void button12_Click(object sender, EventArgs e)
        {
            dfa = new Dfa(dfa);
            updateDfa();

            // Minimalisatie
            dfa.reverse();
            dfa.toDfa();
            dfa.reverse();
            dfa.toDfa();

        }

        private void button6_Click(object sender, EventArgs e)
        {
            regExp = new RegExp(textBox1);
            regExp.importeerData(textBox1.Text);

            dfa = new Dfa(regExp);
            updateDfa();
        }

        private void button13_Click(object sender, EventArgs e)
        {
            // Valideer input
            String input = textBox2.Text;
            dfa.valideerInput(input);
        }

        private void button14_Click(object sender, EventArgs e)
        {
            // Converteer van DFA naar Reg.Gram.
            RegGram reg = new RegGram(dfa, inputBox);
            reg.save();
        }

        private void button15_Click(object sender, EventArgs e)
        {
            // Open Reg.Gram.
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "Text File|*.txt";
            openFileDialog1.Title = "Kies een DFA";

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                String text = File.ReadAllText(openFileDialog1.FileName, Encoding.Default);
                regGram = new RegGram(inputBox);
                regGram.importeerData(text);
                regGram.visualiseerData();
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            // Converteer Reg.Gram. naar ons datamodel
            String input = inputBox.Text;
            regGram.leegToestanden();
            regGram.importeerData(input);

            dfa = new Dfa(regGram);
            updateDfa();
        }


    }
}
