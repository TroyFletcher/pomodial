# pomodial
### Now your keyboard can yell at you at pomodoro frequency!

![Pomodial installed on a Signum 3.1](https://github.com/TroyFletcher/pomodial/raw/master/20200219_085421.jpg)

## Pomodial video on youtube
[![Pomodial on the youtubes](https://img.youtube.com/vi/kT58mEs4q6I/0.jpg)](https://www.youtube.com/watch?v=kT58mEs4q6I)
***
## A rotary encoder controlled countdown timer with an OLED display that doesn't lose rotary encoder polls, and is fine enough to track each individual click of the encoder for precise settings.

### This is currently built into a keyboard, but all it does is share power with the keyboard, so this could be its own standalone device.

TBH this was mostly about getting an arduino nano to process input from a rotary encoder ACURATELY while running an i2c OLED. Please feel free to copy rotary encoder running portions to get your project working. I could not find anything online that did this well enough to track individual rotary encoder shifts without spazzing out and jumping around.

### Requirements 
- If using a Nano, you must use the interrupt pins D2 and D3 for the rotary encoder A and B pins.
- You must use the SSD1306 ASCII library, the Adafruit one is hueg leik xbox and slow slow slow.
- I'm using a mechanical rotary encoder module that only has three resisters on the board with the connection. I've seen others that have components for smoothing out the signals, timing might be a little different on those.
- If you're sharing power with the keyboard, you should unplug the keyboard from the computer before programming the nano, as there might be competing voltages and problems. I don't think this is actually a problem, but it's probably a good practice.
- If you use the faster SPI OLED, you might not have any timing problems at all, so the delays might need to be adjusted

### NOTES
- There are some technical inconsistencies in how the rotary encoder A vs B inputs are processed, this could be cleaned up, but I was just happy to get the rotary encoder to the point where it wasn't slipping reads.
- If you run this a a different clock speed, you may want need to tune the delay in the interrupt function, as that was tuned for the clock in the ATmega328p. This delay serves to let the reads of the traversal settle down, as the interrupt catches all the jitters in the mechanical rotary encoder's brush traversal. An optical encoder might not have this problem. 
- The buzzer is off this build currently, but I will be adding a hilariously gigantic one to it soon.