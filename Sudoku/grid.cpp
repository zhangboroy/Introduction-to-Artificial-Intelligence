#include <fstream>
#include "grid.h"

static bool solve=false;

Grid::Grid()
{
    cout<<"Please Enter the Name of the Sudoku Quest File: "<<flush;
    string line;
    getline(cin,line);

    //read the parameters of the Sudoku quest
    ifstream inData;
    inData.open(line.c_str());
    getline(inData,line);
    v=new int[9*9];
    fix=new bool[9*9];
    availableValues=new list<int>[9*9];
    for (int i=0;i<9;++i)
    {
        getline(inData,line);
        for (int j=0;j<9;++j)
        {
            v[i*9+j]=line[j]-int('0');
            if (v[i*9+j]==0)
            {
                fix[i*9+j]=false;
                for (int k=1;k<10;++k)
                {
                    availableValues[i*9+j].push_back(k);
                }
            }
            else
            {
                fix[i*9+j]=true;
                availableValues[i*9+j].push_back(v[i*9+j]);
            }
        }
    }
    inData.close();

    for (int i=0;i<9*9;++i)
    {
        if (fix[i])
        {
            SetAvailableValues(i,0);
        }
    }
}

void Grid::SetAvailableValues(const int &i, const int &vi)
{
    int temp=0;
    int toBeManipulate1=0;
    int toBeManipulate2=0;
    for (int j=1;j<9;++j)
    {
        toBeManipulate1=(i+j)%9+(i/9)*9;
        toBeManipulate2=(i+j*9)%(9*9);

        if (!fix[toBeManipulate1])
        {
            if (vi)
            {
                temp=v[toBeManipulate1];
                v[toBeManipulate1]=vi;
                if (CSP())
                {
                    availableValues[toBeManipulate1].push_back(vi);
                }
                v[toBeManipulate1]=temp;
            }
            else
            {
                availableValues[toBeManipulate1].remove(v[i]);
            }
        }

        if (!fix[toBeManipulate2])
        {
            if (vi)
            {
                temp=v[toBeManipulate2];
                v[toBeManipulate2]=vi;
                if (CSP())
                {
                    availableValues[toBeManipulate2].push_back(vi);
                }
                v[toBeManipulate2]=temp;
            }
            else
            {
                availableValues[toBeManipulate2].remove(v[i]);
            }
        }
    }

    for (int j=0;j<3;++j)
    {
        if (i/9%3!=j)
        {
            for (int k=0;k<3;++k)
            {
                if (i%9%3!=k)
                {
                    toBeManipulate1=(i/27)*27+j*9+(i%9/3)*3+k;
                    if (!fix[toBeManipulate1])
                    {
                        if (vi)
                        {
                            temp=v[toBeManipulate1];
                            v[toBeManipulate1]=vi;
                            if (CSP())
                            {
                                availableValues[toBeManipulate1].push_back(vi);
                            }
                            v[toBeManipulate1]=temp;
                        }
                        else
                        {
                            availableValues[toBeManipulate1].remove(v[i]);
                        }
                    }
                }
            }
        }
    }
}

bool Alldiff(const int &a1, const int &a2, const int &a3, const int &a4, const int &a5, const int &a6, const int &a7, const int &a8, const int &a9)
{
    int a[9];
    a[0]=a1;
    a[1]=a2;
    a[2]=a3;
    a[3]=a4;
    a[4]=a5;
    a[5]=a6;
    a[6]=a7;
    a[7]=a8;
    a[8]=a9;
    for (int i=0;i<8;++i)
    {
        for (int j=i+1;j<9;++j)
        {
            if (a[i]!=0 && a[j]!=0 && a[i]==a[j])
            {
                return false;
            }
        }
    }
    return true;
}

bool Grid::CSP() const
{
    int j=0;
    for (int i=0;i<9;++i)
    {
        if (!Alldiff(v[i],v[i+9],v[i+18],v[i+27],v[i+36],v[i+45],v[i+54],v[i+63],v[i+72]))
        {
            return false;
        }
        if (!Alldiff(v[i*9],v[i*9+1],v[i*9+2],v[i*9+3],v[i*9+4],v[i*9+5],v[i*9+6],v[i*9+7],v[i*9+8]))
        {
            return false;
        }
        j=i/3;
        if (!Alldiff(v[j*18+i*3],v[j*18+i*3+1],v[j*18+i*3+2],v[j*18+i*3+9],v[j*18+i*3+10],v[j*18+i*3+11],v[j*18+i*3+18],v[j*18+i*3+19],v[j*18+i*3+20]))
        {
            return false;
        }
    }
    return true;
}

bool Grid::NaiveSolve(const int &i)
{
    if (fix[i])
    {
        if (CSP())
        {
            if (i==9*9-1)
            {
                return true;
            }
            else
            {
                if (NaiveSolve(i+1))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        for (int j=1;j<10;++j)
        {
            v[i]=j;
            if (CSP())
            {
                if (i==9*9-1)
                {
                    return true;
                }
                else
                {
                    if (NaiveSolve(i+1))
                    {
                        return true;
                    }
                }
            }
        }
        if (!fix[i])
        {
            v[i]=0;
        }
        return false;
    }
}

bool Grid::SmartSolve()
{
    solve=true;
    int minI=9*9;
    int minAvailableValueNumber=9+1;
    int availableValueNumber=0;
    int toBeRestore=0;
    list<int> restoreList;
    for (int i=0;i<9*9;++i)
    {
        if (!fix[i])
        {
            availableValueNumber=availableValues[i].size();
            if (availableValueNumber==0)
            {
                return false;
            }
            else if (availableValueNumber<minAvailableValueNumber)
            {
                minAvailableValueNumber=availableValueNumber;
                minI=i;
            }
            if (v[i]==0)
            {
                solve=false;
            }
        }
    }

    if (solve)
    {
        return true;
    }

    while (!availableValues[minI].empty())
    {
        v[minI]=availableValues[minI].front();
        availableValues[minI].pop_front();
        fix[minI]=true;
        SetAvailableValues(minI,0);
        if (SmartSolve())
        {
            return true;
        }
        else
        {
            fix[minI]=false;
            toBeRestore=v[minI];
            v[minI]=0;
            SetAvailableValues(minI,toBeRestore);
            restoreList.push_back(toBeRestore);
        }
    }

    for (list<int>::iterator i=restoreList.begin();i!=restoreList.end();++i)
    {
        availableValues[minI].push_back(*i);
    }
    return false;
}

ostream& operator<< (ostream &out, const Grid &grid)
{
    for (int i=0;i<9;++i)
    {
        for (int j=0;j<9;++j)
        {
            out<<grid.GetV(i,j);
        }
        out<<endl;
    }
    return out;
}
