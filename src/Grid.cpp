#include "Grid.h"

using namespace std;

Grid::Grid(){
    numRows = ROWS;
    numColumns = COLS;
    blockSize = BLOCK_SIZE;
    initGrid();
    colors = getColors();
}

void Grid::initGrid(){
    for(int row = ZERO; row < numRows; row++){
        for(int col = ZERO; col<numColumns; col++){
            grid[row][col]=ZERO;
        }
    }
}

void Grid::print(){
    for(int row = ZERO; row < numRows; row++){
        for(int col = ZERO; col<numColumns; col++){
            cout << grid[row][col]<<"";
        }
        cout<<endl;
    }
}

vector<Color> Grid::getColors(){
    return{BLACK, GREEN, RED, ORANGE, YELLOW, PURPLE, CYAN, BLUE};
}

void Grid::draw(){
    for(int row = ZERO; row < numRows; row++){
        for(int col = ZERO; col<numColumns; col++){
            int blockValue = grid[row][col];
            DrawRectangle(col*blockSize+11, row*blockSize+11 , blockSize-1, blockSize-1, colors[blockValue]);
        }
    }
}

bool Grid::blockOutside(int r, int c){
    if(r>=0 && r<numRows && c>=0 && c < numColumns){
        return false;
    }
    return true;
}

bool Grid::cellEmpty(int r, int c)
{
    if(grid[r][c]==0){
        return true;
    }
    return false;
}

int Grid::clearRows()
{
    int full = ZERO;
    for(int row = numRows-1; row>=0; row--){
        if(isRowFull(row)){
            clearRow(row);
            full++;
        }
        else if(full>ZERO){
            rowCollapse(row, full);
        }
    }
    return full;
}

bool Grid::isRowFull(int row){
    for(int col = 0; col < numColumns; col++){
        if(grid[row][col]==0){
            return false;
        }
    }
    return true;
}

void Grid::clearRow(int row){
    for(int col = 0; col < numColumns; col++){
        grid[row][col]=0;
    }
}

void Grid::rowCollapse(int row, int numRows)
{
    for(int col = 0; col < numColumns; col++){
        grid[row+numRows][col] = grid[row][col];
        grid[row][col]=0;
    }
}
