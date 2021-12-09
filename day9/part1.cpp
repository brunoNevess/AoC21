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

int main(){
    string x;
    vector<vector<int>> g;
    int a = 0 , ans = 0;
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
    for(int i = 0; i < N; i++){
        for(int j = 0;j < M; j++){
            int c = 0;
            for(int k = 0 ; k < 4;k++){
                int nx = i + dx[k];
                int ny = j + dy[k];
                int p = isValid(nx,ny) ? g[nx][ny] : 10;
                if(g[i][j] < p) c++;
            }
            if(c == 4) ans += g[i][j] + 1;
        }
    }
    cout << ans << endl;
    return 0;
}

