#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;
vector<int> dx = {0,0,1,-1};
vector<int> dy = {1,-1,0,0};
int N,M;
bool isValid(int x,int y){return x>=0 && x < N && y>=0 && y<M;}

void dfs(vector<vector<int>>& g,int i,int j,vector<vector<bool>>& vis,int& area){
    vis[i][j] = true;
    for(int k = 0 ; k < 4;k++){
        int nx = i + dx[k];
        int ny = j + dy[k];
        if( !isValid(nx,ny) || g[nx][ny] == 9 || vis[nx][ny]) continue;
        else {
            area++;
            dfs(g,nx,ny,vis,area);
        }
    }
    return;
}

int main(){
    string x;
    vector<vector<int>> g;
    int a = 0;
    while(!cin.eof()){
        cin >> x;
        g.push_back(vector<int>());
        for(int i=0;i<x.size();i++){
            int y = x[i] - '0'; g[a].push_back(y);
        }
        a++;
    }
    N = g.size(), M = g[0].size();
    vector<vector<bool>> vis(N,vector<bool>(M,false));
    priority_queue<int, vector<int>, greater<int>> pq; // min heap to store 3 largest values
    for(int i = 0; i < N; i++){
        for(int j = 0;j < M; j++){
            if(!vis[i][j]){
                int area = 0;
                dfs(g,i,j,vis,area);
                pq.push(area);
                if(pq.size() > 3) pq.pop();
            }
        }
    }
    int ans = 1;
    while(!pq.empty()) {
        ans *= pq.top(); pq.pop();
    }
    cout << ans << endl;
    return 0;
}