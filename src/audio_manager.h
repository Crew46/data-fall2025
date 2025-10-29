#ifndef AUDIO_MANAGER.H
#define AUDIO_MANAGER.H


enum SfxEvent
{
  SFX_SHOOT_PLAYER = 1,
  SFX_SHOOT_ENEMY
};

struct AudioNode
{
  AudioNode* next;
  SfxEvent sfx;
};
struct AudioQueue
{
  AudioNode* front;
  AudioNode* back;
};
struct AudioManager
{
  AudioQueue audioQueue;
};

#endif
