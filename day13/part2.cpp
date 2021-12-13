#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
int N = 4000; // make the grid big enough

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
    // reflect just "transports" points to the right of the horizontal/vertical line to the left
    // make two pointers walk in opposite directions

    void reflect(char c, int p){
        if(c == 'x'){
            for(int row = 0;row<N;++row){
                int left,right;
                left = right = p;
                for(int j = 0;j < N ;j++) grid[j][p] = '.'; // folded line
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
                for(int j = 0;j < N ;j++) grid[p][j] = '.'; // folded line
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
    for(pair<char,int> ci: g.instructs){
        g.reflect(ci.first,ci.second);
    }
    // The code is inside a rectangle (a,c) , (b,d)
    // so we have to get the first appereance of '#' and the last
    int a,b,c,d;
    bool first = true;
    for(int i = 0 ; i < N ;i++){
        for(int j = 0 ; j < N; j++){
            if(g.grid[i][j] == '#') {
                if(first){
                    a = i; b = j;
                    first = false;
                }
                c = i; d = j;
            }
        }
    }
    // try reading it ...
    for(int i=a;i<=c;i++){
        for(int j=b;j<=d;j++){
            cout << g.grid[i][j];
        }
        cout << endl;
    }
}