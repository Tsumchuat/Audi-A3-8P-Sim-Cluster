# Audi-A3-8P-Sim-Cluster
A tool to use an Audi A3 8P guage cluster with simhub for simracing games

This uses an arduino leonardo, canbus hat, and the original cluster was modified in order to externally control some of the warning lights.

Simhub is required to use this, just create a new custom aruduino sketch and copy this customprotocol.h and displayclientV2 into yours.

Enter this in custom protocol within the simhub app for your arduino: 
format([DataCorePlugin.GameData.NewData.SpeedKmh],'0') + ';' + format([DataCorePlugin.GameData.NewData.Rpms],'0') + ';' + format([DataCorePlugin.GameData.NewData.WaterTemperature],'0') + ';' + format([DataCorePlugin.GameData.NewData.FuelPercent],'0') + ';' + format([DataCorePlugin.GameData.NewData.ABSActive],'0') + ';' + format([DataCorePlugin.GameData.NewData.EngineIgnitionOn],'0') + ';' +  format([DataCorePlugin.GameData.NewData.EngineStarted],'0') + ';' + format([DataCorePlugin.GameData.NewData.Handbrake],'0') + ';' + format([DataCorePlugin.GameData.NewData.TCActive],'0') + ';' + format([DataCorePlugin.GameData.NewData.TurnIndicatorLeft],'0') + ';' + format([DataCorePlugin.GameData.NewData.TurnIndicatorRight],'0') + ';' + format(isnull([DataCorePlugin.GameRawData.light_HighBeam], 0), '0') + 'b'
