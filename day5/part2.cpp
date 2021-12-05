#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;

int N = 1000;
const double EPS = 1e-9;
typedef pair<int,int> ii;
vector<ii> parseInput(string str){
    vector<int> tmp;
    int a = 0;
    for(int i = 0 ; i < str.size();i++){
        if(isdigit(str[i])) a = 10*a + (str[i] - '0');
        if(str[i] == ','){
            tmp.push_back(a);
            a = 0;
        } else if(str[i] == ' '){
            tmp.push_back(a);
            a = 0;
            i += 3;
        }
    }
    tmp.push_back(a);
    ii p1(tmp[0],tmp[1]);
    ii p2(tmp[2],tmp[3]);
    return {p1,p2};
}

bool is45Degrees(ii p1,ii p2, ii& dir){
    double tg = abs(1.0*(p1.second - p2.second)/(p1.first - p2.first));
    if(fabs(tg - 1.0) > EPS) return false;
    dir.first = p1.first < p2.first ? +1 : -1;
    dir.second = p1.second < p2.second ? +1 : -1;
    return true;
}

int main(){
    string str;
    vector<vector<int>> grid(N,vector<int>(N,0));
    while(!cin.eof()){
        getline(cin, str);
        vector<ii> points;
        for(ii p:parseInput(str)) points.push_back(p);
        sort(begin(points), end(points));
        ii p1 = points[0], p2 = points[1],dir;
        
        if(p1.first == p2.first){
            int x = p1.first, dy = p1.second < p2.second ? + 1: -1;
            for(int y = p1.second; y != p2.second + dy; y += dy) grid[x][y]++;
        } else if(p1.second == p2.second){
            int y = p1.second, dx = p1.first < p2.first ? + 1: -1;
            for(int x = p1.first; x != p2.first + dx; x += dx) grid[x][y]++;
        } else if(is45Degrees(p1,p2,dir)){
            int dx = dir.first,dy = dir.second;
            for(int x = p1.first, y = p1.second ;x != p2.first + dx; x += dx , y += dy) grid[x][y]++;
        }
    }
    int ans = 0;
    for(int i = 0 ; i< N ; i++){
        for(int j = 0 ; j < N; j++){
           if(grid[i][j] >= 2) ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
 