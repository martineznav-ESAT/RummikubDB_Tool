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

    void Init();

    bool IsSoundPaused(SoundsType type);

    void PlaySound(SoundsType type);

    void StopSound(SoundsType type);

    void EmptyMemory();
}

#endif