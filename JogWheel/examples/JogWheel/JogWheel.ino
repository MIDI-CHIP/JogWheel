#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(); 


volatile uint8_t train = 0;

void rotary_onButtonClick() {return;}

void rotary_loop() {
  
	//if (rotaryEncoder.currentButtonState() == BUT_RELEASED) {rotary_onButtonClick();}

	int16_t encoderDelta = rotaryEncoder.encoderChanged();
	
	if (encoderDelta == 0) return;

  train = (train << 1);
	
	if (encoderDelta > 0) {train = train + 1;}
	  
  int brain = train & 0x0F ;
  
  if (brain == 0  ){Serial.println("+"); train = 1;}
    
  if (brain == 15 ){Serial.println("-"); train = 0;} 
	
}

void setup() {

	Serial.begin(115200);


	rotaryEncoder.setup([]{rotaryEncoder.triggered();});

}

void loop() {

	rotary_loop();
	
	delay(5);															 

}
