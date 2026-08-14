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
#include <string.h>

#include "./Utils.h"

namespace Utils{
    //Frames updated per second
    const unsigned char kFPS = 60;

    //Window dimensions
    const int kWindowWidth = 1280, kWindowHeight = 960;

    //Frame management variables
    double current_time,last_time;

    //Generates a new seed for random numbers generation based on the system clock ms
    void GenerateRandomSeed(){
        srand(time(NULL)); 
    }
    
    //Generates a random number between 0 and the given limit without including this last one
    int GenerateRandomNumber(int limit){
        return (rand()%limit);
    }

    //Generates a number between the given limit and this same limit in negative 
    //including the 0 but not including the limit neither in positive nor negative
    int GenerateRandomNumberNegative(int limit){
        return (GenerateRandomNumber(limit)) * (GenerateRandomNumber(2) == 0 ? -1 : 1);
    }

    //Generate a decimal number with precision 2 between 0 and the given limit without including it
    float GenerateRandomFloat(int limit){
        return (GenerateRandomNumber(limit*100)/100.0f);
    }

    //Generates a decimal number with precision 2 between the given limit and this same limit in negative 
    //including the 0 but not including the limit neither in positive nor negative
    float GenerateRandomFloatNegative(int limit){
        return (GenerateRandomFloat(limit) * (GenerateRandomNumber(2) == 0 ? -1 : 1));
    }

    //Manages the maximum FPS at which the application can run
    void ControlFps(){
        do{
            current_time = esat::Time();
        }while((current_time-last_time)<=1000.0/kFPS);
    }

    //Transforms a timestamp given of time_t type into a tm structure corrected with the local timezone.
    tm TimestampToStructTM(time_t timestamp){
        char *time_buffer = (char*)malloc(26);
        tm time_struct;
        _localtime64_s(&time_struct, &timestamp); 
        asctime_s(time_buffer, 26, &time_struct);

        free(time_buffer);
        return time_struct;
    }
}