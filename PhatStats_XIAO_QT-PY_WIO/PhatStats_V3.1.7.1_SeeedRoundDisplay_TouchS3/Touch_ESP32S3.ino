

#if defined(Seeeduino_XIAO_ESP32S3)


void enable_Touch_ESP32S3() {

  if (touch.available()) {

    {
    }

    delay(debounceTouchscreenButton); // Debounce Button / use for touch also
    touch_Button_counter ++;

    next_display();

    /* Clear Screen*/
    backlightOFF();
    tft.fillScreen(GC9A01A_BLACK);

    /* Reset count if over max mode number, */
    if (touch_Button_counter == 4) // Number of screens available when button pressed
    {
      touch_Button_counter = 0;
    }
  }

  else

    /* Change Mode */
    switch (touch_Button_counter) {

      case 0: // 1st SCREEN
        Display_GC9A01_Port_R1(); // USB Socket at the rear
        //tft.setRotation(1);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

        break;

      case 1: // 2nd SCREEN
        Display_GC9A01_Port_R2();
        //tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

        break;

      case 2: // 3rd SCREEN
        Display_GC9A01_Port_R3();
        //tft.setRotation(2);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

        break;

      case 3: // 4th SCREEN
        Display_GC9A01_Port_R0();
        //tft.setRotation(3);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

        break;


        //case 4: // 5th SCREEN
        //Display_GC9A01_Port_R1();
        //tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

        //break;

        //default:
        //Display_GC9A01_Port_R1();
        //break;

    }
}


#endif

//----------------------------------------------------------------------------------------------------------------

#if defined(Seeeduino_XIAO_ESP32S3)

void touch_S3 () {

  if (touch.available()) {

    tft.fillScreen(GC9A01A_BLACK);
    backlightOFF();
    tft.setRotation(ASPECT);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

    tft.setFont(&Org_01);


    tft.drawCircle   (120,   120, 119, GC9A01A_WHITE); // bottom left corner LS


    tft.drawBitmap(44, 20, HSM_BG_BMP,  142, 128, GC9A01A_WHITE);
    tft.drawBitmap(44, 20, HSM_BG2_BMP, 142, 128, GC9A01A_RED);
    tft.drawBitmap(44, 20, HSM_BMP,     142, 128, GC9A01A_GREY);

    tft.setTextSize(3);
    tft.setCursor(86, 140);
    tft.setTextColor(GC9A01A_WHITE);
    tft.println("PHAT ");
    tft.setTextSize(3);
    tft.setCursor(78, 160);
    tft.println("STATS");

    tft.setTextSize(2);
    tft.setCursor(24, 178);
    tft.setTextColor(GC9A01A_SILVER);
    tft.print("PC Hardware Monitor");

    tft.setTextSize(2);
    tft.setCursor(56, 200);
    tft.setTextColor(GC9A01A_RED);
    tft.print("tallmanlabs.com");

    /*  Baud Rate */
    tft.setFont(); // Set Default Adafruit GRFX Font
    tft.setTextColor(GC9A01A_WHITE);
    tft.setTextSize(1);
    tft.setCursor(82, 220);
    tft.print("Baud: ");
    tft.print (baudRate);
    tft.print(" bps ");

    /* Set version */
    tft.setFont(); // Set Default Adafruit GRFX Font
    tft.setTextColor(GC9A01A_WHITE);
    tft.setTextSize(1);
    tft.setCursor(68, 208);
    tft.print("TFT: v");
    tft.print (CODE_VERS);

    backlightON();

    delay(1000);
    tft.fillScreen(GC9A01A_BLACK);
  }
}

#endif
