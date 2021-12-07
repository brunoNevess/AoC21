#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef unsigned long long ull;
const int INF = 1e9 + 8;
vector<int> parseInput(string str){
    vector<int> tmp;
    int a = 0;
    for(int i = 0 ; i < str.size();i++){
        if(isdigit(str[i])) a = 10*a + (str[i] - '0');
        if(str[i] == ','){
            tmp.push_back(a);
            a = 0;
        }
    }
    tmp.push_back(a);
    return tmp;
}

int arith_sum(int n){
    return ((1+n)*n)/2;
}



int main(){
    vector<int> nums;
    string line; getline(cin,line);
    int mx = -INF;
    for(int x: parseInput(line)) {
        nums.push_back(x);
        mx = max(x,mx);
    }
    sort(begin(nums),end(nums));
    unordered_map<int,int> mp;
    int ans = INF;
    for(int i=0;i<=mx;i++){
        int curr = 0;
        for(int j=0;j<nums.size();j++){
            int n = abs(nums[j] - i);
            curr += arith_sum(n);
        }
        ans = min(curr,ans);
    }
    cout << ans << endl;
    return 0;
}
