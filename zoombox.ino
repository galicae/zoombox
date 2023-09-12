//
// Zoom Buttons
// inspired by https://www.instructables.com/Zoom-Control-Box/
//
// Arduino Micro interrupt pins in order = 3, 2, 0, 1, 7 
// 
//#include "Keyboard.h"
#include "HID-Project.h"

// Define Arduino pin numbers for buttons and LEDs
#define LED1 14
#define LED2 15
#define LED3 16

#define BTN1 2  // toggle switch; Alt-V: Turn video on/off
#define BTN2 3  // toggle switch; Alt-A: Turn sound on/off
#define BTN3 4  // toggle switch; Alt-S: Turn screen share on/off
#define BTN4 5  // toggle switch; Alt-R: Turn recording on/off

#define BTN5 6  // push button Alt-Q: exit

#define NUMBUTTONS 5

int buttons[NUMBUTTONS] = {BTN1, BTN2, BTN3, BTN4, BTN5};
bool status[NUMBUTTONS] = {true, true, false, false, false};

void setup() {
  // set up LEDs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

  // set up push buttons
  for (int i = 0; i < NUMBUTTONS; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
    int state = digitalRead(buttons[i]);
    if (state == HIGH) {
      status[i] = true;
    }
    else {
      status[i] = false;
    }
  }

  Keyboard.begin();
}

void loop() {
  //check push buttons and act
  for (int i = 0; i < NUMBUTTONS; i++) {
    if ((digitalRead(buttons[i]) && !status[i]) || (!digitalRead(buttons[i]) && status[i])) {
      // Switch is toggled
      
      RXLED0;
      switch (i) {
        case 0: // Alt-V: video on/off
          Keyboard.press(KEY_LEFT_GUI);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.write('v');
          Keyboard.releaseAll();
          status[i] = !status[i];
          break;
        case 1: // Alt-A: Turn sound on/off
          Keyboard.press(KEY_LEFT_GUI);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.write('a');
          Keyboard.releaseAll();
          status[i] = !status[i];
          break;
        case 2: // Alt-S: Turn screen share on/off
          Keyboard.press(KEY_LEFT_GUI);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.write('s');
          Keyboard.releaseAll();
          status[i] = !status[i];
          break;
        case 3: // Alt-R: Turn recording on/off
          Keyboard.press(KEY_LEFT_GUI);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.write('r');
          Keyboard.releaseAll();
          status[i] = !status[i];
          // if we are recording, turn the light on; else off
          if (status[i]) {
            digitalWrite(LED1, LOW);
            digitalWrite(LED2, LOW);
            digitalWrite(LED3, LOW);
          } else {
            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            digitalWrite(LED3, HIGH);
          }
          break;
        case 4: // Alt-Q: exit. We need to press enter afterwards to confirm.
          Keyboard.press(KEY_LEFT_GUI);
          Keyboard.write('w');
          delay(100);
          // Release all keyboard keys
          Keyboard.releaseAll();

          // Press the return key and wait 1/10 second
          Keyboard.press(KEY_RETURN);
          delay(100);
      
          // Release all keyboard keys
          Keyboard.releaseAll();
          break;
      }
    }
  }
}
