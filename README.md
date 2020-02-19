# pomodial
### Now your keyboard can yell at you at pomodoro frequency!

![Pomodial installed on a Signum 3.1](https://github.com/TroyFletcher/pomodial/raw/master/20200219_085421.jpg)

## Pomodial video on youtube
[![Pomodial on the youtubes](https://img.youtube.com/vi/kT58mEs4q6I/0.jpg)](https://www.youtube.com/watch?v=kT58mEs4q6I)
***
## A rotary encoder controlled countdown timer with an OLED display that doesn't lose rotary encoder polls, and is fine enough to track each individual click of the encoder for precise settings.

### NOTE: this is currently built into a keyboard, but all it does is share power with the keyboard, so this could be its own standalone device.

TBH this was mostly about getting an arduino nano to process input from a rotary encoder ACURATELY while running an OLED. Please feel free to copy rotary encoder running portions to get your project working. I could not find anything online that did this well enough to track individual rotary encoder shifts without spazzing out and jumping around.

The hardest part was figuring out how to write to the oled via i2c fast enough to process interrupts for the rotary encoder on the nano.

(The buzzer is off this build currently, but I will be adding a hilariously gigantic one to it soon.)