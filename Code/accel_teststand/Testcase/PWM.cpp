/*
 * PWM.cpp
 *
 *  Created on: 22 Nov 2019
 *      Author: Rikke
 */

#include "PWM.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fstream>

using namespace std;

/**
 * @brief This constructors sets up device for pwm
 * @param unit The selected type of device
 */
PWM::PWM (const char* unit)
{
	this->device = PB;

	if (strcasecmp (unit, "pb") == 0)
	{
		device = PB;
	}
	else if (strcasecmp (unit, "bbb") == 0)
	{
		device = BBB;
	}
	else
	{
		cout << "Error (Wrong type of device)" << endl;
	}

}

/**
 * @brief Default constructor, sets PB as device
 */
PWM::PWM ( )
{
	//Default pin is set to pocketbeagle
	this->device = PB;
	// TODO Auto-generated constructor stub

}

/**
 * @brief Destructor
 */
PWM::~PWM ( )
{
	// TODO Auto-generated destructor stub
}

/**
 * @brief Initialise pins for the selected device
 * @return status of operation
 */
bool PWM::init ( )
{
	if (device == PB)
	{
		//set predefined pin in pwm mode
		system (PWM_SETUP_PB);
		cout << "PocketBeagle: ";
	}
	else if (device == BBB)
	{
		//set predefined pin in pwm mode
		system (PWM_SETUP_BBB);
		ofstream myfile;
		//set export to 3
		if (myfile.is_open ())
		{
			myfile << '3';
			cout << "Exported" << endl;
			myfile.close ();
		}
		cout << "BeagleBoneBlack: ";
	}
	else //ERROR device not set
	{
		cout << "Error (PWM init)" << endl;
		return false;
	}
	return true;
}

/**
 * @brief Enables PWM by setting enable high on the selected device
 * @return status of operation
 */
bool PWM::startPWM ( )
{
	ofstream myfile;

	//open enable file for the correct device
	if (device == PB) //check for PB
	{
		myfile.open (PWM_ENABLE_PB, ios::out);
	}
	else if (device == BBB) //check for BBB
	{
		myfile.open (PWM_ENABLE_BBB, ios::out);
	}
	else //ERROR device not set
	{
		cout << "Error (PWM start)" << endl;
		return false;
	}

	//set enable to 1
	if (myfile.is_open ())
	{
		myfile << '1';
		cout << "PWM enabled" << endl;
		myfile.close ();
	}
	else //ERROR file not open
	{
		cout << "Error (PWM enable)" << endl;
		return false;
	}
	return true;
}

/**
 * @brief Disables PWM by setting enable low on the selected device
 * @return status of operation
 */
bool PWM::stopPWM ( )
{
	ofstream myfile;

	//open enable file for the correct device
	if (device == PB) //check for PB
	{
		myfile.open (PWM_ENABLE_PB, ios::out);
	}
	else if (device == BBB) //check for BBB
	{
		myfile.open (PWM_ENABLE_BBB, ios::out);
	}
	else //ERROR device not set
	{
		cout << "Error (PWMstop)" << endl;
		return false;
	}

	//set enable to 0
	if (myfile.is_open ())
	{
		myfile << '0';
		cout << "PWM disabled" << endl;
		myfile.close ();
	}
	else //ERROR file not open
	{
		cout << "Error (PWM disable)" << endl;
		return false;
	}
	return true;
}

/**
 * @brief Toggles enable on and off
 * @return The status of enable, 1 if high, 0 if low
 */
unsigned int PWM::toggleEnable ( )
{
	int mode = count % 2;
	if (mode == 1)
	{
		startPWM ();
	}
	else
		stopPWM ();
	count++;
	return mode;
}

/**
 * @brief Changes the frequency and duty cycle of PWM
 * @param freq The wanted frequency for PWM
 * @param duty The wanted duty cycle for PWM
 * @return status of operation
 */
bool PWM::setup (unsigned int freq, unsigned int duty)
{
	//calculate period and duty cycle and make it into strings
	unsigned long period = (1 / double (freq)) * NANOSECONDS;
	unsigned long dutyCycle = period * (double (duty) / 100.00);
	string setDuty = "100";
	string stringPeriod = to_string (period);
	string stringDutyCycle = to_string (dutyCycle);

	//output files
	ofstream myfileDuty;
	ofstream myfilePeriod;

	//open the correct duty cycle file
	if (device == PB)
	{
		myfileDuty.open (PWM_DUTY_PB, ios::out);
	}
	else if (device == BBB)
	{
		myfileDuty.open (PWM_DUTY_BBB, ios::out);
	}
	else
	{
		cout << "Error (open duty cycle file)" << endl;
		return false;
	}
	//write new value and close file
	if (myfileDuty.is_open ())
	{
		myfileDuty << setDuty;
		myfileDuty.close ();
	}
	else
	{
		cout << "Error (Set low duty)" << endl;
		return false;
	}

	//open the correct period file
	if (device == PB)
	{
		myfilePeriod.open (PWM_PERIOD_PB, ios::out);
	}
	else if (device == BBB)
	{
		myfilePeriod.open (PWM_PERIOD_BBB, ios::out);
	}
	else
	{
		return false;
	}
	//write new value and close file
	if (myfilePeriod.is_open ())
	{
		myfilePeriod << stringPeriod;
		myfilePeriod.close ();
	}
	else
	{
		cout << "Error (Set freq)" << endl;
		return false;
	}

	//open the correct duty cycle file
	if (device == PB)
	{
		myfileDuty.open (PWM_DUTY_PB, ios::out);
	}
	else if (device == BBB)
	{
		myfileDuty.open (PWM_DUTY_BBB, ios::out);
	}
	else
	{
		return false;
	}
	//write new value and close file
	if (myfileDuty.is_open ())
	{
		myfileDuty << stringDutyCycle;
		myfileDuty.close ();
	}
	else
	{
		cout << "Error (Set real duty)" << endl;
		return false;
	}

	//print new PWM values
	cout << "Freq: " << freq << " Hz" << endl << "Duty cycle: " << duty << "%"
	    << endl;
	return true;
}

/**
 * @brief Runs a sweep with selected parameters, stops if last step goes past stop frequency
 * @param start Start frequency for sweep
 * @param stop Stop frequency for sweep
 * @param step The increase in frequency per step
 * @return status of operation
 */
bool PWM::runSweep (unsigned int start, unsigned int stop, unsigned int step)
{
	//calculate the amount of steps before reaching the stop frequency
	int steps = (stop - start) / step;
	//make sure the pwm starts at the start frequency
	if (setup (start, 50))
	{

	}
	else
	{
		return false;
	}
	//enable PWM
	startPWM ();
	//run through the step from start to stop frequency
	for (int i = 0; i < steps + 1; i++)
	{
		setup (start, 50);
		usleep (1 * MICROSECONDS);
		start = start + step;
	}
	return true;
}

/**
 * @brief Menu for testing pwm and testing system-to-be, also kwown as testmode
 */
void PWM::testMenu ( )
{
	cout << "Test mode activated - ctrl+c to quit" << endl;
	cout << "f: change frequency" << endl << "d: change duty cycle" << endl;
	cout << "t: toggle PWM on and off" << endl << "s: set up sweep" << endl
	    << "i: information" << endl << "ctrl+c to quit" << endl;
	char choice;
	unsigned int stop, start, step;
	//menu for the test mode
	while (scanf ("%c", &choice))
	{
		switch (choice)
		{
			case 'f':
				cout << "Enter a new frequency (100 - 10.000)" << endl;
				while (scanf ("%d", &freq))
				{
					if (MINFREQ < freq && freq < MAXFREQ)
					{
						setup (freq, dutyCycle);
					}
					else
					{
						cout << "enter a value between 100Hz and 10kHz" << endl;
					}
				}
				break;
			case 'd':
				cout << "Enter a new duty cycle (1 - 100)" << endl;
				while (scanf ("%d", &dutyCycle))
				{
					if (MINDUTYCYCLE < dutyCycle && dutyCycle < MAXDUTYCYCLE)
					{
						setup (freq, dutyCycle);
					}
					else
					{
						cout << "new value must be between 1% and 100%" << endl;
					}
				}
				break;
			case 't':
				toggleEnable ();
				break;
			case 's':
				cout << "Enter a start Hz,end Hz and increase per step" << endl
				    << "min freq: 100, max freq 10000 (recommended)" << endl;
				if (scanf ("%d %d %d", &start, &stop, &step))
				{
					runSweep (start, stop, step);
				}
				else
				{
					cout << "error" << endl;
				}
				break;
			case 'i':
				cout << "f: change frequency" << endl << "d: change duty cycle"
				    << endl;
				cout << "t: toggle PWM on and off" << endl << "ctrl+c to quit"
				    << endl << "s: set up sweep" << endl << "i: information"
				    << endl;
				break;
			default:
				cout << "we are in default. Enter f, d, t, i or s" << endl;
				break;
		}
	}
}
