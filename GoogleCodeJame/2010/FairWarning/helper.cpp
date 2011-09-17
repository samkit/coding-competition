/*
 * helper.cpp
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

long double ConvertToLongDouble(string line)
{
	long double value = 0;
	cout << "Lenght: " << line.length() << endl;
	cout << "Value: ";
	for(size_t i = 0; i <= line.length(); ++i)
	{
		cout << line[i] << endl;
		value = value * 10 + (line[i] - '0');
		cout << "Value: " << value << endl;
	}
	cout << endl;
	return value;
}

void helper()
{
	const unsigned long MAX = 99999999;
	vector<unsigned long> inputs;

//	475668 900316 868340 -- 52
//  49878388 38979864 22115576 -- 0
//  7131464 5488099 -- 1085361
//	30610982 3008078 13537058 -- 718
//	204788, 561, 1585 -- 0
//	20309499 30339162 10354563 -- 3249
//	69842950 34921475
	inputs.push_back(34921475);
	inputs.push_back(69842950);
//	inputs.push_back(30339162);

	unsigned long gcd = inputs[0];

	for(size_t i = 0; i < inputs.size(); ++i)
	{
		gcd = math::gcd(gcd, inputs[i]);
	}

	unsigned long index = 0;

	cout << "GCD: " << gcd << endl;

	for(unsigned long i = 0; i <= MAX; ++i)
	{
		unsigned long newGCD = inputs[0] + i;
		for(size_t j = 0; j < inputs.size(); ++j)
		{
			newGCD = math::gcd(newGCD, inputs[j] + i);
		}

		if (newGCD > gcd)
		{
			gcd = newGCD;
			cout << "New GCD: " << gcd << endl;
			index = i;
		}

		if(i % 1000000 == 0)
			cout << "Index: " << i << endl;
	}

	cout << "Maximum GCD: " << gcd << " @ index: " << index << endl;

}
