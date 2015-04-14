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
	float SolarMass = 1.98855*pow(10.0,30.0);
	float AU = 149597870700;//m

	//simulation integration parameters
	float dt = pow(10,9);
	float maxT = 100*dt;
	unsigned int maxTimeSteps = (maxT/dt);

	unsigned short integration_method = 4;
	//0 = errorflag
	//1 = Euler
	//2 = 2nd order Runga-Kutta
	//4 = 4th order Runga-Kutta

};


#endif /* CPARAMETERS_H_ */
