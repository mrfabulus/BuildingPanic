#include "Resource/Sound.hpp"

Sound::Sound(std::string& aSoundName)
{
    this->soundName = aSoundName;

    this->wav = nullptr;
    char pathBuffer[512];
    snprintf(pathBuffer, sizeof(pathBuffer), "../assets/sounds/%s.wav", aSoundName.c_str());
    // printf("Tried loading %s\n", pathBuffer);
    this->wav = Mix_LoadWAV(pathBuffer);
}

Sound::~Sound()
{
    if (this->wav != nullptr)
    {
        Mix_FreeChunk(this->wav);
        this->wav = nullptr;
    }
}

void Sound::Play()
{
    if( Mix_PlayChannel(-1, this->wav, 0) == -1)
    {
        printf("Couldn't play wav\n");
        return;
    }
}
