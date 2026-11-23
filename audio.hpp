#pragma once
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>
#include <iostream>

ma_engine engine;
//static bool audio_engine_started = false;

class Sound {
    ma_sound sound;
    
    public:
    Sound() {}
    Sound(const char* filename) {
        loadFile(filename);
    }
    ~Sound() {
        ma_sound_uninit(&sound);
    }

    void loadFile(const char* filename) {
        //if(!audio_engine_started) {std::cerr<<"YOU FORGOT TO INIT THE AUDIO, STOOPID!! >:3";exit(-2);}
        ma_result result = ma_sound_init_from_file(&engine, filename, 0, NULL, NULL, &sound);
        if (result != MA_SUCCESS) {
            std::cerr<<"FAILED TO LOAD SOUND: "<<filename;
            exit(-2);
        }
    }

    void setLooping(bool looping) {
        ma_sound_set_looping(&sound, looping);
    }
    void start() {
        ma_sound_start(&sound);
    }
    void stop() {
        ma_sound_stop(&sound);
    }
};

void audioInit() {
    ma_result result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        std::cerr<<"FAILED TO START AUDIO ENGINE";
        exit(-1);
    }
    //audio_engine_started = true;
}