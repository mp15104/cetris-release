#ifndef GRID_H
#define GRID_H
#include "defs.h"

using namespace std;

class Grid{
public:
    Grid();
    void initGrid();
    void print();
    int grid[ROWS][COLS];
    void draw();
    bool blockOutside(int r, int c);
    bool cellEmpty(int r, int c);
    int clearRows();

private:
    vector<Color> getColors();
    int numRows;
    int numColumns;
    int blockSize;
    vector<Color> colors;
    bool isRowFull(int row);
    void clearRow(int row);
    void rowCollapse(int row, int numRows);
    void explodeRow();
};

#endif