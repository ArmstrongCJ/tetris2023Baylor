#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <algorithm>
#include "SDL_Plotter.h"

using namespace std;

const int ROWS = 20;
const int COLS = 10;
const int BLOCK_SIZE = 25;
const int BOARD_WIDTH = 1000;
const int BOARD_HEIGHT = 1000;
const vector<int> BACKGROUND_COLOR = {25, 25, 25};

// Tetrimino shapes
const vector<vector<vector<bool>>> TETRIMINOS = {
    // I
    {
        {1, 1, 1, 1}
    },
    // O
    {
        {1, 1},
        {1, 1}
    },
    // T
    {
        {0, 1, 0},
        {1, 1, 1}
    },
    // L
    {
        {1, 0, 0},
        {1, 1, 1}
    },
    // J
    {
        {0, 0, 1},
        {1, 1, 1}
    },
    // S
    {
        {0, 1, 1},
        {1, 1, 0}
    },
    // Z
    {
        {1, 1, 0},
        {0, 1, 1}
    }
};

// Color values for Tetris
const vector<vector<int>> COLORS = {
    {0, 255, 255},
    {255, 255, 0},
    {128, 0, 128},
    {255, 165, 0},
    {0, 0, 255},
    {0, 255, 0},
    {255, 0, 0}
};

class Tetrimino {
public:
    int x, y, shape;
    vector<vector<bool>> blocks;

    Tetrimino(int shape) : x(COLS / 2 - 2), y(0), shape(shape), blocks(TETRIMINOS[shape]) {}

    void rotate() {
        vector<vector<bool>> rotated(blocks[0].size(), vector<bool>(blocks.size()));
        for (size_t i = 0; i < blocks.size(); i++) {
            for (size_t j = 0; j < blocks[i].size(); j++) {
                rotated[j][blocks.size() - i - 1] = blocks[i][j];
            }
        }
        blocks = rotated;
    }

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }
};

class TetrisBoard {
public:
    vector<vector<int>> grid;

    TetrisBoard() : grid(ROWS, vector<int>(COLS, -1)) {}

    bool isCollision(const Tetrimino& tetrimino) {
        for (size_t i = 0; i < tetrimino.blocks.size(); i++) {
            for (size_t j = 0; j < tetrimino.blocks[i].size(); j++) {
                if (tetrimino.blocks[i][j]) {
                    int x = tetrimino.x + j;
                    int y = tetrimino.y + i;
                    if (x < 0 || x >= COLS || y < 0 || y
                        >= ROWS || grid[y][x] != -1) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }

    void merge(const Tetrimino& tetrimino) {
        for (size_t i = 0; i < tetrimino.blocks.size(); i++) {
            for (size_t j = 0; j < tetrimino.blocks[i].size(); j++) {
                if (tetrimino.blocks[i][j]) {
                    int x = tetrimino.x + j;
                    int y = tetrimino.y + i;
                    grid[y][x] = tetrimino.shape;
                }
            }
        }

            // Check for cleared lines
        for (int i = ROWS - 1; i >= 0;) {
            bool isLineFull = true;
            for (int j = 0; j < COLS; j++) {
                if (grid[i][j] == -1) {
                    isLineFull = false;
                    break;
                }
            }

            if (isLineFull) {
                grid.erase(grid.begin() + i);
                grid.insert(grid.begin(), vector<int>(COLS, -1));
            } else {
                i--;
            }
        }
    }
};


    int main(int argc, char** argv) {
        

        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); // initialize audio player
        Mix_Music *backgroudMUS = Mix_LoadMUS("sound/Tetris.wav");  // load sound;
        Mix_Chunk *sound1 = Mix_LoadWAV("sound/8bit_beep.wav");     // load sound;
        Mix_Chunk *sound2 = Mix_LoadWAV("sound/8bit_boom.wav");     // load sound;
        Mix_Chunk *sound3 = Mix_LoadWAV("sound/8bit_crush.wav");    // load sound;
        Mix_Chunk *sound4 = Mix_LoadWAV("sound/8bit_pick.wav");     // load sound;

        Mix_PlayMusic(backgroudMUS, -1); // play background music for infinite times
        Mix_VolumeMusic(MIX_MAX_VOLUME / 3);// set background music volume

        Mix_Volume(0, 128); //set channel volume
        Mix_Volume(1, 48); //set channel volume
        Mix_Volume(2, 68); //set channel volume

        srand(time(NULL));
        SDL_Plotter g(BOARD_WIDTH, BOARD_HEIGHT);
        TetrisBoard board;
        Tetrimino* currentTetrimino = new Tetrimino(rand() % TETRIMINOS.size());
        char key;
        int speed = 100;
        int fallDelay = 0;
        bool isPaused = false;

        auto drawSquare = [&](int x, int y, int R, int G, int B) {
            int border = 2; // Border thickness
            for (int i = 0; i < BLOCK_SIZE; i++) {
                for (int j = 0; j < BLOCK_SIZE; j++) {
                    if (i < border || j < border || i >= BLOCK_SIZE - border || j >= BLOCK_SIZE - border) {
                        g.plotPixel(x * BLOCK_SIZE + i, y * BLOCK_SIZE + j, 0, 0, 0); // Draw border with black color
                    } else {
                        g.plotPixel(x * BLOCK_SIZE + i, y * BLOCK_SIZE + j, R, G, B); // Draw the block
                    }
                }
            }
        };


        auto drawTetrimino = [&](const Tetrimino& tetrimino) {
            for (size_t i = 0; i < tetrimino.blocks.size(); i++) {
                for (size_t j = 0; j < tetrimino.blocks[i].size(); j++) {
                    if (tetrimino.blocks[i][j]) {
                        drawSquare(tetrimino.x + j, tetrimino.y + i, COLORS[tetrimino.shape][0], COLORS[tetrimino.shape][1], COLORS[tetrimino.shape][2]);
                    }
                }
            }
        };

        auto drawBoard = [&]() {
            for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < COLS; j++) {
                    if (board.grid[i][j] != -1) {
                        int colorIndex = board.grid[i][j];
                        drawSquare(j, i, COLORS[colorIndex][0], COLORS[colorIndex][1], COLORS[colorIndex][2]);
                    } else {
                        drawSquare(j, i, BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2]);
                    }
                }
            }
        };

        while (!g.getQuit()) {
            if (!isPaused) {
                Mix_ResumeMusic(); // resume background music
                fallDelay++;

                if (fallDelay >= speed) {
                    currentTetrimino->move(0, 1);
                    if (board.isCollision(*currentTetrimino)) {
                        currentTetrimino->move(0, -1);
                        board.merge(*currentTetrimino);
                        delete currentTetrimino;
                        currentTetrimino = new Tetrimino(rand() % TETRIMINOS.size());

                        Mix_PlayChannel(2, sound3, 0);  //playsound3
                    }
                    fallDelay = 0;
                }
            }

            if (g.kbhit()) {
                key = g.getKey();
                switch (key) {
                    case RIGHT_ARROW:
                        currentTetrimino->move(1, 0);
                        Mix_PlayChannel(0, sound1, 0);
                        if (board.isCollision(*currentTetrimino)) {
                            currentTetrimino->move(-1, 0);
                        }
                        break;
                    case LEFT_ARROW:
                        currentTetrimino->move(-1, 0);
                        Mix_PlayChannel(0, sound1, 0);  //play sound1
                        if (board.isCollision(*currentTetrimino)) {
                            currentTetrimino->move(1, 0);
                        }
                        break;
                    case UP_ARROW:
                        currentTetrimino->rotate();
                        Mix_PlayChannel(1, sound2, 0); //play sound2
                        if (board.isCollision(*currentTetrimino)) {
                            for (int i = 0; i < 3; i++) {
                                currentTetrimino->rotate(); // Rotate 3 times to go back to the previous state
                            }
                        }
                        break;
                    case 'P':
                        Mix_PlayChannel(0, sound4, 0); //play sound4
                        Mix_PauseMusic(); //pause background music
                        isPaused = !isPaused;
                        break;
                        
                }
            }

            g.clear();
            drawBoard();
            drawTetrimino(*currentTetrimino);
            g.update();
            g.Sleep(1);
        }

        Mix_CloseAudio();//CLOSE AUDIO PLAYER
        delete currentTetrimino;
        return 0;
    }
