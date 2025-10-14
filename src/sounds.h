#ifndef	SOUNDS_H_
#define SOUNDS_H_

void playAudio (int sound_id, int channel_id, bool i, float x)
{
	select_channel (channel_id);	
	set_channel_volume(x);
	play_sound_in_channel (sound_id, channel_id); 
	set_channel_loop (i);
	
	
}







#endif //SOUNDS_H_
