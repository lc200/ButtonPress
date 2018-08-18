#include <ButtonPress.h>

/****************************************************** 
  This is an example of how to use the ButtonPress library to debounce a button press
  see https://github.com/lc200/ButtonPress

 ******************************************************/

#define BUTTON_1_PIN 2

// Create a button press object for each button, enable internal pull up and when the pin goes LOW the button is pressed
ButtonPress button1(BUTTON_1_PIN, true, LOW);

void setup() {
    
  // Set up the button
  button1.begin();

  // Set up serial
  Serial.begin(115200);
  Serial.println("Testing button press, press the button...");
}

void loop() {
  // Make sure the button is checked continually in the loop
  button1.debounceButton();

  // See if button is pressed
  ButtonPressResult result = button1.getButtonPressResult(false);
  if(result == ButtonPressResult::Pressed)
  {
     Serial.println("Button is pressed");
  }
}
