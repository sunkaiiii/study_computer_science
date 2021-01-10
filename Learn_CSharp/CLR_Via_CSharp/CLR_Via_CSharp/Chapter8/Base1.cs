using System;
using System.Collections.Generic;
using System.Text;

namespace Chapter8
{
    internal sealed partial class Base
    {
        private string m_name;

        partial void OnNameChanging(string value);// 分部方法

        public string Name
        {
            get { return m_name; }
            set
            {
                OnNameChanging(value.ToUpper());
                m_name = value;
            }
        }
    }
}
