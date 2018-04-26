#ifndef CROSSOVER_H_INCLUDED
#define CROSSOVER_H_INCLUDED

#include "chromosome.h"

//for search in the chromosome
static int* segment1=new int[presentNumber];
static int* segment2=new int[presentNumber];

//crossover function, uses the parents(a dynamic array) to generate children(a dynamic array), couples=population/2
//it may be several crossover algorithms, each one occurs under certain probability, but never occur at same time
void Crossover(const Chromosome* parents, Chromosome* children, const int &couples, const int &crossOverType, const int &crossOverProbability);

#endif // CROSSOVER_H_INCLUDED
