#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_map>
using namespace std;
typedef pair<int,int> ii;
unordered_map<int,ii> bitCount;
typedef unsigned long long int ull;
vector<string> v;
ull binToInt(string bin){
    ull s = 0;
    for(int i = 0;i<bin.size();i++){
        s = 2*s + (bin[i]-'0');
    }
    return s;
}
vector<string> getFiltered(vector<string>& v, int i,char f){
    vector<string> ans;
    for(int j = 0; j < v.size() ;j++){
        if(v[j][i] == f) ans.push_back(v[j]);
    }
    return ans;
}

void count(vector<string>& _v){
    bitCount.clear();
    for(string s:_v){
        int i = 0;
        for(char c: s){
            if(c == '1') bitCount[i].first++;
            else bitCount[i].second++;
            i++;
        }
    }
}

int main(){
    string input;
    while(!cin.eof()){
        int i = 0;
        cin >> input;
        v.push_back(input);
    }
    count(v);
    string  o2 = "",co2="";
    vector<string> tmp = v;
    int j = 0;
    while(true){
        if(bitCount[j].first >= bitCount[j].second){
            tmp = getFiltered(tmp,j,'1');
        } else {
            tmp = getFiltered(tmp,j,'0');
        }
        if(tmp.size() == 1) break;
        count(tmp);
        j++;
    }
    o2 = tmp[0];
    tmp = v;
    j = 0;
    count(v);
    while(true){
        if(bitCount[j].first < bitCount[j].second){
            tmp = getFiltered(tmp,j,'1');
        } else {
            tmp = getFiltered(tmp,j,'0');
        }
        if(tmp.size() == 1) break;
        count(tmp);
        j++;
    }
    co2 = tmp[0];
    cout << binToInt(o2)*binToInt(co2) << endl;
}