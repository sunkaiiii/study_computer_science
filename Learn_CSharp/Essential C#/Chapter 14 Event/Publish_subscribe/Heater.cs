using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Publish_subscribe
{
    class Heater
    {
        private float Temperature { get; set; }
        public Heater(float temperature)
        {
            Temperature = temperature;
        }

        public void OntemperatureChanged(float temperature)
        {
            if (temperature < Temperature)
            {
                Console.WriteLine("Heater: On");
            }
            else
            {
                Console.WriteLine("Heater: Off");
            }
        }
    }
}
