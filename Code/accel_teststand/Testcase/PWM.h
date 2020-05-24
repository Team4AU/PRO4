/*
 * PWM.h
 *
 *  Created on: 22 Nov 2019
 *      Author: Rikke
 */

#ifndef PWM_H_
#define PWM_H_

#define PWM_EXPORT_PB "/sys/class/pwm/pwmchip0/export"//1
#define PWM_PATH_PB "/sys/class/pwm/pwmchip0/pwm-0:0/" //file path for PB
#define PWM_ENABLE_PB "/sys/class/pwm/pwmchip0/pwm-0:0/enable" //enable for PB
#define PWM_DUTY_PB "/sys/class/pwm/pwmchip0/pwm-0:0/duty_cycle" //duty cycle for PB
#define PWM_PERIOD_PB "/sys/class/pwm/pwmchip0/pwm-0:0/period" //period for PB
#define PWM_SETUP_PB "config-pin p1_36 pwm"

#define PWM_EXPORT_BBB "/sys/class/pwm/pwmchip4/export" //3
#define PWM_PATH_BBB "/sys/class/pwm/pwm4/" //file path for BBB
#define PWM_ENABLE_BBB "/sys/class/pwm/pwmchip4/pwm-4:0/enable" //enable for BBB
#define PWM_DUTY_BBB "/sys/class/pwm/pwmchip4/pwm-4:0/duty_cycle" //duty cycle file for BBB
#define PWM_PERIOD_BBB "/sys/class/pwm/pwmchip4/pwm-4:0/period" //period file for BBB
#define PWM_SETUP_BBB "config-pin P9.14 pwm"

#define NANOSECONDS 1000000000
#define MICROSECONDS 1000000

#define MINDUTYCYCLE 0
#define MAXDUTYCYCLE 101

#define MINFREQ 99
#define MAXFREQ 10001

/**
 * @brief This enum is used to select a type of device
 */
	typedef enum{
						PB,//!< PB
						BBB//!< BBB
				}Device;

/**
 * @brief This class is used to control PWM on BBB/PB (Linux/Debian)
 */
class PWM
{
		int count = 0;
		unsigned int freq = 100;
		unsigned int dutyCycle = 50;
		Device device;
	public:
		PWM ( );
		PWM (const char* unit);
		virtual ~PWM ( );
		bool init ( );
		bool startPWM ( );
		bool stopPWM ( );
		bool setup (unsigned int freq, unsigned int duty);
		unsigned int toggleEnable ();
		bool runSweep (unsigned int start,unsigned int stop,unsigned int step);
		void testMenu ();
};

#endif /* PWM_H_ */
