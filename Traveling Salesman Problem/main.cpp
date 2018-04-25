#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "route.h"

using namespace std;

//the natural selection function
void Select(const Route route1[], Route route2[], const int &population)
{
    //the sum performance
    double sumPerformance=0;
    //the random variable
    int p=0;
    //to indicate the range that the p will be in
    int range=0;
    //compute the sum performance
    for (int i=0;i<population;++i)
    {
        sumPerformance+=route1[i].GetPerformance();
    }
    //generate the random population after the natural selection
    for (int i=0;i<population;++i)
    {
        range=0;
        p=rand()%int(sumPerformance*(population-1));
        for (int j=0;j<population;++j)
        {
            range+=sumPerformance-route1[j].GetPerformance();
            if (p<range)
            {
                route2[i]=route1[j];
                break;
            }
        }
    }
}

//return the mapped city in the PMX function
int Map(const Route &route1, const Route &route2, const int &i, const int &left, const int &right)
{
    //get the position where the stop[i] of route2 in the segment [left, right) of route1
    int position=find(route1.GetStop()+left, route1.GetStop()+right, route2.GetStop(i))-route1.GetStop();
    //if not in this segment, it is the stop[i] of route2
    if (position==right)
    {
        return route2.GetStop(i);
    }
    //if in this segment, map stop[position] of route2
    else
    {
        return Map(route1, route2, position, left, right);
    }
}

//the PMX function
void PMX(const Route route1[], Route route2[], const int &n, const int &couples)
{
    //generate random segment
    int left=rand()%Route::GetCityNumber();
    int right=left+rand()%(Route::GetCityNumber()-left)+1;

    //copy the segment
    for (int i=left;i<right;++i)
    {
        route2[n].SetStop(i,route1[n].GetStop(i));
        route2[n+couples].SetStop(i,route1[n+couples].GetStop(i));
    }
    //map the other parts
    for (int i=0;i<left;++i)
    {
        route2[n].SetStop(i, Map(route1[n], route1[n+couples], i, left, right));
        route2[n+couples].SetStop(i, Map(route1[n+couples], route1[n], i, left, right));
    }
    for (int i=right;i<Route::GetCityNumber();++i)
    {
        route2[n].SetStop(i, Map(route1[n], route1[n+couples], i, left, right));
        route2[n+couples].SetStop(i, Map(route1[n+couples], route1[n], i, left, right));
    }
}

//return the mapped city in the revised PMX function
int RevisedMap(const Route &route1, const Route &route2, const int &i, const int &left, const int &right, int &position)
{
    //if not in this segment, it is the stop[i] of route2
    if (find(route1.GetStop()+left, route1.GetStop()+right, route2.GetStop(i))-route1.GetStop()==right)
    {
        return route2.GetStop(i);
    }
    //if in this segment, map stop[position] of route2
    else
    {
        ++position;
        return RevisedMap(route1, route2, position-1, left, right, position);
    }
}

//the revisedPMS function
void RevisedPMX(const Route route1[], Route route2[], const int &n, const int &couples)
{
    //generate random segment
    int left=rand()%Route::GetCityNumber();
    int right=left+rand()%(Route::GetCityNumber()-left)+1;

    //copy the segment
    for (int i=left;i<right;++i)
    {
        route2[n].SetStop(i,route1[n].GetStop(i));
        route2[n+couples].SetStop(i,route1[n+couples].GetStop(i));
    }
    //map the other parts
    int position1=left;
    int position2=left;
    for (int i=0;i<left;++i)
    {
        route2[n].SetStop(i, RevisedMap(route1[n], route1[n+couples], i, left, right, position1));
        route2[n+couples].SetStop(i, RevisedMap(route1[n+couples], route1[n], i, left, right, position2));
    }
    for (int i=right;i<Route::GetCityNumber();++i)
    {
        route2[n].SetStop(i, RevisedMap(route1[n], route1[n+couples], i, left, right, position1));
        route2[n+couples].SetStop(i, RevisedMap(route1[n+couples], route1[n], i, left, right, position2));
    }
}

//crossover under a probability with a random method
void Crossover(const Route* route1, Route* route2, const int &couples)
{
    for (int i=0;i<couples;++i)
    {
        if (rand()%100<60)
        {
            if (rand()%2==0)
            {
                PMX(route1,route2,i,couples);
            }
            else
            {
                RevisedPMX(route1,route2,i,couples);
            }
        }
        else
        {
            route2[i]=route1[i];
            route2[i+couples]=route1[i+couples];
        }
    }
}

//swap mutation function
void SwapMutate(Route &route)
{
    //generate the 2 random swap cities
    int i=rand()%Route::GetCityNumber();
    int j=(i+rand()%(Route::GetCityNumber()-1)+1)%Route::GetCityNumber();
    //swap the 2 cities
    int temp=route.GetStop(i);
    route.SetStop(i, route.GetStop(j));
    route.SetStop(j, temp);
}

//insert mutation function
void InsertMutate(Route &route)
{
    //generate the random mutate position and its destination
    int position=rand()%Route::GetCityNumber();
    int destination=(position+rand()%(Route::GetCityNumber()-1)+1)%Route::GetCityNumber();
    //move the position to its destination
    int temp=route.GetStop(position);
    if (position<destination)
    {
        for (int i=position;i<destination;++i)
        {
            route.SetStop(i, route.GetStop(i+1));
        }
    }
    else
    {
        for (int i=position;i>destination;--i)
        {
            route.SetStop(i, route.GetStop(i-1));
        }
    }
    route.SetStop(destination, temp);
}

//mutate under a probability with 1 random method
void Mutate(Route* route, const int &population)
{
    for (int i=0;i<population;++i)
    {
        if (rand()%100<10)
        {
            if (rand()%2==0)
            {
                SwapMutate(route[i]);
            }
            else
            {
                InsertMutate(route[i]);
            }
        }
    }
}

int main()
{
    //read the city information
    Route::SetCity();
    //ask user to input the population
    cout<<"\nPlease Enter the Population(must be an even number): "<<flush;
    int population;
    cin>>population;
    int couples=population/2;
    //the 2 generations of routes
    Route *route1=new Route[population];
    Route *route2=new Route[population];
    //the solution
    Route best;

    //ofstream outData;
    //outData.open("solution.txt");

    //to indicate if there is a improvement
    bool improvement=false;
    //to indicate the time when last solution was generated
    int lastTime=time(0);

    int startTime=lastTime;
    int currentTime=lastTime;
    int runTime=lastTime;
    int generation=1;
    while (currentTime-lastTime<300)
    {
        ++generation;
        improvement=false;
        Select(route1, route2, population);
        Crossover(route2, route1, couples);
        Mutate(route1, population);
        for (int i=0;i<population;i++)
        {
            route1[i].SetPerformance();
            if (route1[i].GetPerformance()<best.GetPerformance())
            {
                best=route1[i];
                improvement=true;
            }
        }
        currentTime=time(0);
        if (improvement==true)
        {
            cout<<best<<endl;
            lastTime=currentTime;
        }
        if ((currentTime-runTime)>9)
        {
            cout<<"Run Time: "<<currentTime-startTime<<"\tGeneration: "<<generation<<endl;
            runTime+=10;
        }
    }

    //output the solution
    cout<<"\nSolution:\n";
    cout<<best;

    delete []route1;
    delete []route2;
    Route::DeleteCity();

    return 0;
}
