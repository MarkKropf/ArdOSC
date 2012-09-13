/*
 
 ArdOSC 2.1 - OSC Library for Arduino.
 
 -------- Lisence -----------------------------------------------------------
 
 ArdOSC
 
 The MIT License
 
 Copyright (c) 2009 - 2011 recotana( http://recotana.com )　All right reserved
 
 */



#include <stdlib.h>

#include "OSCCommon/OSCClient.h"

#include <utility/socket.h>
#include <utility/w5100.h>


OSCClient::OSCClient(void){
    _sock = MAX_SOCK_NUM;   
}

OSCClient::~OSCClient(void){
    flushSendData();
}


int16_t OSCClient::sockOpen(void){

    //already open?
    if ( _sock != MAX_SOCK_NUM ) return -1;
    
    for ( int i = 0 ; i < MAX_SOCK_NUM ; i++ ) {
        uint8_t s = W5100.readSnSR(i);
        if ( s == SnSR::CLOSED || s == SnSR::FIN_WAIT ) {
            _sock = i;
            break;
        }
    }
    
    if ( _sock == MAX_SOCK_NUM ) return -1;
    
	socket( _sock, SnMR::UDP , kDummyPortNumber , 0 );

    return 1;
}

void OSCClient::sockClose(void){
    //init value, nothing to do
    if ( _sock == MAX_SOCK_NUM ) return;
    
    close(_sock);
    
    _sock = MAX_SOCK_NUM;

}


 
int16_t OSCClient::send(OSCMessage *_message){
	
    uint16_t result=0;    
    flushSendData();
    
	_sendData = (uint8_t*)calloc(_message->getMessageSize(), 1);
    if (_sendData == NULL) {        
        return -4;
    }   
    
	if (encoder.encode(_message , _sendData ) < 0 ){
		flushSendData();
		return -3;
	}    
    
    if (sockOpen()<0 ) {
        flushSendData();
        return -2; //socket open check
    }

    result = sendto(_sock , _sendData, _message->getMessageSize(), _message->getIpAddress(), _message->getPortNumber() );
 
	sockClose();    
    flushSendData();

    if (result!=_message->getMessageSize()) {
        return -5;
    }

	return result;
/*
    uint16_t result=0;
    flushSendData();
    
    if (preparePacketData(_message, _sendData)<0) {
        flushSendData();
        return -1;        
    }

    result = sendPacketData(_message, _sendData);
    if (result < 0) {
        flushSendData();
        return -1;        
    }

    return result;*/
}

/*
int16_t OSCClient::preparePacketData(OSCMessage *_message, uint8_t *packetData) {
    packetData = (uint8_t*) calloc(_message->getMessageSize(), 1);
    if (packetData == NULL) {
        return -2;
    }
    if (encoder.encode(_message , packetData ) < 0 ) {        
        return -1;
    }

    return _message->getMessageSize();
}



int16_t OSCClient::sendPacketData(OSCMessage *_message, uint8_t *packetData) {
    uint16_t result=0;

    if (sockOpen()<0) return -1; //socket open check

    result = sendto( _sock , packetData , _message->getMessageSize() , _message->getIpAddress(), _message->getPortNumber() );
 
    sockClose();
    
    return result;
}*/


void OSCClient::flushSendData(void){
    
	free(_sendData);
	_sendData=0;
    
}



