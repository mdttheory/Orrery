/*
 * Parameters.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#ifndef CPARAMETERS_H_
#define CPARAMETERS_H_

#include <math.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>

using namespace std;

struct Par{
	//Astronomical units (Me = 1, Re = 1);
	float G = 6.6738480 * pow(10,-11); //m3*kg-1*s-2
	float SolarMass = 1.98855*pow(10.0,30.0);
	float AU = 149597870700; //meters

	//simulation integration parameters
	float dt = 1*pow(10,4);
	float maxT = 0*2*50000*dt;
	unsigned long int maxTimeSteps = (maxT/dt);

	unsigned short integration_method = 4;
	unsigned short print_freq = 100;
	//0 = errorflag
	//1 = Euler
	//2 = 2nd order Runga-Kutta
	//4 = 4th order Runga-Kutta

	float maxThrusterVel = pow(10.0,30);

	float mutateChance = .01;

	//TODO List:
	/*
	 * Create trait class (dvx, dvy, dvz, t)
	 * Overload comparison operators and [] operator
	 * 		for trait in sat
	 * 			for int i=0; i<4; i++
	 * 				if rand()
	 * 					trait[i] = father.trait[i]
	 * Parallelize loop of simulations
	 * Create satellite class with random initialization
	 * Write fitness function
	 * Write loop for parallelization
	 * Small scale test
	 * Parameter for max run time (realtime) & how often to check
	 * Run on HPCC
	 * Write outer (generational) loop with dummy breeding function
	 * test
	 * Improve breeding algorithm
	 * Increase demands on GA with a more specific fitness function
	 */

};
/*
template<typename T>
T randBetween (T min, T max){
	T n = max - min;
	float scale = 1.0;
	if(n>=RAND_MAX){
		scale = n/float(RAND_MAX);
		n=RAND_MAX-1;
	}
	T remainder = fmod(RAND_MAX, n);
	cout << "remainder: " << remainder << "\n";
	cout << "mod: " << (2147483647%2147483646) << "\n";
	T x;
    do{
        x = rand();
    }while (x >= RAND_MAX - remainder);
    return min + scale*(fmod(x, n));
}*/

#endif /* CPARAMETERS_H_ */
