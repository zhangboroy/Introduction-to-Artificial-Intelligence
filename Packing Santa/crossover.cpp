#include "crossover.h"
#include <cstdlib>

using namespace std;

//return the mapped present in the PMX function
int Map(const int segment[], const Chromosome &chromosome, const int &i)
{
    //get the position where the present[i] of chromosome2 in the segment [left, right) of chromosome1
    int position=segment[chromosome.present[i]];
    //if not in this segment, it is the present[i] of chromosome2
    if (position==-1)
    {
        return chromosome.present[i];
    }
    //if in this segment, map present[position] of chromosome2
    else
    {
        return Map(segment, chromosome, position);
    }
}

//the PMX function
void PMX(const Chromosome parents[], Chromosome children[], const int &n, const int &couples)
{
    //generate random segment
    int left=rand()%presentNumber;
    int right=left+rand()%(presentNumber-left)+1;

    for (int i=0;i<left;++i)
    {
        segment1[parents[n].present[i]]=-1;
        segment2[parents[n+couples].present[i]]=-1;
    }

    for (int i=right;i<presentNumber;++i)
    {
        segment1[parents[n].present[i]]=-1;
        segment2[parents[n+couples].present[i]]=-1;
    }

    //copy the segment
    for (int i=left;i<right;++i)
    {
        children[n].present[i]=parents[n].present[i];
        children[n+couples].present[i]=parents[n+couples].present[i];
        segment1[parents[n].present[i]]=i;
        segment2[parents[n+couples].present[i]]=i;
    }
    //map the other parts
    for (int i=0;i<left;++i)
    {
        children[n].present[i]=Map(segment1, parents[n+couples], i);
        children[n+couples].present[i]=Map(segment2, parents[n], i);
    }
    for (int i=right;i<presentNumber;++i)
    {
        children[n].present[i]=Map(segment1, parents[n+couples], i);
        children[n+couples].present[i]=Map(segment2, parents[n], i);
    }
}

//return the mapped present in the revised PMX function
int RevisedMap(const int segment[], const Chromosome &chromosome, const int &i, int &position)
{
    //if not in this segment, it is the present[i] of chromosome2
    if (segment[chromosome.present[i]]==-1)
    {
        return chromosome.present[i];
    }
    //if in this segment, map present[position] of chromosome2
    else
    {
        ++position;
        return RevisedMap(segment, chromosome, position-1, position);
    }
}

//the revisedPMS function
void RevisedPMX(const Chromosome parents[], Chromosome children[], const int &n, const int &couples)
{
    //generate random segment
    int left=rand()%presentNumber;
    int right=left+rand()%(presentNumber-left)+1;

    for (int i=0;i<left;++i)
    {
        segment1[parents[n].present[i]]=-1;
        segment2[parents[n+couples].present[i]]=-1;
    }

    for (int i=right;i<presentNumber;++i)
    {
        segment1[parents[n].present[i]]=-1;
        segment2[parents[n+couples].present[i]]=-1;
    }

    //copy the segment
    for (int i=left;i<right;++i)
    {
        children[n].present[i]=parents[n].present[i];
        children[n+couples].present[i]=parents[n+couples].present[i];
        segment1[parents[n].present[i]]=i;
        segment2[parents[n+couples].present[i]]=i;
    }
    //map the other parts
    int position1=left;
    int position2=left;
    for (int i=0;i<left;++i)
    {
        children[n].present[i]=RevisedMap(segment1, parents[n+couples], i, position1);
        children[n+couples].present[i]=RevisedMap(segment2, parents[n], i, position2);
    }
    for (int i=right;i<presentNumber;++i)
    {
        children[n].present[i]=RevisedMap(segment1, parents[n+couples], i, position1);
        children[n+couples].present[i]=RevisedMap(segment2, parents[n], i, position2);
    }
}

//the Order1 Crossover function
void Order1(const Chromosome parents[], Chromosome children[], const int &n, const int &couples)
{
    //generate random segment
    int left=rand()%presentNumber;
    int right=left+rand()%(presentNumber-left)+1;

    for (int i=0;i<left;++i)
    {
        segment1[parents[n].present[i]]=false;
        segment2[parents[n+couples].present[i]]=false;
    }

    for (int i=right;i<presentNumber;++i)
    {
        segment1[parents[n].present[i]]=false;
        segment2[parents[n+couples].present[i]]=false;
    }

    //copy the segment
    for (int i=left;i<right;++i)
    {
        children[n].present[i]=parents[n].present[i];
        children[n+couples].present[i]=parents[n+couples].present[i];
        segment1[parents[n].present[i]]=true;
        segment2[parents[n+couples].present[i]]=true;
    }

    //map the other parts
    int position1=right%presentNumber;
    int position2=right%presentNumber;
    for (int i=right%presentNumber;i!=left;i=(i+1)%presentNumber)
    {
        while (segment1[parents[n+couples].present[position1]])
        {
            position1=(position1+1)%presentNumber;
        }
        children[n].present[i]=parents[n+couples].present[position1];
        position1=(position1+1)%presentNumber;
        while (segment2[parents[n].present[position2]])
        {
            position2=(position2+1)%presentNumber;
        }
        children[n+couples].present[i]=parents[n].present[position2];
        position2=(position2+1)%presentNumber;
    }
}

//crossover function, uses the parents(a dynamic array) to generate children(a dynamic array), couples=population/2
//it may be several crossover algorithms, each one occurs under certain probability, but never occur at same time
void Crossover(const Chromosome* parents, Chromosome* children, const int &couples, const int &crossOverType, const int &crossOverProbability)
{
    int crossoverMethod=0;
    for (int i=0;i<couples;++i)
    {
        if (rand()%100<crossOverProbability)
        {
            if (crossOverType==3)
            {
                crossoverMethod=rand()%3;
            }
            else
            {
                crossoverMethod=crossOverType;
            }

            if (crossoverMethod==0)
            {
                PMX(parents,children,i,couples);
                //reset the performance
                children[i].performance=0;
                children[i+couples].performance=0;
            }
            else if (crossoverMethod==1)
            {
                RevisedPMX(parents,children,i,couples);
                //reset the performance
                children[i].performance=0;
                children[i+couples].performance=0;
            }
            else
            {
                Order1(parents,children,i,couples);
                //reset the performance
                children[i].performance=0;
                children[i+couples].performance=0;
            }
        }
        else
        {
            children[i]=parents[i];
            children[i+couples]=parents[i+couples];
        }
    }
}
