#include <algorithm>
#include <vector>
#include <utility>
#include "put.h"

//the random Chromosome constructor
Chromosome::Chromosome()
{
    performance=0;
    present=new int[presentNumber];

    for (int i=0;i<presentNumber;++i)
    {
        present[i]=i;
        //present[i]=presentNumber-i-1;
    }
}

//the copy constructor
Chromosome::Chromosome(const Chromosome &chromosome)
{
    for (int i=0;i<presentNumber;i++)
    {
        present[i]=chromosome.present[i];
    }
    performance=chromosome.performance;
}

void Chromosome::operator=(const Chromosome &chromosome)
{
    for (int i=0;i<presentNumber;i++)
    {
        present[i]=chromosome.present[i];
    }
    performance=chromosome.performance;
}

//randomize the chromosome
void Chromosome::Randomize()
{
    random_shuffle(present, present+presentNumber);
}

//calculate the performance of the solution
void Chromosome::Evaluation(const Solution &solution)
{
    performance=0;
    // pairs present order number to its highest z-value
    vector<pair<int,int>> orderZ;

    // Formula: 2 * (highest present height) + (summation of |i - order of present placement|),
    // where i increments from 1 to # of presents

    /*
    // Look through every top-left z-value (14th value)
    for (int i=0;i<24*presentNumber;++i)
    {
        if (i%24 == 14)
        {
            pair<int,int> aPair;
            // present order #
            aPair.first = i/24;
            // z-value
            aPair.second = solution.presentPosition[i];
            orderZ.push_back(aPair);
        }
    }
    */

    // Look through every top-left z-value (14th value)
    int maxZ=0;
    for (int i=0;i<presentNumber;++i)
    //for (int i=0;i<24*presentNumber;++i)
    {
        pair<int,int> aPair;
        // present order #
        aPair.first = i;
        // z-value
        aPair.second = solution.presentPosition[i*24+2];
        if (maxZ<solution.presentPosition[i*24+14])
        {
            maxZ=solution.presentPosition[i*24+14];
        }
        orderZ.push_back(aPair);
    }

    /*
    // Sort by descending Z-value, then by ascending present order number for same z-values
    // The lambda expression can be substituted for a function with the same body
    sort( orderZ.begin(), orderZ.end(),
               []( const pair<int, int> &p1, const pair<int, int> &p2 )
               {
                   return ( p1.second > p2.second ||
                          ( ( p2.second == p1.second ) && p1.first < p2.first ) );
               } );
    */

    // Sort by descending Z-value, then by ascending present order number for same z-values
    // The lambda expression can be substituted for a function with the same body
    sort( orderZ.begin(), orderZ.end(),
               []( const pair<int, int> &p1, const pair<int, int> &p2 )
               {
                   return ( p1.second < p2.second ||
                          ( ( p2.second == p1.second ) && p1.first < p2.first ) );
               } );

    int counter = 0;
    for(auto elem : orderZ)
    {
        performance += abs(counter-elem.first);
        counter++;
    }
    performance += 2*(maxZ+1);
    //performance += 2*(orderZ[0].second+1);
}
