#include <bits/stdc++.h>
#include <climits>
using namespace std;
typedef unsigned long long int ull;
typedef pair<string,ull> si; // type pair<string,big int>

//initial state
unordered_map<char,ull> initialCnt; // count of initial chars
unordered_map<string,ull> initialPairCount; // count of pairs initials NC , BB ....
vector<pair<string,char>> rules; // NC -> B ...


void read(){
    string line, arrow; 
    cin >> line;
    for(char c: line){
        initialCnt[c]++; // initial count if inital template
    } 
    for(int i=0;i+1<line.size();i++){
        string tmp = ""; tmp += line[i]; tmp+=line[i+1];
        initialPairCount[tmp]++; // initate count of initial pairs
    }
    while(!cin.eof()){
        string s1; cin >> s1; cin >> arrow; 
        string s2; cin >> s2; 
        rules.push_back(make_pair(s1,s2[0])); // store rules
    }
}

//for every rule, for example NC->B, increase count of NB and CB (generated) and delete NC
//how much to inc ? by the current count of NC
//and for each rule , increase B by how many times NC is counted , and the pairs NB and CB by the same amount
void gen(unordered_map<char,ull>& cnt, unordered_map<string,ull>& pairCount){ 
    vector<string> toErase;
    vector<si> toAdd;
    for(auto rule:rules){ // for every rule ( pair (NC,B) ) ...
        string pair = rule.first; // NC
        char c = rule.second; // B
        if(pairCount.count(pair)){
            cnt[c] += pairCount[pair]; // increase 
            //generate pairs
            string np1; np1 += pair[0]; np1 += c;
            string np2 ; np2 += c ; np2 += pair[1];
            si si1(np1,pairCount[pair]);
            si si2(np2,pairCount[pair]);
            //save for later, to generate new counts
            toErase.push_back(pair);
            toAdd.push_back(si1); toAdd.push_back(si2);
        }
    }
    for(string x:toErase){ 
        pairCount.erase(x);
    }
    for(auto x:toAdd){
        pairCount[x.first] += x.second;;
    }
}

void solve(int n){
    unordered_map<char,ull> cnt = initialCnt; 
    unordered_map<string,ull> pairCount = initialPairCount;
    for(int i = 0 ; i < n;i++){ 
        gen(cnt,pairCount);
    }

    ull mn = LLONG_MAX; ull mx = 0;
    for(auto it = begin(cnt); it != end(cnt); it++){ // count of chars
        mn = min(mn,it->second);
        mx = max(mx,it->second);
    }
    cout << mx - mn << endl;
}

int main(){
    read();
    solve(10);
    solve(40);
    solve(100);
    solve(200);
    solve(400);
}

