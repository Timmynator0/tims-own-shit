using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FMApplicatie
{
    class Pijl
    {
        private int fromId;
        private int toId;

        private char symbool;

        public Pijl(int fromId, int toId, char symbool)
        {
            this.fromId = fromId;
            this.toId = toId;
            this.symbool = symbool;
        }

        public int getFromId()
        {
            return fromId;
        }
        public int getToId()
        {
            return toId;
        }

        public char getSymbool()
        {
            return symbool;
        }

        public void reverse()
        {
            int to = toId;

            toId = fromId;
            fromId = to;
        }

        public override bool Equals(System.Object o)
        {
            
            if(o.GetType().IsAssignableFrom(this.GetType())) {
                Pijl anderePijl = (Pijl) o;
            
                return anderePijl.toId == this.toId &&
                    anderePijl.fromId == this.fromId &&
                    anderePijl.symbool == this.symbool;
            }

            return false;
        }

        internal void setFromId(int id)
        {
            this.fromId = id;
        }

        internal void setToId(int id)
        {
            this.toId = id;
        }

        internal void setSymbool(char symbool)
        {
            this.symbool = symbool;
        }
    }
}
