using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FMApplicatie
{
    class RegExp : Automaat
    {
        // VB: aa ( bb | ab)*   b+ 
        // 1 methode, die parst de hele regel
        // Als deze methode een openings-haakje tegenkomt, dan wordt gebruik gemaakt van recursie om dat stuk tussen de haakjes te parsen
        // Het karakter wat voor het huidige karakter geparst is, is nog bekend. Zo zijn + en * eenvoudiger te implementeren.
        private TextBox input;

        private Toestand laastToegevoegdeToestand, voorlaatsteToestand;
        private bool isNaHaakjes = false;
        private List<Toestand> verbindToestanden = new List<Toestand>();

        public RegExp(TextBox input)
        {
            this.input = input;
        }
        public RegExp(Automaat automaat, TextBox input)
            : base(automaat)
        {
            this.input = input;
        }

        public void importeerData(String data)
        {
            if (toestanden.Count == 0)
            {
                // Voeg een toestand toe
                Toestand beginToestand = new Toestand(Toestand.Category.Begin);
                voegToestandToe(beginToestand);
            }

            converteerData(data, true);
        }
        // VB: (a|b) (a|b)
        private void converteerData(String data, bool isEindeString)
        {
            // Verwijder alle spaties
            data = data.Replace(" ", "");

            
            Toestand eersteToestand = null;
            char previousChar = '\0';

            bool isTussenHaakjes = false;
            if (data[0] == '(')
            {
                // Dit stuk is tussen haakjes
                eersteToestand = laastToegevoegdeToestand;
                data = data.Substring(1);

                isTussenHaakjes = true;
            }

            for (int i = 0; i < data.Length; previousChar = data[i++])
            {
                char c = data[i];
                bool isLastChar = i + 1 == data.Length && isEindeString;

                if (!isLastChar && !isEindeString)
                {
                    // Misschien is het wel het laatste geldige karakter
                    if (i + 2 == data.Length)
                    {
                        char volgendeChar = data[i + 1];
                        if (volgendeChar == ')' || volgendeChar == '*' || volgendeChar == '+')
                            isLastChar = true;
                    }
                    else if (i + 3 == data.Length)
                    {
                        // Hierna komt misschien nog een haakje en een plus/keer
                        char volgendeChar = data[i + 1];
                        if (volgendeChar == ')' || volgendeChar == '*' || volgendeChar == '+')
                        {
                            volgendeChar = data[i + 2];
                            if (volgendeChar == ')' || volgendeChar == '*' || volgendeChar == '+')
                                isLastChar = true;
                        }
                    }
                }

                // Een haakje niet aan het begin van de data
                if (c == '(' && i != 0)
                {
                    // Openingshaakje
                    // Vind het sluithaakje
                    int index = data.Substring(i).IndexOf(')');
                    if (data[index + 1] == '*' || data[index + 1] == '+')
                    {
                        String subString = data.Substring(i, index + 2);
                        if (i + index + 1 < data.Length)
                            converteerData(subString, false);
                        else
                            converteerData(subString, true);
                        // Skip naar het deel na de haakjes
                        i += index + 1;
                    } else {
                        String subString = data.Substring(i, index + 1);

                        if (i + index + 1 < data.Length)
                            converteerData(subString, false);
                        else
                            converteerData(subString, true);
                        // Skip naar het deel na de haakjes
                        i += index;
                    }

                }
                else if (c == '+' || c == '*')
                {
                    int id = laastToegevoegdeToestand.id;
                    int voorlaatsteId = voorlaatsteToestand.id;

                    if (data[i - 1] == ')')
                    {
                        // Deze + of * gaat over het stuk tussen de haakjes

                        // We kunnen het vorige stuk nog eens herhalen
                        Pijl pijl = new Pijl(id, eersteToestand.id, EPSILON);
                        voegPijlToe(pijl);
                    }
                    else
                    {
                        // We kunnen het vorige karakter nog eens herhalen
                        Pijl pijl = new Pijl(id, id, previousChar);
                        voegPijlToe(pijl);
                    }

                    if (c != '+' || !isLastChar)
                    {
                        // maak de toestand waarin we uit komen
                        Toestand nieuweToestand;
                        if (isLastChar)
                            nieuweToestand = new Toestand(Toestand.Category.Eind);
                        else
                            nieuweToestand = new Toestand(Toestand.Category.Normaal);
                        voegToestandToe(nieuweToestand);

                        // De pijl voor als we het vorige karakter niet herhalen
                        Pijl nietHerhalen = new Pijl(id, nieuweToestand.id, EPSILON);
                        voegPijlToe(nietHerhalen);

                        if (data[i - 1] == ')' && c == '*')
                        {
                            // Deze + of * gaat over het stuk tussen de haakjes


                            Pijl overslaan = new Pijl(eersteToestand.id, nieuweToestand.id, EPSILON);
                            voegPijlToe(overslaan);
                        }
                        else if(c == '*')
                        {
                            // De pijl voor als we het vorige karakter overslaan
                            Pijl overslaan = new Pijl(voorlaatsteId, nieuweToestand.id, EPSILON);
                            voegPijlToe(overslaan);
                        }
                    }
                    else
                    {
                        // Dit is het laatste karakter, het is een eindtoestand
                        laastToegevoegdeToestand.maakEindtoestand();
                    }
                    
                }
                else if (c == '|')
                {
                    // Of-teken

                    // Voeg de laatste toestand van de vorige reeks toe aan de lijst
                    verbindToestanden.Add(laastToegevoegdeToestand);

                    // Pak het volgende karakter
                    c = data[++i];

                    // maak de toestand waarin we uit komen
                    Toestand nieuweToestand;
                    if (isLastChar)
                        nieuweToestand = new Toestand(Toestand.Category.Eind);
                    else
                        nieuweToestand = new Toestand(Toestand.Category.Normaal);
                    voegToestandToe(nieuweToestand);

                    // Maak de pijl met het karakter
                    Pijl pijl = new Pijl(eersteToestand.id, nieuweToestand.id, c);
                    voegPijlToe(pijl);

                    
                }
                else if (c == ')')
                {
                    // Voeg de laatste toestand van de vorige reeks toe aan de lijst
                    verbindToestanden.Add(laastToegevoegdeToestand);

                    Toestand nieuweToestand;
                    if (isLastChar)
                        nieuweToestand = new Toestand(Toestand.Category.Eind);
                    else
                        nieuweToestand = new Toestand(Toestand.Category.Normaal);
                    voegToestandToe(nieuweToestand);
                    
                    if (verbindToestanden.Count > 0)
                    {
                        foreach (Toestand toestand in verbindToestanden)
                        {
                            // Maak pijlen
                            Pijl p = new Pijl(toestand.id, nieuweToestand.id, EPSILON);
                            voegPijlToe(p);
                        }


                        verbindToestanden.Clear();
                    }
                    
                }
                else
                {
                    // Het karakter is deel van het alfabet

                    // maak de toestand waarin we uit komen
                    Toestand nieuweToestand;
                    if (isLastChar)
                        nieuweToestand = new Toestand(Toestand.Category.Eind);
                    else
                        nieuweToestand = new Toestand(Toestand.Category.Normaal);
                    voegToestandToe(nieuweToestand);

                    if (eersteToestand == null)
                        eersteToestand = nieuweToestand;

                    // Maak de pijl met het karakter
                    Pijl pijl = new Pijl(voorlaatsteToestand.id, nieuweToestand.id, c);
                    voegPijlToe(pijl);

                    
                }
            }
        }

        public override void voegToestandToe(Toestand nieuweToestand)
        {
            base.voegToestandToe(nieuweToestand);

            voorlaatsteToestand = laastToegevoegdeToestand;
            laastToegevoegdeToestand = nieuweToestand;
        }
    }

}
