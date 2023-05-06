
/*Mode Button Function*/

void button_Modes() {

  int display_ButtonVal = digitalRead(mode_Button);

  if (display_ButtonVal == LOW)

  {

    delay(debounceButton); // Debounce Button

    display_Button_counter ++;
    next_display();
    /* Clear Screen*/
    backlightOFF();
    tft.fillScreen(ILI9341_BLACK);

    /* Reset count if over max mode number, */
    if (display_Button_counter == 4) // Number of screens available when button pressed
    {
      display_Button_counter = 0;
    }
  }

  else

    /* Change Mode */
    switch (display_Button_counter) {

      //default:
      //Display_GC9A01_Port_R0();
      //break;

      case 0: // 1st SCREEN
        Display_GC9A01_Port_R0();
        break;

      case 1: // 2nd SCREEN
tft.setRotation(1);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
        //Display_GC9A01_Port_R1();
        break;

      case 2: // 3nd SCREEN
tft.setRotation(2);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
        //Display_GC9A01_Port_R2();
        break;
      case 3: // 4nd SCREEN
        //Display_GC9A01_Port_R3();
tft.setRotation(3);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

        break;

    }
}
