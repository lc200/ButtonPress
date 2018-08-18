/* Arduino ButtonPress library to debounce button presses */
// https://github.com/
// Copyright (C) 2018 by L Carpenter and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html

#ifndef ButtonPress_h
#define ButtonPress_h
#define FLAG_LAST_STATE 7
#define FLAG_LATCHED_HIGH 6
#define FLAG_PRESS_IN_PROGRESS 5
#define FLAG_IS_LONG_PRESSED 4
#define FLAG_IS_PRESSED 3
#define FLAG_LONG_LATCHED_HIGH 2
#define FLAG_ENABLE_PULLUP 1

#include <Arduino.h>
typedef enum
{
	None,
	Pressed,
	InProgress
}
ButtonPressResult;

class ButtonPress
{
public:
	// ButtonPress(buttonPin, enableInternalPullup, logicLevelWhenPressed) instantiates a button object.
	//
	// Required parameter:
	// buttonPin				The pin number the button is connected
	// enableInternalPullup		When true the internal pull up is enabled on the pin
	// logicLevelWhenPressed    This is HIGH or LOW and presents the logic level that indicates the button is pressed
	ButtonPress(uint8_t buttonPin, boolean enableInternalPullup, uint8_t logicLevelWhenPressed)
		: _buttonPin(buttonPin), _logicLevelWhenPressed(logicLevelWhenPressed)
	{
		setBitFlag(FLAG_ENABLE_PULLUP, enableInternalPullup);
	}

	// Sets up the button ready to debounce button presses
	void begin();

	// Check the state of the button, this will return a pressed value only once, after that value is reset until the button is pressed again.
	//
	// Required parameter:
	//
	// isCheckedLongPress	When true the value returned is None for no long press registered or Pressed if the button has been held pressed for > 1 sec. Pass false for a normal check
	ButtonPressResult getButtonPressResult(boolean isCheckLongPressed);

	// This must be in the loop to constantly check the button and debounce the button press
	void debounceButton();

private:
	
	// Gets true or false (1 or 0) at the flag position
	//
	// Required parameter:
	// position	The position of the bit in the byte to set	
	bool getBitFlag(uint8_t position);

	// Sets a flag at the byte position
	//
	// Required parameter:
	// position	The position of the bit in the byte to set
	// booleanValue The value to set
	void setBitFlag(uint8_t position, bool booleanValue);
	byte _booleanFlags;
	uint8_t _buttonPin;
	uint8_t _logicLevelWhenPressed;
	uint32_t _lastButtonCheckMillis;
	uint16_t _buttonHeldTimer = 0;
};
#endif
