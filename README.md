
# Important Note
Arduino v1.0.1 (and maybe newer) have a malloc/free bug!

Check:
* http://code.google.com/p/arduino/issues/detail?id=468
* http://code.google.com/p/arduino/issues/detail?id=857

## Howto fix this issue:
* go to  issue #468 
* download malloc.c
* copy malloc.c to arduino-1.0.1/hardware/arduino/cores/arduino

Restart the Arduino IDE!



#Library
For Arduino v1.0.1

tested Arduino Ethernet
http://www.arduino.cc/en/Main/ArduinoBoardEthernet

Installation
ArdOSC folder into ..

**Mac**

~/Documents/Arduino/libraries/

**Win**

MyDocuments\Arduino\libraries\

http://www.arduino.cc/en/Hacking/Libraries


#Release History
ArdOSC 2.1  - OSC Library for Arduino.
 
    This library works with arduino v1.0.1
    2011/09/19 version 2.1 added callback function
                           added osc message argument function
    2010/02/01 version 2.0 changed Project OSCClass -> ArdOSC
    2009/03/22 version 1.0.1 add errror process。change Doc.
    2009/03/21 version 1.0.0
 
 
