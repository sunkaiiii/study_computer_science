﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CP12
{
    public class Defect
    {
        int count=1;
        public Project Project { get; set; }
        /// <summary>
        /// Which user is this defect currently assigned to? Should not be null until the status is Closed.
        /// </summary>
        public User AssignedTo { get; set; }
        public string Summary { get; set; }
        public Severity Severity { get; set; }
        public Status Status { get; set; }
        public DateTime Created { get; set; }
        public DateTime LastModified { get; set; }
        public User CreatedBy { get; set; }
        public int ID { get; set; }

        public Defect()
        {
            ID = StaticCounter.Next();
        }

        public override string ToString()
        {
            return string.Format("{0,2}: {1}\r\n    ({2:d}-{3:d}, {4}/{5}, {6} -> {7})",
                ID, Summary, Created, LastModified, Severity, Status, CreatedBy.Name,
                AssignedTo == null ? "n/a" : AssignedTo.Name);
        }
    }
}
