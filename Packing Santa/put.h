#ifndef PUT_H_INCLUDED
#define PUT_H_INCLUDED

#include <set>
#include <vector>
#include "chromosome.h"

#define boxLength 1000
#define boxWidth 1000

//the arguments for deciding next position
struct DecideNextPutArg
{
    int maxHeight;
    /*
    //indicate the top layer of every (x,y)
    int* topLayer;
    */
    //the next present's top-left point position
    int nextX;
    int nextY;
    //indicate the length, width, height and layer of the present being put
    int putLength;
    int putWidth;
    int putHeight;
    int putLayer;
    //help to find the next line
    int maxWidth;
    ///vector<set<int>*> topLayerVector;
    /*
    ~DecideNextPutArg()
    {
        delete []topLayer;
        topLayer=0;
    }
    */
};

//means one particular set of positions of all gifts
class Solution
{
    void DecideNextPut(const Present gift, DecideNextPutArg &arg);
public:
    //a present#*24 dynamic array, each line is a single present, 24 columns mean x1,y1,z1,...,x8,y8,z8
    int* presentPosition;

    //the default constructor, using the size of length and width of the box
    Solution();
    //the destructor
    ~Solution();
    void operator=(const Solution &solution);
    //the easy way to put the presents into the box, it will fill in the present position array
    void EasyPut(const Chromosome &chromosome, const Present gift[]);
};

#endif // PUT_H_INCLUDED
