#include<iostream>
#include<unordered_set>
#include<queue>
#include<vector>

using namespace std;
const int N = 3;
int moves[4][2] = {{-1, 0}, {1, 0}, {0,-1}, {0,1}};
struct state
{
    int board[N][N];

    state() = default;

    state(const int (&b)[N][N]) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                board[i][j] = b[i][j];
            }
        }
    }
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

namespace std {
    template <>
    struct hash<state> {
        size_t operator()(const state& state) const {
            size_t hash = 0;

            // A simple hash combining values in the board
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    hash ^= std::hash<int>{}(state.board[i][j]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
                }
            }

            return hash;
        }
    };
}
int pathboard[N][N];
state initialstate, finalstate;
vector <state> nextstates;

// void getpath(const state &state)
// {
//     for(int i=0;i<N;i++)
//     {
//         for(int j=0;j<N;j++)
//         {
//             pathboard[i][j] == state.board[i][j];
//         }
//     }
// }
bool isGoalState(state &currentstate)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(currentstate.board[i][j] != finalstate.board[i][j])
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
void printState(state &state)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout<<state.board[i][j];
        }
        cout<<endl;
    }
}
vector <state> nextMoves(state &currentstate)
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
            nextstates.emplace_back(newboard);

        }
    }
    return nextstates;
}

bool bfs(state &initialstate)
{
     queue<state> queue;
     unordered_set<state> visited;
     
     queue.push(initialstate);

     while(!queue.empty())
     {
        state currentState = queue.front();
        queue.pop();

        if(isGoalState(currentState))
        {
            cout<<"hello";
            printState(currentState);
            return true;
        }

        vector <state> nextstates = nextMoves(currentState);

        for(const state & state: nextstates)
        {
            if(visited.find(state)==visited.end())
            {
                queue.push(state);
                visited.insert(state);
            }
        }
     }

return false;
}

int main()
{

    cout<<"Enter the initial state of 8 puzzle: "<<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cin>> initialstate.board[i][j];
        }
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout<<initialstate.board[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"Enter the final state of 8 puzzle: "<<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cin>>finalstate.board[i][j];
        }
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout<<finalstate.board[i][j]<<" ";
        }
        cout<<endl;
    }


    if(bfs(initialstate))
    {
        cout<<"Solution Found!"<<endl;
    }
    else
    {
        cout<<"Solution not found."<<endl;
    }
}