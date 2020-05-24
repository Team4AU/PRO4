//============================================================================
// Name        : JSONTest.cpp
// Author      : dani
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Jsonhandler/jsonHandler.h"
using namespace std;

void runTest1();
void runTest2();
void runTest3();
void runTest4();
void runTest5();
void runTest6();

int main(int arg, char **args) {
	cout << "JSONTest" << endl; //
	if(arg >1){
		int selc = std::stoi(args[1]);
		switch (selc) {
			case 1:
				runTest3();
				break;
			case 2:
				runTest2();
				break;
			case 3:
				runTest1();
				break;
			case 4:
				runTest4();
				break;
			case 5:
				runTest5();
				break;
			case 6:
				runTest6();
				break;
			default:
				break;
		}
	}else {
		cout << "Wrong number of arguments" << endl; //
	}

	return 0;
}

void runTest1() {
	cout << "RUNNING TEST 3.2.1.2.3" << endl; //
	mqttPayload payload;
	payload.setHasTestConfig(true);
	payload.setMsgType("data");
	payload.setProtocolVersion(1.1f);
	payload.setSentBy("dani");
	payload.setStatusCode("200");

	testConfig conf;
	conf.setSensorID(1);
	conf.setSensorType(2);
	conf.setStartFrequency(100);
	conf.setStopFrequency(200);
	conf.setStepFrequency(10);
	conf.setStepTimeMs(500);

	payload.setTestConfig(conf);

	dataPoint p1(14.55f, 755.30f, 156.00f);
	dataPoint p2(1400.37f, 55.90f, 900.00f);
	dataPoint p3(78.57f, 1300.60f, 286.10f);

	payload.addDataPoint(p1);
	payload.addDataPoint(p2);
	payload.addDataPoint(p3);

	jsonHandler handler;

	std::string json = handler.payloadJsonMsg(payload);
	cout << json << endl; //
	cout << "TEST FINISHED" << endl; //
}

void runTest2() {
	cout << "RUNNING TEST 3.2.1.2.2" << endl; //
	mqttPayload payload;
	payload.setHasTestConfig(true);
	payload.setMsgType("data");
	payload.setProtocolVersion(1.1f);
	payload.setSentBy("dani");
	payload.setStatusCode("200");

	testConfig conf;
	conf.setSensorID(1);
	conf.setSensorType(2);
	conf.setStartFrequency(100);
	conf.setStopFrequency(200);
	conf.setStepFrequency(10);
	conf.setStepTimeMs(500);

	payload.setTestConfig(conf);

	dataPoint p1(14.55f, 755.30f, 156.00f);
	dataPoint p2(1400.37f, 55.90f, 900.00f);
	dataPoint p3(78.57f, 1300.60f, 286.10f);

	payload.addDataPoint(p1);
	payload.addDataPoint(p2);
	payload.addDataPoint(p3);

	jsonHandler handler;

	std::string json = handler.payloadJsonMsg(payload);
	cout << json << endl; //
	cout << "TEST FINISHED" << endl; //
}

void runTest3() {
	cout << "RUNNING TEST 3.2.1.2.1" << endl; //
	mqttPayload payload;
	payload.setHasTestConfig(false);
	payload.setMsgType("status");
	payload.setProtocolVersion(1.1f);
	payload.setSentBy("dani");
	payload.setStatusCode("202");
	/*
	 testConfig conf;
	 conf.setSensorID(1);
	 conf.setSensorType(2);
	 conf.setStartFrequency(100);
	 conf.setStopFrequency(200);
	 conf.setStepFrequency(10);
	 conf.setStepTimeMs(500);

	 payload.setTestConfig(conf);

	 dataPoint p1(14.55f,755.30f,156.00f);
	 dataPoint p2(1400.37f,55.90f,900.00f);
	 dataPoint p3(78.57f,1300.60f,286.10f);

	 payload.addDataPoint(p1);
	 payload.addDataPoint(p2);
	 payload.addDataPoint(p3);
	 */
	jsonHandler handler;

	std::string json = handler.payloadJsonMsg(payload);
	cout << json << endl; //
	cout << "TEST FINISHED" << endl;
}

void runTest4() {
	cout << "RUNNING TEST 3.2.1.3.1" << endl; //


	std::string jsonOk =
			R"({
"protocolVersion":1.1,
"sentBy":"dani",
"msgType":"status",
"commandList":["status"],
"statusCode":"200",
"parameterObj":{},
"dataObj":{}
})";

std::string jsonBad =
		R"({
"protocolVersion":1.1,
"sentBy":"dani",
"msgType":status,
"commandList":[],
"statusCode":"200",
"parameterObj":{},
"dataObj":{}
})";

	jsonHandler handler;
	try {
		handler.toMqttMessage(jsonOk);
		cout << "CONVERT OK" << ": Success" << endl;

	} catch (jsonValidationException &e) {
		cout << "TEST FAILED" << endl;
	}

	try {
		handler.toMqttMessage(jsonBad);
		cout << "TEST FAILED" << endl;

	} catch (jsonValidationException &e) {
		cout << e.getErrorNumber() << ": " << e.what() << endl;
		cout << "JSON-string not OK" << ": Success" << endl;
	}
	cout << "TEST FINISHED" << endl;

}

void runTest5() {
	cout << "RUNNING TEST 3.2.1.3.2" << endl; //
	std::string jsonOk =
			R"({
"protocolVersion":1.1,
"sentBy":"dani",
"msgType":"command",
"commandList":["run"],
"statusCode":"200",
"parameterObj":{
"sensorID":1,
"sensorType":2,
"startFrequency":100,
"stopFrequency":200,
"stepFrequency":10,
"stepTime":500},
"dataObj":{}
})";

	std::string jsonBad =
			R"({
"protocolVersion":1.1,
"sentBy":"dani",
"commandList":["run"],
"statusCode":"200",
"parameterObj":{
"sensorID":1,
"sensorType":2,
"startFrequency":"100",
"stopFrequency":200,
"stepFrequency":10,
"stepTime":"500"},
"dataObj":{}
})";

	jsonHandler handler;
	try {
		handler.toMqttMessage(jsonOk);
		cout << "CONVERT OK" << ": Success" << endl;

	} catch (jsonValidationException &e) {
		cout << "TEST FAILED" << endl;
	}

	try {
		handler.toMqttMessage(jsonBad);
		cout << "TEST FAILED" << endl;

	} catch (jsonValidationException &e) {
		cout << e.getErrorNumber() << ": " << e.what() << endl;
		cout << "JSON-string not OK" << ": Success" << endl;
	}
	cout << "TEST FINISHED" << endl;
}

void runTest6() {
	cout << "RUNNING TEST 3.2.1.3.3" << endl; //
	std::string jsonOk =
			R"({
"protocolVersion":1.1,
"sentBy":"dani",
"msgType":"command",
"commandList":["run"],
"statusCode":"200",
"parameterObj":{
"sensorID":1,
"sensorType":2,
"startFrequency":100,
"stopFrequency":200,
"stepFrequency":10,
"stepTime":500},
"dataObj":{}
})";

	std::string jsonBad =
			R"({
"protocolVersion":1.1,
"sentBy":"dani",
"commandList":["run"],
"statusCode":"200",
"parameterObj":{
"sensorType":2,
"startFrequency":100,
"stopFrequency":200,
"stepFrequency":10,
"stepTime":500},
"dataObj":{}
})";

	jsonHandler handler;
	try {
		handler.toMqttMessage(jsonOk);
		cout << "CONVERT OK" << ": Success" << endl;

	} catch (jsonValidationException &e) {
		cout << "TEST FAILED" << endl;
	}

	try {
		handler.toMqttMessage(jsonBad);
		cout << "TEST FAILED" << endl;

	} catch (jsonValidationException &e) {
		cout << e.getErrorNumber() << ": " << e.what() << endl;
		cout << "JSON-string not OK" << ": Success" << endl;
	}
	cout << "TEST FINISHED" << endl;
}
