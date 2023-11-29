#include<iostream>
#include<unordered_set>
#include<queue>
#include<vector>

using namespace std;
const int N = 3;
int moves[4][2] = {{-1, 0}, {1, 0}, {0,-1}, {0,1}};

int board[N][N], initialstateboard[N][N], finalstateboard[N][N];

bool isGoalState(int currentstatebord[N][N])
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(currentstatebord[i][j] != finalstateboard[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool isvalidmove(int blankX, int blankY, int i)
{

    if(moves[i][0] == -1 && blankX>0)
    {
        return true;
    }
    else if(moves[i][0] == 1 && blankX < N-1)
    {
        return true;
    }
    else if(moves[i][1] == -1 && blankY>0)
    {
        return true;
    }
    else if( moves[i][1] == 1 && blankY<N-1)
    {
        return true;
    }
}
vector <int[]> nextMoves(int currentstateboard[N][N])
{
    vector <int[]> nextStates;
    int blankX = -1, blankY = -1;
    for(int i =0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(currentstateboard[i][j] == 0)
            {
                blankX = i;
                blankY = j;
            }
        }
    }

    for(int k=0; k<4; k++)
    {
        int newX = blankX + moves[k][0];
        int newY = blankY + moves[k][1];

        if(isvalidmove(blankX, blankY, k))
        {
            int newboard[N][N];
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    newboard[i][j] = currentstateboard[i][j];
                }
            }
            swap(newboard[blankX][blankY], newboard[newX][newY]);
            nextStates.emplace_back(newboard);

        }
    }
    return nextStates;
}
void evaluator(int currentstate[N][N], int goalstate[N][N])
{
    
}
int main()
{

    cout<<"Enter the initial state of 8 puzzle: "<<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cin>> initialstateboard[i][j];
        }
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout<<initialstateboard[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"Enter the final state of 8 puzzle: "<<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cin>>finalstateboard[i][j];
        }
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout<<finalstateboard[i][j]<<" ";
        }
        cout<<endl;
    }
}