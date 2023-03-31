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

  uVolume, GNATSTATS, PHATSTATS PC Performance Monitor & HardwareSerialMonitor Windows Client
  Rupert Hirst  © 2016 - 2023 http://tallmanlabs.com  http://runawaybrainz.blogspot.com/

  Gnat-Stats & Phat-Stats are optimised for desktop CPU's with dedicated graphics cards,
  You may get weird results on integrated GPU's (iGPU's) on laptops.*/

//--------------------------- Uncomment your Micro Processor---------------------------------

//#define Adafruit_QTPY_ATSAMD
#define Seeeduino_XIAO_ATSAMD
//#define Seeeduino_XIAO_RP2040   // Adafruit QT PY RP2040  (untested)
//#define Seeeduino_XIAO_NRF52840 // Adafruit QT PY NRF52840(untested)

//#define Seeeduino_WIO_ATSAMD51  // Seed Studio WIO Terminal

//--------------------------- Seeeduino_XIAO_ESP32C3 Experimental!!! --------------------------------

/* Uncomment ALT_TFT_RST for XIAO ESP32C3 &  OLD PCB v0.93, TFT_RST is on D9 (Miso) as D0 was used for IR */

//#define Seeeduino_XIAO_ESP32C3   // Adafruit QT PY ESP32S2, QT PY ESP32S3,  QT Py ESP32 Pico (untested)
//#define ALT_TFT_RST              // Use XIAO_ESP32C3 - TFT Reset on PIN D9

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


/* Characters to delete from the start of the CPU/GPU name eg: Remove "Intel" or "Nvidia" to save space*/
#define cpuNameStartLength 10 //i5-9600k = 10 / i9-13900k = 19
#define gpuNameStartLength 18


/* Manually name the CPU,*/
//#define Manual_cpuName
String set_CPUname = "xxxxxx";

/* Manually name the GPU,*/
//#define Manual_gpuName
String set_GPUname = "xxxxxx";

/* Manually set GPU ram total,*/
//#define Manual_gpuRam
String set_GPUram = "xxxxxx"; //in GB


//---------------------------------------------------------------------------------------


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


//----------------------------- TFT Fixed or PWM Brightness -------------------------------------

/* Comment out fixedBacklight for WIO Terminal, or the screen will not turn off */
/* Uncomment   fixedBacklight for ESP32, PWM is not yet supported */

//#define fixedBacklight // enable a fixed backlight (no PWM) powered from VCC

/*Start Up PWM Brightness if using MCU Pin*/
/* Wio Terminal LCD backlight brightness Range = 1 to 50, XIAO Range = 1 to 254 */

volatile int brightness_count = 100; // Start Up PWM Brightness

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
*/
