#include <iostream> //i/o capabilities
#include <vector> //STL for vector - dynamic array
#include <stack> //STL for stack (stack container)
#include <algorithm> //used for algos on data structs. like Swap!
#include <map>

using namespace std;

typedef vector<vector<int>> PuzzleState; //defined a vector for the 8 Puzzle Board

enum ActionType { UP, DOWN, LEFT, RIGHT}; //Defined enum for Actions - L,R,U,D

map<ActionType, string> actionStrings = 
{
    {UP,"UP"}, {DOWN, "DOWN"}, {LEFT, "LEFT"}, {RIGHT, "RIGHT"},
}; //Map that maps the ActionType enum to Strings for each direction

void print(PuzzleState state)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
             cout<<state[i][j]<<"_";
        }
           cout<<endl;
    }
    cout<<endl;
}