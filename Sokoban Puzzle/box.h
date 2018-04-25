#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

class Map;
class State;

class Box
{
    int x;
    int y;
public:
    Box();
    ~Box(){}
    int GetX() const
    {
        return x;
    }
    int GetY() const
    {
        return y;
    }
    void Set(const int &x1, const int &y1);
    //first row, then column
    bool operator<(const Box &box) const;
    //check the position of the box or near the box
    bool Check(const int &direction, const Map &map, const State &state) const;
};

#endif // BOX_H_INCLUDED
