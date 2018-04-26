#ifndef PRESENTS_LIST_H_INCLUDED
#define PRESENTS_LIST_H_INCLUDED

#define presentNumber 1000000

using namespace std;

struct Present
{
    //the shortest dimension of the present
    int x;
    //the middle dimension of the present
    int y;
    //the longest dimension of the present
    int z;
    Present()
    {
        x=0;
        y=0;
        z=0;
    }
};

//read the present list file to a present array
void ReadPresentList(Present present[]);

#endif // PRESENTS_LIST_H_INCLUDED
