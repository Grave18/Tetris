#pragma once
#include <iostream>
#include <raylib.h>

#include "observer.h"

class SoundSystem : public Observer
{
public:
	SoundSystem()
	{
		InitAudioDevice();
		playerFell = LoadSound("resources/player_fell.wav");
		clearRow = LoadSound("resources/clear_row.wav");
	}
	SoundSystem(SoundSystem&) = delete;
	SoundSystem(SoundSystem&&) = delete;
	~SoundSystem() override
	{
		CloseAudioDevice();
		UnloadSound(playerFell);
		UnloadSound(clearRow);
	}
 
	void onNotify(void* entity, Events event) override
	{
		if (event == Events::ROW_CLEARED)
			playSoundClearRow();
		if (event == Events::PLAYER_FELL)
			playSoundPlayerFell();
	}

	void playSoundPlayerFell() const { PlaySound(playerFell); }
	void playSoundClearRow() const { PlaySound(clearRow); }

private:
	Sound playerFell;
	Sound clearRow;
};