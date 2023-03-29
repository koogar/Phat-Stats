
/*Mode Button Function*/

void button_Modes() {

  int display_ButtonVal = digitalRead(mode_Button);
  if (display_ButtonVal == LOW)

  {

    display_Button_counter ++;
    delay(debounceButton); // Debounce Button

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

      //case 4: // 5th SCREEN
      //  Display_CircleGauge ();
      
      //  break;
        

    }
}
