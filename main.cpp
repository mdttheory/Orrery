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

	streambuf * en_buf;
	ofstream en_of;
	en_of.open("data/delta_E.txt");
	en_buf = en_of.rdbuf();
	ostream en_stream(en_buf);

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

	Par par;
	CSolarSystem newSS(&par);
	vector<CSimulation> sims;

	CSimulation RKSim(newSS, &par, "RK4");
	RKSim.print_pos(pos_stream);
	double init_en = RKSim.m_SS.totalEnergy();

	Par par2 = par;
	par2.integration_method=1;
	CSimulation EulerSim(newSS, &par2, "Euler");

	vector<bool> flag;
	for (unsigned int i = 0; i<par.satsPerCore;i++){
		CSatellite a(&par, &newSS, string(string("Sat")+to_string(i)), flag);
		RKSim.m_SS.m_sats.push_back(a);
		a.printThrust(cout);
	}


	sims.push_back(RKSim);
	//sims.push_back(EulerSim);




	for (vector<CSimulation>::iterator it = sims.begin();
				it < sims.end(); it++) {

		param_stream << "-----"<<it->m_name << "-----\n";
		param_stream << "AU: " << it->m_par->AU << "\n";
		param_stream << "G: " << it->m_par->G << "\n";
		param_stream << "SolarMass: " << it->m_par->SolarMass << "\n";
		param_stream << "dt: " << it->m_par->dt << "\n";
		param_stream << "maxT: " << it->m_par->maxT << "\n";
		param_stream << "integration_method: " << it->m_par->integration_method << "\n";
		param_stream << "print_freq: " << it->m_par->print_freq << "\n\n";

		struct timeval tp;
		gettimeofday(&tp,NULL);
		long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		for(unsigned long int t = 0; t<it->m_par->maxTimeSteps; t++){
				if(int(t)%par.print_freq==0){
					cout << "Timestep " << t << " of " << it->m_par->maxTimeSteps << "\n";


					if(it->m_name == RKSim.m_name){
						it->print_pos(pos_stream);
						//com_stream << it->m_SS.calcCOM() << "\n";
					}
					it->print_en(en_stream, init_en);
					gettimeofday(&tp,NULL);
					en_stream << ", " << t << ", " << (tp.tv_sec * 1000 + tp.tv_usec / 1000-ms);
					en_stream << ", " << it->m_SS.kinetic() << ", " << it->m_SS.potential();
					en_stream << "\n";
				}

				it->update();
			}
		en_stream << "-\n"; // Mark new simulation
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

	en_of.close();
	pos_of.close();
	com_of.close();
	return 0;
}


