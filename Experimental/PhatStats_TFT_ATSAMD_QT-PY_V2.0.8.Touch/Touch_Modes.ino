

/*New Touch Screen Button Mode Function*/

#ifdef  touchScreen

void touch_Modes() {

  //while ( touch.touched() )
  if (touch.tirqTouched()) {
    if (touch.touched()) {

      {
      }
    }
    //delay(debounceTouchscreenButton); // Debounce Button / use for touch also
    touch_Button_counter ++;

    /* Clear Screen*/
    tft.fillScreen(ILI9341_BLACK);

    /* Reset count if over max mode number, */
    if (touch_Button_counter == 3) // Number of screens available when button pressed
    {
      touch_Button_counter = 0;
    }
  }

  else

    /* Change Mode */
    switch (touch_Button_counter) {

      case 0: // 1st SCREEN
        DisplayStyle_Portrait_ATSAMD();
        break;

      case 1: // 2nd SCREEN

        DisplayStyle_Landscape_ATSAMD();
        break;

      case 2: // 2nd SCREEN
        DisplayStyle_CircleGauge_ATSAMD();
        break;

    }
}
#endif
