//
// Created by dani on 4/13/20.
//

#include "../Mqtt/callbackExample.h"

#include <thread>
#include <iostream>
#include "../Mqtt/mqttClient2.h"

/**
 *
 * @param message
 */
void callbackExample::onMessage(std::string message) {
    std::cout << message << std::endl;
}

/**
 *
 */
void callbackExample::onSubscribe() {
    std::cout << "subscribed" << std::endl;
}

/**
 *
 * @param rc
 */
void callbackExample::onConnect(int rc) {
    std::cout << "connect status: " << rc << std::endl;
}

/**
 *
 */
void callbackExample::onDisconnect() {
    std::cout << "disconnected" << std::endl;
}

/**
 *
 * @param rc
 */
void callbackExample::onPublish(int rc) {
    std::cout << "publish status: " << rc << std::endl;
}

/**
 *
 */
void callbackExample::startup() {
    mqttClient2 client2(NULL,"localhost",1883,
            "test/#","test",true);
    client2.setCallback(this);
    //start it
    std::thread mqttThread = client2.mqttThread();
    //we use a thread safe queue to handle messages..
    client2.publish("IT MIGHT ACTUALLY WORK");
    while(1){
        //keep on working.

    }
    //kills mqtt thread.
    client2.disconnect();
}


