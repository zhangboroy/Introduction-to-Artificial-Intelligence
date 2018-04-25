#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <iostream>
#include <list>

using namespace std;

class Grid
{
    int *v;
    bool *fix;
    list<int> *availableValues;
public:
    Grid();
    ~Grid()
    {
        delete []v;
        v=0;
        delete []fix;
        fix=0;
    }
    int GetV(const int &i,const int &j) const
    {
        return v[i*9+j];
    }
    void SetAvailableValues(const int &i, const int &vi);
    bool CSP() const;
    bool NaiveSolve(const int &i);
    bool SmartSolve();
};

ostream& operator<< (ostream &out, const Grid &grid);

#endif // GRID_H_INCLUDED
