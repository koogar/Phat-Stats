

/*New Encoder Mode Button Function*/

void encoder_Modes() {



  int enc_buttonVal = digitalRead(encoder_Button);
  if (enc_buttonVal == LOW)

  {
    delay(debounceEncButton); // Debounce Button
    enc_Button_counter ++;

    /* Clear Screen*/
    tft.fillScreen(ILI9341_BLACK);
    tft2.fillScreen(ILI9341_BLACK);

    /* Reset count if over max mode number, */
    if (enc_Button_counter == 3) // Number of screens available when button pressed
    {
      enc_Button_counter = 0;
    }
  }

  else

    /* Change Mode */
    switch (enc_Button_counter) {



      case 0: // 1st SCREEN
        DisplayStyle_Portrait_ATSAMD();
        //delay(20);
        DisplayStyle_CircleGauge_ATSAMD();
        break;

      case 1: // 2nd SCREEN

        DisplayStyle_Landscape_ATSAMD();
        break;

      case 2: // 2nd SCREEN
        DisplayStyle_CircleGauge_ATSAMD();
        break;

    }
}
