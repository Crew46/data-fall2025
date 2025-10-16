#ifndef  _AUDIO_MANAGER_H
#define  _AUDIO_MANAGER_H
#include "misc.h"
#include "audio.h"

enum SoundEffect
{
    EXPLOSION_SOUND_EFFECT,
    LASER_SOUND_EFFECT
};

enum MusicLoop
{
    MENU_MUSIC,
    IN_GAME_MUSIC,
    GAMEPLAY_MUSIC
};

MusicLoop  currentMusicLoop;

void ChangeMusicLoop (MusicLoop musicLoopToChangeTo)
{
    currentMusicLoop  = musicLoopToChangeTo;
}

void PlaySoundFx (SoundEffect soundEffect)
{
    // each sound effect has 4 variants, randomize from 0-3.
    int  randomValue  = rand() % 4;
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

void InitializeAudioManager ()
{
    // temporary music loop location
    //select_sound (THE_ABYSS_MUSIC);
    if (currentState == GAMESTATE_TITLE)
    {
        select_sound (WHAT_IT_IS_CALLED_MUSIC);
        select_channel (0);
        set_channel_loop (false);
    }
    else if (currentState == GAMESTATE_INGAME)
    {
        select_sound (BETTER_THAN_FASTER_THAN_MUSIC);
        select_channel (0);
        set_channel_loop (true);
    }

    assign_channel_sound (get_selected_channel (), get_selected_sound ());
    play_channel (get_selected_channel ());
}

void UpdateAudioManager ()
{
    if (currentState              == GAMESTATE_TITLE)
    {    
        if (get_channel_state (0) == channel_stopped)
        {
            currentState           = GAMESTATE_INGAME;
            select_sound (BETTER_THAN_FASTER_THAN_MUSIC);
            select_channel (0);
            set_channel_loop (true);
            assign_channel_sound (get_selected_channel (), get_selected_sound ());
            play_channel (get_selected_channel ());
        }
    }    
}

#endif // _AUDIO_MANAGER_H
