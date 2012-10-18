/*
 
 ArdOSC 2.1 - OSC Library for Arduino.
 
 -------- Lisence -----------------------------------------------------------
 
 ArdOSC
 
 The MIT License
 
 Copyright (c) 2009 - 2011 recotana( http://recotana.com )　All right reserved
 
 */

#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include "OSCCommon/OSCServer.h"
#include "OSCCommon/OSCcommon.h"
#include "OSCCommon/OSCMessage.h"

#include "OSCCommon/Pattern.h"


Pattern::Pattern(){
    patternNum=0;
}

Pattern::~Pattern(){
}

void Pattern::addOscAddress(char *_adr ,  AdrFunc _func){
    adrFunc[patternNum] = _func;
    addr[patternNum] = _adr;
    patternNum++;
}

void Pattern::execFunc(uint8_t _index,OSCMessage *_mes){
    adrFunc[_index](_mes);
}

void Pattern::paternComp(OSCMessage *_mes){
    for (uint8_t i=0 ; i<patternNum ; i++) {
		String str_addr = String(addr[i]);
		if(str_addr.endsWith("^")) {
			String to_match = str_addr.substring(0, str_addr.length() - 1);
			if(String(_mes->_oscAddress).startsWith(to_match)){
				_mes->parseAddressArgs(addr[i]);					
				execFunc(i, _mes);  
			} 
		}
        else if ( strcmp( addr[i] , _mes->_oscAddress ) == 0 ) execFunc( i , _mes );
	}
}