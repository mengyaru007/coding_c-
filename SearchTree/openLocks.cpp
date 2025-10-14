#include<iostream>
#include<algorithm>
#include<limits>
#include<string>
#include<queue>
#include<unordered_map>
using namespace std;
int direction[8][2] = {{0, 1}, {0, -1}, {1, 1}, {1, -1}, {2, 1}, {2,-1}, {3, 1}, {3, -1}};
int res = INT_MAX;

// 拓展队列
void extendQueue(queue<pair<string, int>>& q, unordered_map<string, int>& cur_visit, unordered_map<string, int>& oth_visit, vector<string>& deadends)
{
    int n = q.size();
    while (n--)
    {
        pair<string, int> cur = q.front();
        q.pop();
        for(int i=0; i<8; i++)
        {
            string next = cur.first;
            next[direction[i][0]] = (next[direction[i][0]] - '0' + direction[i][1] + 10) % 10 + '0';
            // 判断新元素是否已在当前visit存在（已被访问过）且不会锁死
            if(find(deadends.begin(), deadends.end(), next) == deadends.end() && cur_visit.find(next) == cur_visit.end())
            {
                q.push({next, cur.second+1});
                cur_visit[next] = cur.second + 1;
                // 若新元素在另一个visit存在（在另一边已被访问）说明在另一边已被找到，更新最少步骤
                if(oth_visit.find(next) != oth_visit.end())
                {
                    res = min(res, oth_visit[next] + cur_visit[next]);
                }
            }
        }
    }
}

int BFS(vector<string>& deadends, string target)
{
    queue<pair<string, int>> qStart;
    queue<pair<string, int>> qEnd;
    unordered_map<string, int> start_visit;
    unordered_map<string, int> end_visit;
    // 初始化起点和终点(target)
    string start = "0000";
    if(find(deadends.begin(), deadends.end(), start) != deadends.end()) return -1;
    if(start == target) return 0;
    qStart.push({start, 0});
    start_visit[start] = 0;
    qEnd.push({target, 0});
    end_visit[target] = 0;
    while (!qStart.empty() && !qEnd.empty())
    {
        if(qStart.size() < qEnd.size())
        {
            extendQueue(qStart, start_visit, end_visit, deadends);
        }
        else
        {
            extendQueue(qEnd, end_visit, start_visit, deadends); 
        }
        if(res != INT_MAX) return res;
    }
    return -1;
}

int openLock(vector<string>& deadends, string target)
{
    return BFS(deadends, target);
}

int main()
{
    vector<string> deadends = {"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"};
    string target = "0000";
    cout << openLock(deadends, target);
}
