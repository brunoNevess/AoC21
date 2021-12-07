#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;

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

int getMedian(vector<int>& v){
    int n = v.size();
    if (n % 2 == 0){
      return (v[n / 2 - 1] + v[n / 2]) / 2;
    }
      return v[n / 2];
}

int computeCost(vector<int>& v,int x){
    int s = 0;
    for(int a: v) s+= abs(a-x);
    return s;
}
int main(){
    vector<int> nums;
    string line; getline(cin,line);
    for(int x: parseInput(line)) nums.push_back(x);
    sort(begin(nums),end(nums));
    int optX = getMedian(nums);
    cout << computeCost(nums,optX) << endl;
    return 0;
}