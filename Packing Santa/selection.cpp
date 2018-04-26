#include <cmath>
#include <cstdlib>
#include "selection.h"

//the natural selection function
void Select(const Chromosome children[], Chromosome parents[], const int &population)
{
    //the sum performance
    unsigned __int64 sumPerformance=0;
    //the random variable
    unsigned __int64 p=0;
    //to indicate the range that the p will be in
    unsigned __int64 range=0;
    //it is a large number bigger than any performance in the population
    unsigned __int64 max=0;
    //compute the sum performance and get the biggest performance
    for (int i=0;i<population;++i)
    {
        sumPerformance+=children[i].performance;
        if (children[i].performance>max)
        {
            max=children[i].performance;
        }
    }

    ++max;
    /*
    //make the biggest performance even bigger
    int digit=0;
    while (max>0)
    {
        ++digit;
        max=max/10;
    }
    max=pow(10, digit);
    */

    //generate the random population after the natural selection
    for (int i=0;i<population;++i)
    {
        range=0;
        p=rand()%(max*population-sumPerformance);
        for (int j=0;j<population;++j)
        {
            range+=max-children[j].performance;
            if (p<range)
            {
                parents[i]=children[j];
                break;
            }
        }
    }
}
