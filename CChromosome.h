/*
 * CChromosome.h
 *
 *  Created on: Apr 24, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#ifndef CTRAIT_H_
#define CTRAIT_H_

#include "Parameters.cpp"
#include <random>

class CChromosome {
public:
	CChromosome(Par* par, default_random_engine &gen);
	CChromosome(const CChromosome &rhs, default_random_engine &gen);
	virtual ~CChromosome();
	Par* m_par;
	default_random_engine m_gen;

	float m_dvx[3];
	float m_dvy[3];
	float m_dvz[3];
	float m_t[3];
	int chromSize() const {
		return 4;
	}

	bool operator==(const CChromosome& rhs);
	bool operator!=(const CChromosome& rhs);
	CChromosome operator*(CChromosome& rhs);
	bool operator<(const CChromosome& rhs);
	bool operator>(const CChromosome& rhs);
	bool operator>=(const CChromosome& rhs);
	bool operator<=(const CChromosome& rhs);
	float* operator[](const int nIndex);
	friend ostream &operator<<(ostream &output, CChromosome &chrom) {
		const int size = chrom.chromSize();

		for (unsigned short i = 0; i < size; i++) {
			output << chrom[i][0] << "\n";
		}
		output << "\n";
		return output;
	}
};

#endif /* CTRAIT_H_ */
