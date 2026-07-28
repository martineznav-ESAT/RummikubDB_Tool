// @author Jonathan Martínez Navarro

#include <esat/window.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <esat/input.h>
#include <esat/draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef Utils_H
#define Utils_H

namespace Utils{
    struct Color{
        float r, g, b, a ;
    };

    extern const unsigned char kFPS;
    extern const int kWindowWidth, kWindowHeight;
    extern const int kBaseFontSize;

    extern double current_time,last_time;

    //Generates a new random number seed based
    //on clock system ms 
    void GenerateRandomSeed();

    //Genera un número del 0 al límite indicado sin incluirlo
    int GenerateRandomNumber(int limite);

    //Genera un número del limite indicado al limite en negativo pasando por el 0 sin incluir el limite 
    int GenerateRandomNumberNegative(int limite);

    //Genera un número decimal (2 decimales) del 0 al límite indicado sin incluirlo
    float GenerateRandomFloat(int limite);

    //Genera un número decimal (2 decimales) del limite indicado al limite en negativo pasando por el 0 sin incluir el limite 
    float GenerateRandomFloatNegative(int limite);

    void ControlFps();

    //Transforms a timestamp given of time_t type into a tm structure corrected with the local timezone.
    tm TimestampToStructTM(time_t timestamp);
}

#endif

