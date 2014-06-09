using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FMApplicatie
{
    class Dfa : Ndfa
    {
        public Dfa()
        {
        }
        public Dfa(Automaat automaat)  : base(automaat)
        {
            toDfa();
        }
        public override void plaatsPijl(String fromText, String toText, String symboolText)
        {
            base.plaatsPijl(fromText, toText, symboolText);
            toDfa();
        }

        public void toDfa()
        {
            // Vervang eerst de Epsilons door
            foreach (Toestand toestand in toestanden)
            {

                bool isAlleenEpsilon = true;
                foreach (Pijl uitgaand in toestand.geefUitgaandePijlen())
                {
                    if (uitgaand.getSymbool() != EPSILON)
                    {
                        isAlleenEpsilon = false;
                        break;
                    }
                }

                // Check de uitgaande pijlen
                List<Pijl> uitgaandePijlen = toestand.geefUitgaandePijlen();
                for (int i = uitgaandePijlen.Count - 1; i >= 0; i--)
                {
                    Pijl uitgaand = uitgaandePijlen[i];
                    // Als deze pijl een epsilon is
                    if (uitgaand.getSymbool() == EPSILON)
                    {
                        
                        List<Pijl> inkomendePijlen = toestand.geefInkomendePijlen();


                        if (isAlleenEpsilon && uitgaandePijlen.Count == 1 && (toestand.getCategory() & Toestand.Category.Begin) != Toestand.Category.Begin)
                        {
                            // Vervang van alle inkomende pijlen de bestemming(toId) naar de bestemming van de pijl van de epsilon
                            for (int idx = inkomendePijlen.Count - 1; idx >= 0; idx--)
                            {
                                Pijl p = inkomendePijlen[idx];
                                // Update de inkomende pijl -> Verwijder en maak een nieuwe
                                Pijl nieuwePijl = new Pijl(p.getFromId(), uitgaand.getToId(), p.getSymbool());
                                voegPijlToe(nieuwePijl);

                                verwijderPijl(p);

                                
                            }
                            // Verwijder de epsilon pijl
                            verwijderPijl(uitgaand);
                        }
                        else
                        {
                            if ((toestand.getCategory() & Toestand.Category.Begin) == Toestand.Category.Begin)
                            {
                                // Vervang de uitgaande pijlen van de Toestand waar de epsilon pijl naar toe gaat
                                Toestand toToestand = getToestandVanId(uitgaand.getToId());
                                List<Pijl> uitgaande = toToestand.geefUitgaandePijlen();

                                bool isEnigeInkomende = toToestand.geefInkomendePijlen().Count == 1;

                                for(int idx = uitgaande.Count - 1; idx >= 0; idx--)
                                {
                                    Pijl p = uitgaande[idx];
                                    Pijl nieuwePijl = new Pijl(uitgaand.getFromId(), p.getToId(), p.getSymbool());
                                    voegPijlToe(nieuwePijl);

                                    if (isEnigeInkomende)
                                        verwijderPijl(p);
                                }
                            }
                            else
                            {
                                // Voeg extra inkomende pijlen toe, met als bestemming de bestemming(toId) van de pijl met de epsilon
                                foreach (Pijl p in inkomendePijlen)
                                {
                                    Pijl nieuwePijl = new Pijl(p.getFromId(), uitgaand.getToId(), p.getSymbool());
                                    voegPijlToe(nieuwePijl);
                                }
                            }
                            // Verwijder de epsilon pijl
                            verwijderPijl(uitgaand);
                        }
                    }
                }
            }
            // Lijst die weet dat id 7 de samengevoegde toestanden 3,4,5 zijn
            Dictionary<String, int> nieuweToestandIds = new Dictionary<String, int>();

            for (int i = 0; i < toestanden.Count; i++)
            {
                Toestand huidigeToestand = toestanden[i];

                // Check alle uitgaande pijlen, en sorteer ze op symbool
                // Char is het symbool, int is waar de pijl naar toe gaat
                Dictionary<char, List<int>> uitgaandePijlen = new Dictionary<char, List<int>>();

                foreach (Pijl p in huidigeToestand.geefUitgaandePijlen())
                {
                    char symbool = p.getSymbool();
                    int toId = p.getToId();

                    if (uitgaandePijlen.ContainsKey(symbool))
                    {
                        List<int> toIds = uitgaandePijlen[symbool];
                        // Voeg het id toe
                        toIds.Add(toId);

                        uitgaandePijlen.Remove(symbool);

                        // Sorteer de list
                        toIds = toIds.OrderBy(o => o).ToList();

                        // Voeg de lijst toe
                        uitgaandePijlen.Add(symbool, toIds);
                    }
                    else
                    {
                        // De lijst bestaat nog niet, maak de lijst
                        List<int> toIds = new List<int>();
                        // Voeg het id toe
                        toIds.Add(toId);
                        toIds = toIds.OrderBy(o => o).ToList();

                        // Voeg de lijst toe
                        uitgaandePijlen.Add(symbool, toIds);
                    }
                }
                // We hebben nu een Dictionary met per symbool een lijst met uitgaande pijlen
                IDictionaryEnumerator enumerator = uitgaandePijlen.GetEnumerator();
                enumerator.Reset();
                while (enumerator.MoveNext())
                {
                    char symbool = (char) enumerator.Key;
                    List<int> toIds = (List<int>) enumerator.Value;

                    if (toIds.Count == 1)
                    {
                        continue;
                    }

                    List<Pijl> alleUitgaandePijlen = new List<Pijl>();
                    bool isEindtoestand = false;

                    // Maak er een string van in de vorm: 0;1;5;
                    String idString = "";
                    foreach (int id in toIds)
                    {
                        // Maak de String
                        idString += Convert.ToString(id) + ";";

                        Toestand toestand = getToestandVanId(id);

                        // Controleer gelijk of het een eindtoestand is
                       if ((toestand.getCategory() & Toestand.Category.Eind) == Toestand.Category.Eind)
                                isEindtoestand = true;

                      
                        // Maak een lijst van de uitgaande pijlen

                        alleUitgaandePijlen.AddRange(toestand.geefUitgaandePijlen());

                    }

                    // De nieuwe toestand
                    Toestand nieuweToestand;
                    if (nieuweToestandIds.ContainsKey(idString))
                    {
                        // Deze 'samengestelde' toestand hebben we al, gebruik die
                        nieuweToestand = getToestandVanId(nieuweToestandIds[idString]);
                    }
                    else
                    {
                        // Deze samengestelde toestand hebben we nog niet, maak een nieuwe en voeg deze toe
                        if (isEindtoestand)
                            nieuweToestand = new Toestand(Toestand.Category.Eind);
                        else
                            nieuweToestand = new Toestand(Toestand.Category.Normaal);

                        // Voeg de nieuwe toestand toe, en onthoud de ids
                        voegToestandToe(nieuweToestand);
                        nieuweToestandIds.Add(idString, nieuweToestand.id);
                    }

                    foreach (Pijl uitgaandePijl in alleUitgaandePijlen)
                    {
                        Pijl nieuwePijl;

                        
                        nieuwePijl = new Pijl(nieuweToestand.id, uitgaandePijl.getToId(), uitgaandePijl.getSymbool());
                        
                        voegPijlToe(nieuwePijl);
                    }

                    // Verwijder de oude pijlen
                    List<Pijl> pijlen = huidigeToestand.geefUitgaandePijlen();
                    for (int idx = pijlen.Count - 1; idx >= 0; idx--)
                    {
                        // Verwijder alleen als het symbool gelijk is
                        if (pijlen[idx].getSymbool() == symbool)
                            verwijderPijl(pijlen[idx]);
                    }

                    // Maak een vervangende Pijl voor deze toestand
                    Pijl vergangendePijl = new Pijl(huidigeToestand.id, nieuweToestand.id, symbool);
                    voegPijlToe(vergangendePijl);

                }
                
                
                
            }

            bool isRemoved = false;
            do
            {
                isRemoved = false;

                for (int i = toestanden.Count - 1; i >= 0; i--)
                {
                    if (!toestanden[i].heeftInkomendePijlen(this) &&
                        (toestanden[i].getCategory() & Toestand.Category.Begin) != Toestand.Category.Begin)
                    {
                        // Toestand heeft geen inkomende pijlen en is geen begintoestand
                        toestanden.RemoveAt(i);
                        isRemoved = true;
                    }
                }
            } while (isRemoved);
        }

        private void verwijderPijl(Pijl oudePijl)
        {
            foreach (Toestand toestand in toestanden)
            {
                // Verwijder de oude pijl indien deze bestaat
                toestand.geefUitgaandePijlen().Remove(oudePijl);
                toestand.geefInkomendePijlen().Remove(oudePijl);
            }

        }
    }
}
