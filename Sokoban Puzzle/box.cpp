#include "box.h"
#include "map.h"
#include "state.h"

Box::Box()
{
    x=0;
    y=0;
}

void Box::Set(const int &x1, const int &y1)
{
    x=x1;
    y=y1;
}

//first row, then column
bool Box::operator<(const Box &box) const
{
    if (y<box.GetY())
    {
        return true;
    }
    else if (y==box.GetY() && x<box.GetX())
    {
        return true;
    }
    else
    {
        return false;
    }
}

//check the position of the box or near the box
bool Box::Check(const int &direction, const Map &map, const State &state) const
{
    //check if the box is at the storage
    if (direction==0)
    {
        return (state.CheckPosition(x,y,'s',map)==1);
    }
    //check if there is an obstacle at the top of the box
    else if (direction==1)
    {
        return (state.CheckPosition(x,y-1,'w',map)==1 || state.CheckPosition(x,y-1,'b',map)!=-1);
    }
    //check if there is an obstacle to the right of the box
    else if (direction==2)
    {
        return (state.CheckPosition(x+1,y,'w',map)==1 || state.CheckPosition(x+1,y,'b',map)!=-1);
    }
    //check if there is an obstacle at the bottom of the box
    else if (direction==3)
    {
        return (state.CheckPosition(x,y+1,'w',map)==1 || state.CheckPosition(x,y+1,'b',map)!=-1);
    }
    //check if there is an obstacle to the left of the box
    else if (direction==4)
    {
        return (state.CheckPosition(x-1,y,'w',map)==1 || state.CheckPosition(x-1,y,'b',map)!=-1);
    }
}
