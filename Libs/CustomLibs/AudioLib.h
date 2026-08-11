// @author Jonathan Martínez Navarro

#include <esat_extra/soloud/soloud.h>
#include <esat_extra/soloud/soloud_wav.h>
#undef DrawText

#ifndef AudioLib_H
#define AudioLib_h

namespace AudioLib{

    enum SoundsType{
        ACTION,
        // BANG_LARGE,
        // BANG_MEDIUM,
        // BANG_SMALL,
        // BEAT_1,
        // BEAT_2,
        // EXTRA_SHIP,
        // FIRE,
        // UFO_BIG,
        // UFO_SMALL,
        // THRUST,
        TOTAL_SOUNDS
    };

    //Audio channel and sound files inicialization
    void Init();

    //Returns a boolean that determines if de given sound type is currently paused or not
    bool IsSoundPaused(SoundsType type);

    //Stops the given sound type
    void PlaySound(SoundsType type);

    //Plays the given sound type
    void StopSound(SoundsType type);

    //Releases all AudioLib memory variables
    void EmptyMemory();
}

#endif