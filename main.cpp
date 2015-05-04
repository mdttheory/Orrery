/*
 * main.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Mark Wittekind and Drew Murray
 */
#include "CSolarSystem.h"
#include "Parameters.cpp"
#include <algorithm>
#include <fstream>
#include "CSimulation.h"
#include <sys/time.h>
#include "CChromosome.h"
#include <random>
#include <chrono>
#include "CSatellite.h"
#include <string>

using namespace std;

int main()
{
	streambuf * pos_buf;
	ofstream pos_of;
	//set to filename
	pos_of.open("data/raw_positions.txt");
	pos_buf = pos_of.rdbuf();
	ostream pos_stream(pos_buf);

//	streambuf * en_buf;
//	ofstream en_of;
//	en_of.open("data/delta_E.txt");
//	en_buf = en_of.rdbuf();
//	ostream en_stream(en_buf);

	streambuf * param_buf;
	ofstream param_of;
	param_of.open("data/parameters.txt");
	param_buf = param_of.rdbuf();
	ostream param_stream(param_buf);

	streambuf * com_buf;
	ofstream com_of;
	com_of.open("data/center_of_mass.txt");
	com_buf = com_of.rdbuf();
	ostream com_stream(com_buf);

	streambuf * success_buf;
	ofstream success_of;
	success_of.open("data/success.txt");
	success_buf = success_of.rdbuf();
	ostream success_stream(success_buf);

	Par par;
	CSolarSystem newSS(&par);
	// 2nd int params are gen,corenum
	CSimulation RKSim(newSS, &par, "RK4",0,0);
	//RKSim.print_pos(pos_stream);

	//TODO: update parameter output
	param_stream << "-----"<<RKSim.m_name << "-----\n";
	param_stream << "AU: " << RKSim.m_par->AU << "\n";
	param_stream << "G: " << RKSim.m_par->G << "\n";
	param_stream << "SolarMass: " << RKSim.m_par->SolarMass << "\n";
	param_stream << "dt: " << RKSim.m_par->dt << "\n";
	param_stream << "maxT: " <<RKSim.m_par->maxT << "\n";
	param_stream << "integration_method: " << RKSim.m_par->integration_method << "\n";
	param_stream << "print_freq: " << RKSim.m_par->print_freq << "\n\n";

	for (unsigned int g =0;g<par.maxGenerations;g++){
			for(unsigned long int t = 0; t<RKSim.m_par->maxTimeSteps; t++){
					if(int(t)%par.print_freq==0){
						cout << "Timestep " << t << " of " << RKSim.m_par->maxTimeSteps << "\n";
						//RKSim.print_pos(pos_stream);
					}
					RKSim.update(t);
				}
			cout << "Generation: " << RKSim.m_genNum << "\n";
		RKSim = RKSim*RKSim;
		RKSim.successPrint(success_stream);

		//RKSim.genePrint("Gene");
	}
	param_of.close();


	/*
	for(unsigned long int t = 0; t<par.maxTimeSteps; t++){
		RKSim.update();
		EulerSim.update();
		if(int(t)%par.print_freq==0){
			cout << "Timestep " << t << " of " << par.maxTimeSteps << "\n";
			RKSim.print_pos(pos_stream);
			RKSim.print_en(en_stream, init_en);
			en_stream << " ";
			EulerSim.print_en(en_stream, init_en);
			en_stream << "\n";
		}
	}*/

	//en_of.close();
	pos_of.close();
	com_of.close();
	success_of.close();
	cout << "PROGRAM TERMINATING!\n";
	return 0;
}


