#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

class Robot
{
    int x;
    int y;
public:
    Robot();
    ~Robot(){}
    int GetX() const
    {
        return x;
    }
    int GetY() const
    {
        return y;
    }
    void Set(const int &x1, const int &y1);
};

#endif // ROBOT_H_INCLUDED
