#include <bits/stdc++.h>
#include <climits>
using namespace std;
typedef long long int ull;

int xmin,xmax,ymin,ymax; // target area
void movex(int& x,int &v){ 
    x += v;
    if(v > 0) v -= 1;
    else if(v < 0) v += 1;
}

void movey(int& y, int& v){
    y += v;
    v -= 1; // gravity
}

int main(){
    scanf("target area: x=%d..%d, y=%d..%d",&xmin,&xmax,&ymin,&ymax);
    int ans = -1;
    int count = 0;
    for(int vx=xmax;vx>=0;vx--){ // vx cant be larger than the xmax of the grid area , otherwise is a overshoot
        for(int vy=5000;vy>=-5000;vy--){ // just tried a bunch of vy values
            int x0 = 0, y0 = 0; int v0x = vx,v0y = vy;
            while(true){ // we just care if its inside grid, keep updating until it is or ,if below, break it
                movex(x0,v0x); movey(y0,v0y);
                if((x0 >= xmin && x0 <= xmax) && (y0 >= ymin && y0 <= ymax)){
                    count++;
                    break; 
                }
                if(y0 < ymin || x0 > xmax) break;
            }
        }
    }
    cout << count << endl;
    return 0;
}