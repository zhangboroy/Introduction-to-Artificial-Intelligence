#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include "map.h"
#include "state.h"

using namespace std;

//Print the menu
void PrintMenu()
{
    cout<<"1 Play this map"<<endl;
    cout<<"2 Solve this map by Breadth-first Search"<<endl;
    cout<<"3 Solve this map by Depth-first Search"<<endl;
    cout<<"4 Solve this map by Manhattan Distance Heuristic Search"<<endl;
    cout<<"5 Solve this map by Greedy-best Search"<<endl;
    cout<<"6 Solve this map by A* Search"<<endl;
    cout<<"0 Exit"<<endl<<endl;
    cout<<"Your Choice: "<<flush;
}

//Ask the user to choose from the main menu
int MainMenu()
{
    int choice=-1;
    do
    {
        cin.clear();
        PrintMenu();
        cin>>choice;
    }
    while (choice<0 || choice>6);
    return choice;
}

//delete the states in open list
void Clean(queue<State*> &openList)
{
    State* temp=0;
    while (!openList.empty())
    {
        temp=openList.front();
        delete temp;
        temp=0;
        openList.pop();
    }
}

//delete the states in open list
void Clean(stack<State*> &openList)
{
    State* temp=0;
    while (!openList.empty())
    {
        temp=openList.top();
        delete temp;
        temp=0;
        openList.pop();
    }
}

//delete the states in open list
void Clean(priority_queue<State*, vector<State*>, StateEstimatedCostCompare> &openList)
{
    State* temp=0;
    while (!openList.empty())
    {
        temp=openList.top();
        delete temp;
        temp=0;
        openList.pop();
    }
}

//delete the states in closed list
void Clean(set<State*, StateCompare> &closedList, const Map &map)
{
    State* temp=0;
    for (set<State*, StateCompare>::iterator i=closedList.begin();i!=closedList.end();++i)
    {
        if (*i!=0)
        {
            temp=*i;
            delete temp;
            temp=0;
        }
    }
    closedList.clear();
}

int main()
{
    try
    {
        Map map;
        //the goal state
        State* goalState=0;
        //the closed list
        set<State*, StateCompare> closedList;

        //Ask the user to choose from the main menu
        int choice=MainMenu();

        //ask the user to solve the map
        if (choice==1)
        {
            cout<<"Please play the game"<<endl;
            queue<State*> openList;
            goalState=map.ManualSolve(openList, closedList);
        }
        //solve the map by BreadthFirst search
        else if (choice==2)
        {
            cout<<"Start Breadth-first Search"<<endl;
            queue<State*> openList;
            goalState=map.BreadthFirst(openList, closedList);
            //delete the states in open list
            Clean(openList);
        }
        //solve the map by DepthFirst search
        else if (choice==3)
        {
            cout<<"Start Depth-first Search"<<endl;
            stack<State*> openList;
            goalState=map.DepthFirst(openList, closedList);
            //delete the states in open list
            Clean(openList);
        }
        //solve the map by Manhattan Distance Heuristic search
        else if (choice==4)
        {
            cout<<"Start Manhattan Distance Heuristic Search"<<endl;
            priority_queue<State*, vector<State*>, StateEstimatedCostCompare> openList;
            goalState=map.Heuristic(openList, closedList, 'M');
            //delete the states in open list
            Clean(openList);
        }
        //solve the map by Greedy-best search
        else if (choice==5)
        {
            cout<<"Start Greedy-best Search"<<endl;
            priority_queue<State*, vector<State*>, StateEstimatedCostCompare> openList;
            goalState=map.Heuristic(openList, closedList, 'G');
            //delete the states in open list
            Clean(openList);
        }
        //solve the map by A* search
        else if (choice==6)
        {
            cout<<"Start A* Search"<<endl;
            priority_queue<State*, vector<State*>, StateEstimatedCostCompare> openList;
            goalState=map.AStar(openList, closedList, 'A');
            //delete the states in open list
            Clean(openList);
        }

        //if the map is solved
        if (State::GetFinish()==true)
        {
            cout<<"Map Solved!"<<endl;
            //output the solution
            map.OutputSolution(goalState);
        }
        //if the map is not solved
        else
        {
            cout<<"No solution!"<<endl;
        }

        //delete the states in closed list
        Clean(closedList, map);
        return 0;
    }
    catch (const bad_alloc &error)
    {
        cout<<"Run out of memory!\n";
        return 0;
    }
}
