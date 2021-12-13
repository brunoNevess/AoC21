#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
int N = 4000;

vector<string> tokenize(string s, string del = " "){
    int start = 0;
    int end = s.find(del);
    vector<string> strs;
    while (end != -1) {
        strs.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    strs.push_back(s.substr(start, end - start));

    return strs;
}
vector<vector<char>> g(N,vector<char>(N,'.'));

struct Grid {
    
    vector<vector<char>> grid;
    vector<pair<char,int>> instructs;

    void read(){
        grid = vector<vector<char>> (N,vector<char>(N,'.'));
        string line;
        while(!cin.eof()){
            getline(cin,line); if(line.size() == 1) continue;
            if(!isdigit(line[0])){
                vector<string> v = tokenize(line);
                pair<char,int> ci;
                ci.first = v[2][0];
                ci.second = stoi(v[2].substr(2));
                instructs.push_back(ci);
            } else {
                int x,y;
                vector<string> v = tokenize(line,",");
                x = stoi(v[0]); y = stoi(v[1]);
                grid[y][x] = '#';
            }            
        } 
    }

    void reflect(char c, int p){
        if(c == 'x'){
            for(int row = 0;row<N;++row){
                int left,right;
                left = right = p;
                for(int j = 0;j < N ;j++) grid[j][p] = '.';
                while(left >= 0 && right < N){
                    if(grid[row][right] == '#'){
                        grid[row][left] = '#';
                    }
                    grid[row][right] = '.';
                    left--; right++;
                }
            }
        } else {
            for(int col = 0;col<N;++col){
                int up,down;
                up = down = p;
                for(int j = 0;j < N ;j++) grid[p][j] = '.';
                while(up >= 0 && down< N){
                    if(grid[down][col] == '#'){
                        grid[up][col] = '#';
                    }
                    grid[down][col] = '.';
                    up--; down++;
                }
            }
        }
    }
};

int main(){
    Grid g;
    g.read();
    int ans = 0;
    for(pair<char,int> ci: g.instructs){
        g.reflect(ci.first,ci.second);
        break; // we only want the first fold
    }
    for(int i = 0 ; i < N ;i++){
        for(int j = 0 ; j < N; j++){
           if(g.grid[i][j] == '#') ans++;
        }
    }
    cout << ans << endl;
}