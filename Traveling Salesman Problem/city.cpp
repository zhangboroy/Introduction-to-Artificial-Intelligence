#include <cmath>
#include "city.h"

double City::operator-(const City &city) const
{
    return sqrt(pow(x-city.GetX(),2)+pow(y-city.GetY(),2));
}
