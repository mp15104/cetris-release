#include "Game.h"

Game::Game(){
    grid = Grid();
    blocks = {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
    originalBlocks = blocks;
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    savedBlock.id = 8;
    gameOver = false;
    score = 0;
    saveToggle = false;
    InitAudioDevice();
    music = LoadMusicStream("Sound/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sound/rotate.wav");
    clearSound = LoadSound("Sound/clear.wav");
    saveSound = LoadSound("Sound/save.wav");
}

Game::~Game(){
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::getRandomBlock(){
    if(blocks.empty()){
        blocks = originalBlocks;
    }
    int random = rand()%blocks.size();
    Block chosenBlock = blocks[random];
    blocks.erase(blocks.begin() + random);
    return chosenBlock;
}

void Game::draw(){
    grid.draw();
    currentBlock.draw(OFFSET, OFFSET);
    switch(nextBlock.id){
        case 3:
            nextBlock.draw(NEXT_OFFSET_X-15, NEXT_OFFSET_Y+20);
            break;
        case 4:
            nextBlock.draw(NEXT_OFFSET_X-15, NEXT_OFFSET_Y+10);
            break;
        default:
            nextBlock.draw(NEXT_OFFSET_X, NEXT_OFFSET_Y);
    }
    switch(savedBlock.id){
        case 3:
            savedBlock.draw(SAVED_OFFSET_X-15, SAVED_OFFSET_Y-10);
            break;
        case 4:
            savedBlock.draw(SAVED_OFFSET_X+20, SAVED_OFFSET_Y+10);
            break;
        case 8:
            break;
        default:
            savedBlock.draw(SAVED_OFFSET_X, SAVED_OFFSET_Y);
    }
}

void Game::inputHandler(){
    int keyPressed = GetKeyPressed();
    if(gameOver&& keyPressed!=0){
        gameOver=false;
        reset();
    }
    switch(keyPressed){
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            scoreUp(0, 1);
            break;
        case KEY_UP: case KEY_Z:
            rotateBlock();
            break;
        case KEY_C:
            saveBlock();
            break;
    }
}

bool Game::blockoutside()
{
    vector<Position> tiles = currentBlock.getUpdatedCellPositions();
    for(Position item:tiles){
        if(grid.blockOutside(item.row, item.col)){
            return true;
        }
    }
    return false;
}

void Game::MoveBlockLeft(){
    if(!gameOver){
        currentBlock.move(0, -1);
        if(blockoutside()|| blockCollides()){
            currentBlock.move(0, 1);
        }
    }
}

void Game::MoveBlockRight(){
    if(!gameOver){
        currentBlock.move(0, 1);
        if(blockoutside()|| blockCollides()){
            currentBlock.move(0, -1);
        }
    }
}


void Game::MoveBlockDown(){
    if(!gameOver){
        currentBlock.move(1, 0);
        if(blockoutside() || blockCollides()){
            currentBlock.move(-1, 0);
            lockBlock();
        }
    }
}


void Game::rotateBlock(){
    if(!gameOver){
        currentBlock.rotate();
        if(blockoutside()|| blockCollides()){
            currentBlock.unrotate();
        }else{
            PlaySound(rotateSound);
        }
    }
}

void Game::lockBlock()
{
    vector<Position> tiles = currentBlock.getUpdatedCellPositions();
    for(Position item: tiles){
        grid.grid[item.row][item.col] = currentBlock.id;
    }
    currentBlock=nextBlock;
    if(blockCollides()){
        gameOver = true;
    }
    nextBlock = getRandomBlock();
    int rowsCleared = grid.clearRows();
    if(rowsCleared>0){
        PlaySound(clearSound);
        scoreUp(rowsCleared, 0);
    }
    saveToggle=false;
}

bool Game::blockCollides()
{
    vector<Position> tiles = currentBlock.getUpdatedCellPositions();
    for(Position item: tiles){
        if(grid.cellEmpty(item.row, item.col)==false){
            return true;
        }
    }
    return false;
}


void Game::reset()
{
    grid.initGrid();
    blocks = {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    savedBlock.id = 8;
    score = 0;
}


void Game::scoreUp(int lines, int movedown){
    switch(lines){
        case 1:
            score+=100;
            break;
        case 2:
            score+=300;
            break;
        case 3:
            score+=500;
            break;
        case 4:
            score+=800;
            break;
        default:
            break;
    }
    score+=movedown;
}

void Game::saveBlock(){
    Block backupBlock;
    if(!saveToggle){
        switch(savedBlock.id){
            case 8:
                savedBlock = currentBlock;
                savedBlock.resetPos();
                currentBlock =nextBlock;
                nextBlock = getRandomBlock();
                saveToggle=true;
                PlaySound(saveSound);
                break;
            default:
                backupBlock = savedBlock;
                savedBlock = currentBlock;
                savedBlock.resetPos();
                currentBlock =backupBlock;
                saveToggle=true;
                PlaySound(saveSound);
                break;
        }
    }
}