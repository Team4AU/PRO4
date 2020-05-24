/*
 * fsm.h
 *
 *  Created on: Apr 23, 2020
 *      Author: nikolaj
 */

#ifndef FSM_H_
#define FSM_H_

#include <iostream>
#include "Mqtt/mqttClient2.h"
#include "Testcase/Testcase.h"
#include "Jsonhandler/jsonHandler.h"

class fsm : public IMqttCallback {
public:
	fsm();
	virtual ~fsm();

    void onMessage(std::string message) override;
    void onSubscribe() override;
    void onConnect(int rc)override;
    void onDisconnect() override;
    void onPublish(int rc) override;

    void run();
private:
    jsonHandler Jsonhandler;
    mqttClient2 mqtt;

    void startTest();

    enum states{
    	connect,
		ready,
		busy,
		done
    };
    states nextState;
    bool connectedFlag;
    bool subFlag;
    bool messRecviedFlag;
    bool publishSucc;
    bool doneflag;
    int returncode;

    mqttPayload sucPayload;


};

#endif /* FSM_H_ */
