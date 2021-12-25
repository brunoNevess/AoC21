#include <bits/stdc++.h>
using namespace std;

struct VectorHasher {
    int64_t operator()(const vector<int64_t> &V) const {
        int64_t hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

vector<vector<string>> ops = {
    {"inp", "w"}, {"mul", "x", "0"}, {"add", "x", "z"}, {"mod", "x", "26"}, {"div", "z", "1"}, {"add", "x", "13"}, 
    {"eql", "x", "w"}, {"eql", "x", "0"}, {"mul", "y", "0"},  {"add", "y", "25"}, {"mul", "y", "x"}, {"add", "y", "1"}, {"mul", "z", "y"}, {"mul", "y", "0"}, {"add", "y", "w"}, 
    {"add", "y", "0"}, {"mul", "y", "x"}, {"add", "z", "y"}, {"inp", "w"}, {"mul", "x", "0"}, {"add", "x", "z"}, 
    {"mod", "x", "26"}, {"div", "z", "1"}, {"add", "x", "11"}, {"eql", "x", "w"}, {"eql", "x", "0"}, {"mul", "y", "0"},  {"add", "y", "25"}, {"mul", "y", "x"}, {"add", "y", "1"}, 
    {"mul", "z", "y"}, {"mul", "y", "0"}, {"add", "y", "w"}, {"add", "y", "3"}, {"mul", "y", "x"}, {"add", "z", "y"}, 
    {"inp", "w"}, {"mul", "x", "0"}, {"add", "x", "z"},  {"mod", "x", "26"}, {"div", "z", "1"}, {"add", "x", "14"}, 
    {"eql", "x", "w"}, {"eql", "x", "0"}, {"mul", "y", "0"},  {"add", "y", "25"}, {"mul", "y", "x"}, {"add", "y", "1"}, 
    {"mul", "z", "y"}, {"mul", "y", "0"}, {"add", "y", "w"}, {"add", "y", "8"}, {"mul", "y", "x"}, {"add", "z", "y"}, 
    {"inp", "w"}, {"mul", "x", "0"}, {"add", "x", "z"}, {"mod", "x", "26"}, {"div", "z", "26"}, {"add", "x", "-5"}, 
    {"eql", "x", "w"}, {"eql", "x", "0"}, {"mul", "y", "0"}, {"add", "y", "25"}, {"mul", "y", "x"}, {"add", "y", "1"}, 
    {"mul", "z", "y"}, {"mul", "y", "0"}, {"add", "y", "w"}, {"add", "y", "5"}, {"mul", "y", "x"}, {"add", "z", "y"}, 
    {"inp", "w"}, {"mul", "x", "0"}, {"add", "x", "z"},  {"mod", "x", "26"}, {"div", "z", "1"}, {"add", "x", "14"},  {"eql", "x", "w"}, {"eql", "x", "0"}, {"mul", "y", "0"}, 
    {"add", "y", "25"}, {"mul", "y", "x"}, {"add", "y", "1"}, {"mul", "z", "y"}, {"mul", "y", "0"}, {"add", "y", "w"}, 
    {"add", "y", "13"}, {"mul", "y", "x"}, {"add", "z", "y"}, {"inp", "w"}, {"mul", "x", "0"}, {"add", "x", "z"},  {"mod", "x", "26"}, {"div", "z", "1"}, {"add", "x", "10"}, 
    {"eql", "x", "w"}, {"eql", "x", "0"}, {"mul", "y", "0"}, {"add", "y", "25"}, {"mul", "y", "x"}, {"add", "y", "1"}, 
    {"mul", "z", "y"}, {"mul", "y", "0"}, {"add", "y", "w"}, {"add", "y", "9"}, {"mul", "y", "x"}, {"add", "z", "y"}, 
    {"inp", "w"}, {"mul", "x", "0"}, {"add", "x", "z"}, {"mod", "x", "26"}, {"div", "z", "1"}, {"add", "x", "12"}, {"eql", "x", "w"}, 
    {"eql", "x", "0"}, {"mul", "y", "0"}, {"add", "y", "25"},  {"mul", "y", "x"}, {"add", "y", "1"}, {"mul", "z", "y"}, {"mul", "y", "0"}, {"add", "y", "w"}, {"add", "y", "6"}, 
    {"mul", "y", "x"}, {"add", "z", "y"}, {"inp", "w"}, {"mul", "x", "0"},  {"add", "x", "z"}, {"mod", "x", "26"}, {"div", "z", "26"}, {"add", "x", "-14"}, 
    {"eql", "x", "w"}, {"eql", "x", "0"}, {"mul", "y", "0"}, {"add", "y", "25"}, {"mul", "y", "x"}, {"add", "y", "1"}, {"mul", "z", "y"}, {"mul", "y", "0"}, 
    {"add", "y", "w"}, {"add", "y", "1"}, {"mul", "y", "x"}, {"add", "z", "y"}, {"inp", "w"}, {"mul", "x", "0"}, {"add", "x", "z"}, {"mod", "x", "26"}, {"div", "z", "26"}, 
    {"add", "x", "-8"}, {"eql", "x", "w"}, {"eql", "x", "0"}, {"mul", "y", "0"}, {"add", "y", "25"}, {"mul", "y", "x"}, {"add", "y", "1"}, {"mul", "z", "y"}, {"mul", "y", "0"}, {"add", "y", "w"}, 
    {"add", "y", "1"}, {"mul", "y", "x"}, {"add", "z", "y"}, {"inp", "w"}, {"mul", "x", "0"}, {"add", "x", "z"},{"mod", "x", "26"}, {"div", "z", "1"}, {"add", "x", "13"}, {"eql", "x", "w"}, {"eql", "x", "0"}, 
    {"mul", "y", "0"}, {"add", "y", "25"}, {"mul", "y", "x"}, {"add", "y", "1"}, {"mul", "z", "y"}, {"mul", "y", "0"}, {"add", "y", "w"}, {"add", "y", "2"}, {"mul", "y", "x"}, {"add", "z", "y"}, {"inp", "w"}, 
    {"mul", "x", "0"}, {"add", "x", "z"}, {"mod", "x", "26"}, {"div", "z", "26"}, {"add", "x", "0"}, {"eql", "x", "w"},{"eql", "x", "0"}, {"mul", "y", "0"}, {"add", "y", "25"}, {"mul", "y", "x"}, {"add", "y", "1"}, {"mul", "z", "y"}, 
    {"mul", "y", "0"}, {"add", "y", "w"}, {"add", "y", "7"}, {"mul", "y", "x"}, {"add", "z", "y"}, {"inp", "w"}, {"mul", "x", "0"}, {"add", "x", "z"}, {"mod", "x", "26"}, {"div", "z", "26"}, {"add", "x", "-5"}, {"eql", "x", "w"}, {"eql", "x", "0"},
    {"mul", "y", "0"}, {"add", "y", "25"}, {"mul", "y", "x"}, {"add", "y", "1"}, {"mul", "z", "y"}, {"mul", "y", "0"}, {"add", "y", "w"}, {"add", "y", "5"}, {"mul", "y", "x"}, {"add", "z", "y"}, {"inp", "w"}, {"mul", "x", "0"}, {"add", "x", "z"}, {"mod", "x", "26"}, {"div", "z", "26"}, {"add", "x", "-9"}, 
    {"eql", "x", "w"}, {"eql", "x", "0"}, {"mul", "y", "0"}, {"add", "y", "25"}, {"mul", "y", "x"}, {"add", "y", "1"},  {"mul", "z", "y"}, {"mul", "y", "0"}, {"add", "y", "w"}, {"add", "y", "8"}, {"mul", "y", "x"}, {"add", "z", "y"}, {"inp", "w"},
    {"mul", "x", "0"}, {"add", "x", "z"}, {"mod", "x", "26"}, {"div", "z", "26"}, {"add", "x", "-1"}, {"eql", "x", "w"},  {"eql", "x", "0"}, {"mul", "y", "0"}, {"add", "y", "25"}, {"mul", "y", "x"}, {"add", "y", "1"}, {"mul", "z", "y"}, {"mul", "y", "0"}, {"add", "y", "w"}, {"add", "y", "15"}, {"mul", "y", "x"}, {"add", "z", "y"} 
};


typedef pair<bool,string> bool_str;

unordered_map<vector<int64_t>,bool_str,VectorHasher> dp;

int64_t THRESHOLD = 1e7;
bool_str find(int64_t idx, int64_t w,int64_t x,int64_t y, int64_t z){
    if(dp.count({idx,w,x,y,z})) return dp[{idx,w,x,y,z}];
    if(z > THRESHOLD){
        return bool_str(false,""); 
    }
    if(idx >= ops.size()){
        return bool_str(z == 0,"");
    }
    unordered_map<string,int64_t> vals;
    vals["w"] = w; vals["x"] = x;
    vals["y"] = y; vals["z"] = z;

    vector<string> op = ops[idx];
    if(op[0] == "inp"){
        // for the minimum , we do this for loop as d = 9 ... 1
        for(int64_t d = 9 ; d > 0 ; d--){
            vals[op[1]] = d;
            bool_str res = find(idx+1,vals["w"],vals["x"],vals["y"],vals["z"]);
            if(res.first){
                return dp[{idx,w,x,y,z}] = bool_str(true,to_string(d) + res.second);
            }
        }
        return dp[{idx,w,x,y,z}] = bool_str(false,"0");
    }
    // a b , a is where result is gonna be stored
    int64_t bval = vals.count(op[2]) ? vals[op[2]] : stoi(op[2]);
    string a = op[1];
    string operation = op[0];
    if(operation == "add") vals[a] += bval;
    else if(operation == "mul") vals[a] *= bval;
    else if(operation == "div"){
        if(bval == 0) return bool_str(false,"0");
        vals[a] = (int64_t)vals[a] / bval;
    }
    else if(operation == "mod"){
        if(vals[a] < 0 || bval <= 0) return bool_str(false,"0");
        vals[a] %= bval;
    }
    else if(operation == "eql"){
        vals[a] = vals[a] == bval ? 1 : 0;
    }

    return dp[{idx,w,x,y,z}] = find(idx+1,vals["w"],vals["x"],vals["y"],vals["z"]);

}

int main(){
    bool_str ans = find(0,0,0,0,0);
    cout << ans.second << endl;
}