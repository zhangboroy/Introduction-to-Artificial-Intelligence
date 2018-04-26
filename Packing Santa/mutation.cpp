#include <algorithm>
#include "mutation.h"

void SwapMutation(Chromosome &children)
{
    int random1 = 0;
    int random2 = 0;

    // Generate random indexes
    random1 = rand() % presentNumber;
    do
        random2 = rand() % presentNumber;
    while (random1 == random2);
    // Swap at indexes
    int temp = children.present[random1];
    children.present[random1] = children.present[random2];
    children.present[random2] = temp;
}

void ScrambleMutation(Chromosome &children)
{
    int upper = 0;
    int lower = 0;
    int temp = 0;

    // Generate random indexes (upper and lower bound of scramble)
    upper = rand() % presentNumber;
    do
        lower = rand() % presentNumber;
    while (upper == lower);
    if (lower > upper)
    {
        temp = upper;
        upper = lower;
        lower = temp;
    }
    // Scramble between indexes
    random_shuffle(children.present+lower, children.present+upper);
}

//mutation function, the children mutate under certain probability
//it may be several mutation algorithms, each one occurs under certain probability, but never occur at same time
void Mutate(Chromosome* children, const int &population, const int &mutationType, const int &mutationProbability)
{
    int method=0;
    for(int i=0;i<population;++i)
    {
        if (rand()%100<mutationProbability)
        {
            if (mutationType==2)
            {
                method=rand()%2;
            }
            else
            {
                method=mutationType;
            }

            if (method==0)
            {
                SwapMutation(children[i]);
                //reset the performance
                children[i].performance=0;
            }
            else
            {
                ScrambleMutation(children[i]);
                //reset the performance
                children[i].performance=0;
            }
        }
    }
}
