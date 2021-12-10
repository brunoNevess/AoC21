#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

int main(){
    string x;
    unordered_map<char,int> points;
    points[')'] = 3; points[']'] = 57;
    points['}'] = 1197; points['>'] = 25137;
    unordered_map<char,int> opening;
    opening[']'] = '['; opening[')'] = '(';
    opening['}'] = '{'; opening['>'] = '<';
    unordered_set<char> open;
    for(char c: "({[<") open.insert(c);
    int ans = 0;
    while(!cin.eof()){
        stack<char> st;
        cin >> x;
        for(char c:x){
            if(open.count(c)){
                st.push(c);
            } else {
                char cc = opening[c];
                if(st.top() != cc){
                    ans += points[c];
                    break;
                }
                else st.pop();
                
            }
        }
    }
    cout << ans << endl;
}