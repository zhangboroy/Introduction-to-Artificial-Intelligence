#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <iostream>
#include <cmath>
#include "box.h"
#include "robot.h"
#include "map.h"

using namespace std;

class State
{
    static bool finish;
    Box* box;
    Robot robot;
    State* parent;
    int cost;
    int estimatedCost;
    //key for sort
    unsigned __int64 key;
public:
    //generate an empty state
    State(const int &boxNumber);
    //generate from parent state
    State(const int &boxNumber, State &state);
    ~State()
    {
        parent=0;
        delete []box;
        box=0;
    }
    static bool GetFinish()
    {
        return finish;
    }
    static void SetFinish(const bool &a)
    {
        finish=a;
    }
    Box GetBox(const int &n) const
    {
        return box[n];
    }
    Robot GetRobot() const
    {
        return robot;
    }
    State* GetParent() const
    {
        return parent;
    }
    int GetCost() const
    {
        return cost;
    }
    int GetEstimatedCost() const
    {
        return estimatedCost;
    }
    unsigned __int64 GetKey() const
    {
        return key;
    }
    void SetBox(const int &n, const int &x1, const int &y1);
    void SetRobot(const int &x1, const int &y1);
    //set estimated cost by certain method
    void SetEstimatedCost(const char &method, const Map &map);
    //set the key for sort
    void SetKey(const Map &map);
    //sort the boxes by position
    void SortBox(const int &boxNumber);
    //check if there is a certain type of object at the position
    int CheckPosition(const int &x, const int &y, const char &object, const Map &map) const;

    //output the state
    template <typename Output>
    void Print(const Map &map, Output &output) const
    {
        for (int i=0;i<map.GetHeight();i++)
        {
            for (int j=0;j<map.GetWidth();j++)
            {
                if (CheckPosition(j,i,'w',map)!=-1)
                {
                    output<<'O';
                }
                else if (CheckPosition(j,i,'b',map)!=-1)
                {
                    output<<'B';
                }
                else if (CheckPosition(j,i,'r',map)!=-1)
                {
                    output<<'R';
                }
                else if (CheckPosition(j,i,'s',map)!=-1)
                {
                    output<<'S';
                }
                else
                {
                    output<<' ';
                }
            }
            output<<endl;
        }
        output<<endl;
    }

    //try to move the robot to certain direction
    State* MoveRobot(const int &direction, const Map &map);


    //compute the Manhattan Distance of 2 objects
    template <class Object1, class Object2>
    int ManhattanDistance(const Object1 &object1, const Object2 &object2) const
    {
        return abs(object1.GetX()-object2.GetX())+abs(object1.GetY()-object2.GetY());
    }
};

//set the comparison standard for open list
struct StateEstimatedCostCompare
{
    bool operator() (const State* state1, const State* state2)
    {
        return ((*state1).GetEstimatedCost()>(*state2).GetEstimatedCost());
    }
};

//set the comparison standard for closed list
struct StateCompare
{
    bool operator() (const State* state1, const State* state2)
    {
        return ((*state1).GetKey()>(*state2).GetKey());
    }
};

#endif // STATE_H_INCLUDED
