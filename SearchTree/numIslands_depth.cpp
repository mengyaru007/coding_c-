#include<iostream>
#include<vector>

using namespace std;
vector<vector<char>> caseMG;
vector<vector<bool>> visit;
int direction[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};

void DFS(vector<vector<char>>& caseMG, int width, int length, int row, int col) 
{
    for(int i=0; i<4; i++)
    {
        int next_row = row + direction[i][0];
        int next_col = col + direction[i][1];
        if(next_row>=0 && next_row<width && next_col>= 0 && next_col<length && !visit[next_row][next_col] && caseMG[next_row][next_col] == '1')
        {
            
            visit[next_row][next_col] = true;
            DFS(caseMG, width, length, next_row, next_col);
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
                visit[i][j] = true;
                DFS(caseMG, width, length, i, j);
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
