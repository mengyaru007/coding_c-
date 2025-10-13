#include<iostream>
#include<vector>
#include<queue>

using namespace std;
vector<vector<char>> caseMG;
vector<vector<bool>> visit;
int direction[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};

struct Position
{
    int row;
    int col;
    Position(int r, int c): row(r), col(c) {}
};

void BFS(vector<vector<char>>& caseMG, int width, int length, int row, int col) 
{
    Position start = Position(row, col);
    queue<Position> myQueue;
    myQueue.push(start);
    visit[row][col] = true;
    while (!myQueue.empty())
    {
        Position cur = myQueue.front();
        myQueue.pop();
        for(int i=0; i<4; i++)
        {
            Position next = Position(cur.row + direction[i][0], cur.col + direction[i][1]);
            if(next.row>=0 && next.row<width && next.col>= 0 && next.col<length && !visit[next.row][next.col] && caseMG[next.row][next.col] == '1')
            {
                myQueue.push(next);
                visit[next.row][next.col] = true;
            }
        }
    }
}

int numsIslands(vector<vector<char>>& caseMG)
{
    int width = caseMG.size();
    int length = caseMG[0].size();
    int res = 0;
    visit.resize(caseMG.size(), vector<bool>(caseMG[0].size(), false));
    for(int i=0; i<width; i++)
    {
        for(int j=0; j<length; j++)
        {
            if(caseMG[i][j] == '1' && !visit[i][j])
            {
                BFS(caseMG, width, length, i, j);
                res++;
            }
        }
    }
    return res;
}

int main()
{
    caseMG = {{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}};
    printf("%d\n", numsIslands(caseMG));
}
