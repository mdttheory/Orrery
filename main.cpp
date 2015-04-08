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


	return 0;
}


