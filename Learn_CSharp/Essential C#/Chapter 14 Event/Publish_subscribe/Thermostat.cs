using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Publish_subscribe
{
    class Thermostat
    {
        //Define the event publisher
        public Action<float>? OnTemperatureChange { get; set; }
        public float CurrentTemperature
        {
            get { return _currentTemperature; }
            set
            {
                if (value != _currentTemperature)
                {
                    _currentTemperature = value;
                    if (OnTemperatureChange != null)
                    {
                        List<Exception> exceptions = new List<Exception>();
                        foreach (Action<float> handler in OnTemperatureChange.GetInvocationList())
                        {
                            try
                            {
                                handler(value);
                            }
                            catch (Exception ex)
                            {
                                exceptions.Add(ex);
                            }
                        }
                        if (exceptions.Count > 0)
                        {
                            throw new AggregateException("There were exceptions thown by OnTemperatureChange Event subscribers.", exceptions);
                        }
                    }
                }
            }
        }

        private float _currentTemperature;
    }
}
