#include "grid.h"
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
    Grid grid;
    cout<<"The original quest is:\n"<<grid<<endl;
    cout<<"Please choose the algorithm:\n"
        <<"1. Naive Backtracking Algorithm\n"
        <<"2. Smart Backtracking Algorithm\n"
        <<"Your Choice: "<<flush;
    int input;
    cin>>input;

    bool result=false;
    int totalTime=time(0);
    if (input==1)
    {
        result=grid.NaiveSolve(0);
    }
    else if (input==2)
    {
        result=grid.SmartSolve();
    }
    totalTime=time(0)-totalTime;

    if (result)
    {
        cout<<"\nThe Sudoku is solved. The solution is:\n"<<grid<<endl;
        cout<<"Total time: "<<totalTime<<endl;
    }
    else
    {
        cout<<"\nThe Sudoku has no solution!\n";
    }

    return 0;
}
