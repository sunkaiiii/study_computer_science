using System;
using System.Collections.Generic;

namespace CP1
{
    public class Supplier
    {
        public string Name { get; set; }
        public int SupplierID { get; set; }
        public Supplier(string name,int supplierid)
        {
            this.Name = name;
            this.SupplierID = supplierid;
        }

        public static List<Supplier> GetSampleSuppliers()
        {
            List<Supplier> list = new List<Supplier>
            {
                new Supplier("1",1),
                new Supplier("2",2),
                new Supplier("3",3),
            };
            return list;
        }
    }
}
