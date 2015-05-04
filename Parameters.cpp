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
#include <string>

using namespace std;

struct Par{
	//Astronomical units (Me = 1, Re = 1);
	float G = 6.6738480 * pow(10,-11); //m3*kg-1*s-2
	float SolarMass = 1.98855*pow(10.0,30.0);
	float AU = 149597870700; //meters
	double boundaryDistanceSquared = pow(7311000000000*3,2);//must be greater than pluto's

	//Single simulation integration parameters
	float dt = 1*pow(10,4);
	float maxT = 0*10000*dt;
	unsigned long int maxTimeSteps = (maxT/dt);
	unsigned short integration_method = 4;
	unsigned short print_freq = 1000000000;
	//0 = errorflag
	//1 = Euler
	//2 = 2nd order Runga-Kutta
	//4 = 4th order Runga-Kutta

	//GA Params
	float mutateChance = .2;
	unsigned int satsPerCore = 10;
	unsigned int maxGenerations = 3;
	float breedingNum = 3;//10 will breed
	float randomBreedingNum = 1;//2 of breeding pop will be selected without bias for fitness

	// Satellite params
	float maxThrusterVel = 30000;
	unsigned int thrustQuant = 2;
	float satMass = 722;
	string homePlanetName = "Mercury";

	//fitness params
	string destinationPlanetName = "Mars";
	float goalDistanceMultiplier = 1;//multiplied by destiantion planet radius (must be >= 1)
	//multiplied by pluto's aphelion


	//TODO List:
	/*
	 * Write fitness function
	 * write outer loop of generations
	 *
	 * Parallelize loop of simulations
	 * Write loop for parallelization
	 * Parameter for max run time (realtime) & how often to check
	 * Run on HPCC
	 * Improve breeding algorithm
	 * Increase demands on GA with a more specific fitness function
	 */

};

struct SatName{
	unsigned short coreNum = 0;
	unsigned int genNum = 0;
	unsigned long long selfID = 0;
	unsigned long long momID = 0;
	unsigned long long dadID = 0;
};

#endif /* CPARAMETERS_H_ */
