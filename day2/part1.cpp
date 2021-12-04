#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
class point {
public:
    ull x,y;
    point(int _x,int _y){x = _x; y = _y;}

    void read(){
        string key;
        int val;
        cin >> key >> val;
        if(key == "forward") x += val;
        else y += key == "up" ? -val : val;
    }
    void printAns(){
        cout << x << " " << y << endl;
        cout << x*y << endl;
    }

};

int main() {
    point p(0,0);
    while(!cin.eof()){
        p.read();
    }
    p.printAns();
}