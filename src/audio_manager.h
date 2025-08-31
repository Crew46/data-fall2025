#ifndef AUDIO_MANAGER_H
#include AUDIO_MANAGER_H
#include "misc.h"
#include "audio.h"

enum SoundEffect
{
    EXPLOSION_SOUND_EFFECT,
    LASER_SOUND_EFFECT
}

void PlaySoundFx(SoundEffect soundEffect)
{
    //each sound effect has 4 variants, randomize from 0-3.
    int randomValue = rand() % 4;
    switch (soundEffect)
    {
    case EXPLOSION_SOUND_EFFECT:
        break;
    case LASER_SOUND_EFFECT:
        break;
    default:
        break;
    }
}
#endif //AUDIO_MANAGER_H