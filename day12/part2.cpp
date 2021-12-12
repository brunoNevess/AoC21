#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;
unordered_map<string,vector<string>> graph;

void read(){
    string x; cin >> x;
    string n1 = "", n2; int i = 0;
    while(x[i] != '-') n1 += x[i++];
    n2 = x.substr(i+1);
    if(!graph.count(n1)) graph[n1] = vector<string>();
    if(!graph.count(n2)) graph[n2] = vector<string>();
    graph[n1].push_back(n2);
    graph[n2].push_back(n1);
}

//backtracking
//the path variable is just for printing the path for debug
void dfs(string u, unordered_set<string>& vis,int& ans,bool& twice, vector<string>& path){
    if(u == "end"){
        ans++;
        // for(string x: path) cout << x << " ";
        // cout << endl;
        return;
    }
    // for every v adjacent to u
    for(string v: graph[u]){
        if(islower(v[0])){ // if small cave , visit at most twice
            if(!vis.count(v)){ // if it was never visited before
                vis.insert(v);
                path.push_back(v);
                dfs(v,vis,ans,twice,path);
                path.pop_back();
                vis.erase(v);
            } else { // if no other node was visited twice, make this one be the one
                if(!twice && v != "start"){
                    path.push_back(v);
                    twice = true;
                    dfs(v,vis,ans,twice,path);
                    twice = false;
                    path.pop_back();
                }
            }
           
        } else { // big cave , return as you wish
            path.push_back(v);
            dfs(v,vis,ans,twice,path); 
            path.pop_back();
        }
    }
}



int main(){
    while(!cin.eof()){
        read();
    }
    int ans = 0;
    unordered_set<string> vis;
    vis.insert("start");
    bool twice = false;
    vector<string> p;
    p.push_back("start");
    dfs("start",vis,ans,twice,p);
    cout << ans << endl;       

}