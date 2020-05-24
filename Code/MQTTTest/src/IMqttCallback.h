//
// Created by dani on 4/13/20.
//

#ifndef MQTT_IMQTTCALLBACK_H
#define MQTT_IMQTTCALLBACK_H

#include <string>

/**
 * Callback interface following OOP observer pattern
 */
class IMqttCallback {
public:
	virtual ~IMqttCallback(){};
    virtual void onMessage(std::string message) = 0;
    virtual void onSubscribe() = 0;
    virtual void onConnect(int rc) = 0;
    virtual void onDisconnect() = 0;
    virtual void onPublish(int rc) = 0;
};


#endif //MQTT_IMQTTCALLBACK_H
