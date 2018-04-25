#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

class Wall
{
    int x;
    int y;
public:
    Wall();
    ~Wall(){}
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

#endif // WALL_H_INCLUDED
