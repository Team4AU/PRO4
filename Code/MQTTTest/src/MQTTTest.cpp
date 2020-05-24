//============================================================================
// Name        : MQTTTest.cpp
// Author      : dani
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "callbackExample.h"
using namespace std;

int main() {
	cout << "MQTTTest" << endl; // prints server
	cout << "RUNNING TEST 3.2.1" << endl; // prints server
	callbackExample exp;
	exp.runTest();
	return 0;
}
