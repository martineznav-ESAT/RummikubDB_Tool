// @author Jonathan Martínez Navarro

#include "AudioLib.h"

namespace AudioLib{

    SoLoud::Soloud audio_channel;

    //Needed use of arrays for Soloud library consistency
    //Was giving problems with dynamic memory allocation
    SoLoud::Wav sounds[SoundsType::TOTAL_SOUNDS];
    SoLoud::handle sound_handles[SoundsType::TOTAL_SOUNDS];

    //Audio channel and sound files inicialization
    void Init(){
        audio_channel.init();

        //Loads sounds.
        // sounds[SoundsType::ACTION].load("./Assets/Audio/action.wav");
        // sounds[SoundsType::BANG_LARGE].load("./Assets/Audio/bangLarge.wav");
        // sounds[SoundsType::BANG_MEDIUM].load("./Assets/Audio/bangMedium.wav");
        // sounds[SoundsType::BANG_SMALL].load("./Assets/Audio/bangSmall.wav");
        // sounds[SoundsType::BEAT_1].load("./Assets/Audio/beat1.wav");
        // sounds[SoundsType::BEAT_2].load("./Assets/Audio/beat2.wav");
        // sounds[SoundsType::EXTRA_SHIP].load("./Assets/Audio/extraShip.wav");
        // sounds[SoundsType::FIRE].load("./Assets/Audio/fire.wav");
        // sounds[SoundsType::UFO_BIG].load("./Assets/Audio/saucerBig.wav");
        // sounds[SoundsType::UFO_SMALL].load("./Assets/Audio/saucerSmall.wav");
        // sounds[SoundsType::THRUST].load("./Assets/Audio/thrust.wav");
    }

    //Returns a boolean that determines if de given sound type is currently paused or not
    bool IsSoundPaused(SoundsType type){
        return !audio_channel.isValidVoiceHandle(sound_handles[type]);
    }

    //Stops the given sound type
    void StopSound(SoundsType type){
        sounds[type].stop(); 
    }
    
    //Plays the given sound tyoe
    void PlaySound(SoundsType type){
        sound_handles[type] = audio_channel.play(sounds[type]); 
    }

    //Releases all AudioLib memory variables
    void EmptyMemory(){
        audio_channel.deinit();
    }
}
