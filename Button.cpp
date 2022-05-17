#include "Button.h"

Button::Button() {
    opt = 0;
}

Button::~Button() {

}

void Button::loadButton(SDL_Renderer* renderer, const int width, const int height,
                        const int scrPosX, const int scrPosY, const std::string fiImgPath, std::string seImgPath) {
    this->width = width;
    this->height = height;
    this->scrPosX = scrPosX;
    this->scrPosY = scrPosY;
    if (fiImgPath != " ") {
        SDL_Surface* Image = IMG_Load(fiImgPath.c_str());
        fiButtonTexture = SDL_CreateTextureFromSurface(renderer, Image);
        SDL_FreeSurface(Image);
    }
    if (seImgPath != " ") {
        SDL_Surface* Image = IMG_Load(seImgPath.c_str());
        seButtonTexture = SDL_CreateTextureFromSurface(renderer, Image);
        SDL_FreeSurface(Image);
    }
    buttonEffect = Mix_LoadWAV("asset/Sound/EffectButton.wav");
    //buttonEffect = Mix_LoadWAV("asset/Sound/buttonSound.wav");
}

bool Button::checkUserClickPos() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x < scrPosX || y < scrPosY || x > scrPosX + width || y > scrPosY + height) return false;
    Mix_PlayChannel(-1, buttonEffect, 0);
    return true;
}

void Button::renderButton(SDL_Renderer* renderer) {
    SDL_Rect dsRect = {scrPosX, scrPosY, width, height};
    //SDL_RenderDrawRect(renderer, &dsRect);
    if (fiButtonTexture != nullptr) {
        if (opt == 0)
            SDL_RenderCopy(renderer, fiButtonTexture, nullptr, &dsRect);
        else
            SDL_RenderCopy(renderer, seButtonTexture, nullptr, &dsRect);
    }
}

void Button::reloadButton(const int opt) {
    this->opt = opt;
}

