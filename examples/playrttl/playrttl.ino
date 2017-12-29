/*
 * Ring tones can be found on:
 *  http://arcadetones.emuunlim.com/
 * This website contains ringtones with unsupported '_' character
 *  http://www.cellringtones.com/ringtones/
 *  http://www.freefonefun.co.uk/ff/text/RingTonesMenu.htm
 */
#include <Rtttl.h>

static const byte SPEAKER_PIN=9; //Pin you have speaker/piezo connected to (be sure to include a 100 ohm resistor) and other side of speaker to GND.

#ifdef ARDUINO_ARCH_STM32F1
//No need for special tone library on STM32-cores
Rtttl Rtttl1(SPEAKER_PIN, tone);
#else
#include <TimerFreeTone.h>
Rtttl Rtttl1(SPEAKER_PIN, TimerFreeTone);
#endif


FLASH_STRING(song1,"Indy:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6");
FLASH_STRING(song2,"allthatshewants:d=4,o=5,b=90:16g#,16g#,8g#,16c#,16c#,8p,8g#,8g#,16c#,\
16c#,8p,8g#,8f#,8f#,8f#,16e,8f#,16e,8c#,8p,8c#,8f,8c#,8c#,16c#,8f,8c#,c#,\
8p,8d#,8d#,16d#,8c,16a#4,8g#4,8p,8c#,8g#,8g#,8g#,8g#,8g#,16g#,16g#,\
8p,8g#,8a#,8a#,8a#,8a#,a.,8a,8g#,8g#,16f#,8f,8g#,8g#,16f#,8f,c#.,8g#4,\
16b4,8c#,16e,16p,8c#.,g#,8f#,16e,16c#,8p,16e,16p,16e,16e,16e,8f#,8f#");
FLASH_STRING(song3,"TheA-team:d=4,o=6,b=112:p,8f5,e5,8c5,f5,e5,f5,g5,8a5,b5,8p,8c,c,8g5,c,p,8e5,f5,8g5,c5,p,c,8g5,d,c,8a_.5,16a5,16g5,8f.5,g5,p,c,8g5,c,p,8e5,f5,8g5,c5,p,8f5,e5,8c5,f5,e5,f5,g5,8a5,b5,8p,8c");

byte ctr=0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if(!Rtttl1.update())
    {
        switch(++ctr)
        {
        case 1:
            Rtttl1.play(song1);
            break;
        case 2:
            Rtttl1.play(song2);
            break;
        case 3:
            Rtttl1.play(song3);
            ctr=0;
            break;
        }
    }
}
