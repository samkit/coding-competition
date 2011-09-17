/*
 * main.cpp
 *
 *  Created on: 08-May-2010
 *      Author: samkit
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <boost/math/common_factor.hpp>

using namespace std;
using namespace boost;

namespace
{
typedef unsigned long long int ValueTypeToProcess;
typedef long double ValueTypeToRead;
}


// FIXME: Check for return type.
size_t TimeToApocalypse(vector<ValueTypeToRead>& inputList)
{
	if(inputList.size() <= 1)
	{
		// If there is only one input then APOCALYPSE is NOW.
		return 0;
	}
	// In my written tests, sorting was needed.
	// Though I have not tested without sorting, but it should work.
	sort(inputList.begin(), inputList.end());

	cout << "Input: ";
	for(size_t i = 0; i < inputList.size(); ++i)
	{
		cout << inputList[i] << " ";
	}
	cout << endl;

	ValueTypeToProcess greatestCommonDivisor;

	for(size_t i = 0; i < inputList.size() - 1; ++i)
	{
		ValueTypeToProcess difference = inputList[i + 1] - inputList[i];
		if(i == 0)
		{
			greatestCommonDivisor = difference;
		}
		greatestCommonDivisor = math::gcd(greatestCommonDivisor, difference);
	}

//	cout << "greatestCommonDivisor: " << greatestCommonDivisor << endl;
	if(greatestCommonDivisor == 1)
	{
		return 0;
	}

	ValueTypeToRead doubleGCD = greatestCommonDivisor * 1.0;
	ValueTypeToRead doubleQuotient = inputList[0] / doubleGCD;
	ValueTypeToProcess integralQuotient = doubleQuotient;	// Hope to preserve the sanity limits.
//	cout << "integralQuotient: " << integralQuotient << endl;
	ValueTypeToProcess remainder = inputList[0] - (doubleGCD * integralQuotient);
//	cout << "remainder: " << remainder << endl;

	ValueTypeToProcess valueToAdd = greatestCommonDivisor - remainder;
//	ValueTypeToProcess valueToAdd = greatestCommonDivisor - (inputList[0] % greatestCommonDivisor);
//	cout << "valueToAdd: " << valueToAdd << endl;

	return valueToAdd;

//	ValueTypeToProcess largestGCD = 0;
	size_t indexForLargestGCD = 0;


//	cout << "inputList[0]: " << inputList[0] << endl;
//	cout << "(inputList[0] / greatestCommonDivisor): " << (inputList[0] % greatestCommonDivisor) << endl;

//	for(size_t i = 0; i < greatestCommonDivisor; ++i)
//	{
//		ValueTypeToProcess greatestCommonDivisorForInputs;
//		for(size_t j = 0; j < inputList.size(); ++j)
//		{
//			greatestCommonDivisorForInputs = inputList[0] + i;
//			greatestCommonDivisorForInputs = math::gcd(greatestCommonDivisorForInputs, inputList[j] + i);
//		}
//		if(largestGCD < greatestCommonDivisorForInputs)
//		{
//			largestGCD = greatestCommonDivisorForInputs;
//			indexForLargestGCD = i;
//		}
//		cout << "greatestCommonDivisorForInputs: " << greatestCommonDivisorForInputs << endl;
//	}

	// Below tertiary operator is for safety. I don't assume to hit it even once for "-1".
	return indexForLargestGCD;
}

void helper();

int main(int argc, char* argv[])
{
	ios::fmtflags i;
	cout.setf(ios::fixed);
//	cout << "ValueTypeToProcess::max: " << numeric_limits<ValueTypeToProcess>::max() << endl;
//	cout << "ValueTypeToRead::max: " << numeric_limits<ValueTypeToRead>::max() << endl;

	helper();
	return 0;

	if(argc != 2)
	{
		cout << "Usage: " << argv[0] << " <input file>" << endl;
		return -1;
	}

	fstream inFile(argv[1]);
	if(!inFile.is_open())
	{
		cout << "Error opening input file: " << argv[1] << endl;
		return -2;
	}

	int currentTestCase = 0;
	int numberOfTestCases;
	while(inFile >> numberOfTestCases)
	{
		while(numberOfTestCases--)
		{
			int numberOfInputs;
			vector<ValueTypeToRead> inputList;

			inFile >> numberOfInputs;

			cout << "numberOfInputs: " << numberOfInputs << endl;

			while(numberOfInputs--)
			{
				int input;
				inFile >> input;
				cout << "input:" << input << endl;
				inputList.push_back(input);
			}
			cout << "Case #" << ++currentTestCase << ": " << TimeToApocalypse(inputList) << endl;
		}
	}

	return 0;
}
