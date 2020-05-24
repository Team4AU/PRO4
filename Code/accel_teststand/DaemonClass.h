////////////////////////////////////////////////////////////
//
// Source file	: DaemonClass.h
// Author				: Nikolaj
// Date 				: 27 Jan 2020
// Version 			:
//
// Description :
//
////////////////////////////////////////////////////////////
#ifndef DAEMONCLASS_H_
#define DAEMONCLASS_H_

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

using namespace std;

class DaemonClass
{
	private:
		FILE *fp= NULL;
		pid_t process_id = 0;
		pid_t sid = 0;

	public:
		DaemonClass ( );
		virtual ~DaemonClass ( );
		int createdaemon();
};

#endif /* DAEMONCLASS_H_ */
