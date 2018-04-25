#include <stack>
#include "state.h"

static stack<State*> closedList;

bool Performance::operator< (const Performance &performance) const
{
    if (four<performance.four)
    {
        return true;
    }
    else if (four>performance.four)
    {
        return false;
    }
    else if (four==0)
    {
        if (total<performance.total)
        {
            return true;
        }
        else if (total>performance.total)
        {
            return false;
        }
        else
        {
            for (int i=3;i>-1;--i)
            {
                if (number[i]<performance.number[i])
                {
                    return true;
                }
                else if (number[i]>performance.number[i])
                {
                    return false;
                }
            }
            return (step>performance.step);
        }
    }
    else
    {
        return (step>performance.step);
    }
}

bool Performance::operator> (const Performance &performance) const
{
    if (four>performance.four)
    {
        return true;
    }
    else if (four<performance.four)
    {
        return false;
    }
    else if (four==0)
    {
        if (total>performance.total)
        {
            return true;
        }
        else if (total<performance.total)
        {
            return false;
        }
        else
        {
            for (int i=3;i>-1;--i)
            {
                if (number[i]>performance.number[i])
                {
                    return true;
                }
                else if (number[i]<performance.number[i])
                {
                    return false;
                }
            }
            return (step<performance.step);
        }
    }
    else
    {
        return (step<performance.step);
    }
}

State::State()
{
    parent=0;
    player=false;
    place=new char[height*width];
    for (int i=0;i<height*width;++i)
    {
        place[i]='.';
    }
    step=0;
}

State::State(State &state)
{
    parent=&state;
    player=1-state.GetPlayer();
    place=new char[height*width];
    for (int i=0;i<height*width;++i)
    {
        place[i]=state.GetPlace(i);
    }
    step=state.GetStep()+1;
}

int State::DropDisc(const int &column)
{
    int y=-1;
    for (;y<height-1 && place[(y+1)*width+column-1]=='.';++y)
    {
    }
    if (y>-1)
    {
        if (player)
        {
            place[y*width+column-1]='X';
        }
        else
        {
            place[y*width+column-1]='O';
        }
    }
    return y;
}

Performance State::HorizontalChoice(const bool &player1) const
{
    Performance performance1;

    char marker=' ';
    if (player1)
    {
        marker='O';
    }
    else
    {
        marker='X';
    }

    bool available=true;
    int emptySpace=0;

    for (int y=0;y<height;++y)
    {
        for (int x=0;x<width-3;++x)
        {
            available=true;
            emptySpace=0;
            for (int i=0;i<4;++i)
            {
                if (place[y*width+x+i]==marker)
                {
                    available=false;
                    x+=i;
                    break;
                }
                else if (place[y*width+x+i]=='.')
                {
                    ++emptySpace;
                }
            }
            if (available)
            {
                ++performance1.total;
                ++performance1.number[4-emptySpace];
            }
        }
    }

    return performance1;
}

Performance State::VerticalChoice(const bool &player1) const
{
    Performance performance1;

    char marker=' ';
    if (player1)
    {
        marker='O';
    }
    else
    {
        marker='X';
    }

    bool available=true;
    int emptySpace=0;

    for (int x=0;x<width;++x)
    {
        for (int y=0;y<height-3;++y)
        {
            available=true;
            emptySpace=0;
            for (int i=0;i<4;++i)
            {
                if (place[(y+i)*width+x]==marker)
                {
                    available=false;
                    y+=i;
                    break;
                }
                else if (place[(y+i)*width+x]=='.')
                {
                    ++emptySpace;
                }
            }
            if (available)
            {
                ++performance1.total;
                ++performance1.number[4-emptySpace];
            }
            else
            {
                break;
            }
        }
    }

    return performance1;
}

Performance State::DiagonalLeftChoice(const bool &player1) const
{
    Performance performance1;

    char marker=' ';
    if (player1)
    {
        marker='O';
    }
    else
    {
        marker='X';
    }

    bool available=true;
    int emptySpace=0;

    for (int i=4-height;i<width-3;++i)
    {
        for (int x=i,y=0;x<width-3 && y<height-3;++x,++y)
        {
            available=true;
            emptySpace=0;
            for (int j=0;j<4;++j)
            {
                if (x<0 || place[(y+j)*width+x+j]==marker)
                {
                    available=false;
                    x+=j;
                    y+=j;
                    break;
                }
                else if (place[(y+j)*width+x+j]=='.')
                {
                    ++emptySpace;
                }
            }
            if (available)
            {
                ++performance1.total;
                ++performance1.number[4-emptySpace];
            }
        }
    }

    return performance1;
}

Performance State::DiagonalRightChoice(const bool &player1) const
{
    Performance performance1;

    char marker=' ';
    if (player1)
    {
        marker='O';
    }
    else
    {
        marker='X';
    }

    bool available=true;
    int emptySpace=0;

    for (int i=width+height-5;i>2;--i)
    {
        for (int x=i,y=0;x>2 && y<height-3;--x,++y)
        {
            available=true;
            emptySpace=0;
            for (int j=0;j<4;++j)
            {
                if (x>width-1 || place[(y+j)*width+x-j]==marker)
                {
                    available=false;
                    x-=j;
                    y+=j;
                    break;
                }
                else if (place[(y+j)*width+x-j]=='.')
                {
                    ++emptySpace;
                }
            }
            if (available)
            {
                ++performance1.total;
                ++performance1.number[4-emptySpace];
            }
        }
    }

    return performance1;
}

int State::HorizontalConnect(const int &x, const int &y, int &toEnd) const
{
    int length=1;
    char marker=' ';
    if (player)
    {
        marker='X';
    }
    else
    {
        marker='O';
    }

    int position=x+1;
    while (true)
    {
        if (position==width)
        {
            break;
        }
        else if (place[y*width+position]==marker)
        {
            ++length;
            ++position;
        }
        else
        {
            break;
        }
    }
    toEnd=position-x;

    position=x-1;
    while (true)
    {
        if (position==-1)
        {
            break;
        }
        else if (place[y*width+position]==marker)
        {
            ++length;
            --position;
        }
        else
        {
            break;
        }
    }
    return length;
}

int State::VerticalConnect(const int &x, const int &y, int &toEnd) const
{
    int length=1;
    char marker=' ';
    if (player)
    {
        marker='X';
    }
    else
    {
        marker='O';
    }

    int position=y+1;
    while (true)
    {
        if (position==height)
        {
            break;
        }
        else if (place[position*width+x]==marker)
        {
            ++length;
            ++position;
        }
        else
        {
            break;
        }
    }
    toEnd=position-y;

    position=y-1;
    while (true)
    {
        if (position==-1)
        {
            break;
        }
        else if (place[position*width+x]==marker)
        {
            ++length;
            --position;
        }
        else
        {
            break;
        }
    }
    return length;
}

int State::DiagonalLeftConnect(const int &x, const int &y, int &toEnd) const
{
    int length=1;
    char marker=' ';
    if (player)
    {
        marker='X';
    }
    else
    {
        marker='O';
    }

    int xPosition=x+1;
    int yPosition=y+1;
    while (true)
    {
        if (xPosition==width || yPosition==height)
        {
            break;
        }
        else if (place[yPosition*width+xPosition]==marker)
        {
            ++length;
            ++xPosition;
            ++yPosition;
        }
        else
        {
            break;
        }
    }
    toEnd=xPosition-x;

    xPosition=x-1;
    yPosition=y-1;
    while (true)
    {
        if (xPosition==-1 || yPosition==-1)
        {
            break;
        }
        else if (place[yPosition*width+xPosition]==marker)
        {
            ++length;
            --xPosition;
            --yPosition;
        }
        else
        {
            break;
        }
    }
    return length;
}

int State::DiagonalRightConnect(const int &x, const int &y, int &toEnd) const
{
    int length=1;
    char marker=' ';
    if (player)
    {
        marker='X';
    }
    else
    {
        marker='O';
    }

    int xPosition=x+1;
    int yPosition=y-1;
    while (true)
    {
        if (xPosition==width || yPosition==-1)
        {
            break;
        }
        else if (place[yPosition*width+xPosition]==marker)
        {
            ++length;
            ++xPosition;
            --yPosition;
        }
        else
        {
            break;
        }
    }
    toEnd=xPosition-x;

    xPosition=x-1;
    yPosition=y+1;
    while (true)
    {
        if (xPosition==-1 || yPosition==height)
        {
            break;
        }
        else if (place[yPosition*width+xPosition]==marker)
        {
            ++length;
            --xPosition;
            ++yPosition;
        }
        else
        {
            break;
        }
    }
    return length;
}

bool State::CheckWin(const int &x, const int &y) const
{
    int position=0;
    return HorizontalConnect(x, y, position)>3 || VerticalConnect(x, y, position)>3 || DiagonalLeftConnect(x, y, position)>3 || DiagonalRightConnect(x, y, position)>3;
}

bool State::CheckDraw() const
{
    for (int i=0;i<width;++i)
    {
        if (place[i]=='.')
        {
            return false;
        }
    }
    return true;
}

void State::Evaluate1(const int &x, const int &y, Performance &performance)
{
    if (CheckWin(x, y))
    {
        performance.four=1;
    }
    else
    {
        Performance p1=HorizontalChoice(player);
        Performance p2=VerticalChoice(player);
        Performance p3=DiagonalLeftChoice(player);
        Performance p4=DiagonalRightChoice(player);
        Performance p5=HorizontalChoice(1-player);
        Performance p6=VerticalChoice(1-player);
        Performance p7=DiagonalLeftChoice(1-player);
        Performance p8=DiagonalRightChoice(1-player);
        performance.total=p1.total+p2.total+p3.total+p4.total-p5.total-p6.total-p7.total-p8.total;
        for (int i=0;i<4;++i)
        {
            performance.number[i]=p1.number[i]+p2.number[i]+p3.number[i]+p4.number[i]-p5.number[i]-p6.number[i]-p7.number[i]-p8.number[i];
        }
    }
}

Performance State::MiniMax(const int &x, const int &y, const int &stepLimit)
{
    //if N is a leaf
    if (step==stepLimit || CheckWin(x, y) || (y==0 && CheckDraw()))
    {
        Performance performance;
        Evaluate1(x, y, performance);
        performance.step=step;
        if (step%2==0)
        {
            return -performance;
        }
        else
        {
            return performance;
        }
    }
    else
    {
        State* newState=0;
        Performance tempMax(-2);
        Performance tempMin(2);
        Performance temp;
        int y1=-1;
        for (int i=0;i<width;++i)
        {
            newState=new State(*this);
            y1=(*newState).DropDisc(i+1);
            if (y1==-1)
            {
                delete newState;
                newState=0;
            }
            else
            {
                closedList.push(newState);
                temp=(*newState).MiniMax(i, y1, stepLimit);
                if (step%2==0)
                {
                    if (temp>tempMax)
                    {
                        tempMax=temp;
                    }
                }
                else
                {
                    if (temp<tempMin)
                    {
                        tempMin=temp;
                    }
                }
            }
        }

        if (step%2==0)
        {
            return tempMax;
        }
        else
        {
            return tempMin;
        }
    }
}

int State::MiniMaxPlanning(const int &stepLimit)
{
    int column=-1;
    Performance Max(-2);
    Performance temp;
    State* newState=0;
    int y=-1;
    for (int i=0;i<width;++i)
    {
        newState=new State(*this);
        y=(*newState).DropDisc(i+1);
        if (y==-1)
        {
            delete newState;
            newState=0;
        }
        else
        {
            closedList.push(newState);
            temp=(*newState).MiniMax(i, y, stepLimit);
            if (temp>Max)
            {
                Max=temp;
                column=i;
            }
        }
    }

    while (!closedList.empty())
    {
        newState=closedList.top();
        delete newState;
        newState=0;
        closedList.pop();
    }

    return column;
}

Performance State::AlphaBeta(const int &x, const int &y, const int &stepLimit, const Performance &alpha, const Performance &beta)
{
    //if N is a leaf
    if (step==stepLimit || CheckWin(x, y) || (y==0 && CheckDraw()))
    {
        Performance performance;
        Evaluate1(x, y, performance);
        performance.step=step;
        if (step%2==0)
        {
            return -performance;
        }
        else
        {
            return performance;
        }
    }
    else
    {
        State* newState=0;
        Performance alphaMax=alpha;
        Performance betaMin=beta;
        Performance temp;
        int y1=-1;
        for (int i=0;i<width;++i)
        {
            newState=new State(*this);
            y1=(*newState).DropDisc(i+1);
            if (y1==-1)
            {
                delete newState;
                newState=0;
            }
            else
            {
                closedList.push(newState);
                temp=(*newState).AlphaBeta(i, y1, stepLimit, alphaMax, betaMin);
                if (step%2==0)
                {
                    if (temp>alphaMax)
                    {
                        alphaMax=temp;
                    }
                    if (!(alphaMax<betaMin))
                    {
                        break;
                    }
                }
                else
                {
                    if (temp<betaMin)
                    {
                        betaMin=temp;
                    }
                    if (!(alphaMax<betaMin))
                    {
                        break;
                    }
                }
            }
        }

        if (step%2==0)
        {
            return alphaMax;
        }
        else
        {
            return betaMin;
        }
    }
}

int State::AlphaBetaPlanning(const int &stepLimit)
{
    int column=-1;
    Performance alphaMax(-2);
    Performance betaMin(2);
    Performance temp;
    State* newState=0;
    int y=-1;
    for (int i=0;i<width;++i)
    {
        newState=new State(*this);
        y=(*newState).DropDisc(i+1);
        if (y==-1)
        {
            delete newState;
            newState=0;
        }
        else
        {
            closedList.push(newState);
            temp=(*newState).AlphaBeta(i, y, stepLimit, alphaMax, betaMin);
            if (temp>alphaMax)
            {
                alphaMax=temp;
                column=i;
            }
        }
    }

    while (!closedList.empty())
    {
        newState=closedList.top();
        delete newState;
        newState=0;
        closedList.pop();
    }

    return column;
}

ostream& operator<<(ostream &out, const State &state)
{
    out<<' ';
    for (int i=0;i<width;++i)
    {
        out<<i+1;
    }
    out<<endl;
    for (int i=0;i<height;++i)
    {
        out<<i+1;
        for (int j=0;j<width;++j)
        {
            out<<state.GetPlace(i*width+j);
        }
        out<<endl;
    }
    return out;
}
