#include <bits/stdc++.h>
#include <climits>
using namespace std;
typedef unsigned long long int ull;
typedef vector<int> vi;
typedef vector<vi> vvi;

struct step {
    int x0,y0,z0,x1,y1,z1;
    string s;
};
// given a coordinate, how to query its cube index ? 
int bin_search(vector<int>& v, int x){ return (int)(lower_bound(begin(v),end(v),x) - begin(v));}

int main(){
    string s;
    int x0,y0,z0,x1,y1,z1;
    vector<step> steps;
    vector<int> Xs,Ys,Zs;
    while(!cin.eof()){
        cin >> s >> x0 >> x1 >> y0 >> y1 >> z0 >> z1;
        x1++;y1++;z1++;
        step st;
        st.s = s;
        st.x0 = x0;
        st.y0 = y0;
        st.z0 = z0;
        st.x1 = x1;
        st.y1 = y1;
        st.z1 = z1;
        Xs.push_back(x0); Xs.push_back(x1);
        Ys.push_back(y0); Ys.push_back(y1);
        Zs.push_back(z0); Zs.push_back(z1);
        steps.push_back(st);
    }
    sort(begin(Xs),end(Xs));
    sort(begin(Ys),end(Ys));
    sort(begin(Zs),end(Zs));

    int N = Xs.size();

    vector<vector<vector<int>>> grid(N,vector<vector<int>>(N,vector<int>(N,0)));

    for(step& s: steps){
        // given a coordinate in a given axis , get its cube index 
        int cx0 = bin_search(Xs,s.x0);
        int cx1 = bin_search(Xs,s.x1);
        int cy0 = bin_search(Ys,s.y0);
        int cy1 = bin_search(Ys,s.y1);
        int cz0 = bin_search(Zs,s.z0);
        int cz1 = bin_search(Zs,s.z1);
        for(int x=cx0;x<cx1;x++){
            for(int y=cy0;y<cy1;y++){
                for(int z=cz0;z<cz1;z++){
                    grid[x][y][z] = s.s == "on" ? 1 : 0;
                }
            }
        }
    
    }
    int64_t ans = 0;

    for(int i = 0 ; i < N-1;i++){
        for(int j = 0 ; j < N-1;j++){
            for(int k = 0 ; k < N-1;k++){
                if(grid[i][j][k] != 0){ // cube (i,j) is on , therefore its contributions to the final answers is as below
                    ans += (int64_t)(Xs[i+1] - Xs[i])*(Ys[j+1]-Ys[j])*(Zs[k+1]-Zs[k]);
                }
            }
        }
    }
    cout << "Part2: " << ans << endl;
}