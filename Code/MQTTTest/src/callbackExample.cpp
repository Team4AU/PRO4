//
// Created by dani on 4/13/20.
//

#include "callbackExample.h"
#include "mqttClient2.h"
#include <thread>
#include <iostream>

void callbackExample::onMessage(std::string message) {
    std::cout << "Message: "<< message << std::endl;
}

void callbackExample::onSubscribe() {
    std::cout << "subscribed" << std::endl;
}

void callbackExample::onConnect(int rc) {
    std::cout << "connect status: " << rc << std::endl;
}

void callbackExample::onDisconnect() {
    std::cout << "disconnected" << std::endl;
}

void callbackExample::onPublish(int rc) {
    std::cout << "publish status: " << rc << std::endl;
}

void callbackExample::runTest() {
    mqttClient2 client2(NULL,"localhost",1883,
            "test","test",true);
    client2.setCallback(this);
    //start it
    std::thread mqttThread = client2.mqttThread();
    //we use a thread safe queue to handle messages..
    client2.publish("Subscribe - Publish Test");
    while(1){
        //keep on working.

    }
    //kills mqtt thread.
    client2.disconnect();
}


