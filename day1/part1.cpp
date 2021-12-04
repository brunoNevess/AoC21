#include <iostream>

using namespace std;

int main(){
    int next,last;
    cin >> last;
    int ans = 0;
    while(!cin.eof()){
        cin >> next;
        if(next > last) ans++;
        last = next;
    }
    cout << ans << endl;
}
