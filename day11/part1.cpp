#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int N = 10;
vector<int> dx = {0,0,1,-1,1,-1,1,-1};
vector<int> dy = {-1,1,0,0,1,-1,-1,1};

bool isValid(int i,int j){return i >=0 && i < N && j >=0 && j < N;}
typedef pair<int,int> ii;

struct Grid {
    vector<vector<int>> grid; 

    void read() { 
        grid = vector<vector<int>>(N,vector<int>(N));
        int row = 0;
        while(!cin.eof()){
            string line; cin >> line;
            int col = 0;
            for(char c:line){
                int a = c - '0'; grid[row][col++] = a;
            }
            row++;
        }
    }
    
    bool isSync(){ // check if all cells are flashes
        for(int i=0;i<N;i++) {
            for(int j=0;j<N;j++) {
                if(grid[i][j] != 0) return false;
            }
        }
        return true;
    }

    void increase(){ // increase all cells by one
        for(int i=0;i<N;i++) {
            for(int j=0;j<N;j++){
                grid[i][j]++;
            } 
        }
    }

    int bfs(){
        increase();
        queue<ii> q;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(grid[i][j] == 10) q.push((ii(i,j))); // insert all 10's first in queue for processing
            }
        }
        int explosions = q.size();
        while(!q.empty()){
            ii next = q.front(); q.pop();
            int x = next.first, y = next.second;
            for(int k = 0; k < dx.size(); k++){
                int nx = x + dx[k], ny = y + dy[k];
                if(isValid(nx,ny)){
                    grid[nx][ny]++;
                    if(grid[nx][ny] == 10) { // we only care for cells that flashes once
                        explosions++;
                        q.push(ii(nx,ny));
                    }
                }
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(grid[i][j] >= 10) grid[i][j] = 0; // reset all greater than 10 to 0
            }
        }
        return explosions;
    }
};

int main(){
    Grid g;
    g.read();
    int flashes = 0, steps = 1,part1 = -1;
    while(!g.isSync()){
        flashes += g.bfs();
        if(steps == 100) part1 = flashes;
        steps++;
    }
    cout << "Part1: " << part1 << endl;
    cout << "Part2: " << steps << endl;
    cout << "Total flashes in " << steps << " steps: " << flashes << endl;
    return 0;
}
