#include "Core.h"

void Core::dataInit(){
   //if (win || gameOver) gameSound.playMusicBG();
    timeRemaining = 1;
    isContinue = false;
    isRenderQandA = false;
    isMoving = false;
    isRemovingFlag = false;
    isSetingFlag = false;
    isLeft = false;
    healthPoint = 2;
    usedMinesweeper = 2;
    gameOver = false;
    win = false;
    curPosChick.x = 165 - 64;  curPosChick.y = 310;
    curTileChick.x = -1; curTileChick.y = 0;
    nextTileChick.x = -1; nextTileChick.y = 0;
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 20; j++)
        {
            matrixGrass[i][j] = 1;
            matrixFlag[i][j] = 0;
            matrixBomb[i][j] = 0;
        }
            if (difficulty == EASY) maxBomb = 24;
            else if (difficulty == NORMAL) maxBomb = 30;
            else if (difficulty == HARD) maxBomb = 40;
            int numer_bomb = 0;
            while (numer_bomb < maxBomb)
            {
                int tile = rand() % (20 * 7);
                if (matrixBomb[tile / 20][tile - (tile / 20)*20] == 0)
                {
                    matrixBomb[tile / 20][tile - (tile / 20)*20] = 1;
                    numer_bomb++;
                }
            }
    target = 140 - maxBomb;
    score = 0;
    qanda.choose = "";
    isAnswering = false;
    gameTexture.scaleBomb = 0;
    while (listQandA.size() !=0 ) listQandA.pop_back();

    ifstream file("asset/ListQuestionsAndAnswers.txt");
    while (getline(file, qanda.question))
    {
        getline(file, qanda.answerA);
        getline(file, qanda.answerB);
        getline(file, qanda.answerC);
        getline(file, qanda.answerD);
        getline(file, qanda.answer);
        listQandA.push_back(qanda);
    }
    file.close();
    qanda.question = "";
    for (int i = 16; i < 20; i++) button[i].reloadButton(0);

//ofstream/ file("")
}

void Core::init(SDL_Renderer* &renderer) {
    gameTexture.loadMedia(renderer);

    dataInit();
    clickEffect = Mix_LoadWAV("asset/Sound/EffectButton.wav");
    bombEffect = Mix_LoadWAV("asset/Sound/BombEffect.mp3");
    correctEffect = Mix_LoadWAV("asset/Sound/CorrectEffect.mp3");

    curRun = MENU;
    gameSound.load();
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    button[0].loadButton(renderer, 80, 80, 25, 380, "asset/img/set_flag.png");
    button[1].loadButton(renderer, 80, 80, 25, 500, "asset/img/remove_flag.png");
    button[2].loadButton(renderer, 80, 80, 25, 620, "asset/img/radar.png");


    button[3].loadButton(renderer, 324, 86, 840, 340, "asset/img/easy off.png", "asset/img/easy on.png");
    button[4].loadButton(renderer, 324, 86, 840, 440, "asset/img/normal off.png", "asset/img/normal on.png");
    button[5].loadButton(renderer, 324, 86, 840, 540, "asset/img/hard off.png", "asset/img/hard on.png");

    button[6].loadButton(renderer, 80, 80, 1472 - 80, 30 + 98 + 98, "asset/img/vol on.png", "asset/img/vol off.png");
    button[7].loadButton(renderer, 80, 80, 1472 - 80, 20 + 98, "asset/img/mus on.png", "asset/img/mus off.png");
    button[8].loadButton(renderer, 80, 80, 1472 - 80, 10, "asset/img/home.png");
    button[3].reloadButton(1);
    button[9].loadButton(renderer, 80, 80, 1472 - 80, 10, "asset/img/quit.png");

    button[10].loadButton(renderer, 133, 133, 260, 340, "asset/img/continue.png", "asset/img/continue off.png");

    button[11].loadButton(renderer, 133, 133, 420, 340, "asset/img/restart.png");
    button[12].loadButton(renderer, 133, 133, 260, 500, "asset/img/record.png");
    button[13].loadButton(renderer, 133, 133, 420, 500, "asset/img/info.png");

    button[14].loadButton(renderer, 80, 80, 1280, 128, "asset/img/close.png");

    button[15].loadButton(renderer, 1300, 100, 80, 100 - 10, "asset/img/button.png");
    button[16].loadButton(renderer, 300, 110, 80, 220 - 25, "asset/img/button.png", "asset/img/button chose.png" );
    button[17].loadButton(renderer, 300, 110, 413, 220 - 25, "asset/img/button.png", "asset/img/button chose.png");
    button[18].loadButton(renderer, 300, 110, 746, 220 - 25, "asset/img/button.png", "asset/img/button chose.png");
    button[19].loadButton(renderer, 300, 110, 1080, 220 - 25, "asset/img/button.png", "asset/img/button chose.png");

//    curHighScore = highscore[0].first;
//    button[0].loadButton(renderer, 256, 50, 200 - 128, 300, "asset/img/new game.png");
//    button[2].loadButton(renderer, 256, 50, 200 - 128, 460, "asset/Image/record.png");
//    button[3].loadButton(renderer, 85, 40, 72 , 540, "asset/Image/vol on.png", "asset/Image/vol off.png");
//    button[4].loadButton(renderer, 85, 40, 243, 540, "asset/Image/mus on.png", "asset/Image/mus off.png");
//    button[8].loadButton(renderer, 220, 50, 90, 458);
//    button[9].loadButton(renderer, 40, 40, 10, 60, "asset/Image/back.png");
}

bool Core::handlingEvent(SDL_Event &e, SDL_Renderer* renderer){
    if (curRun == MENU) {
        if (!isRenderInfo)
        {
            if (button[6].checkUserClickPos()) {gameSound.changeEffectVol();}
            else if (button[7].checkUserClickPos()) {gameSound.changeMusicVol();}
            else if (button[3].checkUserClickPos())
            {
                button[3].reloadButton(1);
                button[4].reloadButton(0);
                button[5].reloadButton(0);
                difficulty = EASY;
            }
            else if (button[4].checkUserClickPos())
            {
                button[3].reloadButton(0);
                button[4].reloadButton(1);
                button[5].reloadButton(0);
                difficulty = NORMAL;
            }
            else if (button[5].checkUserClickPos())
            {
                button[3].reloadButton(0);
                button[4].reloadButton(0);
                button[5].reloadButton(1);
                difficulty = HARD;
            }
            else if (button[9].checkUserClickPos()) return false;
            else if (button[11].checkUserClickPos())
            {
                getRecord();
                dataInit();
                curRun = INGAME;
                checkClickMenu = true;
                isContinue = true;
            }
            else if (button[13].checkUserClickPos())
            {
                isRenderInfo = true;
            }
            else if (isContinue){if(button[10].checkUserClickPos())
            {
                curRun = INGAME;
                checkClickMenu = true;
                isContinue = true;
            }}
            else if (button[12].checkUserClickPos()) curRun = RECORD_LIST;

        }
        else
        {
            if (button[14].checkUserClickPos())  isRenderInfo = false;
        }




//        if (button[0].checkUserClickPos()) {
//            for(int i = 0; i < 10; ++i)
//            for(int j = 0; j < 10; ++j) a[i][j] = rand() % 5;
//            score = 0; level = 1;
//            target = 1000; more = 1500;
//            scount = 2;
//            gameOver = false;
//            stageClear = false;
//            curRun = INGAME;
//            //Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
//        }
//        else if (button[1].checkUserClickPos()) {
//            if (continuePre) {
//                gameOver = false;
//                stageClear = false;
//                curRun = INGAME;
//                //Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
//            }
//        }
//        else if (button[2].checkUserClickPos()) {
//            curRun = RECORD_LIST;
//            //Mix_VolumeMusic(MIX_MAX_VOLUME);
//        }
//        else if (button[3].checkUserClickPos()) gameSound.changeEffectVol();
//        else if (button[4].checkUserClickPos()) gameSound.changeMusicVol();
    }
    if (curRun == INGAME) {
        curDifficulty = difficulty;
        if (button[8].checkUserClickPos())
        {
            curRun = MENU;
            if (win||gameOver) gameSound.playMusicBG();

        }
        else if (button[6].checkUserClickPos()) {gameSound.changeEffectVol(); isSetingFlag = false; isRemovingFlag = false;}
        else if (button[7].checkUserClickPos()) {gameSound.changeMusicVol(); isSetingFlag = false; isRemovingFlag = false;}
        if (healthPoint != 0)
        {

    //        else if (button[1].checkUserClickPos())
    //        {if (!isSetingFlag) isRemovingFlag = true; else if (isRemovingFlag) isRemovingFlag = false;}

            if (!isAnswering)
            {
                if (button[0].checkUserClickPos() && !isSetingFlag)
                    {
                        //if (isSetingFlag) isSetingFlag = false;
                        if (!isRemovingFlag) isSetingFlag = true;
                    }
                else if (button[0].checkUserClickPos() && isSetingFlag)
                    {
                        isSetingFlag = false;
                    }
                else if (button[1].checkUserClickPos() && !isRemovingFlag)
                    {
                        //if (isSetingFlag) isSetingFlag = false;
                        if (!isSetingFlag) isRemovingFlag = true;
                    }
                else if (button[1].checkUserClickPos() && isRemovingFlag)
                    {
                        isRemovingFlag = false;
                    }
                else if (button[2].checkUserClickPos()) minesweeper();
        //        else if (button[7].checkUserClickPos()) {
        //            continuePre = true;
        //            curRun = MENU;
        //            //Mix_VolumeMusic(MIX_MAX_VOLUME);
        //        }
                else {

                    //SDL_PumpEvents();
                    int x, y;
                    if ( checkClickMenu == false) SDL_GetMouseState(&x, &y);

                    //if (isContinue || healthPoint == 0) SDL_GetMouseState(&x, &y);
                    if (x >= 165 && x <= 165 + 1280 && y >= 310 && y <= 310 + 448) {
                        Position tile ( (x-165)/64 , (y-310)/64 );
                        if (isSetingFlag){
                            if (matrixGrass[tile.y][tile.x] == 1){
                                matrixFlag[tile.y][tile.x] = 1;
                                Mix_PlayChannel(-1, clickEffect, 0);
                            }
                            isSetingFlag = false;
                        }
                        else if (isRemovingFlag) {
                            matrixFlag[tile.y][tile.x] = 0;
                            Mix_PlayChannel(-1, clickEffect, 0);
                            isRemovingFlag = false;
                        }
                        else
                        {
                            if (!isMoving && !(matrixBomb[(y - 310) / 64][(x - 165) / 64] == 1
                                              && matrixGrass [(y - 310) / 64][(x - 165) / 64] == 0)
                                && matrixFlag[(y - 310) / 64][(x - 165) / 64] == 0 && !gameOver)
                            {
                                nextTileChick = Tile((x - 165) / 64, (y - 310) / 64);
                                Mix_PlayChannel(-1, clickEffect, 0);
                                if (isRenderQandA){
                                    isRenderQandA = false;
                                    qanda.choose = "";
                                    qanda.question = "";
                                    gameTexture.scaleBomb = 0;
                                    for (int i = 16; i < 20; i++) button[i].reloadButton(0);
                                }
                            }

                        }
                        timeRemaining = 1;
                        timeAnswer.stop();
                    }
                    checkClickMenu = false;
                }
            }

            else if (timeRemaining > 0){
                if (button[16].checkUserClickPos())
                {
                    button[16].reloadButton(1);
                    qanda.choose = "A";
                    timeAnswer.stop();
                    if (qanda.choose != qanda.answer)
                    {
                        Mix_PlayChannel(-1, bombEffect, 0);
                        healthPoint --;
                    }
                    else Mix_PlayChannel(-1, correctEffect, 0);
                    isAnswering = false;
                }
                else if (button[17].checkUserClickPos())
                {
                    button[17].reloadButton(1);
                    qanda.choose = "B";
                    timeAnswer.stop();
                    if (qanda.choose != qanda.answer)
                    {
                        Mix_PlayChannel(-1, bombEffect, 0);
                        healthPoint --;
                    } else Mix_PlayChannel(-1, correctEffect, 0);
                    isAnswering = false;
                }
                else if (button[18].checkUserClickPos())
                {
                    button[18].reloadButton(1);
                    qanda.choose = "C";
                    timeAnswer.stop();
                    if (qanda.choose != qanda.answer)
                    {
                        Mix_PlayChannel(-1, bombEffect, 0);
                        healthPoint --;
                    }
                    else Mix_PlayChannel(-1, correctEffect, 0);
                    isAnswering = false;
                }
                else if (button[19].checkUserClickPos())
                {
                    button[19].reloadButton(1);
                    qanda.choose = "D";
                    timeAnswer.stop();
                    if (qanda.choose != qanda.answer)
                    {
                        Mix_PlayChannel(-1, bombEffect, 0);
                        healthPoint --;
                    }
                    else Mix_PlayChannel(-1, correctEffect, 0);
                    isAnswering = false;
                }
            }
        }
    }

    if (curRun == RECORD_LIST){
        if (button[6].checkUserClickPos()) {gameSound.changeEffectVol();}
        else if (button[7].checkUserClickPos()) {gameSound.changeMusicVol();}
        else if (button[8].checkUserClickPos())
        {
            curRun = MENU;
        }
    }
    return true;
}

int Core::getNumberBomb(){
    int numberBomb = 0;
    if (curTileChick.y - 1 >= 0 && curTileChick.x - 1 >= 0 && matrixBomb[curTileChick.y - 1][curTileChick.x - 1] == 1) numberBomb++;  // ô phía trên bên trái
    if (curTileChick.y - 1 >= 0 && matrixBomb[curTileChick.y - 1][curTileChick.x] == 1) numberBomb++;                        // ô phía trên
    if (curTileChick.x - 1 >= 0 && matrixBomb[curTileChick.y][curTileChick.x - 1] == 1) numberBomb++;                        // ô pbên trái
    if (curTileChick.y + 1 < 7 && curTileChick.x + 1 < 20 && matrixBomb[curTileChick.y + 1][curTileChick.x + 1] == 1) numberBomb++; // ô phía dưới bên phải
    if (curTileChick.y + 1 < 7 && matrixBomb[curTileChick.y + 1][curTileChick.x] == 1) numberBomb++;                               // ô phía dưới
    if (curTileChick.x + 1 < 20 && matrixBomb[curTileChick.y][curTileChick.x + 1] == 1) numberBomb++;                               // ô bên phải
    if (curTileChick.x + 1 < 20 && curTileChick.y - 1 >= 0 && matrixBomb[curTileChick.y - 1][curTileChick.x + 1] == 1) numberBomb++;  // ô phía trên bên phải
    if (curTileChick.y + 1 < 7 && curTileChick.x - 1 >= 0 && matrixBomb[curTileChick.y + 1][curTileChick.x - 1] == 1) numberBomb++;  // ô phía dưới bên trái
    return numberBomb;
}

void Core::moveRight(Tile nextTile){
    if (curPosChick.x < nextTileChick.x * 64 + 165)
    {
        isMoving = true;
        curPosChick.x += CHICK_SPEED;
        if (curPosChick.x >= nextTileChick.x * 64 + 165)
        {
            curPosChick.x = nextTileChick.x * 64 + 165;
            curTileChick.x = nextTileChick.x;
            isMoving = false;
        }
        isLeft = false;
    }
}

void Core::moveLeft(Tile nextTile){
    if (curPosChick.x > nextTileChick.x * 64 + 165)
    {
        isMoving = true;
        curPosChick.x -= CHICK_SPEED;
        if (curPosChick.x <= nextTileChick.x * 64 + 165)
        {
            curPosChick.x = nextTileChick.x * 64 + 165;
            curTileChick.x = nextTileChick.x;
            isMoving = false;
            isLeft = false;
            return;
        }
        isLeft = true;
    }
}

void Core::moveUp(Tile nextTile){
    if (curPosChick.y > nextTileChick.y * 64 + 310)
    {
        isMoving = true;
        curPosChick.y -= CHICK_SPEED;
        if (curPosChick.y <= nextTileChick.y * 64 + 310)
        {
            curPosChick.y = nextTileChick.y * 64 + 310;
            curTileChick.y = nextTileChick.y;
            isMoving = false;
        }
    }
}

void Core::moveDown(Tile nextTile){
    if (curPosChick.y < nextTileChick.y * 64 + 310)
    {
        isMoving = true;
        curPosChick.y += CHICK_SPEED;
        if (curPosChick.y >= nextTileChick.y * 64 + 310)
        {
            curPosChick.y = nextTileChick.y * 64 + 310;
            curTileChick.y = nextTileChick.y;
            isMoving = false;
        }
    }
}

void Core::renderTexture(SDL_Renderer* renderer) {

    switch(curRun) {
        case MENU: renderMenu(renderer); break;
        case INGAME: renderInGame(renderer); break;
//        case NXLVBOARD: renderNXLVBoard(renderer); break;
        case RECORD_LIST: renderRecordList(renderer); break;
    }
}

void Core::renderMenu(SDL_Renderer* renderer) {
    gameTexture.renderMenu(renderer, isRenderInfo);
    Mix_ResumeMusic();
    if (!isContinue) button[10].reloadButton(1); else button[10].reloadButton(0);
    if (!isRenderInfo)
    {
        for (int i = 3; i < 6; i++) button[i].renderButton(renderer);
        for (int i = 10; i < 14; i++) button[i].renderButton(renderer);
        for (int i = 6; i < 8; i++) button[i].renderButton(renderer);
        button[9].renderButton(renderer);
    }

    if (gameSound.getEffectVol())
        button[6].reloadButton(0);
    else button[6].reloadButton(1);

    if (gameSound.getMusicVol())
        button[7].reloadButton(0);
    else button[7].reloadButton(1);

    if (isRenderInfo) button[14].renderButton(renderer);

//    if (continuePre) button[1].reloadButton(0);
//    else button[1].reloadButton(1);
//
//    if (gameSound.getEffectVol())
//        button[3].reloadButton(0);
//    else button[3].reloadButton(1);
//
//    if (gameSound.getMusicVol())
//        button[4].reloadButton(0);
//    else button[4].reloadButton(1);
//
//    for (int i = 0 ; i < 5; ++i)
//        button[i].renderButton(renderer);

}

void Core::renderInGame(SDL_Renderer* renderer) {

    {
        score = getScore();
        if (gameSound.getEffectVol())
            button[6].reloadButton(0);
        else button[6].reloadButton(1);

        if (gameSound.getMusicVol())
            button[7].reloadButton(0);
        else button[7].reloadButton(1);

        if (!isMoving) numberBomb = getNumberBomb(); else numberBomb = 0;

        gameTexture.renderMedia(renderer, matrixGrass, matrixBomb, matrixFlag, healthPoint,
                                gameOver, win, isSetingFlag, isRemovingFlag, usedMinesweeper, score, target);
        for (int i = 6; i < 9; i++) button[i].renderButton(renderer);
        for (int i = 0; i < 3; i++) button[i].renderButton(renderer);
        //for (int i = 15; i < 20; i++) button[i].renderButton(renderer);
        if (nextTileChick.x >= curTileChick.x && nextTileChick.y >= curTileChick.y)
        {
            if(nextTileChick.x != curTileChick.x) moveRight(nextTileChick);
            else moveDown(nextTileChick);
        }
        else if (nextTileChick.x >= curTileChick.x && nextTileChick.y <= curTileChick.y)
        {
            if(nextTileChick.y != curTileChick.y) moveUp(nextTileChick);
            else moveRight(nextTileChick);
        }
        else if (nextTileChick.x <= curTileChick.x && nextTileChick.y >= curTileChick.y)
        {
            if(nextTileChick.x != curTileChick.x) moveLeft(nextTileChick);
            else moveDown(nextTileChick);
        }
        else if (nextTileChick.x <= curTileChick.x && nextTileChick.y <= curTileChick.y)
        {
            if(nextTileChick.y != curTileChick.y) moveUp(nextTileChick);
            else moveLeft(nextTileChick);
        }

        if (nextTileChick == curTileChick)
        {
            matrixGrass[nextTileChick.y][nextTileChick.x] = 0;
            if (matrixBomb[nextTileChick.y][nextTileChick.x] == 1)
            {
                if (qanda.question == "") getQandA(qanda);
                isRenderQandA = true;
                if (isAnswering) timeAnswer.start();
                if (qanda.choose == "" && timeRemaining > 0) isAnswering = true;
//                if (healthPoint == 2) healthPoint = 1;
//                else healthPoint = 0;
            }
        }
//        for (int i = 15; i < 20; i++) button[i].renderButton(renderer);
//        gameTexture.renderQandA(renderer, &qanda);

        gameTexture.renderChick(renderer, curPosChick, numberBomb, isMoving, isLeft, matrixBomb);
        if (qanda.choose != qanda.answer && qanda.choose != "" || timeRemaining <= 0) gameTexture.renderBombEffect(renderer, curPosChick);
        if (isRenderQandA)
        {
            //qanda = getQandA();
            for (int i = 15; i < 20; i++) button[i].renderButton(renderer);
            if (timeAnswer.get_ticks() <= 15100) timeRemaining = 15 - timeAnswer.get_ticks() / 1000;

            gameTexture.renderQandA(renderer, &qanda, timeRemaining);
            cout << timeRemaining << " " << healthPoint << endl;
            if (timeRemaining == 0) {isAnswering = false; timeRemaining = -2; healthPoint -= 0.5; Mix_PlayChannel(-1, bombEffect, 0);}
        }
    }

    if (score == target)
    {
        if(!win) gameSound.playMusicWin();
        gameTexture.renderWin(renderer);
        // Mix_PauseMusic();
        win = true;
        for (int i = 6; i < 9; i++) button[i].renderButton(renderer);

        if (gameSound.getEffectVol())
            button[6].reloadButton(0);
        else button[6].reloadButton(1);

        if (gameSound.getMusicVol())
            button[7].reloadButton(0);
        else button[7].reloadButton(1);
        isContinue = false;
        if (gameTexture.scale == 200) gameTexture.scale = 0;
        getRecord();

    }
    if (healthPoint <= 0){
        //gameSound.playEffect(15);
        if(!gameOver) gameSound.playMusicGO();
        gameTexture.renderGameOver(renderer);
        gameOver = true;
        //Mix_PauseMusic();
//        for (int i = 6; i < 9; i++) button[i].renderButton(renderer);
//
//        if (gameSound.getEffectVol())
//            button[6].reloadButton(0);
//        else button[6].reloadButton(1);
//
//        if (gameSound.getMusicVol())
//            button[7].reloadButton(0);
//        else button[7].reloadButton(1);
        isContinue = false;
        if (gameTexture.scale == 200) gameTexture.scale = 0;
        getRecord();
    }

//    if (gameOver) {
//        if (Mix_Playing(1)) gameTexture.renderGameOver(renderer);
//        else {
//            gameOver = false;
//            curRun = MENU;
//        }
//        gameTexture.renderGameOver(renderer);
//        gameOver = false;
//        curRun = MENU;
//        return;
//    }
//    if (stageClear) {
//        if (Mix_Playing(2)) gameTexture.renderStageClear(renderer, a, score, level, target, curHighScore);
//        else {
//            stageClear = false;
//            newLevel();
//            curRun = NXLVBOARD;
//        }
//        return;
//    }
    //gameTexture.renderMedia(renderer, a, score, level, target, curHighScore);
    //gameTexture.renderNXLVBoard(renderer, score, level, target);

//    moveRight(nextTileChick);
//    if(!isMoving) moveLeft(nextTileChick);
//    if(!isMoving) moveUp(nextTileChick);
//    if(!isMoving) moveDown(nextTileChick);






//    if(!erasedBlockID.empty())
//    {
//        solveTexture(renderer);
//    }
//    else {
//        id = -1; cnt = 0;
//        for(int i = 0; i < 10; ++i)
//        {
//            while(!q.empty()) q.pop();
//            for(int j = 9; j >= 0; --j)
//            {
//                if(a[j][i] != -1) q.push(a[j][i]);
//            }
//            for(int j = 9; j >= 0; --j)
//            {
//                if(!q.empty()) a[j][i] = q.front(), q.pop();
//                else a[j][i] = -1;
//            }
//        }
//
//        while(!q.empty()) q.pop();
//
//        for(int i = 0; i < 10; ++i)
//        {
//            if(a[9][i] != -1) q.push(i);
//        }
//        for(int i = 0; i < 10; ++i)
//        {
//            if(!q.empty()) {
//                int id = q.front();
//                q.pop();
//                for(int j = 0; j < 10; ++j) a[j][i] = a[j][id];
//            }
//            else {
//                for(int j = 0; j < 10; ++j) a[j][i] = -1;
//            }
//        }
//        bool pass = true;
//        for(int i = 0; i < 10; ++i) {
//            if(a[9][i] != -1)
//            {
//                for(int j = 0; j < 10; ++j) if (a[j][i] != -1) {
//                    for(int k = 0; k < 4; ++k)
//                    {
//                        if (j + dh[k] < 0 || j + dh[k] > 9 || i + dc[k] < 0 || i + dc[k] > 9) continue;
//                        if(a[j + dh[k]][i + dc[k]] == a[j][i]) {
//                            pass = false; break;
//                        }
//                    }
//                }
//            }
//        }
//        if (pass) {
//            if (score >= target) {
//                gameSound.playEffect(Sound::STAGE_CLEAR);
//                stageClear = true;
//                gameOver = false;
//                continuePre = false;
//                return;
//            }
//            else {
//                for (int i = 0; i < 5; ++i) {
//                    if (highscore[i].first < score) {
//                        for (int j = 4; j > i; --j) highscore[j] = highscore[j - 1];
//                        highscore[i] = std::pair<int, int> (score, level);
//                        break;
//                    }
//                }
//                gameSound.playEffect(Sound::GAME_OVER);
//                gameOver = true;
//                stageClear = false;
//                continuePre = false;
//                return;
//            }
//        }
//    }
}

void Core::getRecord(){
        if (curDifficulty == EASY)
        {
            if (score > recordEasy[0])
            {
                recordEasy[2] = recordEasy[1];
                recordEasy[1] = recordEasy[0];
                recordEasy[0] = score;
            }
            else if (score > recordEasy[1] && score < recordEasy[0])
            {
                recordEasy[2] = recordEasy[1];
                recordEasy[1] = score;
            }
            else if (score > recordEasy[2] && score < recordEasy[1])
            {
                recordEasy[2] = score;
            }
        }
        if (curDifficulty == NORMAL)
        {
            if (score > recordNormal[0])
            {
                recordNormal[2] = recordNormal[1];
                recordNormal[1] = recordNormal[0];
                recordNormal[0] = score;
            }
            else if (score > recordNormal[1] && score < recordNormal[0])
            {
                recordNormal[2] = recordNormal[1];
                recordNormal[1] = score;
            }
            else if (score > recordNormal[2] && score < recordNormal[1])
            {
                recordNormal[2] = score;
            }
        }
        if (curDifficulty == HARD)
        {
            if (score > recordHard[0])
            {
                recordHard[2] = recordHard[1];
                recordHard[1] = recordHard[0];
                recordHard[0] = score;
            }
            else if (score > recordHard[1] && score < recordHard[0])
            {
                recordHard[2] = recordHard[1];
                recordHard[1] = score;
            }
            else if (score > recordHard[2] && score < recordHard[1])
            {
                recordHard[2] = score;
            }
        }
}

void Core::minesweeper(){
    if (usedMinesweeper > 0 && curTileChick.x != -1){
        if (curTileChick.y  - 1 >= 0 && curTileChick.x - 1 >= 0
            && matrixBomb[curTileChick.y  - 1][curTileChick.x - 1] == 1
            && matrixGrass[curTileChick.y  - 1][curTileChick.x - 1] == 1
            && matrixFlag[curTileChick.y  - 1][curTileChick.x - 1] == 0)
            {matrixGrass[curTileChick.y - 1][curTileChick.x  - 1] = 0; usedMinesweeper--; return;}          // ô phía trên bên trái

        if (curTileChick.y - 1 >= 0
            && matrixBomb[curTileChick.y - 1][curTileChick.x] == 1
            && matrixGrass[curTileChick.y - 1][curTileChick.x] == 1
            && matrixFlag[curTileChick.y  - 1][curTileChick.x] == 0)
            {matrixGrass[curTileChick.y - 1][curTileChick.x] = 0; usedMinesweeper--; return;}               // ô phía trên

        if (curTileChick.x - 1 >= 0
            && matrixBomb[curTileChick.y][curTileChick.x - 1] == 1
            && matrixGrass[curTileChick.y][curTileChick.x - 1] == 1
            && matrixFlag[curTileChick.y][curTileChick.x - 1] == 0)
            {matrixGrass[curTileChick.y][curTileChick.x  - 1] = 0; usedMinesweeper--; return;}              // ô pbên trái

        if (curTileChick.y + 1 < 20 && curTileChick.x + 1 < 20
            && matrixBomb[curTileChick.y + 1][curTileChick.x + 1] == 1
            && matrixGrass[curTileChick.y + 1][curTileChick.x + 1] == 1
            && matrixFlag[curTileChick.y  + 1][curTileChick.x + 1] == 0)
            {matrixGrass[curTileChick.y + 1][curTileChick.x  + 1] = 0; usedMinesweeper--; return;}          // ô phía dưới bên phải

        if (curTileChick.y + 1 < 20
            && matrixBomb[curTileChick.y + 1][curTileChick.x] == 1
            && matrixGrass[curTileChick.y + 1][curTileChick.x] == 1
            && matrixFlag[curTileChick.y  + 1][curTileChick.x] == 0)
            {matrixGrass[curTileChick.y + 1][curTileChick.x] = 0; usedMinesweeper--; return;}               // ô phía dưới

        if (curTileChick.x + 1 < 20
            && matrixBomb[curTileChick.y][curTileChick.x + 1] == 1
            && matrixGrass[curTileChick.y][curTileChick.x + 1] == 1
            && matrixFlag[curTileChick.y][curTileChick.x + 1] == 0)
            {matrixGrass[curTileChick.y][curTileChick.x  + 1] = 0; usedMinesweeper--; return;}              // ô bên phải

        if (curTileChick.x + 1 < 20 && curTileChick.y - 1 >= 0
            && matrixBomb[curTileChick.y - 1][curTileChick.x + 1] == 1
            && matrixGrass[curTileChick.y - 1][curTileChick.x + 1] == 1
            && matrixFlag[curTileChick.y  - 1][curTileChick.x + 1] == 0)
            {matrixGrass[curTileChick.y - 1][curTileChick.x  + 1] = 0; usedMinesweeper--; return;}          // ô phía trên bên phải

        if (curTileChick.y + 1 < 20 && curTileChick.x - 1 >= 0
            && matrixBomb[curTileChick.y + 1][curTileChick.x - 1] == 1
            && matrixGrass[curTileChick.y + 1][curTileChick.x - 1] == 1
            && matrixFlag[curTileChick.y  + 1][curTileChick.x - 1] == 0)
            {matrixGrass[curTileChick.y + 1][curTileChick.x  - 1] = 0; usedMinesweeper--; return;}          // ô phía dưới bên trái
    }
    else{
        if (matrixBomb[0][0] == 1 && matrixGrass[0][0] == 1 && matrixFlag[0][0] == 0) {
            matrixGrass[0][0] == 0;
            usedMinesweeper--;
            return;
        }
        if (matrixBomb[1][0] == 1 && matrixGrass[1][0] == 1 && matrixFlag[1][0] == 0) {
            matrixGrass[1][0] == 0;
            usedMinesweeper--;
            return;
        }
    }
}

int Core::getScore(){
    int tmp = 0;
    for (int i = 0 ; i < 7; i++)
        for (int j = 0; j < 20; j++)
            if (matrixGrass[i][j] == 0 && matrixBomb[i][j] == 0)
                tmp ++;
    return tmp;
}

void Core::getQandA(QandA &qanda){
    int number = rand() % listQandA.size();
    //qanda = listQandA[number];
    qanda = listQandA[number];
    listQandA.erase(listQandA.begin() +  number);

}

void Core::renderRecordList(SDL_Renderer* renderer) {
    gameTexture.renderRecordList(renderer, recordEasy, recordNormal, recordHard);
    if (gameSound.getEffectVol())
            button[6].reloadButton(0);
    else button[6].reloadButton(1);

    if (gameSound.getMusicVol())
            button[7].reloadButton(0);
    else button[7].reloadButton(1);

    for (int i = 6; i < 9; i++) button[i].renderButton(renderer);
//    button[9].renderButton(renderer);
}

void Core::saveData() {
    freopen("asset/save.txt", "w", stdout);
//    if (!continuePre) {
//        for (int i = 0; i < 10; ++i)
//            for (int j = 0; j < 10; ++j) a[i][j] = -1;
//        score = 0;
//        level = 1;
//        target = 1000;
//        more = 1500;
//        scount = 2;
//    }
//    for (int i = 0; i < 10; ++i) {
//        for (int j = 0; j < 10; ++j) cout << a[i][j] << " ";
//        cout << endl;
//    }
//    cout << score << endl;
//    cout << level << endl;
//    cout << target << endl;
//    cout << more << endl;
//    cout << scount << endl;
//    for (int i = 0; i < 5; ++i)
//        cout << highscore[i].first << " " << highscore[i].second << endl;
    cout << recordEasy[0] << endl;
    cout << recordEasy[1] << endl;
    cout << recordEasy[2] << endl;
    cout << recordNormal[0] << endl;
    cout << recordNormal[1] << endl;
    cout << recordNormal[2] << endl;
    cout << recordHard[0] << endl;
    cout << recordHard[1] << endl;
    cout << recordHard[2] << endl;
}

void Core::getData() {
    freopen("asset/save.txt", "r", stdin);
    cin >> recordEasy[0];
    cin >> recordEasy[1];
    cin >> recordEasy[2];
    cin >> recordNormal[0];
    cin >> recordNormal[1];
    cin >> recordNormal[2];
    cin >> recordHard[0];
    cin >> recordHard[1];
    cin >> recordHard[2];
}

//void Core::renderNXLVBoard(SDL_Renderer* renderer) {
//    gameTexture.renderNXLVBoard(renderer, score, level, target);
//}
//

//const int dh[4] = {-1, 0, 1, 0};
//const int dc[4] = {0, 1, 0, -1};

//void Core::solve()
//{
//    if(!canMove) return;
//    int x, y;
//    SDL_GetMouseState(&x, &y);
//    int i = x / 40, j = (y - 200) / 40;
//    while(!q.empty()) q.pop();
//    while(!erasedBlockID.empty()) erasedBlockID.pop();
//    for(int i = 0; i < 10; ++i)
//        for(int j = 0; j < 10; ++j) color[i][j] = 0;
//    q.push(i * 40 + j);
//    color[j][i] = 1;
//    while(!q.empty())
//    {
//        int id = q.front();
//        erasedBlockID.push(id);
//        q.pop();
//        i = id / 40; j = id % 40;
//        catColor = a[j][i];
//        for(int k = 0; k < 4; ++k)
//        {
//            if (j + dh[k] < 0 || j + dh[k] > 9 || i + dc[k] < 0 || i + dc[k] > 9) continue;
//            if(color[j + dh[k]][i + dc[k]] == 0 && a[j + dh[k]][i + dc[k]] == a[j][i])
//            {
//                q.push((i + dc[k]) * 40 + j + dh[k]);
//                color[j + dh[k]][i + dc[k]] = 1;
//            }
//        }
//        //a[j][i] = -1;
//    }
//    score += 5 * int(erasedBlockID.size() * erasedBlockID.size());
//    if (score > curHighScore) curHighScore = score;
//    canMove = false;
//}
//
//void Core :: solveTexture(SDL_Renderer* renderer)
//{
//    if (id != erasedBlockID.front()) {
//        for (int i = 0; i < TOTAL_PARTICAL; ++i) {
//            partical[i] = new Partical(erasedBlockID.front());
//        }
//        cnt++;
//        if (cnt > 14) cnt = 1;
//        gameSound.playEffect(cnt);
//        id = erasedBlockID.front();
//        a[id % 40][id / 40] = -1;
//    }
//    bool ok = false;
//    for (int i = 0; i < TOTAL_PARTICAL; ++i) if (!partical[i]->isDead()) ok = true;
//    if (ok) {
//        for (int i = 0; i < TOTAL_PARTICAL; ++i) if(!partical[i]->isDead())
//            partical[i]->render(renderer, gameTexture.getCatTexture(catColor));
//    }
//    else {
//        erasedBlockID.pop();
//        for (int i = 0; i < TOTAL_PARTICAL; ++i) delete partical[i];
//    }
//}
//
//void Core::newLevel() {
//    int cnt = 0;
//    for(int i = 9; i >= 0; --i)
//        for(int j = 9; j >= 0; --j)
//        if(a[j][i] != -1) cnt++;
//    if(cnt < 10) {
//        score += (10 - cnt) * 100;
//        if (score > curHighScore) curHighScore = score;
//    }
//    ++level;
//    target += more;
//    scount--;
//    if(scount == 0) more += 500, scount = 2;
//    for(int i = 0; i < 10; ++i)
//        for(int j = 0; j < 10; ++j) a[i][j] = rand() % 5;
//
//    canMove = false;
//}
//

