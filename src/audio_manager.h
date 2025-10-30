#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

//#define SFX_QUEUE_CAP 32
/*
enum SfxEvent
{
  SFX_NONE = -1,
  SFX_SHOOT_PLAYER = 1,
  SFX_SHOOT_ENEMY
};

struct AudioManager
{
  int [SFX_QUEUE_CAP] queue;
  int head;
  int tail;
};

AudioManager audioManager;

void audioPush(SfxEvent sfx)
{
  if(audioManager.tail == SFX_QUEUE_CAP + 1)
    return;

  if(audioManager.queue[head] == NULL)
    audioManager.queue[head] = sfx;
  else
    audioManager.queue[audioManager.tail] = sfx;
  
  audioManager.tail = (audioManager.tail + 1) % SFX_QUEUE_CAP;
}

int audioPop()
{
  if(audio_manager.queue[audioManager.head] == NULL)
    return SFX_NONE;

  SfxEvent sfx = audioManager.queue[audioManager.head];
  audioManager.head = (audioManager.head + 1) % SFX_QUEUE_CAP;

  return sfx;


}*/

void playSound(int sound_id, int channel_id, bool isLooping, float volume)
{
  select_channel (channel_id);	
	set_channel_volume(volume);
	play_sound_in_channel (sound_id, channel_id); 
	set_channel_loop (isLooping);
	
}

#endif
