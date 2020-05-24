//
// Created by dani on 4/12/20.
//

#ifndef MQTT_MQTTCLIENT2_H
#define MQTT_MQTTCLIENT2_H

#include "mosquitto.h"
#include "IMqttCallback.h"
#include <thread>
#include "cstring"
#include <cstdio>
#include <functional>
#include "threadSafeQueue.h"

class mqttClient2 {
public:
    mqttClient2(const char * id, const char * host, int port, const char * subscribeTopic,
            const char * publishTopic, bool cleanSession);
    virtual ~mqttClient2();
    int subscribe();
    int publish(const char * message);
    void disconnect();
    void setCallback(IMqttCallback * _icallback);
    std::thread mqttThread();
private:
    static void _onMessage(struct mosquitto *mosq, void *obj,
                          const struct mosquitto_message *msg);
    static void _onSubscribe(struct mosquitto *mosq, void *obj, int mid,
                            int qos_count, const int *granted_qos);
    static void _onConnect(struct mosquitto *mosq, void *obj, int rc);
    static void _onDisconnect(struct mosquitto *mosq, void *obj, int rc);
    static void _onLog(struct mosquitto *mosq, void *obj,int rc, const char *msg);
    static void _onPublish(struct mosquitto *mosq, void *obj,int rc);
    struct mosquitto *m_mosq;
    const char * subscribeTopic;
    const char * publishTopic;
    const char * id;
    const char * host;
    int port;
    int rc;
    bool cleanSession;
    bool run = true;
    const int keepAlive = 60;
    const int reconnectTime = 1000;
    IMqttCallback * _icallback;
    void worker();
    threadSafeQueue<std::string> msgQueue;
};


#endif //MQTT_MQTTCLIENT2_H
