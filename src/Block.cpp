#include "Block.h"

using namespace std;

Block::Block(){
    blockSize = BLOCK_SIZE;
    rotationState = ZERO;
    colors = getColors();
    rowOffset=ZERO;
    colOffset=ZERO;
}

void Block::draw(int offsetX, int offsetY){
    vector<Position> tiles = getUpdatedCellPositions();
    for(Position item: tiles){
        DrawRectangle(item.col*blockSize+offsetX, item.row*blockSize+offsetY, blockSize-1, blockSize-1, colors[id]);
    }
}


vector<Color> Block::getColors(){
    return{BLACK, GREEN, RED, ORANGE, YELLOW, PURPLE, CYAN, BLUE};
}

void Block::move(int rOffset, int cOffset){
    rowOffset+=rOffset;
    colOffset+=cOffset;
}

void Block::resetPos(){
    rowOffset = ZERO;
    colOffset = ZERO + RESET_OFFSET;
}

vector<Position> Block::getUpdatedCellPositions(){
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
    for(Position item: tiles){
        Position newPos = Position(item.row+rowOffset, item.col+colOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::rotate(){
    rotationState++;
    if(rotationState==int(cells.size())){
        rotationState=ZERO;
    }
}

void Block::unrotate()
{
    rotationState--;
    if(rotationState==-1){
        rotationState=cells.size()-1;
    }
}
