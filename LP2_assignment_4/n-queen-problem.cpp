#include <bits/stdc++.h>
using namespace std;

bool checkDiagonal(int x, int y, vector<string>& board){
    
    int i = x;
    int j = y;
    while (i>=0)
    {
        if(board[i][j] == '*')
        return false;
        i--;
    }
    i = x;
    while (j>=0 && i<board.size())
    {
        if(board[i][j]=='*')
        return false;
        j--;
        i++;
    }
    i = x;
    j = y;
    while (j>=0 && i>=0)
    {
        if(board[i][j] == '*')
        return false;
        j--;
        i--;
    }
    
    return true;
    
}

void printBoard(int x,vector<string>& board){
    if(x == board.size()){
        for(int i=0;i<board.size();i++)
        {
            for (int j = 0; j < board.size(); j++)
            {
                cout<<board[i][j]<<" ";
            }
            cout<<endl;
            
        }
        cout<<"______________________________________________________\n"<<endl;
        return;
    }
    
    for(int row=0;row<board.size();row++){
        if(checkDiagonal(x,row,board)){
            board[x][row] = '*';
            printBoard(x+1,board);
            board[x][row] = '-';
        }
    }
    
}

int main(){

    int n ;
    cout<<"Enter Number of squares: ";
    cin>>n;
    vector<string> board;
    string temp(n,'-');
    for (int i = 0; i < n; i++)
    {
        board.push_back(temp);
    }
    

    printBoard(0,board);

    return 0;
}