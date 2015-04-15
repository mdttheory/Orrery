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


	Par par;
	CSolarSystem newSS(&par);
	cout << newSS << "\n";


	CSimulation RKSim(newSS, &par);
	RKSim.print_pos(pos_stream);
	double init_en = RKSim.m_SS.totalEnergy();
	RKSim.print_en(en_stream,init_en);

	Par par2 = par;
	par2.integration_method=1;
	CSimulation EulerSim(newSS, &par2);
	EulerSim.print_en(en_stream,init_en);

	RKSim.m_SS.adjustMomentum();

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
	}

	pos_of.close();
	return 0;
}


