////////////////////////////////////////////////////////////
//
// Source file	: main.cpp
// Author				: Nikolaj
// Date 				: 9 Apr 2020
// Version 				: 1.0
//
// Description : a fsm that controls the accelerometer teststand
//
////////////////////////////////////////////////////////////




#include <iostream>
#include "fsm.h"
#include "DaemonClass.h"

using namespace std;


int main(int argc, char **argv) {
	//dæmon this
	DaemonClass Daemon;
	Daemon.createdaemon();

	fsm fsm;
	fsm.run();

	return 0;

}


