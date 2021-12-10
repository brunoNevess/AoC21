#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

typedef unsigned long long int ull;

int main(){
    string x;
    unordered_map<char,int> points;
    points[')'] = 1; points[']'] = 2;
    points['}'] = 3; points['>'] = 4;

    unordered_map<char,int> opening;
    opening[']'] = '['; opening[')'] = '(';
    opening['}'] = '{'; opening['>'] = '<';

    unordered_map<char,int> closing;
    closing['['] = ']'; closing['('] = ')';
    closing['{'] = '}'; closing['<'] = '>';

    unordered_set<char> open;
    for(char c: "({[<") open.insert(c);
    
    int ans = 0;
    vector<ull> v;
    while(!cin.eof()){
        bool f = false;
        stack<char> st;
        cin >> x;
        for(char c:x){
            if(open.count(c)){
                st.push(c);
            } else {
                char cc = opening[c];
                if(st.top() != cc){
                    ans += points[c];
                    f = true;
                    break;
                }
                else st.pop();
            }
        }
        if(!f && !st.empty()) {
            string incomplete = "";
            while(!st.empty()){
                incomplete += closing[st.top()]; st.pop();
            }
            ull p = 0;
            for(char c: incomplete) p = 5*p + points[c];
            v.push_back(p);
        }
    }
    sort(begin(v),end(v));
    cout << v[v.size()/2] << endl;
}