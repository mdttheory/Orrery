/*
 * main.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Mark Wittekind and Drew Murray
 */
#include "CSolarSystem.h"
#include "Parameters.cpp"
#include <algorithm>

using namespace std;

int main()
{
	Par par;
	CSolarSystem newSS(&par);
	cout << newSS << "\n";
	cout << newSS.kinetic()[0] << "\n";
	cout << newSS.kinetic()[1] << "\n";
	cout << newSS.potential()[0] << "\n";
	cout << newSS.potential()[1] << "\n";
	cout << newSS.totalEnergy(newSS.kinetic(),newSS.potential())[0] << "\n";
	cout << newSS.totalEnergy(newSS.kinetic(),newSS.potential())[1] << "\n";


	return 0;
}


