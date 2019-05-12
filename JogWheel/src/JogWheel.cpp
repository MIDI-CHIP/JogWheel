 

#include "JogWheel.h"

void IRAM_ATTR JogWheel::triggered()
{	
    static int8_t enc_states[] = { 0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0 };
	portENTER_CRITICAL_ISR(&(this->semaphore));
		this->pins <<= 2;                  
		int8_t temp = ( digitalRead(26)  ? (1 << 1) : 0) | ( digitalRead(25)  ? (1 << 0) : 0);		
		this->pins |= ( temp & 0x03 );  
		this->counter += (enc_states[( this->pins & 0x0f )]);	
		if (this->counter > 0xFFF) this->counter = 0;
		if (this->counter < 0) this->counter = 0xFFF;   
	 portEXIT_CRITICAL_ISR(&(this->semaphore));
}


JogWheel::JogWheel() 
{
	pinMode(25, INPUT);
	pinMode(26, INPUT);
	pinMode(27, INPUT);
}


int16_t JogWheel::encoderChanged() {

	int16_t _counter = this->counter;
	
	int16_t temp = _counter - this->stack_pointer;

		this->stack_pointer = _counter;

	    return temp;

	return 0;

}

void JogWheel::setup(void (*ISR_callback)(void))
{
	attachInterrupt(digitalPinToInterrupt(25), ISR_callback, CHANGE);
	attachInterrupt(digitalPinToInterrupt(26), ISR_callback, CHANGE);
}


ButtonState JogWheel::BUTTON()
{

	uint8_t butt_state = !digitalRead(27);

	if (butt_state && !this->previous_butt_state)
	{
		this->previous_butt_state = true;
		
		return BUT_PUSHED;
	}
	if (!butt_state && this->previous_butt_state)
	{
		this->previous_butt_state = false;
		
		return BUT_RELEASED; 
	}
	return (butt_state ? BUT_DOWN : BUT_UP);
}
