
#ifndef __SHCUSTOMPROTOCOL_H__
#define __SHCUSTOMPROTOCOL_H__
#include <Arduino.h>

class SHCustomProtocol {
  private:

  public:

    /*
      CUSTOM PROTOCOL CLASS
      SEE https://github.com/zegreatclan/SimHub/wiki/Custom-Arduino-hardware-support

      GENERAL RULES :
    	- ALWAYS BACKUP THIS FILE, reinstalling/updating SimHub would overwrite it with the default version.
    	- Read data AS FAST AS POSSIBLE in the read function
    	- NEVER block the arduino (using delay for instance)
    	- Make sure the data read in "read()" function READS ALL THE DATA from the serial port matching the custom protocol definition
    	- Idle function is called hundreds of times per second, never use it for slow code, arduino performances would fall
    	- If you use library suspending interrupts make sure to use it only in the "read" function when ALL data has been read from the serial port.
    		It is the only interrupt safe place

      COMMON FUNCTIONS :
    	- FlowSerialReadStringUntil('\n')
    		Read the incoming data up to the end (\n) won't be included
    	- FlowSerialReadStringUntil(';')
    		Read the incoming data up to the separator (;) separator won't be included
    	- FlowSerialDebugPrintLn(string)
    		Send a debug message to simhub which will display in the log panel and log file (only use it when debugging, it would slow down arduino in run conditions)

    */

      volatile int speed = 0;
      volatile int rpm = 0;
      volatile int coolant = 0;
      volatile int fuel = 0;
      volatile int abs = 0;
      volatile int ignition = 0;
      volatile int started = 0;
      volatile int handbrake = 0;
      volatile int TC = 0;
      volatile int turnLeft = 0;
      volatile int turnRight = 0;
      volatile int highBeam = 0;
    
    // Called when starting the arduino (setup method in main sketch)
    void setup() 
    {

    }

    // Called when new data is coming from computer
    void read() {

      // -------------------------------------------------------
      // EXAMPLE 2 - reads speed and gear from the message
      // Protocol formula must be set in simhub to
      // format([DataCorePlugin.GameData.NewData.SpeedKmh],'0') + ';' + isnull([DataCorePlugin.GameData.NewData.Gear],'N')
      // -------------------------------------------------------

      String line = FlowSerialReadStringUntil('b');

      int values[12];
  int index = 0;

  char buf[line.length() + 1];
  line.toCharArray(buf, sizeof(buf));

  char *token = strtok(buf, ";");
  while (token != NULL && index < 12) {
    values[index++] = atoi(token);
    token = strtok(NULL, ";");
  }

  if (index == 12) {
    speed      = values[0];
    rpm        = values[1];
    coolant    = values[2];
    fuel       = values[3];
    abs        = values[4];
    ignition   = values[5];
    started    = values[6];
    handbrake  = values[7];
    TC         = values[8];
    turnLeft   = values[9];
    turnRight  = values[10];
    highBeam   = values[11];
  }

  FlowSerialDebugPrintLn("sh: " + String(ignition));

    }

    // Called once per arduino loop, timing can't be predicted,
    // but it's called between each command sent to the arduino
    void loop() {
    }

    // Called once between each byte read on arduino,
    // THIS IS A CRITICAL PATH :
    // AVOID ANY TIME CONSUMING ROUTINES !!!
    // PREFER READ OR LOOP METHOS AS MUCH AS POSSIBLE
    // AVOID ANY INTERRUPTS DISABLE (serial data would be lost!!!)
    void idle() {
    }
};

#endif
