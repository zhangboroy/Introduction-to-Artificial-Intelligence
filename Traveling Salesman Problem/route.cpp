#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "route.h"

int Route::cityNumber=0;
City* Route::city=0;

ostream& operator<<(ostream& out, const Route &route)
{
    out<<"Route:\n";
    for (int i=0;i<Route::cityNumber;++i)
    {
        out<<route.GetStop(i)+1<<' ';
    }
    out<<endl;
    out<<"Total Distance: "<<route.GetPerformance()<<endl;
    return out;
}

//read the city information
void Route::SetCity()
{
    srand(time(0));
    //ask the user to input the map file name
    cout<<"Please Enter the Name of the Map File: "<<flush;
    string fileName="";
    getline(cin,fileName);

    //read the map file
    ifstream inData;
    inData.open(fileName.c_str());
    for (int i=0;i<4;i++)
    {
        getline(inData,fileName);
    }
    inData>>fileName>>fileName;
    //read the number of cities
    inData>>cityNumber;
    for (int i=0;i<3;i++)
    {
        getline(inData,fileName);
    }
    //read the coordinate of the cities
    double x=0;
    double y=0;
    city=new City[cityNumber];
    for (int i=0;i<cityNumber;i++)
    {
        inData>>x>>x>>y;
        city[i].Set(x,y);
        cout<<"city"<<i+1<<'\t'<<city[i].GetX()<<'\t'<<city[i].GetY()<<endl;
    }
    inData.close();
}

Route::Route()
{
    //generate the random route
    stop=new int[cityNumber];
    for (int i=0;i<cityNumber;++i)
    {
        stop[i]=i;
    }
    random_shuffle(stop, stop+cityNumber);

    //calculate the performance
    performance=city[stop[0]]-city[stop[cityNumber-1]];
    for (int i=1;i<cityNumber;++i)
    {
        performance+=city[stop[i]]-city[stop[i-1]];
    }
}

Route::Route(const Route &route)
{
    stop=new int[cityNumber];
    for (int i=0;i<cityNumber;i++)
    {
        stop[i]=route.GetStop(i);
    }
    performance=route.GetPerformance();
}

void Route::operator=(const Route &route)
{
    for (int i=0;i<cityNumber;i++)
    {
        stop[i]=route.GetStop(i);
    }
    performance=route.GetPerformance();
}

void Route::SetPerformance()
{
    performance=city[stop[0]]-city[stop[cityNumber-1]];
    for (int i=1;i<cityNumber;++i)
    {
        performance+=city[stop[i]]-city[stop[i-1]];
    }
}
