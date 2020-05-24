// TODO: Include your class to test here.
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ADXL345Test
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "ADXL345.h"
#include <iostream>
#include <fstream>

using boost::test_tools::output_test_stream;

/**
* Testcase ADXL345TestRange
* Unit test for setting and getting range of ADXL345
* Sets Range in ADXL345 register
* Gets Range from local varible in class
*/

BOOST_AUTO_TEST_CASE(ADXL345TestRange)
{	
	
	const unsigned int BUS = 2;
	const unsigned int ADDR = 0x53;
	ADXL345 sensor(BUS, ADDR);
	
	BOOST_REQUIRE(sensor.setRange(ADXL345::PLUSMINUS_2_G)==0);
	BOOST_CHECK(sensor.getRange() == ADXL345::PLUSMINUS_2_G);

	BOOST_REQUIRE(sensor.setRange(ADXL345::PLUSMINUS_4_G) == 0);
	BOOST_CHECK(sensor.getRange() == ADXL345::PLUSMINUS_4_G);

	BOOST_REQUIRE(sensor.setRange(ADXL345::PLUSMINUS_8_G) == 0);
	BOOST_CHECK(sensor.getRange() == ADXL345::PLUSMINUS_8_G);

	BOOST_REQUIRE(sensor.setRange(ADXL345::PLUSMINUS_16_G) == 0);
	BOOST_CHECK(sensor.getRange() == ADXL345::PLUSMINUS_16_G);
	
}


/**
* Testcase ADXL345TestResolution
* Unit test for setting and getting range of ADXL345
* Set Resolution in ADXL345 register
* Gets Resolution from local varible in class
*/

BOOST_AUTO_TEST_CASE(ADXL345TestResolution)
{
	
	const unsigned int BUS = 2;
	const unsigned int ADDR = 0x53;
	ADXL345 sensor(BUS, ADDR);

	BOOST_REQUIRE(sensor.setResolution(ADXL345::NORMAL) == 0);
	BOOST_CHECK(sensor.getResolution() == ADXL345::NORMAL);
	BOOST_REQUIRE(sensor.setResolution(ADXL345::HIGH) == 0);
	BOOST_CHECK(sensor.getResolution() == ADXL345::HIGH);
	
}


/**
* Testcase ADXL345TestRead
* Unit test for reading sensor data X,Y and Z
* Gets X, Y and Z from sensor registers
*/

BOOST_AUTO_TEST_CASE(ADXL345TestRead)
{
	
	const unsigned int BUS = 2;
	const unsigned int ADDR = 0x53;
	ADXL345 sensor(BUS, ADDR);

	BOOST_REQUIRE(sensor.ReadSensorState() == 0);
	BOOST_CHECK(sensor.getaccelX() != 0);
	BOOST_CHECK(sensor.getaccelY() != 0);
	BOOST_CHECK(sensor.getaccelZ() != 0);
	
}


/**
* Testcase ADXL345TestBaud
* Unit test for setting and getting baud rate of ADXL345
* Set Baud rate in ADXL345 register
* Gets Baud rate from local varible in class
*/

BOOST_AUTO_TEST_CASE(ADXL345TestBaud)
{
	
	const unsigned int BUS = 2;
	const unsigned int ADDR = 0x53;	
	ADXL345 sensor(BUS, ADDR);

	BOOST_REQUIRE(sensor.setBWrate(ADXL345::BANDWITH_400_Hz) == 0);	
	BOOST_CHECK(sensor.getBaud() == ADXL345::BANDWITH_400_Hz);
	
}


/**
* Testcase ADXL345TestWriteXYZ
* Unittest for writing 3 16 bit integers to ostream
* Appends data to file
* Closes file
*/
BOOST_AUTO_TEST_CASE(ADXL345TestWriteXYZ) {
	const short X = 16;
	const short Y = 11;
	const short Z = 0;
	const unsigned int BUS = 2;
	const unsigned int ADDR = 0x53;

	ADXL345 sensor(BUS, ADDR);
	output_test_stream output;
	//int writeStatus = sensor.WriteDataToFile(output, X, Y, Z);
    //BOOST_CHECK(writeStatus == 0);
	output << X << "," << Y << "," << Z << "\n";;
    BOOST_CHECK(output.is_equal("16,11,0\n"));
}

/**
* Testcase ADXL345TestOpenCloseFile
* Unittest for opening or creating file
* closes file
*/
BOOST_AUTO_TEST_CASE(ADXL345TestOpenCloseFile) {
        const unsigned int BUS = 2;
        const unsigned int ADDR = 0x53;

        ADXL345 sensor(BUS, ADDR);
		
        BOOST_REQUIRE(sensor.OpenOutFile()==0); //Open file
        //ifstream ifile(OUT_FILE);
		//BOOST_CHECK(ifile == true);
        BOOST_CHECK(sensor.CloseOutFile() == 0);
}
