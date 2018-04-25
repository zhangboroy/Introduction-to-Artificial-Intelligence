#ifndef STORAGE_H_INCLUDED
#define STORAGE_H_INCLUDED

class Storage
{
    int x;
    int y;
public:
    Storage();
    ~Storage(){}
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

#endif // STORAGE_H_INCLUDED
