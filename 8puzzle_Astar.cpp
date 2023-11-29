#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<set>

using namespace std;
int value;
int moves[4][2] = {{-1, 0}, {1, 0}, {0,-1}, {0,1}};
const int N = 3;
vector <state> nextstates;
struct state
{
    int board[N][N];
    int cost;
    int heuristic;

    bool operator==(const state& other) const {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] != other.board[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
};
struct CompareStates
{
    bool operator()(const state &lhs,  const state &rhs) const 
    {
        return (lhs.cost + lhs.heuristic) > (rhs.cost + rhs.heuristic);
    }
};

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

vector<state> nextMoves(state &currentstate)
{
    nextstates.clear();
    int blankX = -1, blankY = -1;
    for(int i =0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(currentstate.board[i][j] == 0)
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
                    newboard[i][j] = currentstate.board[i][j];
                }
            }
            swap(newboard[blankX][blankY], newboard[newX][newY]);
            nextstates.push_back(newboard);
        }
    }
    return nextstates;
}
bool isGoalState(const state &currentstate, const state &goalstate)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(currentstate.board[i][j] != goalstate.board[i][j])
            {
                return false;
                
            }
        }
    }
    return true;
}
void astarImplementation( const state& initial, const state &goalstate)
{
    priority_queue<state, vector<state>, CompareStates> openList;

    state initialState = initial;
    initialState.cost = 0;
    initialState.heuristic  = calculateHeuristic(initialState, goalstate);
    openList.push(initialState);


    vector<state> closedSet;

    while(!openList.empty())
    {
        state currentState = openList.top();
        openList.pop();


        if(isGoalState(currentState, goalstate))
        {
            cout<< "Goal state reached!"<<endl;
            return;
        }

        closedSet.push_back(currentState);
        vector<state> nextstates = nextMoves(currentState);

        for(const auto& onestate: nextstates)
        {
            if(find(closedSet.begin(), closedSet.end(), onestate) == closedSet.end())
            {
                onestate.cost = currentState.cost + 1;
            }
        }
    }
}


int manhattanDistance(int i, int j, int x, int y)
{
    return abs(x - i) + abs(y - j);
}

int calculateHeuristic(const state &currentstate, const state &goalstate)
{
    int heuristic = 0;

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(currentstate.board[i][j]!=0)
            {
                value = currentstate.board[i][j];
                for(int x=0;x<N;x++)
                {
                    for(int y=0;y<N;y++)
                    {
                        if(goalstate.board[x][y] == value)
                        {
                            heuristic += manhattanDistance(i,j,x,y);
                            break;
                        }
                    }
                }
            }
        }
    }
return heuristic;
}