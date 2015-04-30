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
	float maxT = 2*50000*dt;
	unsigned long int maxTimeSteps = (maxT/dt);
	unsigned short integration_method = 4;
	unsigned short print_freq = 5;
	//0 = errorflag
	//1 = Euler
	//2 = 2nd order Runga-Kutta
	//4 = 4th order Runga-Kutta

	//GA Params
	float mutateChance = .01;
	unsigned int satsPerCore = 5;
	unsigned int maxGenerations = 10;
	float breedingPercentage = .1;//10% of pop will breed to make next gen
	float randomBreedPercentage = .25;//25% of breeding pop will be selected without bias for fitness

	// Satellite params
	float maxThrusterVel = 30000;
	float startFuel = 1;
	unsigned int thrustQuant = 5;
	float satMass = 722;
	string homePlanetName = "Mercury";

	//fitness params
	string destinationPlanetName = "Mars";
	float goalDistance = 1;//multiplied by destiantion planet radius
	//multiplied by pluto's aphelion


	//TODO List:
	/*
	 * test breeding of sims with many satellites
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
