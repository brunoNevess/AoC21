#include <iostream>
#include <vector>
using namespace std;

int sum(vector<int>& v){
    int s = 0;
    for(int x: v) s += x;
    return s;
}

void print_vec(vector<int>& v){
    for(int x: v) cout << x << " ";
    cout << endl;
}

int main(){
   vector<int> v;
   int head;
   int ans = 0;
   for(int i = 0 ;i < 3 ; i++){
       cin >> head;
       v.push_back(head);
   }
   while(!cin.eof()){
       int s1 = sum(v);
       cin >> head;
       v.erase(v.begin());
       v.push_back(head);
       int s2 = sum(v);
       if(s2 > s1) ans++;
   }
   cout << ans << endl;    
}
