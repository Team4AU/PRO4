////////////////////////////////////////////////////////////
//
// Source file	: DaemonClass.cpp
// Author				: Nikolaj
// Date 				: 27 Jan 2020
// Version 			:
//
// Description :
//
////////////////////////////////////////////////////////////
#include "DaemonClass.h"

using namespace std;

DaemonClass::DaemonClass ( )
{
	// TODO Auto-generated constructor stub

}

DaemonClass::~DaemonClass ( )
{
	// TODO Auto-generated destructor stub
	fclose (fp);
}

int DaemonClass::createdaemon ( )
{
	// Create child process
	process_id = fork ();
	// Indication of fork() failure
	if (process_id < 0)
	{
		printf ("fork failed!\n");
		// Return failure in exit status
		exit (1);
	}
	// PARENT PROCESS. Need to kill it.
	if (process_id > 0)
	{
		printf ("process_id of child process %d \n", process_id);
		// return success in exit status
		exit (0);
	}
	//unmask the file mode
	umask (0);
	//set new session
	sid = setsid ();
	if (sid < 0)
	{
		// Return failure
		exit (1);
	}
	// Change the current working directory to root.
	chdir ("/");
	// Close stdin. stdout and stderr
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	close (STDERR_FILENO);
	// Open a log file in write mode.
	// Open a log file in write mode.
	fp = fopen ("Log.txt", "w+");
//	while (1)
//	{
		//Dont block context switches, let the process sleep for some time
		sleep (1);
		fprintf (fp, "daemon created...\n");
		fflush (fp);
		// Implement and call some function that does core work for this daemon.
//	}
	return (0);
}
