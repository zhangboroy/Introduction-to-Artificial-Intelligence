#ifndef ROUTE_H_INCLUDED
#define ROUTE_H_INCLUDED

#include "city.h"

using namespace std;

class Route
{
    static int cityNumber;
    static City* city;
    int* stop;
    double performance;
public:
    static int GetCityNumber()
    {
        return cityNumber;
    }
    //read the city information
    static void SetCity();
    static void DeleteCity()
    {
        delete []city;
    }
    Route();
    Route(const Route &route);
    ~Route()
    {
        delete []stop;
    }
    void operator=(const Route &route);
    int* GetStop() const
    {
        return stop;
    }
    int GetStop(const int &n) const
    {
        return stop[n];
    }
    double GetPerformance() const
    {
        return performance;
    }
    void SetStop(const int &n, const int &s)
    {
        stop[n]=s;
    }
    void SetPerformance();
    friend ostream& operator<<(ostream& out, const Route &route);
};

ostream& operator<<(ostream& out, const Route &route);

#endif // ROUTE_H_INCLUDED
