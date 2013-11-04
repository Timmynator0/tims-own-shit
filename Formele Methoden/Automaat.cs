using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FMApplicatie
{
    class Automaat
    {
        public const char EPSILON = 'ε';
        protected List<Toestand> toestanden = new List<Toestand>();

        public Automaat()
        {
        }

        public Automaat(Automaat automaat)
        {
            // Deze automaat krijgt dezelfde toestanden
            this.toestanden = automaat.toestanden;
        }

        public virtual void voegToestandToe(Toestand nieuweToestand) 
        {
            // Geef de toestand alleen een ID als deze nog niet is gegeven
            if (nieuweToestand.id == Toestand.NOT_SET)
            {
                nieuweToestand.setId(getNextId());
            }

            toestanden.Add(nieuweToestand);
        }

        public void voegPijlToe(Pijl nieuwePijl)
        {
            int fromId = nieuwePijl.getFromId();
            int toId = nieuwePijl.getToId();

            // Zoek toestand waar de pijl vandaan komt
            foreach(Toestand toestand in toestanden)
            {
                if (toestand.id == fromId)
                {
                    toestand.voegUitgaandToe(nieuwePijl);
                }
                if (toestand.id == toId)
                {
                    toestand.voegInkomendToe(nieuwePijl);
                }
            }
        }
        public Toestand getToestandVanId(int id)
        {
            foreach (Toestand toestand in toestanden)
            {
                if (toestand.id == id)
                {
                    return toestand;
                }
            }

            return null;
        }
        public int getNextId()
        {
            int id = 0;

            while (true)
            {
                bool idFound = false;
                foreach (Toestand toestand in toestanden)
                {
                    if (toestand.id == id)
                    {
                        id++;
                        idFound = true;
                        break;
                    }
                }
                if (!idFound)
                {
                    return id;
                }
            }
        }

        public void leegToestanden()
        {
            toestanden.Clear();
        }

        public void reverse()
        {
            foreach (Toestand toestand in toestanden)
                toestand.reverse();
        }

        public void valideerInput(String input)
        {
            Toestand toestand = toestanden[0];

            for (int i = 0; i < input.Length; i++)
            {
                char symbool = input[i];
                bool isGeldig = false;

                List<Pijl> uitgaandePijlen = toestand.geefUitgaandePijlen();
                foreach (Pijl pijl in uitgaandePijlen)
                {
                    if (pijl.getSymbool() == symbool)
                    {
                        toestand = getToestandVanId(pijl.getToId());
                        isGeldig = true;
                        break;
                    }
                }

                if (!isGeldig)
                {
                    System.Windows.Forms.MessageBox.Show("Input is niet geldig!");
                    return;
                }
            }

            if((toestand.getCategory() & Toestand.Category.Eind) == Toestand.Category.Eind)
                System.Windows.Forms.MessageBox.Show("De input is geldig! :D ");
            else
                System.Windows.Forms.MessageBox.Show("Input is niet geldig!");
        }
    }
}
