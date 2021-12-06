#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <unordered_map>
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

void solve(string str,int n){
    vector<ull> fishes(9,0);
    for(int x: parseInput(str)){
        fishes[x]++;
    }
    for(int i = 0 ; i<n;i++){
        ull deltaFish = fishes[0]; 
        for(int k=1;k<fishes.size();k++){
            fishes[k-1] = fishes[k];
        }
        fishes[6] += deltaFish;
        fishes[8] = deltaFish;
    }
    ull s = 0;
    for(ull x:fishes) s += x;
    cout << s << endl;
}

int main(){
    string str; getline(cin, str);
    cout << "Part1: "; 
    solve(str,80);
    cout << "Part2: ";
    solve(str,256);
    return 0;
}