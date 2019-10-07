using System;
using System.Collections.Generic;
using System.Text;

namespace CP12
{
    public partial class Project
    {
        public string Name { get; set; }
        public int ProjectID { get; set; }
        public override string ToString()
        {
            return string.Format("Project: {0}", Name);
        }
    }
}
