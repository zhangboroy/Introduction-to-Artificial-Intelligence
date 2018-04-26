#ifndef MUTATION_H_INCLUDED
#define MUTATION_H_INCLUDED

#include "chromosome.h"

//mutation function, the children mutate under certain probability
//it may be several mutation algorithms, each one occurs under certain probability, but never occur at same time
void Mutate(Chromosome* children, const int &population, const int &mutationType, const int &mutationProbability);

#endif // MUTATION_H_INCLUDED
