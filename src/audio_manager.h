#ifndef AUDIO_MANAGER.H
#define AUDIO_MANAGER.H

enum SFX_EVENT
{
  SFX_SHOOT_PLAYER,
  SFX_SHOOT_ENEMY
};

struct AudioManager
{
  Queue* sfxQueue;
};

AudioManager* createAudioManager()
{
  AudioManager* am = (AudioManager*)malloc(sizeof(AudioManager));
  am->sfxQueue = createQueue();

  return am;
}


#endif
