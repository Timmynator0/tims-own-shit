using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FMApplicatie
{
    class Ndfa : Automaat
    {
        public Ndfa()
        {
        }
        public Ndfa(Automaat automaat) : base(automaat)
        {
            
        }

        public void plaatsNormaleToestand()
        {
            if (toestanden.Count == 0)
            {
                // We hebben nog geen toestanden, dus deze toestand is een Begintoestand
                voegToestandToe(new Toestand(Toestand.Category.Begin));
            } else {
                // Voeg normale toestand toe
                voegToestandToe(new Toestand(Toestand.Category.Normaal));
            }
        }

        public void plaatsEindToestand()
        {
            // Voeg eindtoestand toe
           if (toestanden.Count == 0)
            {
                // We hebben nog geen toestanden, dus deze toestand is een ook Begintoestand
                voegToestandToe(new Toestand(Toestand.Category.Begin | Toestand.Category.Eind));
            } else {
                // Voeg eindtoestand toe
                voegToestandToe(new Toestand(Toestand.Category.Eind));
            }
        }

        public virtual void plaatsPijl(String fromText, String toText, String symboolText)
        {
            int from = Convert.ToInt32(fromText);
            int to = Convert.ToInt32(toText);
            char symbool = Convert.ToChar(symboolText);

            Pijl pijl = new Pijl(from, to, symbool);
            voegPijlToe(pijl);
        }

        public void update(System.Windows.Forms.Panel panel)
        {
            
            System.Drawing.Graphics g = System.Drawing.Graphics.FromHwnd(panel.Handle);
            Brush whiteBrush = new System.Drawing.SolidBrush(System.Drawing.Color.White);
            g.FillRectangle(whiteBrush, 0, 0, 10000, 10000);

            for(int i = 0; i < toestanden.Count; i++)
            {
                Toestand toestand = toestanden[i];
                int offset = 50;
                const int circleHeight = 50;
                offset += (i * 100);

                // Teken de cirkel
                Rectangle r = new Rectangle(new Point(offset, circleHeight), new Size(new Point(Toestand.WIDTH, Toestand.HEIGHT)));
                
                g.DrawEllipse(Pens.Black, r);

                // Teken het id
                String id = Convert.ToString(toestand.id);
                RectangleF rf = new RectangleF(new PointF((float)offset + 15f, (float)Toestand.HEIGHT + 25f),
                        new SizeF(new PointF((float)Toestand.WIDTH, (float)Toestand.HEIGHT)));

                g.DrawString(id, panel.Font, Brushes.Black, rf);

                // Teken een dubbele cirkel bij een eindtoestand
                if ((toestand.getCategory() & Toestand.Category.Eind) == Toestand.Category.Eind)
                {
                    r = new Rectangle(new Point(offset + 2, circleHeight + 2), new Size(new Point(Toestand.WIDTH - 4, Toestand.HEIGHT - 4)));
                    g.DrawEllipse(Pens.Black, r);
                }

                // Teken een pijltje bij een begintoestand
                if ((toestand.getCategory() & Toestand.Category.Begin) == Toestand.Category.Begin)
                {
                    // Teken de rechte lijn
                    Point begin = new Point(offset - 20, 67);
                    Point eind = new Point(offset - 2, 67);
                    g.DrawLine(Pens.Black, begin, eind);

                    // Teken de 2 schuine lijntjes
                    Point boven = new Point(offset - 9, 60);
                    Point onder = new Point(offset - 9, 74);

                    g.DrawLine(Pens.Black, boven, eind);
                    g.DrawLine(Pens.Black, onder, eind);
                }
                // Sla positie op
                PointF positie = new PointF(offset, 50);
                toestand.setPositie(positie);
            }

            // Nu gaan we de pijlen per toestand tekenen
            for (int i = 0; i < toestanden.Count; i++)
            {
                Toestand toestand = toestanden[i];

                // We tekenen alleen de uitgaande pijlen
                List<Pijl> uitgaandePijlen = toestand.geefUitgaandePijlen();
                for (int idx = 0; idx < uitgaandePijlen.Count; idx++)
                {
                    Pijl uitgaandePijl = uitgaandePijlen[idx];

                    Toestand from = getToestandVanId(uitgaandePijl.getFromId());
                    Toestand to = getToestandVanId(uitgaandePijl.getToId());
                    String symbool = Convert.ToString(uitgaandePijl.getSymbool());

                    // Pijl klopt niet, we gaan verder naar de volgende pijl
                    if (to == null | from == null)
                        continue;

                    PointF fromPoint = from.getPositie();
                    fromPoint.X += Toestand.WIDTH;
                    fromPoint.Y += (Toestand.HEIGHT / 2);

                    PointF toPoint = to.getPositie();
                    toPoint.Y += (Toestand.HEIGHT / 2);

                    if (Math.Abs(from.id - to.id) == 1 && fromPoint.X < toPoint.X)
                    {
                        // De Toestanden liggen naast elkaar
                        g.DrawLine(Pens.Black, fromPoint, toPoint);

                        // Teken nu het symbool

                        float xPos = (float)(toPoint.X + fromPoint.X) / 2;
                        float yPos = -15f + (float)(toPoint.Y + fromPoint.Y) / 2;

                        RectangleF rect = new RectangleF(new PointF(xPos, yPos), new SizeF(new PointF(50, 50)));
                        g.DrawString(symbool, panel.Font, Brushes.Black, rect);
                    }
                    else
                    {
                        // Teken een halve circel, ze liggen niet naast elkaar
                        RectangleF rect;
                        int width = Math.Abs((int)fromPoint.X - (int)toPoint.X);
                        int height = width / 3 ;

                        // Kijk of de pijl naar dezelfde toestand wijst
                        if (Math.Abs(from.id - to.id) == 0)
                        {
                            // Deze pijl wijst naar dezelfde toestand
                            height *= 5;
                        }

                        // Kijk waar de rectangle moet beginnen
                        if (fromPoint.X > toPoint.X)
                        {
                            // We gaan terug
                            rect = new RectangleF(toPoint.X, toPoint.Y - (height / 2), width, height);

                            // Reken de halve cirkel
                            g.DrawArc(Pens.Black, rect, 180, 180);

                            // Teken het symbool
                            float xPos = (float)(toPoint.X + fromPoint.X) / 2;
                            float yPos = -(height / 2) + ((float)(toPoint.Y + fromPoint.Y) / 2);

                            rect = new RectangleF(new PointF(xPos, yPos), new SizeF(new PointF(50, 50)));
                            g.DrawString(symbool, panel.Font, Brushes.Black, rect);
                        }
                        else
                        {
                            // We gaan vooruit
                            rect = new RectangleF(fromPoint.X, fromPoint.Y - (height / 2), width, height);

                            // Reken de halve cirkel
                            g.DrawArc(Pens.Black, rect, 0, 180);

                            // Teken het symbool
                            float xPos = (float)(toPoint.X + fromPoint.X) / 2;
                            float yPos = (height / 2) + ((float)(toPoint.Y + fromPoint.Y) / 2);

                            rect = new RectangleF(new PointF(xPos, yPos), new SizeF(new PointF(50, 50)));
                            g.DrawString(symbool, panel.Font, Brushes.Black, rect);
                        }
                        

                       
                    }

                    
                }
            }
            
            
        }
    }
}
