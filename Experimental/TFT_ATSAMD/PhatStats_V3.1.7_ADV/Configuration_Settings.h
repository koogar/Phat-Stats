/*
      ____  __  _____  ______   ______________  ___________    __________________
     / __ \/ / / /   |/_  __/  / ___/_  __/   |/_  __/ ___/   /_  __/ ____/_  __/
    / /_/ / /_/ / /| | / /_____\__ \ / / / /| | / /  \__ \     / / / /_    / /
   / ____/ __  / ___ |/ /_____/__/ // / / ___ |/ /  ___/ /    / / / __/   / /
  /_/   /_/ /_/_/  |_/_/     /____//_/ /_/  |_/_/  /____/    /_/ /_/     /_//*

    ___ ___  _  _ ___ ___ ___ _   _ ___    _ _____ ___ ___  _  _
   / __/ _ \| \| | __|_ _/ __| | | | _ \  /_\_   _|_ _/ _ \| \| |
  | (_| (_) | .` | _| | | (_ | |_| |   / / _ \| |  | | (_) | .` |
   \___\___/|_|\_|_| |___\___|\___/|_|_\/_/ \_\_| |___\___/|_|\_|

  uVolume, GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client
  Rupert Hirst © 2016 - 2023 http://tallmanlabs.com http://runawaybrainz.blogspot.com/
  https://github.com/koogar/Phat-Stats  https://hackaday.io/project/19018-phat-stats-pc-performance-tft-display

  Gnat-Stats & Phat-Stats are optimised for desktop CPU's with dedicated graphics cards,
  You may get weird results on integrated GPU's (iGPU's) on laptops.*/

//--------------------------- Uncomment your Micro Processor---------------------------------

//#define Adafruit_QTPY_ATSAMD
//#define Seeeduino_XIAO_ATSAMD
//#define Seeeduino_XIAO_RP2040   // Adafruit QT PY RP2040  (untested)
//#define Seeeduino_XIAO_NRF52840 // Adafruit QT PY NRF52840(untested)

//#define Seeeduino_WIO_ATSAMD51  // Seed Studio WIO Terminal


//--------------------------- Seeeduino_XIAO_ESP32C3 Experimental!!! --------------------------------
/* NOTE: The XIAO ESP32C3 is very problematic when uploading "in circuit" and has to be removed for programming.
  Most of the time it has to be forced into bootloader mode (Hold BOOT button down and power cycle while uploading) */

/* Uncomment ALT_TFT_RST for XIAO ESP32C3 &  OLD PCB v0.93, TFT_RST is on D9 (Miso) as D0 was used for IR */

#define Seeeduino_XIAO_ESP32C3   // Adafruit QT PY ESP32S2, QT PY ESP32S3,  QT Py ESP32 Pico (untested)
#define ALT_TFT_RST              // Use for XIAO_ESP32C3 or old PCB Version- TFT Reset on PIN D9

//--------------------------- Uncomment your CPU/GPU Display  -----------------------------------
/* Uncomment your CPU,*/

#define INTEL_CPU
//#define AMD_CPU


/* Uncomment your GPU,*/

#define NVIDIA_GRAPHICS
//#define NVIDIA_GTX_Ti_GRAPHICS
//#define NVIDIA_RTX_GRAPHICS
//#define NVIDIA_RTX_SUPER_GRAPHICS

//#define AMD_GRAPHICS
//#define INTEL_GRAPHICS

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* Characters to delete from the start of the CPU/GPU name eg: Remove "Intel" or "Nvidia" to save space*/
#define cpuNameStartLength 10 //i5-9600k = 10 / i9-13900k = 19
#define gpuNameStartLength 18

//>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Manually name the CPU,*/
//#define Manual_cpuName
String set_CPUname = "xxxxxx";

/* Manually name the GPU,*/
//#define Manual_gpuName
String set_GPUname = "xxxxxx";

/* Manually set GPU ram total,*/
//#define Manual_gpuRam
String set_GPUram = "xxxxxx"; //in GB

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define noDegree      // lose the "o"
#define smallPercent  // Use small percent symbol

//---------------------------------------------------------------------------------------

/* CPU is overclocked with Turbo boost disabled, to stop "TURBO" indicator,*/
//#define CPU_OverClocked

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* CPU & GPU Thermal Junction Max Temperature in "c" before throttling,*/
#define CPU_TJMAX 100  //  TJ Max for the Intel 9900K    = 100c
#define GPU_TJMAX 83   //  TJ Max for the Nvidia GTX1080 = 83c

/* CPU & GPU Turbo/Boost Frequency Values in Mhz */
#define CPU_BOOST 3700  //  Enter Stock CPU Frequency eg. Intel Core i9600k = 3700MHz
#define GPU_BOOST 1683  //  Enter Stock GPU Frequency eg. MSi GamingX 1080  = 1683MHz

//-------------------------------- Show GPU Stats ------------------------------------

/* Remove Specific GPU stats in landscape mode(enable_gpuVram, enable_gpuShader),
  this helps to make room if your GPU memory is over 9999MB */

//#define enable_gpuVram
//#define enable_gpuShader
#define enable_BigGPUw      // undefine  enable_gpuShader & enable_gpuShader first

//-----------------------------
#define enable_gpuCore
#define enable_gpuPowerStats    // Nvidia Specific???
#define enable_gpuFanStatsRPM
#define enable_gpuFanStatsPerc  // this is only displayed in Portrait!!!

//----------------------------- Frequency Gains Indicator --------------------------------

/* Uncomment to enable the display of frequency gains */
#define enable_ShowFrequencyGain

/* Uncomment only one of the units to display below, MHz or Percent */
//#define ShowFrequencyGainMHz        // Show Overlock/Turbo & Boost Clock Frequency Gains in MHZ  eg: "+24MHz"
#define ShowFrequencyGainPerc       // Show Overlock/Turbo & Boost Clock Frequency Gains in Percent  eg: "+24%"

//----------------------------- Throttle/Boost Indicator --------------------------------

#define enable_ThrottleIndicator // Show TJMax Indicator 
#define enable_BoostIndicator    // Show CPU & GPU Turbo/Boost Indicator


//----------------------------- TFT Fixed or PWM Brightness -------------------------------------

/* Comment out fixedBacklight for WIO Terminal, or the screen will not turn off */
/* Uncomment   fixedBacklight for ESP32, PWM is not yet supported */

#define fixedBacklight // enable a fixed backlight (no PWM) powered from VCC

/*Start Up PWM Brightness if using MCU Pin*/
/* Wio Terminal LCD backlight brightness Range = 1 to 50, XIAO Range = 1 to 254 */

volatile int brightness_count = 100; // Start Up PWM Brightness

//------------------------------- Display Activity Shutdown -----------------------------------

/* Uncomment below to turn off the screen on serial timeout, else keep last display info eg: incase of PC Crash*/
#define enableActivityChecker

/* How long the display takes to timeout due to inactive serial data from the windows application */
#define lastActiveDelay 8000

//-------------------------------- NeoPixel Modes -------------------------------------
#define NUM_PIXELS  4 // define the number of NeoPixels used

/* If  NeoBrightness = 0 Phat-Stats will start with no NeoPixels lit. Turn the Rotary Encoder to turn on the NeoPixels, */
int NeoBrightness   = 50;           // Global start up brightness

/* Uncomment only one of the below*/
//#define enable_NeopixelGauges     // NeoPixel Phat-Stats PCB
#define enable_Thresholdtriggers_PCB // New PCB 4x NeoPixel Rotate States,0,1,2,3  Trigger functions when CPU or GPU thresholds are met 

//-------------------------------- Misco Setting -----------------------------------------

//#define  RETRO_MONO    //CRT Monochrome screen
//#define  RETRO_AMBER   //CRT Amber screen
//#define  RETRO_GREEN   //CRT Green screen

#define  splashScreenLS // quick splash screen landscape hack job, also in FeatureSet

/* Debounce  Button, button mode is a bit flaky at present as it needs interrupts, Sometimes it gets caught during a screen refresh
  and does not change. WIO Terminal & ESP32 seem to like 1000ms and works just!!! ok */

int debounceButton = 150; //  Use a 0.1uf/100nf/(104) ceramic capacitor from button Pin to GND

/* Enable the built in LED blinking when transmitting data, can lag the button mode*/
#define enableTX_LED

int TX_LED_Delay = 0; // TX blink delay, lags button

int baudRate     = 9600; // set serial baud rate to match that of HardwareSerialMonitor 115200 will use more resources

/* Delay screen event, to stop screen data corruption ESP8622 use 25, most others 5 will do*/
int Serial_eventDelay = 5; //


//--------------------------------------- Versions -----------------------------------------------------
/*
  V3.1.1.KiSS     [K]eep [i]t [S]toopid [S]imple

        Bare bones version
        Button to change aspect

        Add enable_gpuVram, enable_gpuShader, enable_gpuCore
        Remove specific GPU stats in landscape mode, this helps to make room if your GPU memory is over 9999MB
        Fix set_GPUram

     V3.1.1.ADV    Advanced

        Button to change aspect
        NeoPixels

        Add enable_gpuVram, enable_gpuShader, enable_gpuCore
        Remove specific GPU stats in landscape mode, this helps to make room if your GPU memory is over 9999MB
        Fix set_GPUram
        NeoPixels

    V3.1.2  Kiss & ADV

        Add support for:
                          Seeed Studio XIAO (ATSAMD21) / Adafruit QT PY (ATSAMD21)
                          Seeed Studio XIAO (NRF52840) / Adafruit QT PY (NRF52840)(untested)
                          Seeed Studio XIAO (RP2040)   / Adafruit QT PY (RP2040)  (untested)
                          Seeed Studio XIAO (ESP32C3)    Experimental

    V3.1.3.KiSS

        Add support for:
                          Seeed Studio WIO Terminal (ATSAMD51)


    V3.1.3.ADV

        Add support for:
                          Seeed Studio WIO Terminal (ATSAMD51)
                          Retro CRT look option
                          + Some Fixes

   V3.1.6.ADV/KiSS

       Clean up code
       Turn off the backlight untill the stats have updated when using button mode.
       Add PCB_ThresholdTriggerEvents for custom PCB, so neopixels rotate with button mode.

      (ADV) Add option to display the splash screen in landscape.

*/




//----------------------------- Debug Screen Erasers ---------------------------------------

/* Debug Screen, Update Erasers, */
//#define Debug

//-------------- Show Networks Stats when using Phatstats edition of WeeStatServer ---------------
//#define enable_LibreNet // Reserved // undefine  enable_gpuCore, enable_gpuShader, enable_gpuShader first, enable_gpuPowerStats
//--------------------------- Throttle/Boost Gains MHZ or % ------------------------------
