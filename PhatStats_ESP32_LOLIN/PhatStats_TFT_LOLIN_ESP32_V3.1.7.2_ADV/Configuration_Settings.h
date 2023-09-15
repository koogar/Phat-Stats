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

//------------------------------- BT Limitations --------------------------------------

/*If BT is enabled you can not use HardwareSerialMonitor with USB serial, even though it is visible.
  You can still upload new code through the Arduino IDE as normal.

  Currently when using BT you only have to connect the device to Windows, no BT pairing is needed.
  When disconnected, you will need to manualy reconnect in HardwareSerialMonitor by clicking
  on the correct COM port “Standard Serial over Bluetooth link”.

  Note: Once connected, two “Standard Serial over Bluetooth Classic link” will be visible
  one is Send, the other is Receive.
  When you know the correct port for Send you can disable the other in Device Manager
  so it does not to show up in HardwareSerialMonitor.*/

//--------------------------- ESP32 BT Board Windows ID -----------------------------------


#define  LOLIN_D32
//#define  LOLIN32_LITE

//--------------------------- Bluetooth Classic -----------------------------------
/*ESP32 Communication type, Uncomment only one option!!!*/

/*Uncomment to enable BT, else default to USB serial only,
  Baud Rate of PhatStats and HardwareSerialMonitor must match*/

//#define enable_BT              // Use baud of 9600, enable only Bluetooth Classic serial connection

/* Enable the built in LED blinking when transmitting, saves power when using battery if disabled,*/
//#define enableTX_LED //
int TX_LED_Delay = 0; // TX blink delay


//----------------------------- Battery Monitor ------------------------------------
/*WARNING!!! Requires voltage divider (GND ---[100K]--- (Pin34 ADC) ----[100k]--- BATT+) (0%)3.2v to (100%)4.2v Range,*/

//#define batteryMonitor // (experimental) Read current LiPo battery level if connected.

//-------------------------------- DISCLAIMER -------------------------------------------
/*
  !!!THE WEMOS LOLIN32, NOT LIMITED TO, APPEARS TO HAVE NO "UNDERVOLTAGE PROTECTION"
  OR "OVER DISCHARGE PROTECTION" ON THE CHARGING CIRCUIT!!!

  OTHER BOARDS ARE THE SAME!!! USE A LiPo BATTERY WITH BUILT IN PROTECTION, EVEN THEN,
  BUILT IN PROTECTION IS CONSIDERED A LAST RESORT SAFETY NET OR "BELTS AND BRACERS" APPROACH.

  YOU MAY GET SOME BENEFITS, OVERVOLTAGE,OVERCURRENT AND SHORT CIRCUIT PROTECTION BUT, USUALLY
  THE OVER DISCHARGE PROTECTION CUT OFF VOLTAGE IS AROUND 2.4v WHICH IS WAY TOO LOW FOR THE
  CONTINUED MAINTAINED HEALTH OF THE BATTERY.

  RECOMMENDED OVER DISCHARGE PROTECTION VOLTAGES FOR LiPo's ARE AROUND 2.9 - 3 VOLTS.

  ALTERNATIVELY USE A BATTERY BANK THROUGH THE USB CONNECTOR

  !!!LITHIUM POLYMER PACKS / BATTERIES CAN BE VERY DANGEROUS, WITH A RISK OF FIRE!!!

  If you are going to use a battery or LiPo pack you must take some responsibility, do your research!!!.
  No advice will be given, or implied regarding which you should use etc.

  Use the battery/type in accordance with the manufacturer's recommendations.*/


//--------------------------- Uncomment your CPU/GPU Display  -----------------------------------

/* Uncomment your CPU,*/

#define INTEL_CPU
//#define AMD_CPU


/* Uncomment your GPU,*/

//#define NVIDIA_GRAPHICS
//#define NVIDIA_GTX_Ti_GRAPHICS
//#define NVIDIA_RTX_GRAPHICS
#define NVIDIA_RTX_Ti_GRAPHICS
//#define NVIDIA_RTX_SUPER_GRAPHICS

//#define AMD_GRAPHICS
//#define INTEL_GRAPHICS

/* Characters to delete from the start of the CPU/GPU name eg: Remove "Intel" or "Nvidia" to save space*/
#define cpuNameStartLength 10 //eg: i5-9600k = 10 / i9-13900k = 19
#define gpuNameStartLength 18 //eg: Geforce GTX1080 (non Ti) = 18 
#define gpuTotalMemPos     13 //Shift right the GPU memory total position in pixels eg: so not to block "Ti"

//>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* Manually name the  CPU,*/
//#define Manual_cpuName
String set_CPUname = "xxxxxxxx";

/* Manually name the GPU,*/
//#define Manual_gpuName
String set_GPUname = "xxxxxxxx";

/* Manually set GPU ram total,*/
//#define Manual_gpuRam
String set_GPUram = "xx";

//>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define noDegree      // lose the "o"
#define smallPercent  // Use small percent symbol
//---------------------------------------------------------------------------------------

/* CPU is overclocked with Turbo boost disabled, to stop "TURBO" indicator,*/
//#define CPU_OverClocked

/* CPU & GPU Thermal Junction Max Temperature in "c" before throttling,*/
#define CPU_TJMAX 100  //  TJ Max for the Intel 9900K    = 100c
#define GPU_TJMAX 105   //  TJ Max for the Nvidia GTX1080 = 83c TJ Max for the Nvidia RTX3080 = 110c

/* CPU & GPU Turbo/Boost Frequency Values in Mhz */
#define CPU_BOOST 3700  //  Enter Stock CPU Frequency eg. Intel Core i5 9600k = 3700MHz
#define GPU_BOOST 1830  //  Enter Stock GPU Frequency eg. MSI  RTX3080 Suprim X = 1845/1830 /MSi GamingX 1080  = 1683MHz /
//-------------------------------- Show GPU Stats ------------------------------------

/* Remove Specific GPU stats in landscape mode(enable_gpuVram, enable_gpuShader),
  this helps to make room if your GPU memory is over 9999MB */

//#define enable_gpuVram
//#define enable_gpuShader
#define enable_BigGPUw      // undefine  enable_gpuShader & enable_gpuShader first

//-----------------------------

#define enable_gpuCore
#define enable_gpuPowerStats    // Nvidia Specific???
#define enable_gpuFanStatsPerc  // this is only displayed in Portrait!!!
#define enable_gpuFanStatsRPM

//----------------------------- Frequency Gains Indicator --------------------------------

/* Uncomment to enable the display of frequency gains */
#define enable_ShowFrequencyGain

/* Uncomment only one of the units to display below, MHz or Percent */
//#define ShowFrequencyGainMHz        // Show Overlock/Turbo & Boost Clock Frequency Gains in MHZ  eg: "+24MHz"
#define ShowFrequencyGainPerc       // Show Overlock/Turbo & Boost Clock Frequency Gains in Percent  eg: "+24%"

//----------------------------- Throttle/Boost Indicator --------------------------------

#define enable_ThrottleIndicator // Show TJMax Indicator 
#define enable_BoostIndicator    // Show CPU & GPU Turbo/Boost Indicator

//-------------------------------- NeoPixel Modes -------------------------------------
#define NUM_PIXELS  16
/* If  NeoBrightness = 0 Phat-Stats will start with no NeoPixels lit. Turn the Rotary Encoder to turn on the NeoPixels, */
int NeoBrightness   = 20;           // Global start up brightness

/* Uncomment only one of the below*/
//#define enable_NeopixelGauges     // NeoPixel ring bargraph example

//#define enable_Thresholdtriggers_PCB // New PCB 4x NeoPixel Rotate States,0,1,2,3  Trigger functions when CPU or GPU thresholds are met



//----------------------------- TFT Fixed or PWM Brightness ------------------------------------

#define fixedBacklight // enable a fixed backlight (no PWM) powered from VCC


/*TFT Start Up Brightness*/
//PWM Brightness Note: espressif (ESP32)    v2.0.5 (v2.08 = ESP32_AnalogWrite compile error use fixedBacklight option)
volatile int brightness_count = 250; // Start Up PWM Brightness

//-------------------------- Display Activity Shutdown -----------------------------------

/* Uncomment below to turn off the screen on serial timeout, else keep last display info eg: incase of PC Crash*/
#define enableActivityChecker

/* How long the display takes to timeout due to inactive serial data from the windows application */
#define lastActiveDelay 8000

//-------------------------------- Miso Setting -----------------------------------------

//#define  RETRO_MONO    //CRT Monochrome screen
//#define  RETRO_AMBER   //CRT Amber screen
//#define  RETRO_GREEN   //CRT Green screen

#define splashScreenLS // quick splash screen landscape hack job, also in FeatureSet

/* Debounce  Button, button mode is a bit flaky at present as it needs interrupts, Sometimes it gets caught during a screen refresh
  and does not change. WIO Terminal & ESP32 seem to like 1000ms and works just!!! ok */

int debounceButton = 1000; //  Use a 0.1uf/100nf/(104) ceramic capacitor from button Pin to GND if poss

/* Delay screen event, to stop screen data corruption ESP8622 / ESP32 use 25, most others 5 or 0 will do*/
int Serial_eventDelay = 15;  // 15 is the minimum setting for an ESP32 with a Silicon Labs CP210x serial chip

int baudRate  = 9600; // set serial baud rate to match that of HardwareSerialMonitor 115200 will use more resources



// BT Board ID

#ifdef LOLIN_D32
#define device_BT "TMLabs_BT_D32"
#endif

#ifdef LOLIN32_LITE
#define device_BT "TMLabs_BT_32Lite"
#endif


//-------------------------------------------- Versions ---------------------------------- -
/*

     V3.1.1.ADV    Advanced

        Button to change aspect
        NeoPixels

        Add enable_gpuVram, enable_gpuShader, enable_gpuCore
        Remove specific GPU stats in landscape mode, this helps to make room if your GPU memory is over 9999MB
        Fix set_GPUram

     V3.1.3.BT.ADV   (ESP32)

        Fixes
        Retro CRT look option


    V3.1.6.ADV/KiSS

       Clean up code
       Turn off the backlight untill the stats have updated when using button mode.
       Add PCB_ThresholdTriggerEvents for custom PCB, so neopixels rotate with button mode.

      (ADV) Add option to display the splash screen in landscape.

    V3.1.7.2.ADV

       Add RTX Ti BMP Logo
       Option to shift GPU total memory in pixels

  Note: Gnat-Stats/Phat-Stats is optimised for desktop CPU's with dedicated graphics cards, such as Nvidia/Radeon.
      You may get wierd results on mobile CPUs and integrated GPU's (iGPU's) on laptops.

*/







//---------------------------- Debug Screen Erasers ---------------------------------------

/* Debug Screen, Update Erasers, */
//#define Debug

//-------------- Show Networks Stats when using Phatstats edition of WeeStatServer ---------------
//#define enable_LibreNet // Reserved // undefine  enable_gpuCore, enable_gpuShader, enable_gpuShader first, enable_gpuPowerStats
//--------------------------- Throttle/Boost Gains MHZ or % ------------------------------
