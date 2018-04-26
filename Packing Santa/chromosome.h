#ifndef CHROMOSOME_H_INCLUDED
#define CHROMOSOME_H_INCLUDED

#include "present.h"

class Solution;

class Chromosome
{
public:
    //the present order list
    int* present;
    unsigned long long int performance;

    //the default constructor
    Chromosome();
    //the copy constructor
    Chromosome(const Chromosome &chromosome);
    //the destructor
    ~Chromosome()
    {
        delete []present;
        present=0;
    }
    void operator=(const Chromosome &chromosome);
    //randomize the chromosome
    void Randomize();
    //calculate the performance of the solution
    void Evaluation(const Solution &solution);
} ;

#endif // CHROMOSOME_H_INCLUDED
