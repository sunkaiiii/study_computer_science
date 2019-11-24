using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace CP6
{
    class IterationSampleIterator : IEnumerator
    {
        InterationSample parent;
        int position;

        internal IterationSampleIterator(InterationSample parent)
        {
            this.parent = parent;
            position = -1;
        }

        public bool MoveNext()
        {
            if(position!=parent.values.Length)
            {
                position++;
            }
            return position < parent.values.Length;
        }

        public object Current
        {
            get
            {
                if(position ==-1||position==parent.values.Length)
                {
                    throw new InvalidOperationException();
                }
                int index = position + parent.startingPoint;
                index = index % parent.values.Length;
                return parent.values;
            }
        }

        public void Reset()
        {
            position = -1;
        }
    }
}
