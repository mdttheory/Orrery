/*
 * Parameters.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#ifndef CPARAMETERS_H_
#define CPARAMETERS_H_

#include <math.h>

struct Par{
	//Astronomical units (Me = 1, Re = 1);
	float G = 6.6738480 * pow(10,-11);//m3kg-1s-2
	float SolarMass = 1.98855*pow(10,30);
	float AU = 149597870700;//m

};


#endif /* CPARAMETERS_H_ */
