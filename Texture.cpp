#include "Texture.h"
#include <SDL_mixer.h>
#include <iostream>

using namespace std;

Texture::Texture(){
//    background = nullptr;
//    for(int i = 0; i < 5; ++i) catTexture[i] = nullptr;
//    chicken_R = nullptr;
//    chicken_L = nullptr;
}

Texture::~Texture(){
    background = nullptr;
    grass = nullptr;
    chicken_L = nullptr;
    chicken_R = nullptr;
    land = nullptr;
    bomb =  nullptr;
    header = nullptr;
    gameOver = nullptr;
    flag = nullptr;
    win = nullptr;
    menuBoard = nullptr;
    difficultyBoard = nullptr;
    for (int i = 0; i < 8; i++) numberBomb[i] = nullptr;
}

SDL_Texture* Texture::loadImage(SDL_Renderer* renderer, const std::string imgPath) {
    SDL_Surface* Image = IMG_Load(imgPath.c_str());
    SDL_Texture* loadTexture = SDL_CreateTextureFromSurface(renderer, Image);
    SDL_FreeSurface(Image);
    return loadTexture;
}

void Texture::renderText(SDL_Renderer* renderer, std::string text, SDL_Color color, int posX, int posY) {
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Rect Rect = {posX, posY, textSurface->w, textSurface->h};
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, nullptr, &Rect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Texture::renderTextUTF8(SDL_Renderer* renderer, std::string text, SDL_Color color,
                             int posX, int posY, int wrap, int maxHeight) {
    SDL_Surface *textSurface =  TTF_RenderUTF8_Solid_Wrapped(font, text.c_str(), color, wrap);
    SDL_Rect Rect = {posX, posY + (maxHeight - textSurface->h)/2, textSurface->w, textSurface->h};
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, nullptr, &Rect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Texture::loadMedia(SDL_Renderer* renderer){
    background = loadImage(renderer, "asset/img/background.png");
    numberBomb[0] = loadImage(renderer, "asset/img/1.png");
    numberBomb[1] = loadImage(renderer, "asset/img/2.png");
    numberBomb[2] = loadImage(renderer, "asset/img/3.png");
    numberBomb[3] = loadImage(renderer, "asset/img/4.png");
    numberBomb[4] = loadImage(renderer, "asset/img/5.png");
    numberBomb[5] = loadImage(renderer, "asset/img/6.png");
    numberBomb[6] = loadImage(renderer, "asset/img/7.png");
    numberBomb[7] = loadImage(renderer, "asset/img/8.png");
    HP = loadImage(renderer, "asset/img/heart.png");
    land = loadImage(renderer, "asset/img/land.png");
    bomb =  loadImage(renderer, "asset/img/bomb.png");
    grass =  loadImage(renderer, "asset/img/grass.png");
    flag =  loadImage(renderer, "asset/img/flag.png");
//    catTexture[0] = loadImage(renderer, "asset/Image/catyelow.png");
//    catTexture[1] = loadImage(renderer, "asset/Image/catgreen.png");
//    catTexture[2] = loadImage(renderer, "asset/Image/catblue.png");
//    catTexture[3] = loadImage(renderer, "asset/Image/catred.png");
//    catTexture[4] = loadImage(renderer, "asset/Image/catpurple.png");
//    menuBG = loadImage(renderer, "asset/Image/menu.png");
//    nxlvBoard = loadImage(renderer, "asset/Image/next level board.png");
//    recordList = loadImage(renderer, "asset/Image/record list.png");
//    stageClear = loadImage(renderer, "asset/Image/stage clear.png");
    gameOver = loadImage(renderer, "asset/img/gameover.png");
    win = loadImage(renderer, "asset/img/win.png");
    chicken_R = loadImage(renderer, "asset/img/chickright.png");
    chicken_L = loadImage(renderer, "asset/img/chickleft.png");
    header = loadImage(renderer, "asset/img/header.png");
    difficultyBoard = loadImage(renderer, "asset/img/difficulty.png");
    menuBoard = loadImage(renderer, "asset/img/menu.png");
    banner = loadImage(renderer, "asset/img/banner.png");
    infoBoard = loadImage(renderer, "asset/img/information.png");
    teacher = loadImage(renderer, "asset/img/teacher.png");
    student = loadImage(renderer, "asset/img/student.png");
    bombEffect = loadImage(renderer, "asset/img/bombEffect.png");
    easyBoard = loadImage(renderer, "asset/img/easyBoard.png");
    normalBoard = loadImage(renderer, "asset/img/normalBoard.png");
    hardBoard = loadImage(renderer, "asset/img/hardBoard.png");
    tileRecord = loadImage(renderer, "asset/img/tileRecord.png");
}

void Texture::renderMedia(SDL_Renderer* renderer, int matrixGrass[7][20],
                          int matrixBomb[7][20], int matrixFlag[7][20], float hp,
                          bool isGameOver, bool isWin, bool isSetting, bool isRemoving,
                          int usedMinesweeper, int score, int target){
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_Rect Rect;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 20; j++) {
            Rect = {j * 64 + 165, i * 64 + 310, 64, 64};
            SDL_RenderCopy(renderer, land, nullptr, &Rect);
            if (matrixBomb[i][j] == 1)
                SDL_RenderCopy(renderer, bomb, nullptr, &Rect);
            if (matrixGrass[i][j] == 1)
                SDL_RenderCopy(renderer, grass, nullptr, &Rect);
            if (matrixFlag[i][j] == 1)
                SDL_RenderCopy(renderer, flag, nullptr, &Rect);
        }
    }
    Rect = {165 - 64, 310, 64, 64};
    SDL_RenderCopy(renderer, land, nullptr, &Rect);

    Rect = {0, 0, 1472, 416};
    SDL_RenderCopy(renderer, header, nullptr, &Rect);

    if (hp > 0)
    {
        Rect = {128, 0, 57, 57};
        SDL_RenderCopy(renderer, HP, nullptr, &Rect);
        if (hp == 2)
        {
            Rect = {185, 0, 57, 57};
            SDL_RenderCopy(renderer, HP, nullptr, &Rect);
        }
    }

    if (isGameOver)
    {

    }

    font = TTF_OpenFont("asset/ttf/font_game.ttf", 20);
    if (!isSetting) renderText(renderer, "SET FLAG", {0, 0, 255, 255}, 25, 450);
    else renderText(renderer, "SET FLAG", {255, 0, 0, 255}, 25, 450);

    if (!isRemoving) renderText(renderer, "REMOVE FLAG", {0, 0, 255, 255}, 5, 570);
    else renderText(renderer, "REMOVE FLAG", {255, 0, 0, 255}, 5, 570);

    renderText(renderer, "MINESWEEPER", {0, 0, 255, 255}, 5, 690);
    renderText(renderer, "Remaining: " + to_string(usedMinesweeper), {0, 0, 0, 255}, 10, 715);


    font = TTF_OpenFont("asset/ttf/font_game.ttf", 30);
    renderText(renderer, "Target: " + to_string(target), {0, 0, 0, 255}, 350, 5);
    font = TTF_OpenFont("asset/ttf/font_game.ttf", 40);
    renderText(renderer, "SCORE: " + to_string(score), {255, 0, 0, 255}, 350, 40);


//    renderText(renderer, "Level: " + to_string(level), {255, 126, 0, 255}, 0, 30);
//    renderText(renderer, "Target: " + to_string(target), {255, 234, 22, 255}, 120, 30);
//
//    SDL_Surface* textSurface = TTF_RenderText_Blended(font, ("Score: " + to_string(score)).c_str(), {255, 255, 255, 255});
//    dsRect = {200 - textSurface->w / 2, 60, textSurface->w, textSurface->h};
//    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
//    SDL_FreeSurface(textSurface);
//    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

void Texture::renderChick(SDL_Renderer* renderer, Position posChick, int number, bool isMoving, bool left, int matrixBomb[7][20]){
    SDL_Rect Rect;
    Rect = {posChick.x, posChick.y, 64, 64};
    if (!left)
        SDL_RenderCopy(renderer, chicken_R, nullptr, &Rect);
    else
        SDL_RenderCopy(renderer, chicken_L, nullptr, &Rect);

    if (posChick.x != 165 - 64 && number != 0 && !isMoving && matrixBomb[(posChick.y-310)/64][(posChick.x - 165)/64] == 0)
    {
        Rect = {posChick.x, posChick.y - 64, 64, 64};
        SDL_RenderCopy(renderer, numberBomb[number - 1], nullptr, &Rect);
    }

}

void Texture::renderMenu(SDL_Renderer* renderer, bool isRenderInfo) {
    scale = 0;
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_Rect Rect;
    Rect = {800, 200, 408, 540};
    SDL_RenderCopy(renderer, difficultyBoard, nullptr, &Rect);
    Rect = {200, 200, 408, 540};
    SDL_RenderCopy(renderer, menuBoard, nullptr, &Rect);
    Rect = {460, 0, 512, 190};
    SDL_RenderCopy(renderer, banner, nullptr, &Rect);

    if (isRenderInfo)
    {
        Rect = {80, 120, 1320, 715};
        SDL_RenderCopy(renderer, infoBoard, nullptr, &Rect);
    }
}

void Texture::renderQandA(SDL_Renderer* renderer, QandA *qanda, int timeRemaining){
    font = TTF_OpenFont("asset/ttf/RadioCanada-Bold.ttf", 25);
    renderTextUTF8(renderer, qanda->question, {0, 0, 0, 255}, 110, 95, 1250, 90);

    font = TTF_OpenFont("asset/ttf/RadioCanada-Bold.ttf", 25);
    renderTextUTF8(renderer, qanda->answerA, {0, 0, 0, 255}, 100 - 10, 205, 280, 90);
    renderTextUTF8(renderer, qanda->answerB, {0, 0, 0, 255}, 433 - 10, 205, 280, 90);
    renderTextUTF8(renderer, qanda->answerC, {0, 0, 0, 255}, 766 - 10, 205, 280, 90);
    renderTextUTF8(renderer, qanda->answerD, {0, 0, 0, 255}, 1100 - 10, 205, 280, 90);
    SDL_Rect Rect;
    Rect = {0, 100, 90, 90};
    SDL_RenderCopy(renderer, teacher, nullptr, &Rect);
    Rect = {5, 210, 75, 75};
    SDL_RenderCopy(renderer, student, nullptr, &Rect);
    if (qanda->choose == "")
    {
        if (timeRemaining > 0)
        {
            font = TTF_OpenFont("asset/ttf/font_game.ttf", 30);
            renderText(renderer, "Choose a correct answer!", {255, 255, 0, 255}, 1010, 12);
            font = TTF_OpenFont("asset/ttf/dlxfont_.ttf", 25);
            if (timeRemaining >= 10)
                renderText(renderer, "Time Remaining:" + to_string(timeRemaining), {255, 0, 0, 255}, 960, 52);
            else
                renderText(renderer, "Time Remaining:0" + to_string(timeRemaining), {255, 0, 0, 255}, 960, 52);
        }
    }
    if (qanda->answer == qanda->choose)
    {
        font = TTF_OpenFont("asset/ttf/font_game.ttf", 50);
        renderText(renderer, "CORRECT ANSWER!", {35, 133, 37, 255}, 970, 5);
        font = TTF_OpenFont("asset/ttf/font_game.ttf", 30);
        renderText(renderer, "You are safe here", {0, 0, 0, 255}, 1050, 55);
    }
    else if (timeRemaining <= 0)
    {
        font = TTF_OpenFont("asset/ttf/font_game.ttf", 50);
        renderText(renderer, "TIME OUT!", {255, 0, 0, 255}, 1065, 5);
        font = TTF_OpenFont("asset/ttf/font_game.ttf", 30);
        renderText(renderer, "Correct answer is: " + qanda->answer, {0, 0, 255, 255}, 1050, 55);
    }
    else if(qanda->choose != "")
    {
        font = TTF_OpenFont("asset/ttf/font_game.ttf", 50);
        renderText(renderer, "INCORRECT!", {255, 0, 0, 255}, 1050, 5);
        font = TTF_OpenFont("asset/ttf/font_game.ttf", 30);
        renderText(renderer, "Correct answer is: " + qanda->answer, {0, 0, 255, 255}, 1050, 55);
    }

    TTF_CloseFont(font);
}

void Texture::renderGameOver(SDL_Renderer* renderer) {
    //SDL_RenderCopy(renderer, background, nullptr, nullptr);
//    font = TTF_OpenFont("x.ttf", 20);
//    renderText(renderer, "High Score: " + to_string(highscore), {0, 255, 255, 255}, 0, 0);
//    renderText(renderer, "Level: " + to_string(level), {255, 126, 0, 255}, 0, 30);
//    renderText(renderer, "Target: " + to_string(target), {255, 234, 22, 255}, 120, 30);
//    SDL_Surface* textSurface = TTF_RenderText_Blended(font, ("Score: " + to_string(score)).c_str(), {255, 255, 255, 255});
//    SDL_Rect dsRect = {200 - textSurface->w / 2, 60, textSurface->w, textSurface->h};
//    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
//    SDL_FreeSurface(textSurface);
//    SDL_DestroyTexture(textTexture);
//    TTF_CloseFont(font);
    SDL_Rect Rect;
    scale+=3;
    //if (Mix_Playing(2) == 0) scale = 0;
    if (scale > 200) scale = 200;
    Rect.w = 5 * scale;
    Rect.h = 1 * scale;
    Rect.x = (1472 - Rect.w) / 2;
    Rect.y = (64*12 - Rect.h) / 2;
    SDL_RenderCopy(renderer, gameOver, nullptr, &Rect);
}

void Texture::renderBombEffect(SDL_Renderer* renderer, Position posChick) {
    //SDL_RenderCopy(renderer, background, nullptr, nullptr);
//    font = TTF_OpenFont("x.ttf", 20);
//    renderText(renderer, "High Score: " + to_string(highscore), {0, 255, 255, 255}, 0, 0);
//    renderText(renderer, "Level: " + to_string(level), {255, 126, 0, 255}, 0, 30);
//    renderText(renderer, "Target: " + to_string(target), {255, 234, 22, 255}, 120, 30);
//    SDL_Surface* textSurface = TTF_RenderText_Blended(font, ("Score: " + to_string(score)).c_str(), {255, 255, 255, 255});
//    SDL_Rect dsRect = {200 - textSurface->w / 2, 60, textSurface->w, textSurface->h};
//    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
//    SDL_FreeSurface(textSurface);
//    SDL_DestroyTexture(textTexture);
//    TTF_CloseFont(font);

    SDL_Rect Rect;
    scaleBomb+=1;


    //if (Mix_Playing(2) == 0) scale = 0;
    if (scaleBomb > 20) scaleBomb = 20;
    //Rect = {posChick.x, posChick.y, 64, 64};
    Rect.w = 3 * scaleBomb;
    Rect.h = 3 * scaleBomb;
//    Rect.x = (posChick.x + 64 - Rect.w) / 2;
//    Rect.y = (posChick.y + 64 - Rect.h) / 2;
    Rect.x = posChick.x + (64 - Rect.w)/2;
    Rect.y = posChick.y + (64 - Rect.h)/2;
    //cout << Rect.x << " " << Rect.y << endl;
    if (scaleBomb !=20) SDL_RenderCopy(renderer, bombEffect, nullptr, &Rect);
}

void Texture::renderWin(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
//    font = TTF_OpenFont("x.ttf", 20);
//    renderText(renderer, "High Score: " + to_string(highscore), {0, 255, 255, 255}, 0, 0);
//    renderText(renderer, "Level: " + to_string(level), {255, 126, 0, 255}, 0, 30);
//    renderText(renderer, "Target: " + to_string(target), {255, 234, 22, 255}, 120, 30);
//    SDL_Surface* textSurface = TTF_RenderText_Blended(font, ("Score: " + to_string(score)).c_str(), {255, 255, 255, 255});
//    SDL_Rect dsRect = {200 - textSurface->w / 2, 60, textSurface->w, textSurface->h};
//    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
//    SDL_FreeSurface(textSurface);
//    SDL_DestroyTexture(textTexture);
//    TTF_CloseFont(font);
    SDL_Rect Rect;
    scale+=3;
    //if (Mix_Playing(2) == 0) scale = 0;
    if (scale > 200) scale = 200;
    Rect.w = 5 * scale;
    Rect.h = 1 * scale;
    Rect.x = (1472 - Rect.w) / 2;
    Rect.y = (64*12 - Rect.h) / 2;
    SDL_RenderCopy(renderer, win, nullptr, &Rect);
}

SDL_Texture* Texture :: getNumberBombAround(int number){
    return numberBomb[number + 1];
}

void Texture::renderRecordList(SDL_Renderer* renderer, int recordEasy[], int recordNormal[], int recordHard[]) {
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_Rect Rect;
    //Rect = {487, 10, 497, 97};
    Rect = {470, 10, 497, 97};
    SDL_RenderCopy(renderer, tileRecord, nullptr, &Rect);
    Rect = {70, 200, 408, 540};
    SDL_RenderCopy(renderer, easyBoard, nullptr, &Rect);
    Rect = {500, 200, 408, 540};
    SDL_RenderCopy(renderer, normalBoard, nullptr, &Rect);
    Rect = {930, 200, 408, 540};
    SDL_RenderCopy(renderer, hardBoard, nullptr, &Rect);

    font = TTF_OpenFont("asset/ttf/dlxfont_.ttf", 35);
    //renderText(renderer, "TOP1:" + to_string(recordEasy[0]), {255, 0, 0, 255}, 130, 350);
    renderText(renderer, "TOP1:" + to_string(recordEasy[0]), {255, 0, 0, 255}, 130, 370);
    renderText(renderer, "TOP2:" + to_string(recordEasy[1]), {255, 0, 0, 255}, 130, 470);
    renderText(renderer, "TOP3:" + to_string(recordEasy[2]), {255, 0, 0, 255}, 130, 570);

    renderText(renderer, "TOP1:" + to_string(recordNormal[0]), {37, 97, 46, 255}, 570, 370);
    renderText(renderer, "TOP2:" + to_string(recordNormal[1]), {37, 97, 46, 255}, 570, 470);
    renderText(renderer, "TOP3:" + to_string(recordNormal[2]), {37, 97, 46, 255}, 570, 570);

    renderText(renderer, "TOP1:" + to_string(recordHard[0]), {245, 240, 36, 255}, 990, 370);
    renderText(renderer, "TOP2:" + to_string(recordHard[1]), {245, 240, 36, 255}, 990, 470);
    renderText(renderer, "TOP3:" + to_string(recordHard[2]), {245, 240, 36, 255}, 990, 570);
//    SDL_Rect dsRect = {200 - 190, 100, 380, 476};
//    SDL_RenderCopy(renderer, recordList, nullptr, &dsRect);
//    font = TTF_OpenFont("x.ttf", 30);
//    renderText(renderer, "Level " + to_string(hightscore[0].second) + ": " + to_string(hightscore[0].first), {255, 126, 0, 255}, 110, 215);
//    renderText(renderer, "Level " + to_string(hightscore[1].second) + ": " + to_string(hightscore[1].first), {216, 255, 0, 255}, 110, 295);
//    renderText(renderer, "Level " + to_string(hightscore[2].second) + ": " + to_string(hightscore[2].first), {48, 255, 13, 255}, 110, 372);
//    renderText(renderer, "Level " + to_string(hightscore[3].second) + ": " + to_string(hightscore[3].first), {255, 255, 255, 255}, 110, 445);
//    renderText(renderer, "Level " + to_string(hightscore[4].second) + ": " + to_string(hightscore[4].first), {255, 255, 255, 255}, 110, 523);
//    TTF_CloseFont(font);
}

//void Texture::renderStageClear(SDL_Renderer* renderer, int a[10][10], const int score, const int level, const int target, const int highscore) {
//    SDL_RenderCopy(renderer, background, nullptr, nullptr);
//    SDL_Rect dsRect;
//    for(int i = 0; i < 10; ++i) {
//        for(int j = 0; j < 10; ++j) {
//            dsRect = {i * 40, j * 40 + 200, 40, 40};
//            if (a[j][i] == -1) continue;
//            SDL_RenderCopy(renderer, catTexture[a[j][i]], nullptr, &dsRect);
//        }
//    }
//    font = TTF_OpenFont("x.ttf", 20);
//    renderText(renderer, "High Score: " + to_string(highscore), {0, 255, 255, 255}, 0, 0);
//    renderText(renderer, "Level: " + to_string(level), {255, 126, 0, 255}, 0, 30);
//    renderText(renderer, "Target: " + to_string(target), {255, 234, 22, 255}, 120, 30);
//
//    SDL_Surface* textSurface = TTF_RenderText_Blended(font, ("Score: " + to_string(score)).c_str(), {255, 255, 255, 255});
//    dsRect = {200 - textSurface->w / 2, 60, textSurface->w, textSurface->h};
//    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
//    SDL_FreeSurface(textSurface);
//    SDL_DestroyTexture(textTexture);
//    TTF_CloseFont(font);
//
//    static int scale = 0;
//    scale += 2;
//    if (Mix_Playing(2) == 0) scale = 0;
//    if (scale > 130) scale = 130;
//    dsRect.w = 2 * scale;
//    dsRect.h = 1 * scale;
//    dsRect.x = 200 - dsRect.w / 2;
//    dsRect.y = 333 - dsRect.h / 2;
//    SDL_RenderCopy(renderer, stageClear, nullptr, &dsRect);
//}


//void Texture::renderNXLVBoard(SDL_Renderer* renderer, const int score, const int level, const int target) {
//    SDL_RenderCopy(renderer, background, nullptr, nullptr);
//    SDL_Rect dsRect = {200 - 141, 333 - 175, 282, 350};
//    SDL_RenderCopy(renderer, nxlvBoard, nullptr, &dsRect);
//    font = TTF_OpenFont("x.ttf", 20);
//    renderText(renderer, to_string(level), {255, 255, 255, 255}, 190, 337);
//    renderText(renderer, to_string(target), {255, 255, 255, 255}, 190, 375);
//    TTF_CloseFont(font);
//    font = TTF_OpenFont("x.ttf", 30);
//    SDL_Surface* textSurface = TTF_RenderText_Blended(font, to_string(score).c_str(), {255, 255, 255, 255});
//    dsRect = {200 - textSurface->w / 2, 250, textSurface->w, textSurface->h};
//    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
//    SDL_FreeSurface(textSurface);
//    SDL_DestroyTexture(textTexture);
//    TTF_CloseFont(font);
//}
