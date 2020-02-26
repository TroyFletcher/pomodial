#include <Wire.h>

#define outputA 2
#define outputB 3

#define readA bitRead(PIND,outputA)//faster than digitalRead()
#define readB bitRead(PIND,outputB)//faster than digitalRead()

int oldhours   ; //the remainder from days division (in milliseconds) divided by hours, this gives the full hours
int oldminutes ;      //and so on...
int oldseconds  ;// second;
long reset_time;
const long day = 86400000; // 86400000 milliseconds in a day
const long hour = 3600000; // 3600000 milliseconds in an hour
const long minute = 60000; // 60000 milliseconds in a minute
const long second =  1000; // 1000 milliseconds in a second
int encoder_button_state;
int encoder_button_last_state; 
int counter = 0;
int lastcounter = -1;
int countdown_minutes = 0;
int countdown_minutes_prev = -1;
byte aState;
byte bState;
byte aLastState;
int buzzerPin = 15; // 15 = A1
int buttonPin = 4;     // the number of the pushbutton pin

//   pin   label  NANO    label  pin
//           ________________
//_____1_____TX1__________VIN______________
//_____0_____RX0__________GND______________
//___________RST__________RST______________
//___________GND___________5V______________
//_____2_____D2____________A7______________
//_____3_____D3____________A6______________
//_____4_____D4____________A5____19________
//_____5_____D5____________A4____18________
//_____6_____D6____________A3____17________
//_____7_____D7____________A2____16________
//_____8_____D8____________A1____15________
//_____9_____D9____________A0____14________
//____10_____D10_________AREF______________
//____11_____D11__|    |__3v3______________
//____12_____D12__|    |__D13____13__LED___
//________________|    |___________________

#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiAvrI2c oled;

void setup() {
  

#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif // RST_PIN >= 0
  // Call oled.setI2cClock(frequency) to change from the default frequency.

  oled.setFont(Adafruit5x7);
	pinMode (buzzerPin, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(outputA), isrA, CHANGE);
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);

  pinMode (buttonPin,INPUT_PULLUP);
  /* lastcounter = counter; */
  reset_time = millis();
  Serial.begin (9600);
  // Reads the initial state of the outputA
  aLastState = readA;
}

void loop() {
  aState = readA; // Reads the "current" state of the outputA
  bState = readB; // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  aLastState = aState; // Updates the previous state of the outputA with the current state

  /* long timeNow = millis() - reset_time; */
	/* int hours = 0; */
	/* int minutes = 0; */
  /* int seconds = 0; */
	int hours = 0;
	int minutes =  0;
	int seconds =  0;
	char timer_state = ' ';
	if (reset_time > millis()){ // set time is in the future
		hours =(((reset_time - millis())/1000)/3600);
		minutes = (((reset_time - millis())/1000) - (3600*hours))/60;
		seconds = (((reset_time - millis())/1000) -(3600*hours)-(60*minutes));
		timer_state = ' ';
	}
	else if (countdown_minutes == 0){ // time is blank
		timer_state = ' ';
	}
	else if (reset_time < millis()){ // time is OVERDUE
		hours =(((millis() - reset_time)/1000)/3600);
		minutes = (((millis() - reset_time)/1000) - (3600*hours))/60;
		seconds = (((millis() - reset_time)/1000) -(3600*hours)-(60*minutes));
		timer_state = '-';
	}
  if (   counter != lastcounter
				 || seconds != oldseconds)
    {
      oldseconds = seconds;
      /* if time past due */
			if (millis() > reset_time){
				oled.invertDisplay(seconds % 2);
				if(timer_state == '-' && 0 == ( seconds % 5 )){
				chirp();
				}
			}
      if (counter != lastcounter){
        Serial.print("Position: ");
        Serial.println(counter/2);
        lastcounter = counter;
      }
      //oled.clear();
      //fastClear() ;
      //oled.clearToEOL();
      //oled.clearField(0,0,20);
      //oled.setContrast(counter/2);
      oled.setCursor(0,0);
			oled.set1X();
			if(countdown_minutes_prev != countdown_minutes){
				oled.clearToEOL();
				oled.print("Countdown ");
				oled.print(countdown_minutes);
				oled.println(" minutes");
				countdown_minutes_prev = countdown_minutes;
			}
			else{
				oled.println("C");
			}
      oled.set2X();
      oled.clearToEOL();
      oled.print(timer_state);
      if (hours   < 10){oled.print("0");}
      oled.print(hours);
      oled.print(":");
      if (minutes < 10){oled.print("0");}
      oled.print(minutes);
      oled.print(":");
      if (seconds < 10){oled.print("0");}
      oled.println(seconds);
      oled.set1X();
      oled.clearToEOL();
      oled.println(counter/2);
    }

	encoder_button_last_state = encoder_button_state; // Updates the previous state of the outputA with the current state
  encoder_button_state = digitalRead(buttonPin); // Reads the "current" state of the outputA
  if (encoder_button_last_state != encoder_button_state){ // button state has changed
    if (digitalRead(buttonPin) == LOW) { // button just pressed
      // display.setTextSize(4);
      // display.setTextColor(WHITE); // 'inverted' text
      // display.println("BUTT");
      // digitalWrite(basePin, HIGH);
      // display.setTextSize(1);

      reset_time = millis() + (abs(counter/2) * 60000);
      oldseconds = -1; // force a screen update by setting old seconds to unmatchable value
			oled.invertDisplay(0);
			countdown_minutes = abs(counter/2);
    } else { // button just released
			if (countdown_minutes != 0){ // if the counter is zero, keep quiet
				chirp();
			}
			/* annoy(); */
      // display.println("NOTT");
      // display.setTextSize(1);
      // digitalWrite(basePin, LOW);
    }
  }
}
void isrA() {
  aState = readA; // Reads the "current" state of the outputA
  bState = readB; // Reads the "current" state of the outputA
  // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
  if (bState != aState) {  // anticlockwise
    counter --;
  } else { // clockwise
    counter ++;
  }
  delay(30);
}

void fastClear() {
  for (uint8_t r = 0; r < 8; r++) {
    // set row to clear
    oled.setCursor(0, r);
    // Wire has 32 byte buffer so send 8 packets of 17 bytes.
    for (uint8_t b = 0; b < 8; b++) {
      Wire.beginTransmission(I2C_ADDRESS);
      Wire.write(0X40);
      for (uint8_t i = 0; i < 16; i++) {
        Wire.write(0);  
      }
      Wire.endTransmission();
    }
  }
  oled.setCursor(0, 0);
}


void chirp() {
	int delay_short = 5; // this time varies based on the buzzer type
  tone(buzzerPin, 2078, delay_short);
  delay(delay_short);
  tone(buzzerPin, 4978, delay_short);
  delay(delay_short);
	tone(buzzerPin, 2078, delay_short);
  delay(delay_short);
}

void annoy() {
	int delay_medium = 10;
	tone(buzzerPin, 220, 10); 
  delay(10); 
	tone(buzzerPin, 100, 10); 
	delay(10); 
}
