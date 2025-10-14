#ifndef	SOUNDS_H_
#define SOUNDS_H_

void playAudio (int sound_id)
{
	play_sound(sound_id);
	set_sound_loop (true);
}







#endif //SOUNDS_H_
