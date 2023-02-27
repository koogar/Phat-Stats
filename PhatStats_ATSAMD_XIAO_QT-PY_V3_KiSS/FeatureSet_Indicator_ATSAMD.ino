

void FeatureSet_Indicator2 () {

#define X_Offset 0
#define Y_Offset 210

  int featureDelay = 200;
  delay(featureDelay);

  tft.setFont(&Org_01);
  tft.setTextSize(1);


  //------ 1 Adjustable PWM Brightness


  // Fixed PWM PWM Brightness , Show default TFT backlight brightness setting
  tft.drawBitmap(20 + X_Offset, 24 + Y_Offset, PWM_BL_BMP, 36, 36, ILI9341_WHITE);
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(31 + X_Offset, 78 + Y_Offset); tft.print(brightness_count);
  tft.fillCircle(38 + X_Offset, 41 + Y_Offset,  11,         ILI9341_YELLOW);
  tft.setTextColor(ILI9341_WHITE); tft.setCursor(24 + X_Offset, 68 + Y_Offset); tft.print("FIXED");

  delay(featureDelay);

  tft.setFont(); // Set Default Adafruit GRFX Font
}
