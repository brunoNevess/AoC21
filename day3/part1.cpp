#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_map>
using namespace std;
typedef pair<int,int> ii;
unordered_map<int,ii> bitCount;
typedef unsigned long long int ull;

ull binToInt(string bin){
    ull s = 0;
    for(int i = 0;i<bin.size();i++){
        s = 2*s + (bin[i]-'0');
    }
    return s;
}
int main(){
    string input;
    int len = 0;
    while(!cin.eof()){
        int i = 0;
        cin >> input;
        for(char c: input){
            if(c == '1') bitCount[i].first++;
            else bitCount[i].second++;
            i++;
        }
    }
    string gamma = "",epsilon="";
    for(int j = 0 ; j < input.size(); j++){
        if(bitCount[j].first > bitCount[j].second){
            gamma += "1";
            epsilon += "0";
        } else {
            gamma += "0";
            epsilon += "1";
        }
 
    }
    cout << binToInt(gamma)*binToInt(epsilon) << endl;
}