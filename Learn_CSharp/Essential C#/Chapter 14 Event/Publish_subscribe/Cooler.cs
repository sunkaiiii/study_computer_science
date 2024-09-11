using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Publish_subscribe
{
    class Cooler
    {
        private float Temperature { get; set; }
        public Cooler(float temperature)
        {
            Temperature = temperature;
        }

        public void OntemperatureChanged(float temperature)
        {
            if (temperature > Temperature)
            {
                Console.WriteLine("Cooler: On");
            }
            else
            {
                Console.WriteLine("Cooler: Off");
            }
        }
    }
}
