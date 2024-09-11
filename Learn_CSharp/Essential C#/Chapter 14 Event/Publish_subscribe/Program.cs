using Publish_subscribe;

Thermostat thermostat = new();
Heater heater = new(60);
Cooler cooler = new(80);

thermostat.OnTemperatureChange += heater.OntemperatureChanged;
thermostat.OnTemperatureChange += cooler.OntemperatureChanged;

thermostat.CurrentTemperature = 40;
thermostat.CurrentTemperature = 80;