#ifndef BLOCK_H
#define BLOCK_H
#include "defs.h"
#include "Position.h"

using namespace std;

class Block{
public:
    Block();
    void draw(int offsetX, int offsetY);
    int id;
    map<int, vector<Position>> cells;
    void move(int rows, int columns);
    void resetPos();
    vector<Position> getUpdatedCellPositions();
    void rotate();
    void unrotate();
private:
    vector<Color> getColors();
    int blockSize;
    int rotationState;
    vector<Color> colors;
    int rowOffset;
    int colOffset;
};

#endif