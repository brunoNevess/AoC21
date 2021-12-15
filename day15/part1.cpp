// if the problem only allowed right,down movements , it could be solved by the following: 
// vector<vector<int>> dp(N,vector<int>(M,INT_MAX));
// dp[0][0] = 0;
// for(int i = 1 ; i < M;i++) dp[0][i] = g[0][i] + dp[0][i-1];
// for(int i = 1 ; i < N;i++) dp[i][0] = g[i][0] + dp[i-1][0];
// for(int i = 1; i < N ; i++){
//     for(int j = 1;j<M;j++){
//         dp[i][j] = g[i][j] +  min(dp[i-1][j],dp[i][j-1]);
//     }
// }
// cout << dp[N-1][M-1] << endl;

#include <bits/stdc++.h>
#include <climits>
using namespace std;
typedef pair<int,int> ii;
vector<int> dx = {0,0,1,-1};
vector<int> dy = {1,-1,0,0};
vector<vector<int>> g;
int N,M;

bool isValid(int x,int y){return x>=0 && x < N && y>=0 && y<M;}

//just a little helper, if we are at position (i,j) in graph , then this is the i*M + j vertex
//we can also get the position from te vertex number , by quotient and remainder (i*M + j) / M = i , (i*M + j)%M = j
int id(int i,int j){
    return i*M + j;
}
//boring building graph
void buildGraph(){
    string line;
    int row = 0;
    while(!cin.eof()){
        cin >> line; g.push_back(vector<int>());
        for(int col = 0 ; col < line.size() ; col++){
            int num = line[col] - '0'; g[row].push_back(num);
        }
        row++;
    }
    N = g.size(); M = g[0].size();
}

// making a min heap with a pair of (weight,vertex) is simpler
vector<int> djs(){
    priority_queue<ii,vector<ii>,greater<ii>> pq; // this heap makes the vertex with the smallest acc sum at the top
    vector<int> d(N*M,INT_MAX); // store the distances / acumulated sums
    d[0] = 0;
    pq.push(ii(0,0));
    while(!pq.empty()){
        ii next = pq.top();  pq.pop();
        int dd = next.first; int u = next.second;
        int x = u/M; int y = u%M;// get positions
        if(d[u] < dd) continue; // if this guy has already been processed with a smaller dist, throw it away
        for(int k = 0 ; k < 4 ; k++){ // or every neighbour...
            int nx = x + dx[k]; int ny = y + dy[k];
            if(isValid(nx,ny)){
                int v = id(nx,ny);
                if(d[v] > d[u] + g[nx][ny]){
                    d[v] = d[u] + g[nx][ny]; // acumulated cost + current cost at that position 
                    pq.push(ii(d[v],v));
                }
            }
        }
    }
    return d;
}


int main(){
    buildGraph();
    vector<int> d = djs();
    cout << d[id(N-1,M-1)] << endl;
}
