/*
 * main.cpp
 *
 *  Created on: 08-May-2010
 *      Author: samkit
 */

#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>

using namespace std;


namespace
{
typedef long double ValueType;
typedef long long RemainderValueType;

const ValueType ZERO = 0.0;
const ValueType ONE = 1.0;
const ValueType TWO = 2.0;
}

bool IsSwitchOn(int numberOfSnappers, ValueType numberOfClicks)
{
//	cout << "  recv: " << numberOfSnappers << " " << numberOfClicks << " ";
	ValueType totalClicksToTurnOn = pow(TWO, numberOfSnappers);

	ValueType quotient = (numberOfClicks + ONE) / totalClicksToTurnOn;

	RemainderValueType dividentIntegralValue = quotient;
	ValueType remainderOfDivision = quotient - dividentIntegralValue;

	if(ZERO == remainderOfDivision)
	{
		return true;
	}

	return false;
}

int main(int argc, char* argv[])
{
	int numberOfSnappers;
	ValueType numberOfClicks;

	if(argc != 2)
	{
		cout << "Usage: " << argv[0] << " <input file>";
		return -1;
	}

	fstream inFile(argv[1]);
	if(!inFile.is_open())
	{
		cout << "Error opening file: " << argv[1] << endl;
		return -2;
	}

	fstream outFile("output", fstream::out);
	if(!outFile.is_open())
	{
		cout << "Error opening out file" << endl;
		return -2;
	}

	unsigned int currentTestCase = 0;
	unsigned int numberOfTestCases;	// limit of 10,000
	while(inFile >> numberOfTestCases)
	{
		while(numberOfTestCases--)
		{
			++currentTestCase;
			inFile >> numberOfSnappers >> numberOfClicks;	// format "1 4"

			outFile << "Case #" << currentTestCase << ": "
				    << (IsSwitchOn(numberOfSnappers, numberOfClicks) ? "ON" : "OFF")
				    << endl;
		}
	}

	return 0;
}
