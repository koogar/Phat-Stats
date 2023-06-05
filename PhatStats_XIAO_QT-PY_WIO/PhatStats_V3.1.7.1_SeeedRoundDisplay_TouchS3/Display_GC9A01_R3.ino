
/* Version 3.3 Optimised for GC9A01 240 x 240 ,
  Do not turn on the screen till there is activity and the Screen is drawn, #ifdef CPU_OverClocked --->>>> move delay if not enabled */


void Display_GC9A01_Port_R3() {  // Round 240x240 portrait

#define X_Offset  17 // - Portrait
#define Y_Offset  0  // + Portrait


  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


  /* TFT DRAW STATS */
  if (stringComplete) {

    if (bootMode) {

      backlightOFF();

      tft.fillScreen(GC9A01A_BLACK);

      tft.fillCircle  (136 - 17, 120, 112, GC9A01A_BLACK); // landscape circle 119 for radius -1 for line thickness


      bootMode = false;
    }

    lastActiveConn = millis();
    //tft.setTextColor(GC9A01A_BLACK, GC9A01A_WHITE);
    tft.setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);

#ifdef Debug
    tft.setTextColor(GC9A01A_BLACK, GC9A01A_RED); // used to stop flickering when updating digits that do not increase in length. CPU/GPU load still need a clear box on the end digits
#endif

    //--------------------------------------- Display Background ----------------------------------------------------

    tft.setFont(); // set to default Adafruit library font
    tft.setRotation(3);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


    //tft.drawFastVLine(160 - X_Offset, 10 + Y_Offset, 220, GC9A01A_WHITE);
    tft.drawRect     (26 - X_Offset, 118 + Y_Offset, 220, 4, GC9A01A_RED);
    tft.drawFastHLine(26 - X_Offset, 120 + Y_Offset, 220, GC9A01A_WHITE);

    /* DiplayStyle Number */
    tft.fillCircle (4 + X_Offset - 2,  105 + Y_Offset + 14, 10, GC9A01A_BLACK); // landscape circle 119 for radius -1 for line thickness
    tft.drawCircle (4 + X_Offset - 2,  105 + Y_Offset + 14, 10, GC9A01A_RED); // landscape circle 119 for radius -1 for line thickness
    tft.setCursor  (0 + X_Offset - 2,  102 + Y_Offset + 14); // (Left/Right, UP/Down)
    tft.setTextSize(1); tft.println("R3");

    tft.fillCircle (204 + X_Offset - 2,  105 + Y_Offset + 14, 10, GC9A01A_BLACK); // landscape circle 119 for radius -1 for line thickness
    tft.drawCircle (204 + X_Offset - 2,  105 + Y_Offset + 14, 10, GC9A01A_RED); // landscape circle 119 for radius -1 for line thickness
    //tft.setCursor  (200 + X_Offset - 2,  102 + Y_Offset + 14); // (Left/Right, UP/Down)
    //tft.setTextSize(1); tft.println("R3");

    tft.setCursor  (200 + X_Offset - 6,  102 + Y_Offset + 14); // (Left/Right, UP/Down)
    tft.setTextSize(1); tft.println("270");
    //---------------------------------------CPU & GPU Hardware ID---------------------------------------------------------

    /* CPU & GPU Hardware ID */

    if (inputString.indexOf("CPU") > -1)
    {

      String cpuName = "";

      int cpuNameStart = inputString.indexOf("CPU:");
      if (inputString.indexOf("Intel", cpuNameStart) > -1) {
        cpuNameStart = cpuNameStart + cpuNameStartLength;
      }
      else {
        cpuNameStart = cpuNameStart + 8;
      }
      if (inputString.indexOf("GPU") > -1)
      {
        cpuName = inputString.substring(cpuNameStart, inputString.indexOf("GPU:"));
      }
      else
        cpuName = inputString.substring(cpuNameStart);

      tft.setTextSize(1);
      tft.setCursor(98 - X_Offset, 19 + Y_Offset); // (Left/Right, UP/Down)

      /* CPU Manual Name*/
#ifdef Manual_cpuName
      tft.println(set_CPUname);
#else
      /* CPU Auto Detect Name*/
      tft.println(cpuName);
#endif

    }
    if (inputString.indexOf("GPU") > -1)
    {

      int gpuNameStart = inputString.indexOf("GPU:");
      if (inputString.indexOf("NVIDIA", gpuNameStart) > -1) {
        gpuNameStart = gpuNameStart + gpuNameStartLength;
      }
      else {
        gpuNameStart = gpuNameStart + 8;
      }

      int gpuNameEnd = inputString.indexOf("|", gpuNameStart);

      /* GPU Manual Name*/
#ifdef Manual_gpuName
      String gpuName = set_GPUname; // Name spacing test
#else
      /* GPU Auto Detect Name*/
      String gpuName = inputString.substring(gpuNameStart, gpuNameEnd);
#endif

      tft.setTextSize(1);
      tft.setCursor(51 - X_Offset, 130 + Y_Offset); // Position GPU Name
      tft.println(gpuName);
    }

    //------------------------------------------------------RX indicator---------------------------------------------------

#ifdef enable_BT

    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 111, GC9A01A_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 112, GC9A01A_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 113, GC9A01A_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 114, GC9A01A_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 115, GC9A01A_BLUE); // landscape circle 119 for radius -1 for line tickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 116, GC9A01A_BLUE); // landscape circle 119 for radius -1 for line tickness

    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 116, GC9A01A_WHITE); // landscape circle 119 for radius -1 for line tickness
#else

    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 111, GC9A01A_RED); // // flash circle surround
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 112, GC9A01A_RED); // // flash circle surround
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 113, GC9A01A_RED); // // flash circle surround
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 114, GC9A01A_RED); // // flash circle surround
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 115, GC9A01A_RED); // // flash circle surround
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 116, GC9A01A_RED); // // flash circle surround

    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 116, GC9A01A_WHITE); // // flash circle surround
#endif

    //--------------------------------------------DATA CLEARING BOXES------------------------------------------------------

    /* New Update Clearing Boxes see: tft.setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);*/
#ifdef Debug

    tft.setTextColor(GC9A01A_WHITE, GC9A01A_RED);

#define GC9A01A_updateBox GC9A01A_GREY  // Fill boxes grey for text alignment 

#else

#define GC9A01A_updateBox  GC9A01A_BLACK // Default for normal running

#endif

    //------------------------------------------ CPU Load/Temp -------------------------------------------------

    /* CPU Display String */
    int cpuStringStart = inputString.indexOf("C");
    int cpuDegree = inputString.indexOf("c");
    int cpuStringLimit = inputString.indexOf("|");
    String cpuString1 = inputString.substring(cpuStringStart + 1, cpuDegree);
    String cpuString2 = inputString.substring(cpuDegree + 1, cpuStringLimit - 1);

    //Char erase and spacing adjust, MaDerer
    /* CPU TEMP,*/
    if (cpuString1.length() == 1) cpuString1 = " "  + cpuString1;


    /* CPU LOAD,*/
    if (cpuString2.length() == 3) cpuString2 = " "  + cpuString2;
    if (cpuString2.length() == 2) cpuString2 = "  " + cpuString2;

    /* CPU TEMPERATURE */
    tft.setTextSize(3);
    tft.setCursor(64 - X_Offset, 72 + Y_Offset); // (Left/Right, UP/Down)
    tft.print(cpuString1);  // CPU TEMP


    tft.setTextSize(1);
#ifdef noDegree
    tft.print("C");       // Centigrade Symbol
#else
    tft.print((char)247); //Degrees Symbol
    tft.print("C");       // Centigrade Symbol
#endif

    /* CPU LOAD, ALL CORES */
    tft.setTextSize(3);
    tft.setCursor(122 - X_Offset, 72 + Y_Offset); // (Left/Right, UP/Down)
    tft.print(cpuString2);  // CPU Load

#ifdef  smallPercent
    tft.setTextSize(2);
    tft.print("%");
#else
    tft.setTextSize(3);
    tft.print("%");
#endif

    //------------------------------------------ CPU Freq -------------------------------------------------

    /* CPU Freq Display String*/
    int cpuCoreClockStart = inputString.indexOf("CHC") + 3;
    int cpuCoreClockEnd = inputString.indexOf("|", cpuCoreClockStart);
    String cpuClockString = inputString.substring(cpuCoreClockStart, cpuCoreClockEnd);

    //Char erase and spacing adjust, MaDerer
    while (cpuClockString.length() < 4) cpuClockString = " " + cpuClockString;

    /* CPU OVERCLOCK Freq Gain */
    double cpuOverclockGain = atof(cpuClockString.c_str());
    double  cpuOverclockSum = cpuOverclockGain - CPU_BOOST; //values in Mhz

    /* CPU OVERCLOCK Freq Gain in Percent, eg: 3700MHz/100 = 37MHz(1%)  , (OC Gain)895MHz / 37MHz(1%) = 24.19%,*/

    double cpuOverclockGainPercentSum = cpuOverclockSum / (CPU_BOOST / 100); // % of gain over Stock CPU

    /* CPU  Freq Display */
    tft.setTextSize(4);
    tft.setCursor(90 - X_Offset, 35 + Y_Offset ); // (Left/Right, UP/Down)
    tft.print(cpuClockString);
    tft.setTextSize(1);
    tft.print("MHz");


#ifdef  enable_ShowFrequencyGain

    /* CPU OVERCLOCK Display Freq Gain in MHz */
    tft.setCursor(182 - X_Offset, 47 + Y_Offset);// (Left/Right, UP/Down)
    tft.fillRect (184 - X_Offset, 47 + Y_Offset , 37, 10, GC9A01A_BLACK);

#ifdef ShowFrequencyGainMHz
    tft.setTextSize(1);

    if (cpuOverclockSum > 0)
      tft.print (" +");
    else
      tft.print ("  ");

    tft.print(cpuOverclockSum, 0);            // Show Value in MHz
    //tft.setTextSize(1);
    //tft.println ("MHz");
#endif
#ifdef ShowFrequencyGain%
    tft.setTextSize(1);

    if (cpuOverclockGainPercentSum > 0)
      tft.print (" +");
    else
      tft.print ("  ");

    tft.print(cpuOverclockGainPercentSum, 0); // Show Value in %
    tft.println ("%");
#endif
#endif

    //------------------------------------------ GPU Load/Temp -------------------------------------------------

    /* GPU Display String */
    int gpuStringStart = inputString.indexOf("G", cpuStringLimit);
    int gpuDegree = inputString.indexOf("c", gpuStringStart);
    int gpuStringLimit = inputString.indexOf("|", gpuStringStart);
    String gpuString1 = inputString.substring(gpuStringStart + 1, gpuDegree);
    String gpuString2 = inputString.substring(gpuDegree + 1, gpuStringLimit - 1);

    //Char erase and spacing adjust, MaDerer
    /* GPU TEMP,*/
    if (gpuString1.length() == 1) gpuString1 = " "  + cpuString1;
    /* GPU LOAD,*/
    if (gpuString2.length() == 3) gpuString2 = " "  + gpuString2;
    if (gpuString2.length() == 2) gpuString2 = "  " + gpuString2;

    /* GPU TEMPERATURE */
    tft.setTextSize(3);
    tft.setCursor(64 - X_Offset, 144 + Y_Offset); // (Left/Right, UP/Down)
    tft.print(gpuString1);
    tft.setTextSize(1);

#ifdef noDegree
    tft.print("C");       // Centigrade Symbol
#else
    tft.print((char)247); //Degrees Symbol
    tft.print("C");       // Centigrade Symbol
#endif

    /* GPU LOAD */
    tft.setTextSize(3);
    tft.setCursor(112 - X_Offset, 144 + Y_Offset); // (Left/Right, UP/Down)
    tft.print(gpuString2);

#ifdef  smallPercent
    tft.setTextSize(2);
    tft.print("%");
#else
    tft.setTextSize(3);
    tft.print("%");
#endif


    //------------------------------------------ GPU Freq/Temp -------------------------------------------------

    /* GPU temp V's GPU freq to check for throttling and max 'GPU Boost' */

    /* GPU Core Freq, */
    int gpuCoreClockStart = inputString.indexOf("GCC") + 3;
    int gpuCoreClockEnd = inputString.indexOf("|", gpuCoreClockStart);
    String gpuCoreClockString = inputString.substring(gpuCoreClockStart, gpuCoreClockEnd);

    //Char erase and spacing adjust, MaDerer
    while (gpuCoreClockString.length() < 4) gpuCoreClockString = " " + gpuCoreClockString;

    /* GPU OVERCLOCK Freq Gain in MHz, */
    double gpuOverclockGain = atof(gpuCoreClockString.c_str());
    double  gpuOverclockSum = gpuOverclockGain - GPU_BOOST; //values in Mhz

    /* GPU OVERCLOCK Freq Gain in Percent, eg: 1683MHz/100 = 16.83MHz(1%) , (OC Gain)254MHz / 16.83MHz(1%) = 15.09%,*/
    double gpuOverclockGainPercentSum = gpuOverclockSum / (GPU_BOOST / 100); // % of gain over Stock GPU


#ifdef  enable_ShowFrequencyGain
    /* GPU OVERCLOCK Display Freq Gain, */
    //tft.setCursor(225, 56);// (Left/Right, UP/Down)
    tft.setCursor(182 - X_Offset, 180 + Y_Offset);
    tft.fillRect (182 - X_Offset, 179 + Y_Offset , 40, 10, GC9A01A_BLACK);

#ifdef ShowFrequencyGainMHz
    tft.setTextSize(1);

    if (gpuOverclockSum > 0)
      tft.print (" +");
    else
      tft.print ("  ");

    tft.print(gpuOverclockSum, 0);            // Show Value in MHz
    //tft.setTextSize(1);
    //tft.println ("MHz");
#endif
#ifdef ShowFrequencyGain%
    tft.setTextSize(1);


    if (gpuOverclockGainPercentSum > 0)
      tft.print (" +");
    else
      tft.print ("  ");

    tft.print(gpuOverclockGainPercentSum, 0); // Show Value in %
    tft.println ("%");
#endif

#endif

    // GPU Frequency
    tft.setTextSize(4);
    tft.setCursor(90 - X_Offset, 170 + Y_Offset); // (Left/Right, UP/Down)
    tft.print(gpuCoreClockString);
    tft.setTextSize(1);
    tft.print("MHz");

    //----------------------------------------------GPU Memory Total----------------------------------------------------------

    int gpuMemoryStart = inputString.indexOf("GMT") + 3;
    int gpuMemoryEnd = inputString.indexOf("|", gpuMemoryStart);
    String gpuMemoryString = inputString.substring(gpuMemoryStart, gpuMemoryEnd);

    //Char erase and spacing adjust, MaDerer
    while (gpuMemoryString.length() < 4) gpuMemoryString = " " + gpuMemoryString;

    double totalGPUmem = atof(gpuMemoryString.c_str());
    double totalGPUmemSum = totalGPUmem / 1024;    // divide by 1024 to get the correct value
    float  totalGPUmemSumDP = totalGPUmemSum ;     // float to handle the decimal point when printed (totalGPUmemSumDP, 0)

    tft.setTextSize(1);
    tft.setCursor(201 - X_Offset, 130 + Y_Offset); // Position GPU Total Memory

#ifdef Manual_gpuRam
    tft.print(set_GPUram);
#else
    tft.print(totalGPUmemSumDP, 0); // Show Value in GB
#endif

    tft.setTextSize(1);
    tft.print("GB");
    //----------------------------------------------GPU Memory Used----------------------------------------------------------

    /*GPU Memory Used */
    int gpuMemoryUsedStart = inputString.indexOf("GMU") + 3;
    int gpuMemoryUsedEnd = inputString.indexOf("|", gpuMemoryUsedStart);
    String gpuMemoryUsedString = inputString.substring(gpuMemoryUsedStart, gpuMemoryUsedEnd);
    //Char erase and spacing adjust, MaDerer
    while (gpuMemoryUsedString.length() < 4) gpuMemoryUsedString = " " + gpuMemoryUsedString;

    tft.setCursor(103 - X_Offset, 204 + Y_Offset); // (Left/Right, UP/Down)
    tft.setTextSize(3);
    tft.print(gpuMemoryUsedString); //  show values in MB

    tft.setTextSize(1);
    tft.print("MB");



    //------------------------------------------------GPU Power Consumption--------------------------------------------------------
#ifdef enable_gpuPowerStats

    /* GPU Power */  // Nvidia Driver 457.51 works. Broken in Driver Version: 460.79 460.89
    int gpuPowerStart = inputString.indexOf("GPWR") + 4;
    int gpuPowerEnd = inputString.indexOf("|", gpuPowerStart);
    String gpuPowerString = inputString.substring(gpuPowerStart, gpuPowerEnd);
    //Char erase and spacing adjust, MaDerer
    while (gpuPowerString.length() < 6) gpuPowerString = " " + gpuPowerString;

    tft.setTextSize(1);
    tft.setCursor(46 - X_Offset, 180 + Y_Offset);   // (Left/Right, UP/Down)
    tft.print(gpuPowerString); //GPU Power Watts
    tft.setTextSize(1);
    tft.print("w");
#endif

    //----------------------------------------SYSTEM RAM USAGE---------------------------------------------------

    /* SYSTEM RAM String */
    int ramStringStart = inputString.indexOf("R", gpuStringLimit);
    int ramStringLimit = inputString.indexOf("|", ramStringStart);
    String ramString   = inputString.substring(ramStringStart + 1 , ramStringLimit - 2);
    //Char erase and spacing adjust, MaDerer
    while (ramString.length() < 4) ramString = " " + ramString;

    /* SYSTEM RAM AVALABLE String */
    int AramStringStart = inputString.indexOf("RA", ramStringLimit);
    int AramStringLimit = inputString.indexOf("|", AramStringStart);
    String AramString = inputString.substring(AramStringStart + 2 , AramStringLimit);
    //Char erase and spacing adjust, MaDerer
    while (AramString.length() < 5) AramString = " " + AramString;

    /* SYSTEM RAM TOTAL String */
    double intRam = atof(ramString.c_str());
    double intAram = atof(AramString.c_str());
    //double  intRamSum = intRam + intAram;
    float  intRamSum = intRam + intAram; //float to handle the decimal point when printed (intRamSum,0)

    /* RAM & TOTAL */

    tft.setCursor(86 - X_Offset, 100 + Y_Offset); // (Left/Right, UP/Down)
    tft.setTextSize(2);
    tft.print(intRamSum, 0) ; tft.setTextSize(0); tft.print("GB"); tft.print(" / ");
    tft.setTextSize(2);
    tft.print(ramString)    ; tft.setTextSize(0); tft.println("GB");

    //------------------------------------------ RX indicator Clear------------------------------------------------

    delay(TX_LED_Delay);

    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 111, GC9A01A_BLACK); // landscape circle 119 for radius -1 for line thickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 112, GC9A01A_BLACK); // landscape circle 119 for radius -1 for line thickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 113, GC9A01A_BLACK); // landscape circle 119 for radius -1 for line thickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 114, GC9A01A_BLACK); // landscape circle 119 for radius -1 for line thickness
    tft.drawCircle(136 - X_Offset, 120 + Y_Offset, 115, GC9A01A_BLACK); // landscape circle 119 for radius -1 for line thickness


    //-------------------------------------- ETHERNET USAGE Libre ----------------------------------------------

    /* Reserved,*/

#ifdef enable_LibreNet
    /* Network Outline, */
    //                 ( X  , Y ,  W , H , Radius ,    Color
    //tft.drawRoundRect  (196, 209, 120, 22, 2, GC9A01A_RED); //

    /* ETHERNET UP String,*/
    int EthUpStringStart = inputString.indexOf("ETU") + 3;
    int EthUpStringLimit = inputString.indexOf("|", EthUpStringStart);
    String EthUpString   = inputString.substring(EthUpStringStart, EthUpStringLimit);
    while (EthUpString.length() < 9) EthUpString = " " + EthUpString;

    /* UP USAGE DISPLAY,*/
    tft.setTextSize(1);
    //tft.setCursor(198, 212);
    tft.print("Net UP  : ");
    tft.println(EthUpString);

    /* ETHERNET Down String,*/
    int EthDownStringStart = inputString.indexOf("ETD") + 3;
    int EthDownStringLimit = inputString.indexOf("|", EthDownStringStart);
    String EthDownString   = inputString.substring(EthDownStringStart, EthDownStringLimit);
    while (EthDownString.length() < 9) EthDownString = " " + EthDownString;

    /* DOWN USAGE DISPLAY,*/
    tft.setTextSize(1);
    //tft.setCursor(198, 221);
    tft.print("Net DOWN: ");
    tft.println(EthDownString);
#endif

    displayDraw = 1;



    //--------------------------Trigger an event when CPU or GPU threshold is met ---------------------------------

#ifdef enable_BoostIndicator
    CustomTriggerCPU_BOOST_Rot3( cpuClockString.toInt     ()); // CPU Frequency
    CustomTriggerGPU_BOOST_Rot3( gpuCoreClockString.toInt ()); // GPU Frequency
#endif

#ifdef enable_ThrottleIndicator
    CustomTriggerCPU_ThrottleIndicator_Rot3( cpuString1.toInt() ); //  CPU TJMax/Throttle Incicator BMP
    CustomTriggerGPU_ThrottleIndicator_Rot3( gpuString1.toInt() ); //  GPU TJMax/Throttle Incicator BMP
#endif


    //--------------------------Trigger an event when CPU or GPU threshold is met ---------------------------------


#ifdef enable_Thresholdtriggers_PCB

    //PCB_TriggerCPU_temp_LS( cpuString1.toInt() ); // Neopixel CPU  Temperature
    PCB_TriggerCPU_load_LS( cpuString2.toInt() ); // Neopixel CPU  Load

    //PCB_TriggerGPU_temp_LS( gpuString1.toInt() ); // Neopixel GPU  Temperature
    PCB_TriggerGPU_load_LS( gpuString2.toInt() ); // Neopixel GPU  Load

#endif

#ifdef enable_CustomThresholdtriggers

    //CustomTriggerCPU_temp( cpuString1.toInt() ); // Neopixel CPU  Temperature
    CustomTriggerCPU_load( cpuString2.toInt() ); // Neopixel CPU  Load

    //CustomTriggerGPU_temp( gpuString1.toInt() ); // Neopixel GPU  Temperature
    CustomTriggerGPU_load( gpuString2.toInt() ); // Neopixel GPU  Load

#endif

#ifdef enable_NeopixelGauges // Uncomment only 2, in any combination

    CPU_loadGauge( cpuString2.toInt() ); // Neopixel Ring Gauge  CPU  Load
    //CPU_tempGauge( cpuString1.toInt() ); // Neopixel Ring Gauge  CPU  Temperature

    GPU_loadGauge( gpuString2.toInt() ); // Neopixel Ring Gauge  GPU  Load
    // GPU_tempGauge( gpuString1.toInt() ); // Neopixel Ring Gauge  GPU  Temperature

#endif

#ifdef enableSideLevelGauges // Phat-Tacho CircleGauge only

    CPU_loadLevelGauge( cpuString2.toInt() ); // Side Level Gauge  CPU  Load
    CPU_tempLevelGauge( cpuString1.toInt() ); // Side Level Gauge  CPU  Temperature

    GPU_loadLevelGauge( gpuString2.toInt() ); // Side Level Gauge  GPU  Load
    GPU_tempLevelGauge( gpuString1.toInt() ); // Side Level Gauge  GPU  Temperature

#endif

    //---------------------------------

    inputString = "";
    stringComplete = false;
    backlightON (); //Turn ON display when there is  activity and the Screen is drawn

  }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// -------------------  CPU Turbo Boost Indicator Event Portrait --------------------

void CustomTriggerCPU_BOOST_Rot3(int cpuClockString ) {
  float CPUboostfactor = cpuClockString;


  if (CPUboostfactor >  CPU_BOOST) {  // i5-9600k boost is 3700Mhz to 4700Mhz
    //Do Something!!!

#ifdef CPU_OverClocked //Do Nothing!!

    //Do Nothing!!!

#else

    delay(350); // Small delay so Turbo frequency gains stay on screen longer
    //tft.drawRoundRect  (106, 90, 88, 22, 4, GC9A01A_WHITE); //

    /* CPU Turbo Clock, */
    //                 (   X,    Y,   Length, Height, Radius,   Colour    )
    tft.fillRoundRect  (  90 - X_Offset,    35 + Y_Offset,    93,      28,     3,   GC9A01A_WHITE); //
    tft.fillRoundRect  (  92 - X_Offset,    37 + Y_Offset,    89,      24,     2,   GC9A01A_GREEN); //
    tft.setTextSize(2);
    tft.setCursor(110 - X_Offset, 42 + Y_Offset);
    tft.setTextColor(GC9A01A_BLACK);
    tft.println("TURBO");

#endif

  }
}

// -------------------  GPU Boost Clock Indicator Event Portrait --------------------

void CustomTriggerGPU_BOOST_Rot3(int gpuCoreClockString ) {
  float GPUboostfactor = gpuCoreClockString ;

  //Do Something!!!

  if (GPUboostfactor >  GPU_BOOST) {  //GTX 1080 boost = 1607Mhz to 1733mhz

    /* GPU Boost Clock, */
    //                 (   X,    Y,   Length, Height, Radius,   Colour    )
    tft.fillRoundRect  (  91 - X_Offset,    170 + Y_Offset,    93,      28,     3,   GC9A01A_WHITE); //
    tft.fillRoundRect  (  93 - X_Offset,    172 + Y_Offset,    89,      24,     2,   GC9A01A_GREEN); //
    tft.setTextSize(2);
    tft.setCursor(111 - X_Offset, 177 + Y_Offset);
    tft.setTextColor(GC9A01A_BLACK);
    tft.println("BOOST"); //

  }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// -------------------  CPU Throttle Indicator Event Portrait --------------------

void CustomTriggerCPU_ThrottleIndicator_Rot3(int cpuDegree ) {  // i5-9600k TJMax is 100c
  float CPUtempfactor = cpuDegree ;


  if (CPUtempfactor >= CPU_TJMAX ) {  // TJ Max for the Intel 9900K 100c

    /* CPU Junction Max Throttle Temp, */
    //                 (   X,    Y,   Length, Height, Radius,   Colour    )
    tft.fillRoundRect  (  90 - X_Offset,    35 + Y_Offset,    93,      28,     3,   GC9A01A_WHITE); //
    tft.fillRoundRect  (  92 - X_Offset,    37 + Y_Offset,    89,      24,     2,   GC9A01A_RED); //
    tft.setTextSize(2);
    tft.setCursor(110 - X_Offset, 42 + Y_Offset);
    tft.setTextColor(GC9A01A_WHITE);

    tft.println("TJMax");
  }
}


// -------------------  GPU Throttle Indicator Event Portrait --------------------

void CustomTriggerGPU_ThrottleIndicator_Rot3(int gpuDegree ) {
  float GPUtempfactor = gpuDegree ;


  if (GPUtempfactor >= GPU_TJMAX ) {  //GTX 1080 TJMax = 83c

    /* GPU Junction Max Throttle Temp, */

    //                 (   X,    Y,   Length, Height, Radius,   Colour    )
    tft.fillRoundRect  (  91 - X_Offset,    170 + Y_Offset,    93,      28,     3,   GC9A01A_WHITE); //
    tft.fillRoundRect  (  93 - X_Offset,    172 + Y_Offset,    89,      24,     2,   GC9A01A_RED); //
    tft.setTextSize(2);
    tft.setCursor(111 - X_Offset, 177 + Y_Offset);
    tft.setTextColor(GC9A01A_WHITE);

    tft.println("TJMax");
  }
}


//---------------------- CPU--------------------

//>>>>>>>>>>>> CPU TEMP

void CPU_tempLevel_Rot3(int cpuDegree ) {

  /*Top CPU Temp Level Clear Box,*/
  tft.fillRoundRect(293 - X_Offset, 0 + Y_Offset,   8, 102 , 1, GC9A01A_BLACK);

  float CPUtempfactor = cpuDegree;

  /*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*/
  int CPUtempScalefactor = (CPUtempfactor + 1); // +1 so it always shows something

  if (CPUtempfactor >= 0 ) {
    /*Top CPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset, 1 + Y_Offset,   8, CPUtempScalefactor  , 1, GC9A01A_GREEN); // Top CPU Temp Scale
  }

  if (CPUtempfactor >= 45 ) {
    /*Top CPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset, 1 + Y_Offset,   8, CPUtempScalefactor   , 1, GC9A01A_GREEN); // Top CPU Temp Scale
  }

  if (CPUtempfactor >= 65 ) {
    /*Top CPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset, 1 + Y_Offset,   8, CPUtempScalefactor   , 1, GC9A01A_ORANGE); // Top CPU Temp Scale
  }

  if (CPUtempfactor >= 85 ) {
    /*Top CPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset, 1 + Y_Offset,   8, CPUtempScalefactor  , 1, GC9A01A_RED); // Top CPU Temp Scale
  }

  tft.drawRoundRect(293 - X_Offset, 0 + Y_Offset,   8, 94  , 1, GC9A01A_WHITE); // Draw rectangle round CPU temp bar

  /*Stop Scale running into MAX box,*/
  tft.fillRect (288 - X_Offset , 94 + Y_Offset,  27, 19 , GC9A01A_BLACK); // Stop Scale running into MAX box

  // Max Text box CPU
  tft.setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
  tft.setCursor(295 - X_Offset , 100 + Y_Offset);
  tft.setTextSize(1);
  tft.setTextColor(GC9A01A_WHITE);
  tft.print("MAX");
  tft.drawRoundRect(292 - X_Offset , 97 + Y_Offset,  23, 13 , 1, GC9A01A_WHITE);

}


//>>>>>>>>>>>> CPU LOAD

void CPU_loadLevel_Rot3(int cpuUsage ) {

  /*Top CPU Load Level Clear Box,*/
  tft.fillRoundRect(306 - X_Offset, 0 + Y_Offset,   8, 102 , 1, GC9A01A_BLACK);

  float CPUloadfactor = cpuUsage;

  /*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*/
  int CPUloadScalefactor =   ( CPUloadfactor + 1); // +1 so it always shows something


  if (CPUloadfactor >= 0 ) {
    /*Top CPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset, 1 + Y_Offset,   8,  CPUloadScalefactor   , 1, GC9A01A_GREEN); // Top CPU Load Scale
  }

  if (CPUloadfactor >= 50 ) {
    /*Top CPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset, 1 + Y_Offset,   8,  CPUloadScalefactor   , 1, GC9A01A_GREEN); // Top CPU Load Scale
  }

  if (CPUloadfactor >= 75) {
    /*Top CPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset, 1 + Y_Offset,   8,  CPUloadScalefactor   , 1, GC9A01A_ORANGE); // Top CPU Load Scale
  }

  if (CPUloadfactor >= 83 ) {
    /*Top CPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset, 1 + Y_Offset,   8,  CPUloadScalefactor  , 1, GC9A01A_RED); // Top CPU Load Scale
  }

  tft.drawRoundRect(306 - X_Offset, 0 + Y_Offset,   8,  94 , 1, GC9A01A_WHITE); // Draw rectangle round CPU load bar
}


//---------------------- GPU--------------------


//>>>>>>>>>>>> GPU TEMP

void GPU_tempLevel_Rot3(int gpuDegree ) {

  /*Bottom GPU Temp Level Clear Box,*/
  tft.fillRoundRect(293 - X_Offset , 129 + Y_Offset,   8, 102 , 1, GC9A01A_BLACK);

  float GPUtempfactor = gpuDegree;

  /*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*/
  int GPUtempScalefactor = (GPUtempfactor + 1); // +1 so it always shows something

  if (GPUtempfactor >= 0 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset , 130 + Y_Offset,  8, GPUtempScalefactor , 1, GC9A01A_GREEN); // Bottom GPU Temp Scale
  }

  if (GPUtempfactor >= 25 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset , 130 + Y_Offset,  8, GPUtempScalefactor , 1, GC9A01A_GREEN); // Bottom GPU Temp Scale
  }

  if (GPUtempfactor >= 50 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset , 130 + Y_Offset,  8, GPUtempScalefactor , 1, GC9A01A_GREEN); // Bottom GPU Temp Scale
  }

  if (GPUtempfactor >= 75 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset , 130 + Y_Offset,  8, GPUtempScalefactor , 1, GC9A01A_ORANGE); // Bottom GPU Temp Scale
  }

  if (GPUtempfactor >= 83 ) {
    /*Bottom GPU Temp Bar Scale,*/
    tft.fillRoundRect(293 - X_Offset , 130 + Y_Offset,  8, GPUtempScalefactor , 1, GC9A01A_RED); // Bottom GPU Temp Scale
  }

  tft.drawRoundRect(293 - X_Offset , 129 + Y_Offset,   8, 94 , 1, GC9A01A_WHITE); // Draw rectangle round GPU temp bar

  /*Stop Scale running into MAX box,*/
  tft.fillRect (289 - X_Offset , 223 + Y_Offset,  27, 17 , GC9A01A_BLACK);

  // Max Text box GPU
  tft.setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
  tft.setCursor(295 - X_Offset , 229 + Y_Offset);
  tft.setTextSize(1);
  tft.setTextColor(GC9A01A_WHITE);
  tft.print("MAX");
  tft.drawRoundRect(292 - X_Offset , 226 + Y_Offset,  23, 13 , 1, GC9A01A_WHITE);
}

//>>>>>>>>>>>> GPU LOAD

void GPU_loadLevel_Rot3(int gpuUsage ) {

  /*Bottom GPU Load Level Clear Box,*/
  tft.fillRoundRect(306 - X_Offset , 129 + Y_Offset,   8, 102 , 1, GC9A01A_BLACK);

  float GPUloadfactor = gpuUsage;

  /*Attempt to reverse direction of Bar Scale, and get rid of decimal point for coordinates,*/
  int GPUloadScalefactor = (GPUloadfactor + 1); // +1 so it always shows something

  if (GPUloadfactor >= 0 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset , 130 + Y_Offset, 8, GPUloadScalefactor , 1, GC9A01A_GREEN);
  }
  if (GPUloadfactor >= 25 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset , 130 + Y_Offset, 8, GPUloadScalefactor , 1, GC9A01A_GREEN);
  }
  if (GPUloadfactor >= 50 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset , 130 + Y_Offset, 8, GPUloadScalefactor  , 1, GC9A01A_GREEN);
  }
  if (GPUloadfactor >= 75 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset , 130 + Y_Offset, 8, GPUloadScalefactor , 1, GC9A01A_ORANGE);
  }
  if (GPUloadfactor >= 90 ) {
    /*Bottom GPU Load Bar Scale,*/
    tft.fillRoundRect(306 - X_Offset , 130 + Y_Offset, 8, GPUloadScalefactor , 1, GC9A01A_RED);
  }

  tft.drawRoundRect(306 - X_Offset , 129 + Y_Offset,   8, 94 , 1, GC9A01A_WHITE); // Draw rectangle round GPU load bar
}
