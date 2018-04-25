#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

//the Ackley's function
double Ackley(const double x, const double y)
{
    return -20*exp(-0.2*sqrt(0.5*(x*x+y*y)))-exp(0.5*(cos(2*M_PI*x)+cos(2*M_PI*y)));
}

//the Hill Climbing function
void HillClimbing(ofstream &outData)
{
    //the position
    double x=(rand()%999+1)/100-5;
    double y=(rand()%999+1)/100-5;
    //the new position
    double x1=0;
    double y1=0;
    //the best Ackley value till now
    double result=Ackley(x,y);
    //the new Ackley value
    double f=0;
    //steps that haven't found a better value
    int step=0;
    while (step<100)
    {
        //generate the new position
        x1=(rand()%100/100-0.5)*0.1+x;
        y1=(rand()%100/100-0.5)*0.1+y;
        //calculate the new value
        f=Ackley(x1,y1);
        //if a better value, save it and the new position
        if (f<result)
        {
            result=f;
            x=x1;
            y=y1;
            step=0;
        }
        //if a same value, save the new position, but count the step
        else if (f==result)
        {
            x=x1;
            y=y1;
            ++step;
        }
        //if a worse value, discard the position, count the step
        else
        {
            ++step;
        }
    }
    //output the result
    outData<<"x="<<x<<"\ty="<<y<<"\tf="<<result<<endl;
}

//the Differential Evolution function
void DifferentialEvolution(ofstream &outData)
{
    //initialize the parameters for DifferentialEvolution
    //the population
    int np=200;
    //the crossover and recombination probability
    int cr=30;
    //the differential weight
    double f=0.8;
    //steps that haven't found a better value
    int step=0;
    //for the mutant vector
    int r0=0;
    int r1=0;
    int r2=0;
    //the mutant vector
    double vx=0;
    double vy=0;
    //the temp new generation
    double ux=0;
    double uy=0;
    //the random variable for crossover and recombination
    int u=0;
    //the temp Ackley value
    double ackley=0;
    //the best Ackley value till now
    double result=999;

    //initialize the population
    //the current generation
    double* x0=new double[np];
    double* y0=new double[np];
    //the new generation
    double* x1=new double[np];
    double* y1=new double[np];
    //the best position
    double x=0;
    double y=0;
    for (int i=0;i<np;++i)
    {
        x0[i]=0;
        y0[i]=0;
        x1[i]=(rand()%999+1)/100-5;
        y1[i]=(rand()%999+1)/100-5;

        ackley=Ackley(x1[i],y1[i]);
        if (ackley<result)
        {
            result=ackley;
        }
    }

    while (step<100)
    {
        ++step;

        //Set the current generation
        for (int i=0;i<np;++i)
        {
            x0[i]=x1[i];
            y0[i]=y1[i];
        }

        for (int i=0;i<np;++i)
        {
            //Generate integer random numbers r0, r1, r2
            r0=(i+1+rand()%(np-1))%np;
            do
            {
                r1=rand()%np;
            }
            while (r1==i || r1==r0);
            do
            {
                r2=rand()%np;
            }
            while (r2==i || r2==r0 || r2==r1);

            //Compute the mutant vector V
            vx=x0[r0]+f*(x0[r1]-x0[r2]);
            vy=y0[r0]+f*(y0[r1]-y0[r2]);

            //Compute the temp new generation
            u=rand()%100;
            if (u<cr)
            {
                ux=vx;
            }
            else
            {
                ux=x0[i];
            }
            u=rand()%100;
            if (u<cr)
            {
                uy=vy;
            }
            else
            {
                uy=y0[i];
            }
            ackley=Ackley(ux,uy);

            //Set the new generation
            if (ackley<Ackley(x0[i],y0[i]))
            {
                x1[i]=ux;
                y1[i]=uy;
                if (ackley<result)
                {
                    result=ackley;
                    x=x1[i];
                    y=y1[i];
                    step=0;
                }
            }
            else
            {
                x1[i]=x0[i];
                y1[i]=y0[i];
            }
        }
    }
    //output the result
    outData<<"x="<<x<<"\ty="<<y<<"\tf="<<result<<endl;
}

int main()
{
    srand(time(0));

    ofstream outData;
    outData.open("output.txt");
    outData<<"Hill Climbing:\n";
    for (int i=0;i<100;++i)
    {
        HillClimbing(outData);
    }
    outData<<"\nDifferential Evolution:\n";
    for (int i=0;i<100;++i)
    {
        DifferentialEvolution(outData);
    }
    outData.close();
    return 0;
}
