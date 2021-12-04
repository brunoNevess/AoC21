#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

vector<string> tokenize(string s, string del = " "){
    int start = 0;
    int end = s.find(del);
    vector<string> strs;
    while (end != -1) {
        strs.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    strs.push_back(s.substr(start, end - start));

    return strs;
}

typedef pair<int,int> ii;

class Board {
public:
    vector<vector<int>> grid;
    unordered_map<int,int> row_count;
    unordered_map<int,int> col_count;
    unordered_map<int,ii> s;
    int totalSum;
    int SIZE;
    int winnerCol;
    int winnerRow;
    Board(int N){
        SIZE = N;
        grid = vector<vector<int>>(N,vector<int>(N));
        totalSum = 0;
        winnerCol = winnerRow = -1;
  
    }
    void readBoard(){
        for(int i = 0; i < SIZE ; i++){
            for(int j = 0 ; j < SIZE ; j++){
                int x; cin >> x;
                grid[i][j] = x;
                s[x] = ii(i,j);
                totalSum += grid[i][j];
            }
        }
    }
    bool isWinner(){
        for(int i = 0 ; i < SIZE ; i++){
            if(row_count[i] == SIZE || col_count[i] == SIZE) {
                if(row_count[i] == SIZE) winnerRow = i;
                else winnerCol = i;
                return true;
            }
        }
        return false;
    }
    void markNumber(int x){
        if(!s.count(x)){
            return;
        }
        int i = s[x].first;
        int j = s[x].second;
        row_count[i]++;
        col_count[j]++;
        totalSum -= x;
    }
    int getAns(int x){
        cout << x << " " << totalSum << endl;
        return totalSum*x;
    }

    void printBoard(){
        for(int i = 0; i < SIZE ; i++){
            for(int j = 0 ; j < SIZE ; j++){
               cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main(){
    vector<int> numbers;
    string str;
    cin >> str;
    vector<string> nums = tokenize(str,",");
    for(string n:nums) {
        numbers.push_back(stoi(n));
    }
   
    vector<Board> boards;
    int x;
    int N = 5;
    while(!cin.eof()){
        Board b(N);
        b.readBoard();
        boards.push_back(b);
    }
    unordered_set<int> winners;
    for(int x: numbers){
        int i = 1;
        for(int i = 0 ; i < boards.size();i++){
            if(winners.count(i)) continue;
            boards[i].markNumber(x);
            if(boards[i].isWinner()){
                if(winners.size() == boards.size() - 1){
                    cout << "Board " << i+1 << " (finally) won !" << endl;
                    cout << boards[i].getAns(x) << endl;;
                }
                winners.insert(i);
            }
        }
        if(winners.size() == N){ 
            break;
        }
    }
    return 0;
}


