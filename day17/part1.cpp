#include <bits/stdc++.h>
#include <climits>
using namespace std;
typedef long long int ull;

int xmin,xmax,ymin,ymax; // target area

void movex(int& x,int &v){ 
    x += v;
    if(v > 0) v -= 1;  // drag
    else if(v < 0) v += 1;
}

void movey(int& y, int& v){
    y += v;
    v -= 1; // gravity
}

int main(){
    scanf("target area: x=%d..%d, y=%d..%d",&xmin,&xmax,&ymin,&ymax);
    int ans = -1;
    for(int vx=xmax;vx>=0;vx--){  // vx cant be larger than the xmax of the grid area , otherwise is a overshoot
        for(int vy=500;vy>=0;vy--){ // just tried a bunch of vy values
            int x0 = 0, y0 = 0; int v0x = vx,v0y = vy; int hy = -1;
            while(v0x != 0){  // get the positions at which the x velocity is 0 , because for max height it stops at x and keeps falling in y
                hy = max(hy,y0); // highest y so far for this pair (vx,vy)
                movex(x0,v0x); movey(y0,v0y);
            }
            if((y0 >= ymin && y0 <= ymax)){ // if its inside grid area , update answer and skip
                ans = max(ans,hy);
                continue;
            }
            if(y0 < ymin || !(x0 >= xmin && x0 <= xmax)) continue; // if its below grid area , skip it 

            while(!(y0 >= ymin && y0 <= ymax) && !(y0 < ymin)){ // its a free fall , keep moving downwards until it maybe is inside grid area and not below
                movey(y0,v0y);
                if((y0 >= ymin && y0 <= ymax)){ // inside , update answer
                    ans = max(ans,hy);
                }
            } 
        }
    }
    cout << ans << endl;
    return 0;
}
