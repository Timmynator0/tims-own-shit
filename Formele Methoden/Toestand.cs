using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FMApplicatie
{
    class Toestand
    {
        public const int WIDTH = 50;
        public const int HEIGHT = 35;

        public const int NOT_SET = -1;
        public enum Category
        {
            Begin = 1, Normaal = 2, Eind = 4
        }

        public int id { get; private set; }
        private Category categorie;

        private List<Pijl> inkomend = new List<Pijl>();
        private List<Pijl> uitgaand = new List<Pijl>();
        private PointF positie;

        public Toestand(int id, Category category)
        {
            this.id = id;
            this.categorie = category;
        }
        public Toestand(Category categorie)
        {
            this.categorie = categorie;
            this.id = NOT_SET;
        }

        public void setId(int id)
        {
            this.id = id;

            foreach(Pijl pijl in uitgaand)
                pijl.setFromId(id);

            foreach (Pijl pijl in inkomend)
                pijl.setToId(id);
        }

        public void voegInkomendToe(Pijl pijl)
        {
            Pijl nieuwePijl = new Pijl(pijl.getFromId(), id, pijl.getSymbool());

            if(!inkomend.Contains(nieuwePijl))
                inkomend.Add(nieuwePijl);
        }
        public void voegUitgaandToe(Pijl pijl)
        {
            Pijl nieuwePijl = new Pijl(id, pijl.getToId(), pijl.getSymbool());

            if (!uitgaand.Contains(nieuwePijl))
            uitgaand.Add(nieuwePijl);
        }

        public List<Pijl> geefUitgaandePijlen()
        {
            return uitgaand;
        }

        public List<Pijl> geefInkomendePijlen()
        {
            return inkomend;
        }

        public Category getCategory()
        {
            return categorie;
        }

        public void maakEindtoestand()
        {
            this.categorie = this.categorie | Category.Eind;
        }

        public void setPositie(PointF positie)
        {
            this.positie = positie;
        }
        public PointF getPositie()
        {
            return positie;
        }

        internal void VoegUitgaandePijlenToe(List<Pijl> list)
        {
            foreach (Pijl pijl in list)
            {
                Pijl nieuwePijl = new Pijl(id, pijl.getToId(), pijl.getSymbool());
                this.uitgaand.Add(nieuwePijl);
            }

        }

        internal bool heeftInkomendePijlen(Automaat automaat)
        {

            if (inkomend.Count == 0)
                return false;

            int geldigePijlen = inkomend.Count;
            for (int i = 0; i < inkomend.Count; i++)
            {
                if (automaat.getToestandVanId(inkomend[i].getFromId()) == null ||
                    automaat.getToestandVanId(inkomend[i].getToId()) == null ||
                    (inkomend[i].getToId() == inkomend[i].getFromId()))
                {
                    // De pijl is niet geldig
                    geldigePijlen--;
                }
            }

            return geldigePijlen > 0;
        }

        public void reverse()
        {
            List<Pijl> uitgaandePijlen = uitgaand;

            uitgaand = inkomend;
            inkomend = uitgaandePijlen;

            foreach (Pijl p in uitgaand)
                p.reverse();

            foreach (Pijl p in inkomend)
                p.reverse();

            if (categorie == Category.Begin)
                categorie = Category.Eind;
            else if (categorie == Category.Eind)
                categorie = Category.Begin;
        }
    }
}
