#include <iostream>
#include <algorithm>
#include "state.h"
#include "map.h"

using namespace std;

bool State::finish=false;

//generate an empty state
State::State(const int &boxNumber)
{
    box=new Box[boxNumber];
    parent=0;
    cost=0;
    estimatedCost=0;
    key=0;
}

//generate from parent state
State::State(const int &boxNumber, State &state)
{
    box=new Box[boxNumber];
    for (int i=0;i<boxNumber;i++)
    {
        box[i]=state.GetBox(i);
    }
    robot=state.GetRobot();
    parent=&state;
    cost=state.GetCost()+1;
    estimatedCost=0;
    key=0;
}

void State::SetBox(const int &n, const int &x1, const int &y1)
{
    box[n].Set(x1,y1);
}

void State::SetRobot(const int &x1, const int &y1)
{
    robot.Set(x1,y1);
}

//set estimated cost by certain method
void State::SetEstimatedCost(const char &method, const Map &map)
{
    //use sum Manhattan Distance as the estimated cost
    if (method=='M')
    {
        //Manhattan Distance of box[i]
        int distanceI=0;
        //Manhattan Distance of box[i] and storage[j]
        int distanceIJ=0;
        //compute sum Manhattan Distance
        for (int i=0;i<map.GetBoxNumber();i++)
        {
            distanceI=map.GetHeight()+map.GetWidth();
            for (int j=0;j<map.GetBoxNumber();j++)
            {
                //compute Manhattan Distance of box[i] and storage[j]
                distanceIJ=ManhattanDistance(box[i], map.GetStorage(j));
                //compute Manhattan Distance of box[i]
                if (distanceIJ==0)
                {
                    distanceI=distanceIJ;
                    break;
                }
                else if (distanceIJ<distanceI)
                {
                    distanceI=distanceIJ;
                }
            }
            estimatedCost+=distanceI;
        }
    }
    //use min sum Manhattan Distance of pairs of box and storage as well as Manhattan Distance from the robot to its nearest box as the estimated cost
    else if (method=='G')
    {
        //compute Manhattan Distance between every box and storage
        //as well as Manhattan Distance from the robot to its nearest box
        int *distance=new int[map.GetBoxNumber()*map.GetBoxNumber()];
        int tempRobotDistance=0;
        int minRobotDistance=map.GetHeight()+map.GetWidth();
        for (int i=0;i<map.GetBoxNumber();i++)
        {
            tempRobotDistance=ManhattanDistance(robot, box[i])-1;
            if (tempRobotDistance<minRobotDistance)
            {
                minRobotDistance=tempRobotDistance;
            }
            for (int j=0;j<map.GetBoxNumber();j++)
            {
                distance[i*map.GetBoxNumber()+j]=ManhattanDistance(box[i], map.GetStorage(j));
            }
        }

        //generate for permutation index
        int *num=new int[map.GetBoxNumber()];
        for (int i=0;i<map.GetBoxNumber();i++)
        {
            num[i]=i;
        }

        //compute the min sum Manhattan Distance
        estimatedCost=(map.GetHeight()+map.GetWidth())*map.GetBoxNumber();
        int tempSumDistance=0;
        do
        {
            tempSumDistance=0;
            for (int i=0;i<map.GetBoxNumber();i++)
            {
                tempSumDistance+=distance[i*map.GetBoxNumber()+num[i]];
            }
            if (tempSumDistance<estimatedCost)
            {
                estimatedCost=tempSumDistance;
            }
        }
        while (next_permutation(num,num+map.GetBoxNumber()));
        estimatedCost+=minRobotDistance;

        //delete the dynamic arrays
        delete num;
        num=0;
        delete distance;
        distance=0;
    }
    //Manhattan Distance to push the nearest box(not at storage) to its nearest storage
    else if (method=='m')
    {
        //the index of the nearest box
        int nearestBox=0;
        int tempRobotDistance=0;
        estimatedCost=map.GetHeight()+map.GetWidth();
        //Manhattan Distance between the nearest box and its nearest storage
        int storageDistance=estimatedCost;
        //determine the nearest box and its distance
        for (int i=0;i<map.GetBoxNumber();i++)
        {
            if (!box[i].Check(0, map, *this))
            {
                tempRobotDistance=ManhattanDistance(robot, box[i])-1;
                if (tempRobotDistance<estimatedCost)
                {
                    nearestBox=i;
                    estimatedCost=tempRobotDistance;
                }
            }
        }
        //Manhattan Distance between the nearest box and storage[i]
        int distanceI=0;
        //compute the distance between the nearest box and its nearest storage
        for (int i=0;i<map.GetBoxNumber();i++)
        {
            distanceI=ManhattanDistance(box[nearestBox], map.GetStorage(i));
            if (distanceI<storageDistance)
            {
                storageDistance=distanceI;
            }
        }
        estimatedCost+=storageDistance;
    }
    //A* estimated cost
    else if (method=='A')
    {
        SetEstimatedCost('G', map);
        estimatedCost+=cost;
    }
}

//set the key for sort
void State::SetKey(const Map &map)
{
    key=(robot.GetX()+robot.GetY()*map.GetWidth())*pow(map.GetWidth()*map.GetHeight(),map.GetBoxNumber());
    for (int i=0;i<map.GetBoxNumber();i++)
    {
        key+=(box[i].GetX()+box[i].GetY()*map.GetWidth())*pow(map.GetWidth()*map.GetHeight(),i);
    }
}

//sort the boxes by position
void State::SortBox(const int &boxNumber)
{
    sort(box,box+boxNumber);
}

//check if there is a certain type of object at the position
int State::CheckPosition(const int &x, const int &y, const char &object, const Map &map) const
{
    //check if there is a storage at the position
    if (object=='s')
    {
        for (int i=0;i<map.GetBoxNumber();i++)
        {
            if (map.GetStorage(i).GetX()==x && map.GetStorage(i).GetY()==y)
            {
                return 1;
            }
        }
        return -1;
    }
    //check if there is a wall at the position
    else if (object=='w')
    {
        for (int i=0;i<map.GetWallNumber();i++)
        {
            if (map.GetWall(i).GetX()==x && map.GetWall(i).GetY()==y)
            {
                return 1;
            }
        }
        return -1;
    }
    //check if there is a box at the position
    else if (object=='b')
    {
        for (int i=0;i<map.GetBoxNumber();i++)
        {
            if (GetBox(i).GetX()==x && GetBox(i).GetY()==y)
            {
                return i;
            }
        }
        return -1;
    }
    //check if there is a robot at the position
    else if (object=='r')
    {
        if (GetRobot().GetX()==x && GetRobot().GetY()==y)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
}

//try to move the robot to certain direction
State* State::MoveRobot(const int &direction, const Map &map)
{
    //transfer the direction into coordinate
    int x1=0;
    int y1=0;
    if (direction==1)
    {
        y1=-1;
    }
    else if (direction==2)
    {
        x1=1;
    }
    else if (direction==3)
    {
        y1=1;
    }
    else if (direction==4)
    {
        x1=-1;
    }

    //check if there is a box at the direction
    int targetBox=CheckPosition(GetRobot().GetX()+x1, GetRobot().GetY()+y1, 'b', map);
    //if there is a box
    if (targetBox!=-1)
    {
        //check if there is something at the direction of the box
        if (box[targetBox].Check(direction, map, *this))
        {
            return this;
        }
        else
        {
            if (CheckPosition(box[targetBox].GetX()+x1, box[targetBox].GetY()+y1, 's', map)==-1)
            {
                //check every position next to the box's new position
                int up=CheckPosition(box[targetBox].GetX()+x1, box[targetBox].GetY()+y1-1, 'w', map);
                int right=CheckPosition(box[targetBox].GetX()+x1+1, box[targetBox].GetY()+y1, 'w', map);
                int down=CheckPosition(box[targetBox].GetX()+x1, box[targetBox].GetY()+y1+1, 'w', map);
                int left=CheckPosition(box[targetBox].GetX()+x1-1, box[targetBox].GetY()+y1, 'w', map);
                bool dead=false;

                //check if a dead state
                if (up==1)
                {
                    if (left==1 || right==1)
                    {
                        dead=true;
                    }
                }
                else if (down==1)
                {
                    if (left==1 || right==1)
                    {
                        dead=true;
                    }
                }

                if (dead)
                {
                    return this;
                }
            }

            //generate a new state
            State* newState;
            newState=new State(map.GetBoxNumber(),*this);

            //set the position of the robot and the target box of the new state
            (*newState).SetRobot(robot.GetX()+x1,robot.GetY()+y1);
            (*newState).SetBox(targetBox, box[targetBox].GetX()+x1, box[targetBox].GetY()+y1);

            //check if it is the goal state
            State::SetFinish(true);
            for (int i=0;i<map.GetBoxNumber();i++)
            {
                if (!(*newState).GetBox(i).Check(0, map, *newState))
                {
                    State::SetFinish(false);
                    break;
                }
            }

            //sort the boxes
            (*newState).SortBox(map.GetBoxNumber());
            (*newState).SetKey(map);

            return newState;
        }
    }
    //check if there is a wall at the direction
    else if (CheckPosition(GetRobot().GetX()+x1, GetRobot().GetY()+y1, 'w', map)==-1)
    {
        State* newState;
        newState=new State(map.GetBoxNumber(),*this);
        (*newState).SetRobot(robot.GetX()+x1,robot.GetY()+y1);
        (*newState).SetKey(map);

        return newState;
    }
    else
    {
        return this;
    }
}
