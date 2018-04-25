#ifndef CITY_H_INCLUDED
#define CITY_H_INCLUDED

class City
{
    double x;
    double y;
public:
    City()
    {
        x=0;
        y=0;
    }
    ~City(){};
    double GetX() const
    {
        return x;
    }
    double GetY() const
    {
        return y;
    }
    void Set(const double &x1, const double &y1)
    {
        x=x1;
        y=y1;
    }
    double operator-(const City &city) const;
};

#endif // CITY_H_INCLUDED
