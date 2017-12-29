# Rtttl
This code allows to play monophonic Nokia ringtones on your Arduino.
This is an adaptation of a sample sketch from the [tone library](https://code.google.com/archive/p/rogue-code/wikis/ToneLibraryDocumentation.wiki) by Brett Hagman, and the Arduino RTTTL-player by [Spica](https://github.com/spicajames/Rtttl).

## Why Rtttl?
* Compact
* its just a string you can paste in your code.  The string is stored to flash, so it doesn't eat up your RAM.
* You can change the octave and tempo fast and easy.

## What change from the original library?
* Compatible with STM32-platforms
* Allows non-blocking music playing
* String storage in flash area
* Detection of song completion

## More info
* [Wikipedia](https://en.wikipedia.org/wiki/Ring_Tone_Transfer_Language)
