#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
int mod(int x,int m){return ((x%m) + m)%m;}
int N,M;
vector<string> grid;

bool step(){
    vector<string> orig = grid;
    vector<string> ng = grid;
    for(int i = 0; i < N;i++)
        for(int j = 0 ; j < M; j++){
            char& c = grid[i][j];
            if(c == '>') {
                int nj = mod(j+1,M);   
                if(grid[i][nj] == '.'){
                   swap(ng[i][j],ng[i][nj]);
                } 
            }
        }
    grid = ng;
    ng = grid;
    for(int i = 0; i < N;i++)
        for(int j = 0 ; j < M; j++){
            char& c = grid[i][j];
            if(c == 'v') {
                int ni = mod(i+1,N);   
                if(grid[ni][j] == '.'){
                   swap(ng[i][j],ng[ni][j]);
                } 
            }
        }
    grid = ng;
    return grid != orig;
}

int main(){
    while(!cin.eof()){
        string x; cin >> x;
        grid.push_back(x);
    }
    N = grid.size();
    M = grid[0].size();
    int steps = 1;
    while(step()) steps++;
    cout << steps << endl;
}

