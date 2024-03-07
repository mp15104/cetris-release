#ifndef GAME_H
#define GAME_H
#include "Grid.h"
#include "Blocks.cpp"

using namespace std;

class Game{
    public:
        Game();
        ~Game();
        void draw();
        void inputHandler();
        void MoveBlockDown();
        bool gameOver;
        int score;
        Music music;
        Sound rotateSound;
        Sound clearSound;
        Sound saveSound;

    private:
        Grid grid;
        bool saveToggle;
        bool blockoutside();
        vector<Block> blocks;
        vector<Block> originalBlocks;
        Block currentBlock;
        Block nextBlock;
        Block savedBlock;
        Block getRandomBlock();
        void MoveBlockLeft();
        void MoveBlockRight();
        void rotateBlock();
        void lockBlock();
        bool blockCollides();
        void reset();
        void scoreUp(int lines, int movedown);
        void saveBlock();
};

#endif