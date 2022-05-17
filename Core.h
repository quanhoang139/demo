#ifndef _CORE_H_
#define _CORE_H_

#include "Texture.h"
#include<random>
#include<queue>
// #include "Partical.h"
#include "Button.h"
#include "Sound.h"
#include "Time.h"
#include <windows.h>
#include <iostream>
#include <fstream>



using namespace std;

class Core {
    private:
        Texture gameTexture;
        Sound gameSound;
        Mix_Chunk* clickEffect;
        Mix_Chunk* bombEffect;
        Mix_Chunk* correctEffect;


        int matrixBomb[7][20];
        int matrixGrass[7][20];
        int matrixFlag[7][20];
        int recordEasy[3] = {0};
        int recordNormal[3] = {0};
        int recordHard[3] = {0};
        Position curPosChick;
        Tile curTileChick, nextTileChick;


        int score;
        int level;
        int target;
        int more;
        int scount;
        float healthPoint;
        int difficulty = 0, curDifficulty = 0;
        std::pair<int, int> highscore[5];
        int curHighScore;
        int curRun;
        int numberBomb;
        int usedMinesweeper;
        bool canMove = false;
        bool isContinue = false;
        bool isLeft;
        bool gameOver = false;
        bool win = false;
        bool stageClear = false;
        bool checkClickMenu;
        bool isRenderInfo = false;
        bool isAnswering = false;
        QandA qanda;
        vector<QandA> listQandA;

        bool isSetingFlag;
        bool isRemovingFlag;
        bool isMoving;
        bool isRenderQandA;
        queue<int> q, erasedBlockID;

        Button button[20];
        void renderMenu(SDL_Renderer* renderer);
        void renderInGame(SDL_Renderer* renderer);
        void renderNXLVBoard(SDL_Renderer* renderer);
        void renderRecordList(SDL_Renderer* renderer);
        void renderInfo(SDL_Renderer* renderer);
        void renderBombEffect();

        int maxBomb;
    public:
        static const int TOTAL_PARTICAL = 16;
        static const int MENU = 0;
        static const int INGAME = 1;
        static const int NXLVBOARD = 2;
        static const int RECORD_LIST = 3;
        static const int EASY = 0;
        static const int NORMAL = 1;
        static const int HARD = 2;
        static const int CHICK_SPEED = 16;

        Timer gameTime;
        Timer timeAnswer;
        int timeRemaining;

        Core () {;};
        ~Core() {;};
        void init(SDL_Renderer* &renderer);
        void renderTexture(SDL_Renderer* renderer);
        bool handlingEvent(SDL_Event &e, SDL_Renderer* renderer);
        void solve();
        void solveTexture(SDL_Renderer* renderer);
        void minesweeper();

        void newLevel();
        void saveData();
        void getData();

        int getNumberBomb();
        void moveRight(Tile nextTile);
        void moveLeft(Tile nextTile);
        void moveUp(Tile nextTile);
        void moveDown(Tile nextTile);
        void setUpBomb();
        void dataInit();
        void getRecord();
        int getScore();
        void getQandA(QandA &qanda);
};

#endif // _CORE_H_

