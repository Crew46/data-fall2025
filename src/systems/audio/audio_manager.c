#ifndef AUDIO_MANAGER_C
#define AUDIO_MANAGER_C
#include "audio_manager.h"
#include "misc.h"
#include "audio.h"
#include "../../configuration/sound_configurations.h"
#include "time.h"
#include "math.h"

void PlayRandomSFXOfType(SFXType soundEffect)
{
    int randResult = rand() % 4;
    //each sound effect has 4 variants, randomize from 0-3.
    switch (soundEffect)
    {
    case EXPLOSION_SOUND_EFFECT:
        if(randResult == 0) PlaySFX(EXPLOSION_0);
        else if(randResult == 1) PlaySFX(EXPLOSION_1);
        else if(randResult == 2) PlaySFX(EXPLOSION_2);
        else if(randResult == 3) PlaySFX(EXPLOSION_3);
        break;
    case LASER_SOUND_EFFECT:
        if(randResult == 0) PlaySFX(LASER_SHOOT_0);
        else if(randResult == 1) PlaySFX(LASER_SHOOT_1);
        else if(randResult == 2) PlaySFX(LASER_SHOOT_2);
        else if(randResult == 3) PlaySFX(LASER_SHOOT_3);
        break;
    default:
        break;
    }
}

void InitializeAudioManager()
{
    select_sound(THE_ABYSS_MUSIC);
    select_channel(0);
    assign_channel_sound(get_selected_channel(), get_selected_sound());
    play_channel(get_selected_channel());
    set_channel_loop(true);
}

void PlaySFX(int id)
{
    play_sound(id);
}

void DeInitializeAudioManager()
{

}
#endif //AUDIO_MANAGER_C