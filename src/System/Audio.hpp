#ifndef _AUDIO_
#define _AUDIO_

#include <raylib.h>

class Audio
{
private:
    Sound _shot;
public:
    Audio(/* args */);
    ~Audio();
    void playSoundMulti(Sound sound);
    void loadShotSound(const char *path);
    void unloadShotSound();
    void playSound(Sound sound);
    Sound getShot();
    void setSoundVolume(Sound sound, float volume);
    void stopSound(Sound sound);
};

#endif