#ifndef SELECTION_H_INCLUDED
#define SELECTION_H_INCLUDED

#include "chromosome.h"

//the natural selection function, base on the performance selects the parentsBeforeSelection and get the parentsAfterSelection
void Select(const Chromosome* parentsBeforeSelection, Chromosome* parentsAfterSelection, const int &population);

#endif // SELECTION_H_INCLUDED
