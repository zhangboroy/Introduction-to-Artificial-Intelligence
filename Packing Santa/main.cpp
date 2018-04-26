#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include "crossover.h"
#include "mutation.h"
#include "selection.h"
#include "put.h"

using namespace std;

int main()
{
    //create a present array
    Present* gift=new Present[presentNumber];
    //read the present list file to the present array
    ReadPresentList(gift);

    //set the population
    int population=0;
    cout<<"Please enter the population (must be an even number): "<<flush;
    cin>>population;
    int couple=population/2;
    //set the end condition
    int endTurn=0;
    cout<<"After how many generations will it stop when no better result is found: "<<flush;
    cin>>endTurn;
    //set the cross over probability
    cout<<"Please enter the cross over probability (0~100): "<<flush;
    int crossOverProbability=0;
    cin>>crossOverProbability;
    //set the cross over method
    cout<<"Please enter the cross over method (0: PMX, 1: Revised PMX, 2: Order 1, 3: Random): "<<flush;
    int crossOverType=0;
    cin>>crossOverType;
    //set the mutation probability
    cout<<"Please enter the mutation probability (0~100): "<<flush;
    int mutationProbability=0;
    cin>>mutationProbability;
    //set the mutation method
    cout<<"Please enter the mutation method (0: Swap, 1: Scramble, 2: Random): "<<flush;
    int mutationType=0;
    cin>>mutationType;
    //set the initial generation type
    cout<<"Please choose random initial generation or reversed order generation (0: random, 1: in-order): "<<flush;
    int initialType=0;
    cin>>initialType;

    //create the chromosomes
    Chromosome* parents;
    Chromosome* children;
    parents=new Chromosome[population];
    children=new Chromosome[population];

    srand(time(0));

    if (initialType==0)
    {
        //randomize the first generation
        for (int i=0;i<population;++i)
        {
            children[i].Randomize();
        }
    }
    else
    {
        //create the reversed order and mutated chromosomes
        Mutate(children,population,0, 100);
    }

    //create a temp solution
    Solution solution;
    //the best solution
    Solution bestSolution;
    //the best performance
    unsigned long long int bestPerformance=999999999999;
    //the generation number
    int generation=1;
    //the signal for improvement
    bool improvement=false;

    stringstream stream;
    stream<<time(0)-1511337000;
    string fileTime=stream.str();
    string fileName="";
    ofstream outData;
    //loop for evolution, i is the timer
    int startTime=time(0);
    for (int i=0;i<endTurn;)
    {
        //reset the improvement signal
        improvement=false;
        cout<<"\nGeneration "<<generation<<":\n";
        //get the performance of the children generation
        for (int j=0;j<population;++j)
        {
            if (children[j].performance==0)
            {
                //put the number j chromosome into the box and get the solution
                solution.EasyPut(children[j], gift);
                //calculate the performance of the solution
                children[j].Evaluation(solution);
            }

            /*
            //put the number j chromosome into the box and get the solution
            solution.EasyPut(children[j], gift);
            //calculate the performance of the solution
            children[j].Evaluation(solution);
            */

            //if there is a better solution
            if (children[j].performance<bestPerformance)
            {
                //reset the timer
                i=0;
                //change the improvement signal
                improvement=true;
                //change the best performance
                bestPerformance=children[j].performance;
                //change the best solution
                bestSolution=solution;
                cout<<"Current Best Performance: "<<bestPerformance<<endl;

                if (generation>1)
                {
                    //output the performance
                    fileName="performance"+fileTime+".txt";
                    outData.open(fileName);
                    outData<<"time\tscore\tpopulation\tgeneration\tend turn\tcross over probability\tcross over type\tmutation probability\tmutation type\tinitial type\n";
                    outData<<time(0)-startTime<<'\t'<<bestPerformance<<'\t'<<population<<'\t'<<generation<<'\t'<<endTurn<<'\t'<<crossOverProbability<<'\t'
                           <<crossOverType<<'\t'<<mutationProbability<<'\t'<<mutationType<<'\t'<<initialType<<endl;
                    outData.close();

                    //output the result
                    fileName="output"+fileTime+".txt";
                    outData.open(fileName);
                    outData<<"PresentId,x1,y1,z1,x2,y2,z2,x3, ...,x8,y8,z8\n";
                    for (int i=0;i<presentNumber;++i)
                    {
                        outData<<i+1;
                        for (int j=0;j<24;++j)
                        {
                            outData<<","<<bestSolution.presentPosition[i*24+j]+1;
                        }
                        outData<<endl;
                    }
                    outData.close();
                }
            }
        }
        //if there is no better solution in this generation
        if (!improvement)
        {
            //timer increase
            ++i;
        }
        //select the children to get the parents
        Select(children, parents, population);
        //cross over the parents to get the new children
        Crossover(parents,children,couple,crossOverType,crossOverProbability);
        //the new children mutate
        Mutate(children,population,mutationType, mutationProbability);
        ++generation;
    }

    cout<<"\nFinal Best Performance: "<<bestPerformance<<endl;

    //output the performance
    fileName="performance"+fileTime+".txt";
    outData.open(fileName);
    outData<<"time\tscore\tpopulation\tgeneration\tend turn\tcross over probability\tcross over type\tmutation probability\tmutation type\tinitial type\n";
    outData<<time(0)-startTime<<'\t'<<bestPerformance<<'\t'<<population<<'\t'<<generation<<'\t'<<endTurn<<'\t'<<crossOverProbability<<'\t'
           <<crossOverType<<'\t'<<mutationProbability<<'\t'<<mutationType<<'\t'<<initialType<<endl;
    outData.close();

    //output the result
    fileName="output"+fileTime+".txt";
    outData.open(fileName);
    outData<<"PresentId,x1,y1,z1,x2,y2,z2,x3, ...,x8,y8,z8\n";
    for (int i=0;i<presentNumber;++i)
    {
        outData<<i+1;
        for (int j=0;j<24;++j)
        {
            outData<<","<<bestSolution.presentPosition[i*24+j]+1;
        }
        outData<<endl;
    }
    outData.close();

    delete parents;
    parents=0;
    delete children;
    children=0;
    delete gift;
    gift=0;
    delete []segment1;
    segment1=0;
    delete []segment2;
    segment2=0;

	return 0;
}
