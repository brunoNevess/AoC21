#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int decode(vector<string>& s, unordered_map<string,int>& d, unordered_map<char,char>& mp){
    int decoded = 0;
    for(string x: s){
        string p = ""; for(char c:x){ p += mp[c];}
        sort(begin(p),end(p));
        decoded = 10*decoded + d[p];
    }
    return decoded;
}

int main(){
    string x; vector<string> toDec;
    unordered_map<char,int> count; // count of every segment in numbers 0...9
    unordered_map<char,char> mp; // mapping from new setting to original

    unordered_map<string,int> d; // original setting
    d["abcefg"] = 0; d["cf"] =   1; d["acdeg"] = 2;
    d["acdfg"] =  3; d["bcdf"] = 4; d["abdfg"] = 5;
    d["abdefg"] = 6; d["acf"] =  7; d["abcdefg"] = 8; d["abcdfg"] = 9;

    int ans = 0;
    while(!cin.eof()){
        mp.clear(); toDec.clear(); count.clear();
        string s1,s7,s4,s8; // numbers 1,4,7,8
        for(int i = 0; i < 10; i++){
            cin >> x; for(char c:x) count[c]++;
            if(x.size() == 2) { s1 = x; } if(x.size() == 4) { s4 = x; }
            if(x.size() == 3) { s7 = x; } if(x.size() == 7) { s8 = x; }
        }
        for(auto it=begin(count); it!=end(count); it++){
           if(it->second == 6) mp[it->first] = 'b';  // b is the only one that appears 6 times
           if(it->second == 4) mp[it->first] = 'e';  // ...
           if(it->second == 9) mp[it->first] = 'f';  // ...
        }
        // use information from 1,7,4 and 8 to uniquely determine the others (in this order)
        for(char c: s1) { if(!mp.count(c)) mp[c] = 'c';}
        for(char c: s7) { if(!mp.count(c)) mp[c] = 'a';}
        for(char c: s4) { if(!mp.count(c)) mp[c] = 'd';}
        for(char c: s8) { if(!mp.count(c)) mp[c] = 'g';}
        cin >> x; // get rid of |
        for(int j = 0 ; j < 4 ; j++){ cin >> x; toDec.push_back(x); }
        ans += decode(toDec,d,mp);
    }
    cout << ans << endl;
}
