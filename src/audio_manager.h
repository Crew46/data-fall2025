#ifndef  _AUDIO_MANAGER_H
#define  _AUDIO_MANAGER_H
#include "misc.h"
#include "audio.h"

/*
struct AudioTrigger
{
    int position;
    int vy_obj_factor;
    int max_obj_vy;
    int min_obj_vy;
};

struct AudioAction
{
    int           num_triggers; // number of triggers
    AudioTrigger *segment;      // array containing the AudioTriggers for a track
};

    AudioAction [6] AudioOffset;
    AudioOffset[0].num_triggers              = 4;
    AudioOffset[0].segment                   = (AudioTrigger *) malloc (sizeof (AudioTrigger) * 4);
    AudioOffset[0].segment[0].position       = 220000;
    AudioOffset[0].segment[0].vy_obj_factor  = 0;
    AudioOffset[0].segment[0].max_obj_vy     = -1000;
    AudioOffset[0].segment[0].min_obj_vy     = -1000;
    AudioOffset[0].segment[1].position       = 350000;
    AudioOffset[0].segment[1].vy_obj_factor  = 1;
    AudioOffset[0].segment[1].max_obj_vy     = -1000;
    AudioOffset[0].segment[1].min_obj_vy     = -1000;
    AudioOffset[0].segment[2].position       = 575000;
    AudioOffset[0].segment[2].vy_obj_factor  = 1;
    AudioOffset[0].segment[2].max_obj_vy     = 4;
    AudioOffset[0].segment[2].min_obj_vy     = 1;
    AudioOffset[0].segment[3].position       = -1000;
    AudioOffset[0].segment[3].vy_obj_factor  = 2;
    AudioOffset[0].segment[3].max_obj_vy     = -1000;
    AudioOffset[0].segment[3].min_obj_vy     = -1000;
    AudioOffset[1].num_triggers              = 4;
    AudioOffset[1].segment                   = (AudioTrigger *) malloc (sizeof (AudioTrigger) * 4);
    AudioOffset[1].segment[0].position       = 100000;
    AudioOffset[1].segment[0].vy_obj_factor  = 0;
    AudioOffset[1].segment[0].max_obj_vy     = -1000;
    AudioOffset[1].segment[0].min_obj_vy     = -1000;
    AudioOffset[1].segment[1].position       = 315000;
    AudioOffset[1].segment[1].vy_obj_factor  = 1;
    AudioOffset[1].segment[1].max_obj_vy     = -1000;
    AudioOffset[1].segment[1].min_obj_vy     = -1000;
    AudioOffset[1].segment[2].position       = 600000;
    AudioOffset[1].segment[2].vy_obj_factor  = 1;
    AudioOffset[1].segment[2].max_obj_vy     = 4;
    AudioOffset[1].segment[2].min_obj_vy     = 1;
    AudioOffset[1].segment[3].position       = -1000;
    AudioOffset[1].segment[3].vy_obj_factor  = 2;
    AudioOffset[1].segment[2].max_obj_vy     = -1000;
    AudioOffset[1].segment[2].min_obj_vy     = -1000;

    position                   = get_channel_position (0);
    for (index = 0; index < AudioOffset[currentState].num_triggers; index++)
    {
        if (position          <  AudioOffset[currentState].segment[index].position;
        {
            if (AudioOffset[currentState].segment[index].vy_obj_factor >  -1000)
            {
                vy_obj_factor  = AudioOffset[currentState].segment[index].vy_obj_factor;
            }

            if (AudioOffset[currentState].segment[index].max_obj_vy >  -1000)
            {
                max_obj_vy     = AudioOffset[currentState].segment[index].max_obj_vy;
            }

            if (AudioOffset[currentState].segment[index].min_obj_vy >  -1000)
            {
                min_obj_vy     = AudioOffset[currentState].segment[index].min_obj_vy;
            }
        }
    }
*/

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
    else if (currentState == GAMESTATE_GAMEPLAY)
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
            currentState           = GAMESTATE_GAMEPLAY;
            select_sound (BETTER_THAN_FASTER_THAN_MUSIC);
            select_channel (0);
            assign_channel_sound (get_selected_channel (), get_selected_sound ());
            play_channel (get_selected_channel ());
            set_channel_loop (true);
        }
    }    
}

#endif // _AUDIO_MANAGER_H
