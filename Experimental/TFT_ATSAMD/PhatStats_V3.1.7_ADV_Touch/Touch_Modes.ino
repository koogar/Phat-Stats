/*New Touch Screen Button Mode Function*/

#define touchScreen // Use touch screen to change DisplayStyles

#ifdef  touchScreen
//----------------------------- Touch Screen Button---------------------------------------

/*ONLY ENABLE IF YOU HAVE A ILI9341 "TOUCH" SCREEN!!!! Use touch screen to change DisplayStyles
  (Rotary Encoder modes must be disabled)*/

//#ifdef  touchScreen
/* XPT2046 touch_Button modes*/
#include <XPT2046_Touchscreen.h> /* https://github.com/PaulStoffregen/XPT2046_Touchscreen */

#define TOUCH_IRQ_PIN  3 // T_IRQ Touch Screen Interupt pin)
#define TOUCH_CS_PIN   2 // T_CS  Touch Screen select

//XPT2046_Touchscreen touch(TOUCH_CS_PIN);  // Param 2 - NULL - No interrupts
//XPT2046_Touchscreen touch(TOUCH_CS_PIN, 255);  // Param 2 - 255 - No interrupts
XPT2046_Touchscreen touch( TOUCH_CS_PIN, TOUCH_IRQ_PIN ); // Param 2 - Touch IRQ Pin - interrupt enabled polling

int touch_Button_counter = 0;

//#endif

int debounceTouchscreenButton = 100;

void touch_Modes() {

  //while ( touch.touched() )
  if (touch.tirqTouched()) {
    if (touch.touched()) {

      {
      }
    }
    //delay(debounceTouchscreenButton); // Debounce Button / use for touch also
    touch_Button_counter ++;

    next_display();
    /* Clear Screen*/
    backlightOFF();
    tft.fillScreen(ILI9341_BLACK);

    /* Reset count if over max mode number, */
    if (touch_Button_counter == 6) // Number of screens available when button pressed
    {
      touch_Button_counter = 0;
    }
  }

  else

    /* Change Mode */
    switch (display_Button_counter) {

      //default:
      //Display_LS();
      //break;

      case 0: // 1st SCREEN
        Display_LS();

        break;

      case 1: // 2nd SCREEN

        Display_LS_180();
        break;

      case 2: // 3nd SCREEN

        Display_Port();
        break;

      case 3: // 4nd SCREEN
        Display_Port_180();

        break;
      case 4: // 4nd SCREEN
        Display_CircleGauge();

        break;
      case 5: // 4nd SCREEN
        Display_CircleGauge_180();

        break;

    }
}
#endif
