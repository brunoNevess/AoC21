#include <bits/stdc++.h>
#include <climits>
using namespace std;
typedef long long int ull;
typedef vector<int> vi;
typedef vector<vi> vvi;

int main(){
    int N = 50; 
    int SIZE = 2*N + 2;
    vector<vector<vector<int>>> grid(SIZE,vector<vector<int>>(SIZE,vector<int>(SIZE,0)));
    string s;
    int x0,y0,z0,x1,y1,z1;
    while(!cin.eof()){
        cin >> s >> x0 >> x1 >> y0 >> y1 >> z0 >> z1;
        x0 = max(x0,-N) + N;
        y0 = max(y0,-N) + N;
        z0 = max(z0,-N) + N;
        x1 = min(x1,N) + N;
        y1 = min(y1,N) + N;
        z1 = min(z1,N) + N;
        for(int x=x0;x<=x1;x++){
            for(int y=y0;y<=y1;y++){
                for(int z=z0;z<=z1;z++){
                    grid[x][y][z] = s == "on" ? 1 : 0;
                }
            }
        }
        
    }
    int ans = 0;
    for(int x=0;x<2*N+2;x++){
        for(int y=0;y<2*N+2;y++){
            for(int z=0;z<2*N+2;z++){
                ans += grid[x][y][z];
            }
        }
    }
    cout << "Part1: " << ans << endl;
}