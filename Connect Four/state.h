#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <iostream>

using namespace std;

const int height=6;
const int width=7;

struct Performance
{
    int four;
    int step;
    int total;
    int number[4];
    Performance(const int &four1=0)
    {
        four=four1;
        step=0;
        total=0;
        number[0]=0;
        number[1]=0;
        number[2]=0;
        number[3]=0;
    }

    Performance operator- () const
    {
        Performance performance;
        performance.four=-four;
        performance.step=-step;
        performance.number[0]=-number[0];
        performance.number[1]=-number[1];
        performance.number[2]=-number[2];
        performance.number[3]=-number[3];
        performance.total=-total;
        return performance;
    }
    bool operator<(const Performance &performance) const;
    bool operator>(const Performance &performance) const;
};

class State
{
    State* parent;
    bool player;
    char* place;
    int step;
public:
    State();
    State(State &state);
    ~State()
    {
        delete []place;
    }
    State* GetParent() const
    {
        return parent;
    }
    bool GetPlayer() const
    {
        return player;
    }
    char GetPlace(const int &n) const
    {
        return place[n];
    }
    int GetStep() const
    {
        return step;
    }
    void ChangePlayer()
    {
        player=1-player;
    }
    int DropDisc(const int &column);
    Performance HorizontalChoice(const bool &player1) const;
    Performance VerticalChoice(const bool &player1) const;
    Performance DiagonalLeftChoice(const bool &player1) const;
    Performance DiagonalRightChoice(const bool &player1) const;
    int HorizontalConnect(const int &x, const int &y, int &toEnd) const;
    int VerticalConnect(const int &x, const int &y, int &toEnd) const;
    int DiagonalLeftConnect(const int &x, const int &y, int &toEnd) const;
    int DiagonalRightConnect(const int &x, const int &y, int &toEnd) const;
    bool CheckWin(const int &x, const int &y) const;
    bool CheckDraw() const;
    Performance MiniMax(const int &x, const int &y, const int &stepLimit);
    int MiniMaxPlanning(const int &stepLimit);
    Performance AlphaBeta(const int &x, const int &y, const int &stepLimit, const Performance &alpha, const Performance &beta);
    int AlphaBetaPlanning(const int &stepLimit);
    void Evaluate1(const int &x, const int &y, Performance &performance);
};

ostream& operator<<(ostream &out, const State &state);

#endif // STATE_H_INCLUDED
