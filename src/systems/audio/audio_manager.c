#ifndef AUDIO_MANAGER_C
#define AUDIO_MANAGER_C
#include "misc.h"
#include "audio.h"

enum SoundEffectType
{
    EXPLOSION_SOUND_EFFECT,
    LASER_SOUND_EFFECT
};

enum SoundEffect
{

};

enum MusicLoop
{
    MENU_MUSIC,
    IN_GAME_MUSIC
};

MusicLoop currentMusicLoop;

void ChangeMusicLoop(MusicLoop musicLoopToChangeTo)
{
    currentMusicLoop = musicLoopToChangeTo;
}

void PlayRandomSFXOfType(SoundEffectType soundEffect)
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

void PlaySFX(SoundEffect sfx)
{

}

void InitializeAudioManager()
{
    //temporary music loop location
    select_sound(THE_ABYSS_MUSIC);
    select_channel(0);
    assign_channel_sound(get_selected_channel(), get_selected_sound());
    play_channel(get_selected_channel());
    set_channel_loop(true);
}

void UpdateAudioManager()
{

}
#endif //AUDIO_MANAGER_C