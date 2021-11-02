#pragma once
#include <iostream>
#include <raylib.h>
#include <any>

#include "observer.h"

class SoundSystem : public Observer
{
public:
    SoundSystem()
    {
        InitAudioDevice();
        sounds_.push_back(LoadSound("resources/player_fell.wav"));
        sounds_.push_back(LoadSound("resources/clear_row.wav"));
    }
    SoundSystem(SoundSystem&) = delete;
    SoundSystem(SoundSystem&&) = delete;
    ~SoundSystem() override
    {
        for (const auto& sound : sounds_)
        {
            UnloadSound(sound);
        }
        CloseAudioDevice();
    }
 
    void onNotify(const std::any& entity, Events event) override
    {
        if (event == Events::ROW_CLEARED)
            playSoundClearRow();
        else if (event == Events::PLAYER_FELL)
            playSoundPlayerFell();
    }

    void playSoundPlayerFell() const { PlaySound(sounds_[0]); }
    void playSoundClearRow() const { PlaySound(sounds_[1]); }

    void setSoundVolume(float volume) 
    {
        if (volume > 1.0f) soundVolume_ = 1.0f;
        else if (volume < 0.0f) soundVolume_ = 0.0f;
        else soundVolume_ = volume;

        for (auto& sound : sounds_)
        {
            SetSoundVolume(sound, soundVolume_);
        }
    }
    float getSoundVolume() const { return soundVolume_; }

private:
    float soundVolume_ = 0.5f;

    std::vector<Sound> sounds_;
};