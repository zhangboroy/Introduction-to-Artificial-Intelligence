#include <string>
#include "state.h"

int main()
{
    cout<<"Welcome to Connect Four Game!\n";
    int player1=0;
    int player2=0;
    int algorithm1=0;
    int algorithm2=0;
    int level1=0;
    int level2=0;
    int levelLimit=0;
    string garbage;

    while (player1<1 || player1>2)
    {
        cout<<"Please Choose Player 1 (1- Human, 2- Computer): "<<flush;
        cin>>player1;
        if (!cin)
        {
            cin.clear();
            getline(cin, garbage);
            player1=0;
        }
    }

    if (player1==2)
    {
        while (algorithm1<1 || algorithm1>2)
        {
            cout<<"Please Choose Algorithm (1- MiniMax, 2- AlphaBeta): "<<flush;
            cin>>algorithm1;
            if (!cin)
            {
                cin.clear();
                getline(cin, garbage);
                algorithm1=0;
            }
        }
        if (algorithm1==1)
        {
            levelLimit=8;
        }
        else if (algorithm1==2)
        {
            levelLimit=10;
        }
        while (level1<1 || level1>levelLimit)
        {
            cout<<"Please Choose Level (1- Easiest, ... , "<<levelLimit<<"- Hardest): "<<flush;
            cin>>level1;
            if (!cin)
            {
                cin.clear();
                getline(cin, garbage);
                level1=0;
            }
        }
    }

    while (player2<1 || player2>2)
    {
        cout<<"Please Choose Player 2 (1- Human, 2- Computer): "<<flush;
        cin>>player2;
        if (!cin)
        {
            cin.clear();
            getline(cin, garbage);
            player1=0;
        }
    }

    if (player2==2)
    {
        while (algorithm2<1 || algorithm2>2)
        {
            cout<<"Please Choose Algorithm (1- MiniMax, 2- AlphaBeta): "<<flush;
            cin>>algorithm2;
            if (!cin)
            {
                cin.clear();
                getline(cin, garbage);
                algorithm2=0;
            }
        }
        if (algorithm2==1)
        {
            levelLimit=8;
        }
        else if (algorithm2==2)
        {
            levelLimit=10;
        }
        while (level2<1 || level2>levelLimit)
        {
            cout<<"Please Choose Level (1- Easiest, ... , "<<levelLimit<<"- Hardest): "<<flush;
            cin>>level2;
            if (!cin)
            {
                cin.clear();
                getline(cin, garbage);
                level2=0;
            }
        }
    }


    State state;
    int input=-1;
    int y=0;

    cout<<state<<endl;
    do
    {
        y=-1;
        if (player1==1)
        {
            state.ChangePlayer();
            do
            {
                cout<<"Player "<<2-state.GetPlayer()<<" turn:\n";
                cin>>input;
                if (!cin)
                {
                    cin.clear();
                    getline(cin, garbage);
                    input=-1;
                }
                else if (input==0)
                {
                    break;
                }
                else
                {
                    y=state.DropDisc(input);
                    if (y==-1)
                    {
                        cout<<"Column "<<input<<" is full!\n";
                    }
                }
            }
            while (y==-1);

            if (input==0)
            {
                break;
            }
            else
            {
                cout<<state<<endl;

                if (state.CheckWin(input-1, y))
                {
                    cout<<"Player "<<2-state.GetPlayer()<<" wins!\n";
                    break;
                }
            }
        }
        else
        {
            if (algorithm1==1)
            {
                input=state.MiniMaxPlanning(level1)+1;
            }
            else
            {
                input=state.AlphaBetaPlanning(level1)+1;
            }
            state.ChangePlayer();
            y=state.DropDisc(input);
            cout<<state<<endl;

            if (state.CheckWin(input-1, y))
            {
                cout<<"Player "<<2-state.GetPlayer()<<" wins!\n";
                break;
            }
        }

        if (player2==1)
        {
            state.ChangePlayer();
            do
            {
                cout<<"Player "<<2-state.GetPlayer()<<" turn:\n";
                cin>>input;
                if (!cin)
                {
                    cin.clear();
                    getline(cin, garbage);
                    input=-1;
                }
                else if (input==0)
                {
                    break;
                }
                else
                {
                    y=state.DropDisc(input);
                    if (y==-1)
                    {
                        cout<<"Column "<<input<<" is full!\n";
                    }
                }
            }
            while (y==-1);

            if (input==0)
            {
                break;
            }
            else
            {
                cout<<state<<endl;
                if (state.CheckWin(input-1, y))
                {
                    cout<<"Player "<<2-state.GetPlayer()<<" wins!\n";
                    break;
                }
                else if (y==0 && state.CheckDraw())
                {
                    cout<<"Draw game!\n";
                    break;
                }
            }
        }
        else
        {
            if (algorithm2==1)
            {
                input=state.MiniMaxPlanning(level2)+1;
            }
            else
            {
                input=state.AlphaBetaPlanning(level2)+1;
            }
            state.ChangePlayer();
            y=state.DropDisc(input);
            cout<<state<<endl;

            if (state.CheckWin(input-1, y))
            {
                cout<<"Player "<<2-state.GetPlayer()<<" wins!\n";
                break;
            }
            else if (y==0 && state.CheckDraw())
            {
                cout<<"Draw game!\n";
                break;
            }
        }
    }
    while (input!=0);

    cin>>garbage;

    return 0;
}
