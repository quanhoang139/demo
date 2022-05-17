#include "Sound.h"
#include <iostream>

Sound::Sound() {
}

Sound::~Sound() {
}

void Sound::load() {
    gameBG = Mix_LoadMUS("asset/Sound/GameBG.flac");
    //gameBG = Mix_LoadMUS("asset/Sound/Darix Togni Digi G'Alessio - Vanoss Gaming Background Music (HD).mp3");
    if (gameBG == nullptr) std::cout << Mix_GetError();
    Mix_PlayMusic(gameBG, -1);
    effectVol = musicVol = true;
//    effect[0] = Mix_LoadWAV("asset/Sound/EffectSelectStar.wav");
//    effect[1] = Mix_LoadWAV("asset/Sound/EliminateEffect1.wav");
//    effect[2] = Mix_LoadWAV("asset/Sound/EliminateEffect2.wav");
//    effect[3] = Mix_LoadWAV("asset/Sound/EliminateEffect3.wav");
//    effect[4] = Mix_LoadWAV("asset/Sound/EliminateEffect4.wav");
//    effect[5] = Mix_LoadWAV("asset/Sound/EliminateEffect5.wav");
//    effect[6] = Mix_LoadWAV("asset/Sound/EliminateEffect6.wav");
//    effect[7] = Mix_LoadWAV("asset/Sound/EliminateEffect7.wav");
//    effect[8] = Mix_LoadWAV("asset/Sound/EliminateEffect8.wav");
//    effect[9] = Mix_LoadWAV("asset/Sound/EliminateEffect9.wav");
//    effect[10] = Mix_LoadWAV("asset/Sound/EliminateEffect10.wav");
//    effect[11] = Mix_LoadWAV("asset/Sound/EliminateEffect11.wav");
//    effect[12] = Mix_LoadWAV("asset/Sound/EliminateEffect12.wav");
//    effect[13] = Mix_LoadWAV("asset/Sound/EliminateEffect13.wav");
//    effect[14] = Mix_LoadWAV("asset/Sound/EliminateEffect14.wav");
//    effect[15] = Mix_LoadWAV("asset/Sound/EffectGameOver.wav");
//    effect[16] = Mix_LoadWAV("asset/Sound/EffectLevelCleared.wav");
    gameOver = Mix_LoadMUS("asset/Sound/EffectGameOver.wav");
    win = Mix_LoadMUS("asset/Sound/EffectLevelCleared.wav");
}

void Sound::playMusicBG(){
    Mix_PlayMusic(gameBG, -1);
}

void Sound::playMusicGO(){
    Mix_PlayMusic(gameOver, -1);
}

void Sound::playMusicWin(){
    Mix_PlayMusic(win, -1);
}

void Sound::changeMusicVol() {
    musicVol = !musicVol;
    if (musicVol) Mix_VolumeMusic(MIX_MAX_VOLUME);
    else Mix_VolumeMusic(0);
}

void Sound::changeEffectVol() {
    effectVol = !effectVol;
    if (effectVol) Mix_Volume(-1, MIX_MAX_VOLUME);
    else Mix_Volume(-1, 0);
}

bool Sound::getEffectVol() const {
    return effectVol;
}

bool Sound::getMusicVol() const {
    return musicVol;
}

void Sound::playEffect(int id) {
    if (id == 15 || id == 16) Mix_PlayMusic(gameOver, -1);
       //Mix_PlayChannel(1, effect[id], 0);//Mix_PlayMusic(gameOver, -1);//
    else Mix_PlayChannel(-1, effect[id], 0);

}
