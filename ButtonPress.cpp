/* Arduino ButtonPress library to debounce button presses */
// https://github.com/
// Copyright (C) 2018 by L Carpenter and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html

#include "Arduino.h"
#include "ButtonPress.h"

/*----------------------------------------------------------------------*
/ Initialise a ButtonPress object and set the pin internal pullup       *
/-----------------------------------------------------------------------*/
void ButtonPress::begin()
{
	// Set the pin mode and enable the pull up if set to
	pinMode(_buttonPin, getBitFlag(FLAG_ENABLE_PULLUP) ? INPUT_PULLUP : INPUT);
	
	if (_logicLevelWhenPressed == LOW)
	{
		// Default the current state to high
		_booleanFlags ^= (-true ^ _booleanFlags) & (1UL << FLAG_LAST_STATE);
	}
}

/*----------------------------------------------------------------------*
/ Get the result to see if the button was pressed after being dobounced *
/-----------------------------------------------------------------------*/
ButtonPressResult ButtonPress::getButtonPressResult(boolean isCheckLongPressed)
{
	if (isCheckLongPressed)
	{
		if (getBitFlag(FLAG_IS_LONG_PRESSED))
		{
			setBitFlag(FLAG_IS_LONG_PRESSED, false);
			setBitFlag(FLAG_IS_PRESSED, false);
			return ButtonPressResult::Pressed;
		}
		else if (getBitFlag(FLAG_PRESS_IN_PROGRESS))
		{
			return ButtonPressResult::InProgress;
		}
	}
	else if (getBitFlag(FLAG_IS_PRESSED))
	{
		setBitFlag(FLAG_IS_PRESSED, false);
		return ButtonPressResult::Pressed;
	}

	return ButtonPressResult::None;
}

/*----------------------------------------------------------------------*
/ In the loop constantly checks the button pressed stated and debounce  *
/-----------------------------------------------------------------------*/
void ButtonPress::debounceButton()
{
	const unsigned long buttonLongTimeMillis = 1000;
	const unsigned long debounceMillis = 20;
	unsigned long currentMillis = millis();

	// Is it time to check the buttons
	if (currentMillis - _lastButtonCheckMillis > debounceMillis)
	{
		// Set up next debounce check
		_lastButtonCheckMillis = currentMillis;

		// Is the button pressed
		boolean isPressed = digitalRead(_buttonPin) == _logicLevelWhenPressed;

		if (isPressed != getBitFlag(FLAG_LAST_STATE))
		{
			// Need to set the state and see if it is the same next time
			setBitFlag(FLAG_LAST_STATE, isPressed);
		}
		else
		{
			// State is the same as the last time around
			if (isPressed)
			{
				if (!getBitFlag(FLAG_LATCHED_HIGH))
				{
					setBitFlag(FLAG_IS_PRESSED, true);
					setBitFlag(FLAG_LATCHED_HIGH, true);
				}

				// Flag the button press is in progress				
				setBitFlag(FLAG_PRESS_IN_PROGRESS, true);

				// Time for long press
				_buttonHeldTimer += debounceMillis;

				if (_buttonHeldTimer >= buttonLongTimeMillis && !getBitFlag(FLAG_LONG_LATCHED_HIGH))
				{
					setBitFlag(FLAG_IS_LONG_PRESSED, true);
					setBitFlag(FLAG_LONG_LATCHED_HIGH, true);
				}
			}
			else
			{
				setBitFlag(FLAG_PRESS_IN_PROGRESS, false);
				_buttonHeldTimer = 0;
				setBitFlag(FLAG_LATCHED_HIGH, false);
				setBitFlag(FLAG_LONG_LATCHED_HIGH, false);
			}
		}
	}
}

/*----------------------------------------------------------------------*
/ Gets a flag in the status byte                                        *
/-----------------------------------------------------------------------*/
bool ButtonPress::getBitFlag(uint8_t position)
{
	return (_booleanFlags >> position) & 1U;
}

/*----------------------------------------------------------------------*
/ Sets a flag in the status byte                                        *
/-----------------------------------------------------------------------*/
void ButtonPress::setBitFlag(uint8_t position, bool booleanValue)
{
	_booleanFlags ^= (-booleanValue ^ _booleanFlags) & (1UL << position);
}




