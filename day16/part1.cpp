#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long int ull; 
int versions = 0; // answer for part1

ull binToInt(string bin){ // binary string to to int
    ull s = 0;
    for(int i = 0;i<bin.size();i++){
        s = 2*s + (bin[i]-'0');
    }
    return s;
}

struct Packet {
    ull id,version,val;
    vector<Packet> subPackets; // if its an operator , save its sub packets
    bool read(string& bin,int& i){ // i is the pointer of the outermost package
        if(i + 5 >= bin.size()) return false;
        string sversion  = ""; sversion += bin[i]; sversion += bin[i+1]; sversion += bin[i+2];
        string sid = ""; sid += bin[i+3]; sid += bin[i+4]; sid += bin[i+5];
        id = binToInt(sid); version = binToInt(sversion);
        versions += version;
        i = i + 6;
        if(i >= bin.size()) return false;
        if(id == 4){ // already a value
            string num = "";
            while(bin[i] != '0'){
                num += bin[i+1] ;num += bin[i+2] ; num += bin[i+3] ; num += bin[i+4];
                i = i + 5;  
            }
            num += bin[i+1] ;num += bin[i+2] ; num += bin[i+3] ; num += bin[i+4];
            i = i + 5;
            val = binToInt(num);
        } else { // operator, at the end evaluate its value
            int length = bin[i] == '0' ? 15 : 11;
            i = i + 1; 
            string len = ""; for(int j = 0;j<length;j++) len += bin[i++];
            if(length == 15){
                ull subpacklen = binToInt(len); int L = i + subpacklen;
                while(i < L){
                    Packet p; 
                    if(p.read(bin,i)) subPackets.push_back(p);
                }
            } else {
                ull numbersubPack = binToInt(len);
                for(int r = 0 ; r < numbersubPack ; r++){
                    Packet p;
                    if(p.read(bin,i)) subPackets.push_back(p);
                }
            }
            evaluate(); 
        }
      
        return true;
    }
    
    void evaluate(){
        ull res;
        if(id == 0){
            res = 0;
            for(Packet& p:subPackets){ res += p.val;}
            val = res;
        }
        if(id == 1){
            res = 1;
            for(Packet& p:subPackets){ res *= p.val;}
            val = res;
        }
        if(id == 2){
            res = INT_MAX;
            for(Packet& p:subPackets){ res = min(res,p.val);}
            val = res;
        }
        if(id == 3){
            res = 0;
            for(Packet& p:subPackets){ res = max(res,p.val);}
            val = res;
        }
        if(id == 5){
            val = subPackets[0].val > subPackets[1].val ? 1 : 0;
        }
        if(id == 6){
            val = subPackets[0].val < subPackets[1].val ? 1 : 0;
        }
        if(id == 7){
            val = subPackets[0].val == subPackets[1].val ? 1 : 0;
        }
    }
};

int main(){
    unordered_map<char,string> toBin;
    toBin['0'] = "0000";toBin['1'] = "0001"; toBin['2'] = "0010"; toBin['3'] = "0011"; toBin['4'] = "0100";
    toBin['5'] = "0101";toBin['6'] = "0110"; toBin['7'] = "0111"; toBin['8'] = "1000"; toBin['9'] = "1001"; toBin['A'] = "1010";
    toBin['B'] = "1011";toBin['C'] = "1100"; toBin['D'] = "1101"; toBin['E'] = "1110"; toBin['F'] = "1111";
    string line; cin >> line;
    string bin = "";
    for(char c:line) bin += toBin[c];
    int i = 0;
    Packet p; p.read(bin,i);
    cout << "Sum of versions: " << versions << endl; // part1
    cout << "Package value: " << p.val << endl; // part2
}
