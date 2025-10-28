#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

enum SFXType
{
    EXPLOSION_SOUND_EFFECT,
    LASER_SOUND_EFFECT
};

struct SFX
{
    int id;
    SFXType type;
};

struct AudioManager
{
    DoublyLinkedList* sfxList;
};

//AudioManager* GetAudioManager();
void PlayRandomSFXOfType(SFXType type);
void PlaySFX(int id);
void InitializeAudioManager();
void DeInitializeAudioManager();
void UpdateAudioManager();


#endif //AUDIO_MANAGER_H