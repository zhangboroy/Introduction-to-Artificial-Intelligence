#include "put.h"

//the default constructor, using the size of length and width of the box
Solution::Solution()
{
    presentPosition=new int[24*presentNumber];

    for (int i=0;i<24*presentNumber;++i)
    {
        presentPosition[i]=-1;
    }
}

//the destructor
Solution::~Solution()
{
    delete presentPosition;
    presentPosition=0;
}

void Solution::operator=(const Solution &solution)
{
    for (int i=0;i<24*presentNumber;++i)
    {
        presentPosition[i]=solution.presentPosition[i];
    }
}

//compute the arguments for putting the next present
void Solution::DecideNextPut(const Present gift, DecideNextPutArg &arg)
{
    //no enough length left
    if (arg.nextX+gift.x>boxLength)
    {
        arg.nextX=0;
        arg.nextY+=arg.maxWidth;
        arg.maxWidth=0;
        DecideNextPut(gift, arg);
    }
    //length left can just fit x
    else if (arg.nextX+gift.y>boxLength)
    {
        //width left can't fit y
        if (arg.nextY+gift.y>boxWidth)
        {
            if (arg.maxWidth==0)
            {
                arg.nextY=0;
                arg.putLayer+=arg.maxHeight;
                arg.maxHeight=0;
                DecideNextPut(gift, arg);
            }
            else
            {
                arg.nextX=0;
                arg.nextY+=arg.maxWidth;
                arg.maxWidth=0;
                DecideNextPut(gift, arg);
            }
        }
        //width left can fit y
        else
        {
            arg.putLength=gift.x;
            //width left can't fit z
            if (arg.nextY+gift.z>boxWidth)
            {
                arg.putWidth=gift.y;
                arg.putHeight=gift.z;
            }
            //width left can fit z
            else
            {
                arg.putWidth=gift.z;
                arg.putHeight=gift.y;
            }
            /*
            arg.putLayer=0;
            for (int y=arg.nextY;y<arg.nextY+arg.putWidth;++y)
            {
                for (int x=arg.nextX;x<arg.nextX+arg.putLength;++x)
                {
                    if (arg.topLayer[y*boxLength+x]>arg.putLayer)
                    {
                        arg.putLayer=arg.topLayer[y*boxLength+x];
                    }
                }
            }
            */
        }
    }
    //length left can't fit z
    else if (arg.nextX+gift.z>boxLength)
    {
        //width left can't fit x
        if (arg.nextY+gift.x>boxWidth)
        {
            if (arg.maxWidth==0)
            {
                arg.nextY=0;
                arg.putLayer+=arg.maxHeight;
                arg.maxHeight=0;
                DecideNextPut(gift, arg);
            }
            else
            {
                arg.nextX=0;
                arg.nextY+=arg.maxWidth;
                arg.maxWidth=0;
                DecideNextPut(gift, arg);
            }
        }
        //width left can fit x
        else
        {
            arg.putLength=gift.y;
            //width left can't fit z
            if (arg.nextY+gift.z>boxWidth)
            {
                arg.putWidth=gift.x;
                arg.putHeight=gift.z;
            }
            //width left can fit z
            else
            {
                arg.putWidth=gift.z;
                arg.putHeight=gift.x;
            }
            /*
            arg.putLayer=0;
            for (int y=arg.nextY;y<arg.nextY+arg.putWidth;++y)
            {
                for (int x=arg.nextX;x<arg.nextX+arg.putLength;++x)
                {
                    if (arg.topLayer[y*boxLength+x]>arg.putLayer)
                    {
                        arg.putLayer=arg.topLayer[y*boxLength+x];
                    }
                }
            }
            */
        }
    }
    //length left can fit z
    else
    {
        //width left can't fit x
        if (arg.nextY+gift.x>boxWidth)
        {
            if (arg.maxWidth==0)
            {
                arg.nextY=0;
                arg.putLayer+=arg.maxHeight;
                arg.maxHeight=0;
                DecideNextPut(gift, arg);
            }
            else
            {
                arg.nextX=0;
                arg.nextY+=arg.maxWidth;
                arg.maxWidth=0;
                DecideNextPut(gift, arg);
            }
        }
        //width left can fit x
        else
        {
            arg.putLength=gift.z;
            //width left can't fit y
            if (arg.nextY+gift.y>boxWidth)
            {
                arg.putWidth=gift.x;
                arg.putHeight=gift.y;
            }
            //width left can fit y
            else
            {
                arg.putWidth=gift.y;
                arg.putHeight=gift.x;
            }
            /*
            arg.putLayer=0;
            for (int y=arg.nextY;y<arg.nextY+arg.putWidth;++y)
            {
                for (int x=arg.nextX;x<arg.nextX+arg.putLength;++x)
                {
                    if (arg.topLayer[y*boxLength+x]>arg.putLayer)
                    {
                        arg.putLayer=arg.topLayer[y*boxLength+x];
                    }
                }
            }
            */
        }
    }
}

//the easy way to put the presents into the box, it will fill in the present position array
void Solution::EasyPut(const Chromosome &chromosome, const Present gift[])
{
    //set the arguments for deciding next position
    DecideNextPutArg arg;
    arg.maxHeight=0;
    //initiate the top layer
    ///set<int>* topLayerSet=new set<int>;
    /*
    arg.topLayer=new int[boxLength*boxWidth];
    for (int i=0;i<boxLength*boxWidth;++i)
    {
        arg.topLayer[i]=0;
        ///(*topLayerSet).insert(i);
    }
    */
    ///arg.topLayerVector.push_back(topLayerSet);

    //the next present's top-left point position
    arg.nextX=0;
    arg.nextY=0;
    //indicate the length, width, height and layer of the present being put
    arg.putLength=gift[chromosome.present[0]].z;
    arg.putWidth=gift[chromosome.present[0]].y;
    arg.putHeight=gift[chromosome.present[0]].x;
    arg.putLayer=0;
    //help to find the next line
    arg.maxWidth=0;

    //put the presents 1 by 1
    for (int i=0;i<presentNumber-1;++i)
    {
        //put the present i
        if (arg.maxHeight<arg.putHeight)
        {
            arg.maxHeight=arg.putHeight;
        }
        /*
        for (int y=arg.nextY;y<arg.nextY+arg.putWidth;++y)
        {
            for (int x=arg.nextX;x<arg.nextX+arg.putLength;++x)
            {
                arg.topLayer[y*boxLength+x]=arg.putLayer+arg.putHeight;
            }
        }
        */

        presentPosition[chromosome.present[i]*24]=arg.nextX;
        presentPosition[chromosome.present[i]*24+1]=arg.nextY;
        presentPosition[chromosome.present[i]*24+2]=arg.putLayer;
        presentPosition[chromosome.present[i]*24+3]=arg.nextX+arg.putLength-1;
        presentPosition[chromosome.present[i]*24+4]=arg.nextY;
        presentPosition[chromosome.present[i]*24+5]=arg.putLayer;
        presentPosition[chromosome.present[i]*24+6]=arg.nextX;
        presentPosition[chromosome.present[i]*24+7]=arg.nextY+arg.putWidth-1;
        presentPosition[chromosome.present[i]*24+8]=arg.putLayer;
        presentPosition[chromosome.present[i]*24+9]=arg.nextX+arg.putLength-1;
        presentPosition[chromosome.present[i]*24+10]=arg.nextY+arg.putWidth-1;
        presentPosition[chromosome.present[i]*24+11]=arg.putLayer;
        presentPosition[chromosome.present[i]*24+12]=arg.nextX;
        presentPosition[chromosome.present[i]*24+13]=arg.nextY;
        presentPosition[chromosome.present[i]*24+14]=arg.putLayer+arg.putHeight-1;
        presentPosition[chromosome.present[i]*24+15]=arg.nextX+arg.putLength-1;
        presentPosition[chromosome.present[i]*24+16]=arg.nextY;
        presentPosition[chromosome.present[i]*24+17]=arg.putLayer+arg.putHeight-1;
        presentPosition[chromosome.present[i]*24+18]=arg.nextX;
        presentPosition[chromosome.present[i]*24+19]=arg.nextY+arg.putWidth-1;
        presentPosition[chromosome.present[i]*24+20]=arg.putLayer+arg.putHeight-1;
        presentPosition[chromosome.present[i]*24+21]=arg.nextX+arg.putLength-1;
        presentPosition[chromosome.present[i]*24+22]=arg.nextY+arg.putWidth-1;
        presentPosition[chromosome.present[i]*24+23]=arg.putLayer+arg.putHeight-1;

        //decide the next position
        arg.nextX+=arg.putLength;
        if (arg.putWidth>arg.maxWidth)
        {
            arg.maxWidth=arg.putWidth;
        }

        DecideNextPut(gift[chromosome.present[i+1]], arg);
    }

    //put the last present
    presentPosition[chromosome.present[presentNumber-1]*24]=arg.nextX;
    presentPosition[chromosome.present[presentNumber-1]*24+1]=arg.nextY;
    presentPosition[chromosome.present[presentNumber-1]*24+2]=arg.putLayer;
    presentPosition[chromosome.present[presentNumber-1]*24+3]=arg.nextX+arg.putLength-1;
    presentPosition[chromosome.present[presentNumber-1]*24+4]=arg.nextY;
    presentPosition[chromosome.present[presentNumber-1]*24+5]=arg.putLayer;
    presentPosition[chromosome.present[presentNumber-1]*24+6]=arg.nextX;
    presentPosition[chromosome.present[presentNumber-1]*24+7]=arg.nextY+arg.putWidth-1;
    presentPosition[chromosome.present[presentNumber-1]*24+8]=arg.putLayer;
    presentPosition[chromosome.present[presentNumber-1]*24+9]=arg.nextX+arg.putLength-1;
    presentPosition[chromosome.present[presentNumber-1]*24+10]=arg.nextY+arg.putWidth-1;
    presentPosition[chromosome.present[presentNumber-1]*24+11]=arg.putLayer;
    presentPosition[chromosome.present[presentNumber-1]*24+12]=arg.nextX;
    presentPosition[chromosome.present[presentNumber-1]*24+13]=arg.nextY;
    presentPosition[chromosome.present[presentNumber-1]*24+14]=arg.putLayer+arg.putHeight-1;
    presentPosition[chromosome.present[presentNumber-1]*24+15]=arg.nextX+arg.putLength-1;
    presentPosition[chromosome.present[presentNumber-1]*24+16]=arg.nextY;
    presentPosition[chromosome.present[presentNumber-1]*24+17]=arg.putLayer+arg.putHeight-1;
    presentPosition[chromosome.present[presentNumber-1]*24+18]=arg.nextX;
    presentPosition[chromosome.present[presentNumber-1]*24+19]=arg.nextY+arg.putWidth-1;
    presentPosition[chromosome.present[presentNumber-1]*24+20]=arg.putLayer+arg.putHeight-1;
    presentPosition[chromosome.present[presentNumber-1]*24+21]=arg.nextX+arg.putLength-1;
    presentPosition[chromosome.present[presentNumber-1]*24+22]=arg.nextY+arg.putWidth-1;
    presentPosition[chromosome.present[presentNumber-1]*24+23]=arg.putLayer+arg.putHeight-1;
}
