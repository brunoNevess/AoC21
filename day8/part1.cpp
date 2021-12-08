#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main(){
    string x;
    int ans = 0;
    while(!cin.eof()){
        for(int i=0;i<10;i++){ cin >> x; }
        cin >> x; // get rid of |
        for(int j = 0 ; j < 4 ; j++){
            cin >> x;
            if(x.size() == 2 || x.size() == 4 || x.size() == 3 || x.size() == 7) ans++;
        }
    }
    cout << ans << endl;
}
