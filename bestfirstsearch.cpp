#include<iostream>
#include<vector>
#include<queue>
#include<set>
using namespace std;
int possibleMoves[5][2] = {{1,0}, {0,1}, {2,0}, {0,2}, {1,1}};
struct state
{
    int missionaries_left;
    int cannibals_left;
    int missionaries_right;
    int cannibals_right;
    bool boatonLeft; //if boat on Left - return true, else return False

    //Default Constructor 
    state(int ml, int cl, int mr, int cr, bool b):
    missionaries_left(ml), cannibals_left(cl), missionaries_right(mr), cannibals_right(cr), boatonLeft(b){}

    //overload the == operator to check if two states are equal 
    bool operator==(const state &other) const
    {
        return missionaries_left == other.missionaries_left &&
        cannibals_left == other.cannibals_left &&
        missionaries_right == other.missionaries_right &&
        cannibals_right == other.cannibals_right &&
        boatonLeft == other.boatonLeft;
    }
};

struct stateHash
{
    bool operator()(const state &s1, const state &s2) const
    {
        return s1 == s2;
    }
};

state initialState = {3,3,0,0, true};
// state goalState = {0,0,3,3, false};

struct comparestates
{
    bool operator()(const state &lhs, const state &rhs) const
    {
        return (rhs.missionaries_right + rhs.cannibals_right) > (rhs.missionaries_left + rhs.missionaries_left);
    }
};

bool isGoalstate(const state &currentstate)
{
    if(currentstate.missionaries_right == 3 && currentstate.cannibals_right == 3 && currentstate.missionaries_left == 0 && currentstate.cannibals_left == 0)
    {
        return true;
    }
    // if(currentstate == goalState)
    // {
    //     return true;
    // }

return false;
}

bool isValidState(const state &currentstate)
{
    if(currentstate.missionaries_left >= currentstate.cannibals_left && currentstate.missionaries_right>=currentstate.cannibals_right)
    {
        return true;
    }
return false;
}
void generateStates(const state &currentstate, priority_queue<state, vector<state>, comparestates> OpenQueue, set <state, stateHash> visited)
{
    for(int i =0;i<5;i++)
    {
        int move[2] = {possibleMoves[i][0], possibleMoves[i][1]};

        int missionaries_L, cannibals_L, missionaries_R, cannibals_R;

        if(currentstate.boatonLeft == true)
        {
            missionaries_L = currentstate.missionaries_left - move[0];
            cannibals_L = currentstate.cannibals_left - move[1];
            missionaries_R = currentstate.missionaries_right + move[0];
            cannibals_R = currentstate.cannibals_right + move[1];
        }

        else
        {
            missionaries_L = currentstate.missionaries_left + move[0];
            cannibals_L = currentstate.cannibals_left + move[1];
            missionaries_R = currentstate.missionaries_right - move[0];
            cannibals_R = currentstate.cannibals_right - move[1];
        }
        state newState
        {
            missionaries_L,
            cannibals_L,
            missionaries_R,
            cannibals_R,
            !currentstate.boatonLeft
        };
        if(isValidState(newState) && visited.find(newState) == visited.end())
        {
            OpenQueue.push(newState);
        }
    }
}
void bestfirstsearch()
{
    priority_queue<state, vector<state>, comparestates> OpenQueue;
    set <state, stateHash> visited;
    OpenQueue.push(initialState);
cout<<"hello";
    while(!OpenQueue.empty())
    {
        state currentstate = OpenQueue.top();
        OpenQueue.pop();

        if(isGoalstate(currentstate))
        {
            cout<<"Solution found."<<endl;
            return;
        }
        if(isValidState(currentstate) && visited.find(currentstate) == visited.end())
        {
            visited.insert(currentstate);
            generateStates(currentstate, OpenQueue, visited);
        }
    }
    cout<<"No solution detected."<<endl;
}

int main()
{
    bestfirstsearch();
    return 0;
}