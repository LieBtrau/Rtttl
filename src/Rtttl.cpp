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
#include "Rtttl.h"

#define DEBUG
#ifdef DEBUG
#define DELAY(...) delay(__VA_ARGS__)
#define debug(...) Serial.print(__VA_ARGS__)
#define debugl(...) Serial.println(__VA_ARGS__)
#else
#define DELAY(...)
#define debug(...)
#define debugl(...)
#endif


FLASH_STRING(playingSong,"");

Rtttl::Rtttl(int buzzerPin, Tone_Function tf):
    _buzzerPin(buzzerPin),
    toneplayer(tf)
{
}

void Rtttl::play(_FLASH_STRING songInPlay)
{
    int num;
    playingSong = songInPlay;

    pinMode(_buzzerPin, OUTPUT);
    // Absolutely no error checking in here

    // format: d=N,o=N,b=NNN:
    // find the start (skip name, etc)
    while (playingSong[melodyIdx] != ':')
    {
        melodyIdx++;  // ignore name
    }
    melodyIdx++; // skip ':'

    // get default duration
    if (playingSong[melodyIdx] == 'd')
    {
        melodyIdx++;
        melodyIdx++; // skip "d="
        num = 0;
        while (isDigit(playingSong[melodyIdx]))
        {
            num = (num * 10) + (playingSong[melodyIdx++] -'0');
        }
        if (num > 0)
        {
            default_dur = num;
        }
        melodyIdx++; // skip comma
    }
    debug("ddur: ");
    debugl(default_dur, 10);

    // get default octave
    if (playingSong[melodyIdx] == 'o')
    {
        melodyIdx++;
        melodyIdx++; // skip "o="
        num = playingSong[melodyIdx++] -'0';
        if (num >= 3 && num <= 7)
        {
            default_oct = num;
        }
        melodyIdx++; // skip comma
    }
    debug("doct: ");
    debugl(default_oct, 10);

    // get BPM
    if (playingSong[melodyIdx] == 'b')
    {
        melodyIdx++;
        melodyIdx++; // skip "b="
        num = 0;
        while (isdigit(playingSong[melodyIdx]))
        {
            num = (num * 10) + (playingSong[melodyIdx++] -'0');
        }
        bpm = num;
        melodyIdx++; // skip colon
    }
    debug("bpm: ");
    debugl(bpm, 10);
    // BPM usually expresses the number of quarter notes per minute
    wholenote = (60 * 1000L / bpm) << 2; // this is the time for whole note (in milliseconds)
    debug("wn: ");
    debugl(wholenote, 10);

    melodyTimestamp = millis();
    debugl(F(""));
    debugl(F("Playing Melody"));
    nextDuration=0;
}

void Rtttl::getNextNote()
{
    if(melodyIdx >= playingSong.length())
    {
        stopTone();
        return;
    }
    byte note, scale;
    long duration;
    int num=0;
    // first, get note duration, if available
    while (isDigit(playingSong[melodyIdx]))
    {
        num = (num * 10) + (playingSong[melodyIdx++] -'0');
    }
    duration = wholenote / (num ? num : default_dur);   // we will need to check if we are a dotted note after

    // now get the note
    note = 0;
    switch (playingSong[melodyIdx])
    {
    case 'c': note = 1; break;
    case 'd': note = 3; break;
    case 'e': note = 5; break;
    case 'f': note = 6; break;
    case 'g': note = 8; break;
    case 'a': note = 10; break;
    case 'b': note = 12;  break;
    case 'p':
    default: note = 0;
    }
    melodyIdx++;

    //debugl(note);

    // now, get optional '#' sharp
    if (playingSong[melodyIdx] == '#')
    {
        note++;
        melodyIdx++;
    }

    // now, get optional '.' dotted note
    if (playingSong[melodyIdx] == '.')
    {
        duration += (duration>>1);
        melodyIdx++;
    }

    // now, get scale
    if (isDigit(playingSong[melodyIdx]))
    {
        scale = playingSong[melodyIdx] - '0';
        melodyIdx++;
    }
    else
    {
        scale = default_oct;
    }
    scale += OCTAVE_OFFSET;

    if (playingSong[melodyIdx] == ',')
    {
        melodyIdx++;  // skip comma for next note (or we may be at the end)
    }

    // now play the note
    nextFrequency = note ? notes[(scale - 4) * 12 + note] : 0;
    nextDuration = duration;
    debugl("");
    debug(nextFrequency);
    debug(" (");
    debug(nextDuration);
    debugl(")");
}

bool Rtttl::update()
{
    if (!melodyIdx)
    {
        return false;
    }
    unsigned long ts = millis();
    if (ts - melodyTimestamp > nextDuration + 5)
    { // Add 5 to give tone time between calls (Seems to need it)
        getNextNote();
        melodyTimestamp = ts;
        toneplayer(_buzzerPin, nextFrequency, nextDuration);
    }
    return true;
}

void Rtttl::stopTone()
{
    melodyLoopCount = melodyIdx = melodyLoopCounter = 0;
}

