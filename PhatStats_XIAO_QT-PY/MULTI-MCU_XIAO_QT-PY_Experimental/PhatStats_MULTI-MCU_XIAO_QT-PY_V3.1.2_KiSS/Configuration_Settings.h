/*
      ____  __  _____  ______   ______________  ___________    __________________
     / __ \/ / / /   |/_  __/  / ___/_  __/   |/_  __/ ___/   /_  __/ ____/_  __/
    / /_/ / /_/ / /| | / /_____\__ \ / / / /| | / /  \__ \     / / / /_    / /
   / ____/ __  / ___ |/ /_____/__/ // / / ___ |/ /  ___/ /    / / / __/   / /
  /_/   /_/ /_/_/  |_/_/     /____//_/ /_/  |_/_/  /____/    /_/ /_/     /_/

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
                          XIAO NRF52840 / QT PY NRF52840(untested)
                          XIAO RP2040   / QT PY RP2040  (untested)
                          XIAO ESP32C3  / QT PY ESP32C3 (untested)
                          

  Note: Gnat-Stats/Phat-Stats is optimised for desktop CPU's with dedicated graphics cards, such as Nvidia/Radeon.
      You may get wierd results on mobile CPUs and integrated GPU's (iGPU's) on laptops.

  --------------------------------------------------------------------------------------
    ___ ___  _  _ ___ ___ ___ _   _ ___    _ _____ ___ ___  _  _
   / __/ _ \| \| | __|_ _/ __| | | | _ \  /_\_   _|_ _/ _ \| \| |
  | (_| (_) | .` | _| | | (_ | |_| |   / / _ \| |  | | (_) | .` |
   \___\___/|_|\_|_| |___\___|\___/|_|_\/_/ \_\_| |___\___/|_|\_|
     ___  ___ _____ ___ ___  _  _ ___
    / _ \| _ \_   _|_ _/ _ \| \| / __|
   | (_) |  _/ | |  | | (_) | .` \__ \
    \___/|_|   |_| |___\___/|_|\_|___/

  --------------------------------------------------------------------------------------
*/



//--------------------------- Micro Controller Selection---------------------------------

/* Uncomment your Micro Processor,*/

//#define Adafruit_QTPY_ATSAMD
#define Seeeduino_XIAO_ATSAMD
//#define Seeeduino_XIAO_RP2040   // Adafruit QT PY RP2040  (untested)
//#define Seeeduino_XIAO_NRF52840 // Adafruit QT PY NRF52840(untested)
//#define Seeeduino_XIAO_ESP32C3  // Adafruit QT PY ESP32S2, QT PY ESP32S3,  QT Py ESP32 Pico (untested)


//----------------------------------------------------------------------------------------

//#define OLDPCB_V0_93 //  TFT_RST is on D9 (Miso) as D0 was used for IR

//--------------------------- CPU/GPU Display Settings -----------------------------------

/* Uncomment your CPU,*/
//#define AMD_CPU
#define INTEL_CPU

/* Uncomment your GPU,*/
//#define NVIDIA_GRAPHICS
//#define NVIDIA_GTX_Ti_GRAPHICS
//#define NVIDIA_RTX_GRAPHICS
#define NVIDIA_RTX_SUPER_GRAPHICS

//#define AMD_GRAPHICS

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* Characters to delete from the start of the CPU/GPU name eg: Remove "Intel" or "Nvidia" to save space*/
#define cpuNameStartLength 10 //i5-9600k = 10 / i9-13900k = 19
#define gpuNameStartLength 18

//>>>>>>>>>>>>>>>>>>>>>>>>>>>
/* Manually name the  CPU,*/
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
#define CPU_OverClocked

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* CPU & GPU Thermal Junction Max Temperature in "c" before throttling,*/
#define CPU_TJMAX 100  //  TJ Max for the Intel 9900K    = 100c
#define GPU_TJMAX 83   //  TJ Max for the Nvidia GTX1080 = 83c

/* CPU & GPU Turbo/Boost Frequency Values in Mhz */
#define CPU_BOOST 3700  //  Enter Stock CPU Frequency eg. Intel Core i9600k = 3700MHz
#define GPU_BOOST 1683  //  Enter Stock GPU Frequency eg. MSi GamingX 1080  = 1683MHz

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* Remove Specific GPU stats in landscape mode, this helps to make room if your GPU memory is over 9999MB */

//#define enable_gpuVram
//#define enable_gpuShader
#define enable_gpuCore
#define enable_gpuPowerStats // Nvidia Specific???
#define enable_gpuFanStats%  // this is only displayed in Portrait!!!
#define enable_gpuFanStatsRPM

//--------------------------- Throttle/Boost Gains MHZ or % ------------------------------
/* Uncomment to show Frequency gain MHz or Percent,*/
#define enable_ShowFrequencyGain

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* Uncomment only one of the below,*/
//#define ShowFrequencyGainMHz    // Show Overlock/Turbo & Boost Clock Frequency Gains in MHZ  eg: "+24MHz"
#define ShowFrequencyGain%       // Show Overlock/Turbo & Boost Clock Frequency Gains in Percent  eg: "+24%"

//----------------------------- Throttle/Boost Indicator --------------------------------

#define enable_ThrottleIndicator // Show TJMax Indicator 
#define enable_BoostIndicator    // Show CPU & GPU Turbo/Boost Indicator


//-------------------------------- TFT Fixed or PWM Brightness -------------------------------------

#define fixedBacklight // enable a fixed backlight (no PWM) powered from VCC

/*Start Up PWM Brightness if using MCU Pin*/
volatile int brightness_count = 200; // Start Up PWM Brightness


//-------------------------- Display Activity Shutdown -----------------------------------

/* Uncomment below to turn off the screen on serial timeout, else keep last display info eg: incase of PC Crash*/
#define enableActivityChecker

/* How long the display takes to timeout due to inactive serial data from the windows application */
#define lastActiveDelay 8000

//-------------------------------- Misco Setting -----------------------------------------

#define splashScreenLS // quick splash screen landscape hack job, also in FeatureSet

/* Debounce Rotary Encoder Button,Sometimes it gets caught during a screen refresh and does not change*/
int debounceButton = 1000; //  Use a 0.1uf/100nf/(104) ceramic capacitor from button Pin to GND

/* Enable the built in LED blinking when transmitting data,*/
//#define enableTX_LED

int TX_LED_Delay = 100; // TX blink delay

int baudRate = 9600; // set serial baud rate to match that of HardwareSerialMonitor 115200 will use more resources

/* Delay screen event, to stop screen data corruption ESP8622 use 25, most others 5 will do*/
int Serial_eventDelay = 0; //








//----------------------------- Debug Screen Erasers ---------------------------------------

/* Debug Screen, Update Erasers, */
//#define Debug

//------------------- Show Networks Stats when using WeeStatServer -----------------------

//#define enable_LibreNet
