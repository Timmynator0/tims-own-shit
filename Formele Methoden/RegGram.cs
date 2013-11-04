using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FMApplicatie
{
    class RegGram : Automaat
    {
        private TextBox input;

        public RegGram(TextBox input)
        {
            this.input = input;
        }
        public RegGram(Automaat automaat, TextBox input)
            : base(automaat)
        {
            this.input = input;
        }


        public void importeerData(String input)
        {
            String[] inputLines = input.Split(new string[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries);

            // Haal alle spaties weg
            for (int i = 0; i < inputLines.Length; i++)
            {
                inputLines[i] = inputLines[i].Replace(" ", "");
            }
            // We gaan nu alle regels doorlopen om toestanden met de juiste id's aan te maken
            for(int i = 0; i < inputLines.Length; i++)
            {
                String line = inputLines[i];

                int index = line.IndexOf("->");
                String idString = line.Substring(0, index);
                int id = Convert.ToInt32(idString);

                Toestand toestand;
                if (i == 0)
                {
                    toestand = new Toestand(id, Toestand.Category.Begin);
                }
                else
                {
                    toestand = new Toestand(id, Toestand.Category.Normaal);
                }
                // Voeg de (lege) toestand toe aan de automaat
                voegToestandToe(toestand);
            }
            // Lees per regel de pijlen uit
            for (int i = 0; i < inputLines.Length; i++)
            {
                List<char> eindSymbolen = new List<char>();

                String line = inputLines[i];

                
                int index = line.IndexOf("->");

                // Haal het id van de toestand op
                String idString = line.Substring(0, index);
                int fromId = Convert.ToInt32(idString);

                // 2 + omdat het pijltje 2 karakters lang is
                int start = 2 + index;

                // Verwijder het pijltje van de string
                line = line.Substring(start);

                bool continueParsing = true;
                do
                {
                    if (line == null || line.Length == 0)
                    {
                        break;
                    }
                    // Lees het symbool uit, deze staat aan het begin van de string
                    char symbool = Convert.ToChar(line[0]);

                    // Het symbool gaat niet naar een eindtoestand
                    if (line.Length >= 2)
                    {
                        // Kijk naar welke toestand de pijl toe gaat
                        // Lees het karakter(lengte 1) na het symbool uit

                        String to;
                        if (line.Contains("|"))
                        {
                            // Die 1 is er omdat we al 1 karakter hebben gelezen : Het symbool
                            to = line.Substring(1, line.IndexOf("|") - 1);
                        }
                        else
                        {
                            // Lees de rest uit
                            to = line.Substring(1);
                        }

                        if (to.Length == 0) // Er staat geen id achter, maar een | 
                        {
                            // Deze pijl gaat naar een eindtoestand toe
                            eindSymbolen.Add(symbool);
                        }
                        else
                        {

                            // Converteer de char naar het id
                            // In een char heeft de nul de waarde 48, dit moeten we er dus vanaf trekken
                            int toId = Convert.ToInt32(to);

                            // Voeg de pijl toe
                            Pijl pijl = new Pijl(fromId, toId, symbool);
                            voegPijlToe(pijl);
                        }
                    }
                    else
                    {
                        // Deze pijl gaat naar een eindtoestand toe
                        eindSymbolen.Add(symbool);
                    }

                    // Verwijder alle karakters tot de volgende | 
                    if (line.Contains("|"))
                    {
                        line = line.Substring(line.IndexOf("|") + 1);
                        continueParsing = true;
                    }
                    else
                    {
                        continueParsing = false;
                    }
                }
                while (continueParsing);

                // Voeg nu de missende symbolen toe
                List<Pijl> uitgaandePijlen = getToestandVanId(fromId).geefUitgaandePijlen();
                
                foreach (char symbool in eindSymbolen)
                {
                    // Doorloop alle pijlen
                    foreach (Pijl pijl in uitgaandePijlen)
                    {
                        if (pijl.getSymbool() == symbool)
                        {
                            // We hebben een pijl die naar een toestand gaat, en we hetzelfde symbool gaat naar een (onbekende) eindtoestand
                            // We gaan er van uit dat dit symbool naar die toestand gaat
                            // TODO Maak hier betere code van
                            getToestandVanId(pijl.getToId()).maakEindtoestand();
                        }
                    }
                }
            }


        }
        public void visualiseerData()
        {
            input.Text = "";

            foreach (Toestand toestand in toestanden)
            {
                // 0 ->
                input.Text += toestand.id;
                input.Text += " -> ";

                List<Pijl> uitgaandePijlen = toestand.geefUitgaandePijlen();
                for(int i = 0; i < uitgaandePijlen.Count; i++) 
                {
                    Pijl pijl = uitgaandePijlen[i];
                    // a2
                    input.Text += pijl.getSymbool();
                    input.Text += pijl.getToId();

                    Toestand naarToestand = getToestandVanId(pijl.getToId());
                    if ((naarToestand.getCategory() & Toestand.Category.Eind) == Toestand.Category.Eind)
                    {
                        // Eind toestand, we kunnen ook 'symbool' hebben
                        input.Text += " | ";
                        input.Text += pijl.getSymbool();
                    }

                    if (i + 1 < uitgaandePijlen.Count)
                    {
                        input.Text += " | ";
                    }
                    
                }

                input.Text += Environment.NewLine;
            }
        }

        internal void save()
        {
            visualiseerData();

            String text = input.Text;

            String[] inputLines = text.Split(new string[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries);

            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "Text File|*.txt";
            saveFileDialog1.Title = "Sla de data op";
            saveFileDialog1.ShowDialog();

            // If the file name is not an empty string open it for saving.
            if (saveFileDialog1.FileName != "")
            {
                // Saves the Image via a FileStream created by the OpenFile method.
                System.IO.FileStream fs =
                 (System.IO.FileStream)saveFileDialog1.OpenFile();
                //WriteAllLines creates a file, writes a collection of strings to the file, 
                //and then closes the file.

                StreamWriter sw = new StreamWriter(fs);
                // Save the data
                foreach(String line in inputLines)
                    sw.WriteLine(line);
                sw.Flush();
                sw.Close();
            }
                
        }
    }
}
