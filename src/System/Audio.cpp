#include "./Audio.hpp"

Audio::Audio(/* args */)
{
}

Audio::~Audio()
{
}

void Audio::loadShotSound(const char *path)
{
    _shot = LoadSound(path);
}

void Audio::playSoundMulti(Sound sound)
{
    PlaySoundMulti(sound);
}

void Audio::unloadShotSound()
{
    UnloadSound(_shot);
}

void Audio::playSound(Sound sound)
{
    PlaySound(sound);
}

Sound Audio::getShot()
{
    return _shot;
}

void Audio::setSoundVolume(Sound sound, float volume)
{
    SetSoundVolume(sound, volume);
}

void Audio::stopSound(Sound sound)
{
    StopSound(sound);
}