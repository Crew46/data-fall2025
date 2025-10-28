#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

int numSFX = 8;

enum SFXName
{
    LASER_SHOOT_ZERO,
    LASER_SHOOT_ONE,
    LASER_SHOOT_TWO,
    LASER_SHOOT_THREE,
    EXPLOSION_ZERO,
    EXPLOSION_ONE,
    EXPLOSION_TWO,
    EXPLOSION_THREE
};

enum SFXType
{
    EXPLOSION_SOUND_EFFECT,
    LASER_SOUND_EFFECT
};

struct SFX
{
    int id;
    SFXName Name;
    SFXType type;
};

struct AudioManager
{
    SFX* sfxArray;
};

//AudioManager* GetAudioManager();
void PlayRandomSFXOfType(SFXType type);
void PlaySFX(SFXName id);
void InitializeAudioManager();
void DeInitializeAudioManager();
void UpdateAudioManager();


#endif //AUDIO_MANAGER_H