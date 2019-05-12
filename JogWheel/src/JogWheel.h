
#ifndef JOG
#define JOG
#include "Arduino.h"

typedef enum {
	BUT_DOWN = 0,
	BUT_PUSHED = 1,
	BUT_UP = 2,
	BUT_RELEASED = 3,
} ButtonState;

class JogWheel {
	
private:


	volatile int16_t counter = 0;

	uint8_t pins             = 0;
	int16_t stack_pointer    = 0;

	bool previous_butt_state = 0;

	void(*ISR_callback)();
	portMUX_TYPE semaphore = portMUX_INITIALIZER_UNLOCKED;

public: 

	JogWheel();

	void IRAM_ATTR triggered();
	void setup(void (*ISR_callback)(void));

	int16_t readEncoder();
	int16_t encoderChanged();

	ButtonState BUTTON();
};
#endif

