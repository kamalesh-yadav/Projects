#include<bits/stdc++.h>
using namespace std;
/*Backtracking*/
const int N=9;
bool isSafe(int grid[N][N],int row, int col, int num)
{
    /*checking row*/
    for(int d = 0; d<N; d++)
    {
        if(grid[row][d]==num)
        {
            return false;
        }
    }
    /*checking column*/
    for(int s = 0; s<N; s++)
    {
        if(grid[s][col]==num)
        {
            return false;
        }
    }
    int startrow=row-row%3;
    int startcol=col-col%3;
    for(int r = 0; r<3; r++)
    {
        for(int c = 0; c<3; c++)
        {
            if(grid[r+startrow][c+startcol]==num)
            {
                return false;
            }
        }
    }
    return true;
}
bool SolveSudoku(int grid[N][N])
{
    int row,col;
    bool emptyCell = false;
    for(row=0; row<N; row++)
    {
        for(col=0; col<N; col++)
        {
            if(grid[row][col]==0)
            {
                emptyCell=true;
                break;
            }
        }
        if(emptyCell)
        {
            break;
        }
    }
    if(!emptyCell)
    {
        return true;
    }
    for(int num = 1; num<=N; num++)
    {
        if(isSafe(grid,row,col,num))
        {
            grid[row][col]=num;
            if(SolveSudoku(grid))
            {
                return true;
            }
            grid[row][col]=0;
        }
    }
    return false;
}
void printGrid(int grid[N][N])
{
    for(int row = 0; row<N; row++)
    {
        if(row%3==0)
        {
            cout<<"=========================="<<endl<<endl;
        }
        for(int col = 0; col<N; col++)
        {
            if(col%3==0)
            {
                cout<<"| ";
            }
            cout<<grid[row][col]<<" ";
            if(col==N-1)
            {
                cout<<"|";
            }
        }
        if(row==8)
        {
            cout<<endl<<"========================"<<endl;
        }
        cout<<endl;
    }
}
int main()
{
    int grid[N][N]={
        {3,0,6,5,0,8,4,0,0},
        {5,2,0,0,0,0,0,0,0},
        {0,8,7,0,0,0,0,3,1},
        {0,0,3,0,1,0,0,8,0},
        {9,0,0,8,6,3,0,0,5},
        {0,5,0,0,9,0,6,0,0},
        {1,3,0,0,0,0,2,5,0},
        {0,0,0,0,0,0,0,7,4},
        {0,0,5,2,0,6,3,0,0}
    };
    printGrid(grid);
    cout<<endl;
    if(SolveSudoku(grid))
    {
        cout<<"Sudoku is Solved:"<<endl;
        printGrid(grid);
    }
    else
    {
        cout<<"No solution exist "<<endl;
    }
    
}