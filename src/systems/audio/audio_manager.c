#ifndef AUDIO_MANAGER_C
#define AUDIO_MANAGER_C
#include "audio_manager.h"
#include "misc.h"
#include "audio.h"
#include "../../configuration/sound_configurations.h"

AudioManager* audioManager = NULL;

AudioManager* GetAudioManager()
{
    return audioManager;
}

void PlayRandomSFXOfType(SFXType soundEffect)
{
    //each sound effect has 4 variants, randomize from 0-3.
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

void InitializeAudioManager()
{
    audioManager = (AudioManager*)malloc(sizeof(AudioManager));
    audioManager->sfxArray = (SFX*)malloc(sizeof(SFX) * numSFX);
    select_sound(THE_ABYSS_MUSIC);
    select_channel(0);
    assign_channel_sound(get_selected_channel(), get_selected_sound());
    play_channel(get_selected_channel());
    set_channel_loop(true);
}

void PlaySFX(SFXName id)
{

}

void DeInitializeAudioManager()
{

}

void UpdateAudioManager()
{

}
#endif //AUDIO_MANAGER_C