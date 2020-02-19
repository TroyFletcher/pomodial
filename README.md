# pomodial
### Now your keyboard can yell at you at pomodoro frequency!

![Pomodial installed on a Signum 3.1](https://github.com/TroyFletcher/pomodial/raw/master/20200219_085421.jpg)

[![Pomodial on the youtubes](https://img.youtube.com/vi/kT58mEs4q6I/0.jpg)](https://www.youtube.com/watch?v=kT58mEs4q6I)
***
TBH this was mostly about getting an arduino nano to process input from a rotary encoder ACURATELY while running an OLED. Please feel free to copy rotary encoder running portions to get your project working. I could not find anytying online that did this.

A keyboard add on of a Rotary encoder controlled Pomodoro timer that uses an OLED for display and a buzzer for timing.

The hardest part was figuring out how to write to the oled via i2c fast enough to process interrupts for the rotary encoder on the nano.