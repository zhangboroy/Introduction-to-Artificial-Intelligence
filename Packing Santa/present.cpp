#include <fstream>
#include <string>
#include "present.h"

//read the present list file to a present array
void ReadPresentList(Present present[])
{
    ifstream inData;
    inData.open("presents.csv");
    string line="";
    getline(inData, line);

    //read 1 single line of present information to temp variables
    int d[3]={0};
    char a=' ';
    for (int i=0;i<presentNumber;++i)
    {
        inData>>d[0]>>a>>d[0]>>a>>d[1]>>a>>d[2];
        //d[0]<d[1]
        if (d[0]<d[1])
        {
            //d[0]<d[1] and d[0]<d[2]
            if (d[0]<d[2])
            {
                present[i].x=d[0];
                //d[0]<d[1] and d[0]<d[2] and d[1]<d[2], then d[0]<d[1]<d[2]
                if (d[1]<d[2])
                {
                    present[i].y=d[1];
                    present[i].z=d[2];
                }
                //d[0]<d[1] and d[0]<d[2] and d[1]>=d[2], then d[0]<d[2]<=d[1]
                else
                {
                    present[i].y=d[2];
                    present[i].z=d[1];
                }
            }
            //d[2]<=d[0]<d[1]
            else
            {
                present[i].x=d[2];
                present[i].y=d[0];
                present[i].z=d[1];
            }
        }
        //d[0]>=d[1]
        else
        {
            //d[1]<=d[0]<d[2]
            if (d[0]<d[2])
            {
                present[i].x=d[1];
                present[i].y=d[0];
                present[i].z=d[2];
            }
            //d[0]>=d[1] and d[0]>=d[2]
            else
            {
                present[i].z=d[0];
                //d[0]>=d[1] and d[0]>=d[2] and d[1]<d[2], then d[1]<d[2]<=d[0]
                if (d[1]<d[2])
                {
                    present[i].x=d[1];
                    present[i].y=d[2];
                }
                //d[0]>=d[1] and d[0]>=d[2] and d[1]>=d[2], then d[2]<=d[1]<=d[0]
                else
                {
                    present[i].x=d[2];
                    present[i].y=d[1];
                }
            }
        }
    }

    inData.close();
}
