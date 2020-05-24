/*
 * testBase.hpp
 *
 *  Created on: Apr 26, 2020
 *      Author: nikolaj
 */

#ifndef TESTCASE_TESTSTATS_HPP_
#define TESTCASE_TESTSTATS_HPP_

namespace TestStatusCodes {

	static const int _504 = -504;	//sensor not found.
	static const int _511 = -511;	//init pwm failed.
	static const int _512 = -512;	//wrong pwm setup.
	static const int _514 = -514;	//start pwm failed.
	static const int _515 = -515;	//stop pwm failed.
	static const int _520 = -520;	//read sensor failed.
	static const int _555 = -555;	//not implemented.
}

#endif /* TESTCASE_TESTSTATS_HPP_ */
