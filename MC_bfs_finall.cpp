#include<iostream>
#include<queue>
#include<vector>
#include<unordered_map>
#include<string>

using namespace std;
state initialstate, finalstate;
struct state
{
    int scene[4][1]; //state[0] == m_L, state[1] == c_L, state[2] == m_R, state[3] == c_R

    state() = default;
    state(const int (&b)[1][4]) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 1; ++j) {
                scene[i][j] = b[i][j];
            }
        }
    }
        bool operator==(const state& other) const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 1; ++j) {
                if (scene[i][j] != other.scene[i][j]) {
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
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 1; ++j) {
                    hash ^= std::hash<int>{}(state.scene[i][j]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
                }
            }

            return hash;
        }
    };
}

bool isGoalState(state &currentstate)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<1;j++)
        {
            if(currentstate.scene[i][j] != finalstate.scene[i][j])
            {
                return false;
                
            }
        }
    }
    return true;
}

void printState(state &state)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<1;j++)
        {
            cout<<state.scene[i][j];
        }
        cout<<endl;
    }
}
int main()
{
    cout<<"Enter the initial state: "<<endl;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<1;j++)
        {
            cin>> initialstate.scene[i][j];
        }
         cout<<endl;
    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<1;j++)
        {
            cout<<initialstate.scene[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"Enter the final state: "<<endl;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<1;j++)
        {
            cin>> finalstate.scene[i][j];
        }
         cout<<endl;
    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<1;j++)
        {
            cout<<finalstate.scene[i][j]<<" ";
        }
        cout<<endl;
    }
}