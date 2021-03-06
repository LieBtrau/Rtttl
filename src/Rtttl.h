/*
   Rtttl.h - Library for playing rtttl melodies
   Created by James BM, June 15, 2016.
   Based on the gits from Daniel Hall https://gist.github.com/smarthall/1618800
   Released into the public domain.

   To mix the output of the signals to output to a small speaker (i.e. 8 Ohms or higher),
   simply use 1K Ohm resistors from each output pin and tie them together at the speaker.
   Don't forget to connect the other side of the speaker to ground!

   You can get more RTTTL (RingTone Text Transfer Language) songs from
   http://code.google.com/p/rogue-code/wiki/ToneLibraryDocumentation
 */
#ifndef Rtttl_h
#define Rtttl_h

#include "Arduino.h"
#ifdef ARDUINO_ARCH_STM32F1
#define _FLASH_STRING String
#define FLASH_STRING(name, value) \
    const String name##_flash = value; \
    _FLASH_STRING name(name##_flash);
#else
#include <Flash.h>
#endif

class Rtttl
{
    typedef void(*Tone_Function)(uint32_t _pin, uint32_t frequency, uint32_t duration);
public:
    Rtttl(int buzzerPin, Tone_Function tf);
    void play(_FLASH_STRING songInPlay);
    bool update();//return true while playing else false
    void stopTone();
    void getNextNote();
    typedef enum{
        PAUSE = 0,
        NOTE_B0  = 33,
        NOTE_CS1 = 35,
        NOTE_D1  = 37,
        NOTE_DS1 = 39,
        NOTE_E1  = 41,
        NOTE_F1  = 44,
        NOTE_FS1 = 46,
        NOTE_G1  = 49,
        NOTE_GS1 = 52,
        NOTE_A1  = 55,
        NOTE_AS1 = 58,
        NOTE_B1  = 62,
        NOTE_C2  = 65,
        NOTE_CS2 = 69,
        NOTE_D2  = 73,
        NOTE_DS2 = 78,
        NOTE_E2  = 82,
        NOTE_F2  = 87,
        NOTE_FS2 = 93,
        NOTE_G2  = 98,
        NOTE_GS2 = 104,
        NOTE_A2  = 110,
        NOTE_AS2 = 117,
        NOTE_B2  = 123,
        NOTE_C3  = 131,
        NOTE_CS3 = 139,
        NOTE_D3  = 147,
        NOTE_DS3 = 156,
        NOTE_E3  = 165,
        NOTE_F3  = 175,
        NOTE_FS3 = 185,
        NOTE_G3  = 196,
        NOTE_GS3 = 208,
        NOTE_A3  = 220,
        NOTE_AS3 = 233,
        NOTE_B3  = 247,
        NOTE_C4  = 262,
        NOTE_CS4 = 277,
        NOTE_D4  = 294,
        NOTE_DS4 = 311,
        NOTE_E4  = 330,
        NOTE_F4  = 349,
        NOTE_FS4 = 370,
        NOTE_G4  = 392,
        NOTE_GS4 = 415,
        NOTE_A4  = 440,
        NOTE_AS4 = 466,
        NOTE_B4  = 494,
        NOTE_C5  = 523,
        NOTE_CS5 = 554,
        NOTE_D5  = 587,
        NOTE_DS5 = 622,
        NOTE_E5  = 659,
        NOTE_F5  = 698,
        NOTE_FS5 = 740,
        NOTE_G5  = 784,
        NOTE_GS5 = 831,
        NOTE_A5  = 880,
        NOTE_AS5 = 932,
        NOTE_B5  = 988,
        NOTE_C6  = 1047,
        NOTE_CS6 = 1109,
        NOTE_D6  = 1175,
        NOTE_DS6 = 1245,
        NOTE_E6  = 1319,
        NOTE_F6  = 1397,
        NOTE_FS6 = 1480,
        NOTE_G6  = 1568,
        NOTE_GS6 = 1661,
        NOTE_A6  = 1760,
        NOTE_AS6 = 1865,
        NOTE_B6  = 1976,
        NOTE_C7  = 2093,
        NOTE_CS7 = 2217,
        NOTE_D7  = 2349,
        NOTE_DS7 = 2489,
        NOTE_E7  = 2637,
        NOTE_F7  = 2794,
        NOTE_FS7 = 2960,
        NOTE_G7  = 3136,
        NOTE_GS7 = 3322,
        NOTE_A7  = 3520,
        NOTE_AS7 = 3729,
        NOTE_B7  = 3951,
        NOTE_C8  = 4186,
        NOTE_CS8 = 4435,
        NOTE_D8  = 4699,
        NOTE_DS8 = 4978,
    }NOTES;
    NOTES notes[49] = {PAUSE,
                       NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
                       NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
                       NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
                       NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7};
    byte _buzzerPin;
    static const byte OCTAVE_OFFSET=0;
    byte default_dur = 4;
    byte default_oct = 6;
    int bpm = 63;
    long wholenote;
    unsigned int nextFrequency;
    unsigned int nextDuration;
    unsigned int melodyIdx = 0;
    byte melodyLoopCount;
    unsigned long melodyTimestamp;
    unsigned long melodyLoopCounter;
    Tone_Function toneplayer;
};


#endif
