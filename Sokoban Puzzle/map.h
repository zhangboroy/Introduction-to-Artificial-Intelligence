#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <set>
#include <queue>
#include <stack>
#include "wall.h"
#include "storage.h"

using namespace std;

class State;
struct StateEstimatedCostCompare;
struct StateCompare;

class Map
{
    int boxNumber;
    int wallNumber;
    int width;
    int height;
    Wall* wall;
    Storage* storage;
    State* initialState;
public:
    Map();
    ~Map()
    {
        delete []storage;
        storage=0;
        delete []wall;
        wall=0;
        delete initialState;
        initialState=0;
    }
    int GetBoxNumber() const
    {
        return boxNumber;
    }
    int GetWallNumber() const
    {
        return wallNumber;
    }
    int GetWidth() const
    {
        return width;
    }
    int GetHeight() const
    {
        return height;
    }
    Wall GetWall(const int &n) const
    {
        return wall[n];
    }
    Storage GetStorage(const int &n) const
    {
        return storage[n];
    }
    State* GetInitialState() const
    {
        return initialState;
    }
    //ask the user to solve the map
    State* ManualSolve(queue<State*> &openList, set<State*, StateCompare> &closedList) const;
    //solve the map by BreadthFirst search
    State* BreadthFirst(queue<State*> &openList, set<State*, StateCompare> &closedList) const;
    //solve the map by DepthFirst search
    State* DepthFirst(stack<State*> &openList, set<State*, StateCompare> &closedList) const;
    //solve the map by Heuristic search
    State* Heuristic(priority_queue<State*, vector<State*>, StateEstimatedCostCompare> &openList, set<State*, StateCompare> &closedList, const char &method) const;
    //solve the map by A* search
    State* AStar(priority_queue<State*, vector<State*>, StateEstimatedCostCompare> &openList, set<State*, StateCompare> &closedList, const char &method) const;
    //output the solution
    void OutputSolution(State* goalState) const;
};

#endif // MAP_H_INCLUDED
