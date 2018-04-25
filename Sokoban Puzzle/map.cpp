#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <list>
#include "map.h"
#include "state.h"

using namespace std;

Map::Map()
{
    boxNumber=0;
    wallNumber=0;
    width=0;
    height=0;
    wall=0;
    storage=0;
    initialState=0;

    //ask user to input the map file name
    string line;
    cout<<"Please Enter the Map File Name: "<<flush;
    getline(cin,line);

    //read the parameters of the map
    ifstream inData;
    inData.open(line.c_str());

    while (getline(inData,line))
    {
        height++;
        if (line.size()>width)
        {
            width=line.size();
        }
        for (int i=0;i<line.size();i++)
        {
            if (line[i]=='B')
            {
                boxNumber++;
            }
            else if (line[i]=='O')
            {
                wallNumber++;
            }
        }
    }

    //generate the objects in the map
    storage=new Storage[boxNumber];
    wall=new Wall[wallNumber];
    initialState=new State(boxNumber);

    //read the position of the objects
    inData.clear();
    inData.seekg(0);
    //index of the boxes
    int b=0;
    //index of the walls
    int w=0;
    //index of the storages
    int s=0;

    for (int i=0;i<height;i++)
    {
        getline(inData,line);
        for (int j=0;j<line.size();j++)
        {
            if (line[j]=='B')
            {
                (*initialState).SetBox(b,j,i);
                b++;
            }
            else if (line[j]=='O')
            {
                wall[w].Set(j,i);
                w++;
            }
            else if (line[j]=='S')
            {
                storage[s].Set(j,i);
                s++;
            }
            else if (line[j]=='R')
            {
                (*initialState).SetRobot(j,i);
            }
        }
    }
    inData.close();

    (*initialState).SetKey(*this);

    //output the parameters of the map
    cerr<<"\nNumber of Boxes: "<<boxNumber<<endl;
    cerr<<"Number of Walls: "<<wallNumber<<endl;
    cerr<<"Map Width: "<<width<<endl;
    cerr<<"Map Height: "<<height<<endl<<endl;
    //output the map
    (*initialState).Print(*this, cout);
}

//ask the user to solve the map
State* Map::ManualSolve(queue<State*> &openList, set<State*, StateCompare> &closedList) const
{
    char input;
    State* currentState=GetInitialState();
    State* newState=0;
    do
    {
        cout<<"Please move the robot: "<<flush;
        cin>>input;
        //try to move the robot up
        if (input=='w')
        {
            newState=(*currentState).MoveRobot(1, *this);
            if (newState!=currentState)
            {
                currentState=newState;
                closedList.insert(currentState);
                (*currentState).Print(*this, cout);
            }
        }
        //try to move the robot right
        else if (input=='d')
        {
            newState=(*currentState).MoveRobot(2, *this);
            if (newState!=currentState)
            {
                currentState=newState;
                closedList.insert(currentState);
                (*currentState).Print(*this, cout);
            }
        }
        //try to move the robot down
        else if (input=='s')
        {
            newState=(*currentState).MoveRobot(3, *this);
            if (newState!=currentState)
            {
                currentState=newState;
                closedList.insert(currentState);
                (*currentState).Print(*this, cout);
            }
        }
        //try to move the robot left
        else if (input=='a')
        {
            newState=(*currentState).MoveRobot(4, *this);
            if (newState!=currentState)
            {
                currentState=newState;
                closedList.insert(currentState);
                (*currentState).Print(*this, cout);
            }
        }
    }
    while (input!='q' && State::GetFinish()==false);
    return currentState;
}

//solve the map by BreadthFirst search
State* Map::BreadthFirst(queue<State*> &openList, set<State*, StateCompare> &closedList) const
{
    //reset the search start time and steps
    int startTime=time(0);
    int lastTime=startTime;
    int step=0;
    int tempTime=0;

    //put the initial state into both open list and closed list
    openList.push(GetInitialState());
    closedList.insert(GetInitialState());

    //set the iterator for closed list
    set<State*, StateCompare>::iterator current=closedList.begin();

    State* currentState=0;
    State* newState=0;

    while (!openList.empty())
    {
        //pick the first state out of the open list
        currentState=openList.front();
        //closedList.push_front(currentState);
        openList.pop();

        //output progress every 10 seconds
        tempTime=time(0);
        if (tempTime-lastTime>9)
        {
            cout<<"Run Time: "<<tempTime-startTime<<" seconds\t";
            lastTime=tempTime;
            cout<<"Steps Examined: "<<step<<endl;
        }

        //check all 4 directions of the robot
        for (int i=1;i<5;i++)
        {
            //try to move the robot to i direction
            newState=(*currentState).MoveRobot(i, *this);

            //check if the robot can move to i direction
            if (newState!=currentState)
            {
                //if it is the goal state
                if (State::GetFinish()==true)
                {
                    //output the total time
                    cout<<"Total Search Time: "<<time(0)-startTime<<endl;
                    //output the total steps
                    step++;
                    cout<<"Total Steps Examined: "<<step<<endl;

                    //put the goal state into closed list
                    closedList.insert(newState);
                    return newState;
                }
                //if it is not the goal state
                else
                {
                    //if it has been generated before
                    if (closedList.find(newState)!=closedList.end())
                    {
                        //delete the new state
                        delete newState;
                        newState=0;
                    }
                    //if it has not been generated before
                    else
                    {
                        //put it to the end of open list
                        openList.push(newState);
                        //put it into the closed list
                        closedList.insert(newState);
                        step++;
                    }
                }
            }
        }
    }
    return 0;
}

//solve the map by DepthFirst search
State* Map::DepthFirst(stack<State*> &openList, set<State*, StateCompare> &closedList) const
{
    //reset the search start time and steps
    int startTime=time(0);
    int lastTime=startTime;
    int step=0;
    int tempTime=0;

    //put the initial state into both open list and closed list
    openList.push(GetInitialState());
    closedList.insert(GetInitialState());

    //set the iterator for closed list
    set<State*, StateCompare>::iterator current=closedList.begin();

    State* currentState=0;
    State* newState=0;

    while (!openList.empty())
    {
        //pick the first state out of the open list
        currentState=openList.top();
        //closedList.push_front(currentState);
        openList.pop();

        //output progress every 10 seconds
        tempTime=time(0);
        if (tempTime-lastTime>9)
        {
            cout<<"Run Time: "<<tempTime-startTime<<" seconds\t";
            lastTime=tempTime;
            cout<<"Steps Examined: "<<step<<endl;
        }

        //check all 4 directions of the robot
        for (int i=1;i<5;i++)
        {
            //try to move the robot to i direction
            newState=(*currentState).MoveRobot(i, *this);

            //check if the robot can move to i direction
            if (newState!=currentState)
            {
                //if it is the goal state
                if (State::GetFinish()==true)
                {
                    //output the total time
                    cout<<"Total Search Time: "<<time(0)-startTime<<endl;
                    //output the total steps
                    step++;
                    cout<<"Total Steps Examined: "<<step<<endl;

                    //put the goal state into closed list
                    closedList.insert(newState);
                    return newState;
                }
                //if it is not the goal state
                else
                {
                    //if it has been generated before
                    if (closedList.find(newState)!=closedList.end())
                    {
                        //delete the new state
                        delete newState;
                        newState=0;
                    }
                    //if it has not been generated before
                    else
                    {
                        //put it to the front of open list
                        openList.push(newState);
                        //put it into the closed list
                        closedList.insert(newState);
                        step++;
                    }
                }
            }
        }
    }
    return 0;
}

//solve the map by Heuristic search
State* Map::Heuristic(priority_queue<State*, vector<State*>, StateEstimatedCostCompare> &openList, set<State*, StateCompare> &closedList, const char &method) const
{
    //reset the search start time and steps
    int startTime=time(0);
    int lastTime=startTime;
    int step=0;
    int tempTime=0;

    //set the estimated cost for the initial state
    (*initialState).SetEstimatedCost(method, *this);
    //put the initial state into both open list and closed list
    openList.push(GetInitialState());
    closedList.insert(GetInitialState());

    //set the iterator for closed list
    set<State*, StateCompare>::iterator current=closedList.begin();

    State* currentState=0;
    State* newState=0;

    while (!openList.empty())
    {
        //pick the first state out of the open list
        currentState=openList.top();
        openList.pop();

        //output progress every 10 seconds
        tempTime=time(0);
        if (tempTime-lastTime>9)
        {
            cout<<"Run Time: "<<tempTime-startTime<<" seconds\t";
            lastTime=tempTime;
            cout<<"Steps Examined: "<<step<<endl;
        }

        //check all 4 directions of the robot
        for (int i=1;i<5;i++)
        {
            //try to move the robot to i direction
            newState=(*currentState).MoveRobot(i, *this);

            //check if the robot can move to i direction
            if (newState!=currentState)
            {
                //if it is the goal state
                if (State::GetFinish()==true)
                {
                    //output the total time
                    cout<<"Total Search Time: "<<time(0)-startTime<<endl;
                    //output the total steps
                    step++;
                    cout<<"Total Steps Examined: "<<step<<endl;

                    //put the goal state into closed list
                    closedList.insert(newState);
                    return newState;
                }
                //if it is not the goal state
                else
                {
                    //check if it has been generated before
                    if (closedList.find(newState)!=closedList.end())
                    {
                        //delete the new state
                        delete newState;
                        newState=0;
                    }
                    //if it has not been generated before
                    else
                    {
                        //set the estimated cost for the new state
                        (*newState).SetEstimatedCost(method, *this);
                        //put it into the open list
                        openList.push(newState);
                        //put it into the closed list
                        closedList.insert(newState);
                        step++;
                    }
                }
            }
        }
    }
    return 0;
}

//solve the map by A* search
State* Map::AStar(priority_queue<State*, vector<State*>, StateEstimatedCostCompare> &openList, set<State*, StateCompare> &closedList, const char &method) const
{
    //reset the search start time and steps
    int startTime=time(0);
    int lastTime=startTime;
    int step=0;
    int tempTime=0;

    //set the estimated cost for the initial state
    (*initialState).SetEstimatedCost(method, *this);
    //put the initial state into open list
    openList.push(GetInitialState());

    //set the iterator for closed list
    set<State*, StateCompare>::iterator current=closedList.begin();

    State* currentState=0;
    State* newState=0;

    while (!openList.empty())
    {
        //pick the first state out of the open list and put into the closed list
        currentState=openList.top();
        closedList.insert(currentState);
        openList.pop();

        //check if it is the goal state
        State::SetFinish(true);
        for (int i=0;i<GetBoxNumber();i++)
        {
            if (!(*currentState).GetBox(i).Check(0, *this, *currentState))
            {
                State::SetFinish(false);
                break;
            }
        }

        if (State::GetFinish())
        {
            //output the total time
            cout<<"Total Search Time: "<<time(0)-startTime<<endl;
            //output the total steps
            cout<<"Total Steps Examined: "<<step<<endl;
            return currentState;
        }

        //output progress every 10 seconds
        tempTime=time(0);
        if (tempTime-lastTime>9)
        {
            cout<<"Run Time: "<<tempTime-startTime<<" seconds\t";
            lastTime=tempTime;
            cout<<"Steps Examined: "<<step<<endl;
        }

        //check all 4 directions of the robot
        for (int i=1;i<5;i++)
        {
            //try to move the robot to i direction
            newState=(*currentState).MoveRobot(i, *this);

            //check if the robot can move to i direction
            if (newState!=currentState)
            {
                //check if it has been generated before
                if (closedList.find(newState)!=closedList.end())
                {
                    //delete the new state
                    delete newState;
                    newState=0;
                }
                //if it has not been generated before
                else
                {
                    //set the estimated cost for the new state
                    (*newState).SetEstimatedCost(method, *this);
                    //put it into the open list
                    openList.push(newState);
                    step++;
                }
            }
        }
    }
    return 0;
}

//output the solution
void Map::OutputSolution(State* goalState) const
{
    //create a state list for the solution
    list<State*> solution;

    //from the goal state, put every parent state to the front of the solution list
    do
    {
        solution.push_front(goalState);
        goalState=(*goalState).GetParent();
    }
    while (goalState!=0);

    //from the initial state, output every state
    ofstream outData;
    outData.open("solution.txt");
    for (list<State*>::iterator current=solution.begin();current!=solution.end();current++)
    {
        (**current).Print(*this,outData);
    }

    outData.close();
    //clear the solution list
    solution.clear();
}
