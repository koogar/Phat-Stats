
/*

  ------------------------------------------------------------------------------------------

  CPU_loadGauge( cpuString2.toInt() ); // Neopixel Ring Gauge  CPU  Load
  CPU_tempGauge( cpuString1.toInt() ); // Neopixel Ring Gauge  CPU  Temperature

  GPU_loadGauge( gpuString2.toInt() ); // Neopixel Ring Gauge  GPU  Load
  GPU_tempGauge( gpuString1.toInt() ); // Neopixel Ring Gauge  GPU  Temperature

  refreshNeopixels(); // Clear neopixels every screen refresh, only have one instance running!!!

  Portrait
  --------
  CPU Pixel ID: 0 & 1
  GPU Pixel ID: 2 & 3

  Landscape
  ---------
  CPU Pixel ID: 0 & 3
  GPU Pixel ID: 1 & 2
  ------------------------------------------------------------------------------------------



void refreshNeopixels() {
  for ( int i = 0; i < NUM_PIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 0, 0 );
  }
  //pixels.show();
}
//-------------------------------------- NeoPixel_Landscape ---------------------------------

#ifdef NeoPixel_Landscape  // else use portrait


//---------------------- CPU--------------------

void CPU_loadGauge(int cpuUsage ) {

  refreshNeopixels();

  float CPUloadfactor = cpuUsage ;


  if (CPUloadfactor >=  (0) ) {

    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);

  }
  if (CPUloadfactor >=  (25) ) {

    pixels.setPixelColor(0, neo_GREEN);
    pixels.setPixelColor(3, neo_GREEN);
  }

  if (CPUloadfactor >=  (50) ) {

    pixels.setPixelColor(0, neo_DARKORANGE);
    pixels.setPixelColor(3, neo_DARKORANGE);
  }

  if (CPUloadfactor >=  (90) ) {

    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  pixels.show();

}



void CPU_tempGauge(int cpuDegree ) {

  //refreshNeopixels();

  float CPUtempfactor = cpuDegree ;

  if (CPUtempfactor >=  (50) ) {

    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);
  }

  if (CPUtempfactor >=  (60) ) {

    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(3, neo_RED);

  }

  if (CPUtempfactor >=  (70) ) {

    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(3, neo_RED);

  }

  if (CPUtempfactor >=  (80) ) {

    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(3, neo_RED);

  }

  pixels.show();

}

//---------------------- GPU--------------------

void GPU_loadGauge(int gpuUsage ) {

  //refreshNeopixels();

  float GPUloadfactor = gpuUsage ;

  if (GPUloadfactor >=  (0) ) {

    pixels.setPixelColor(2, neo_BLUE);
    pixels.setPixelColor(1, neo_BLUE);
  }

  if (GPUloadfactor >=  (25) ) {

    pixels.setPixelColor(2, neo_GREEN);
    pixels.setPixelColor(1, neo_GREEN);
  }

  if (GPUloadfactor >=  (50) ) {

    pixels.setPixelColor(2, neo_GREEN);
    pixels.setPixelColor(1, neo_GREEN);
  }

  if (GPUloadfactor >=  (70) ) {

    pixels.setPixelColor(2, neo_DARKORANGE);
    pixels.setPixelColor(1, neo_DARKORANGE);
  }
  if (GPUloadfactor >=  (90) ) {

    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(1, neo_RED);
  }

  pixels.show();

}



void GPU_tempGauge(int gpuDegree ) {

  //refreshNeopixels();

  float GPUtempfactor = gpuDegree ;

  if (GPUtempfactor >=  (50) ) {

    pixels.setPixelColor(2, neo_BLUE);
    pixels.setPixelColor(1, neo_BLUE);

  }

  if (GPUtempfactor >=  (60) ) {

    pixels.setPixelColor(2, neo_BLUE);
    pixels.setPixelColor(1, neo_BLUE);

  }

  if (GPUtempfactor >=  (70) ) {

    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(1, neo_RED);
  }

  if (GPUtempfactor >= (80) ) {

    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(1, neo_RED);
  }

  pixels.show();

}

#else // NeoPixel_Portrait

//-------------------------------------- NeoPixel_Portrait ---------------------------------


//---------------------- CPU--------------------

void CPU_loadGauge(int cpuUsage ) {

  refreshNeopixels();

  float CPUloadfactor = cpuUsage ;


  if (CPUloadfactor >=  (0) ) {

    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(1, neo_BLUE);

  }
  if (CPUloadfactor >= (25) ) {

    pixels.setPixelColor(0, neo_GREEN);
    pixels.setPixelColor(1, neo_GREEN);
  }

  if (CPUloadfactor >= (50) ) {

    pixels.setPixelColor(0, neo_DARKORANGE);
    pixels.setPixelColor(1, neo_DARKORANGE);
  }

  if (CPUloadfactor >= (90) ) {

    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(1, neo_RED);
  }

  pixels.show();

}



void CPU_tempGauge(int cpuDegree ) {

  //refreshNeopixels();

  float CPUtempfactor = cpuDegree ;

  if (CPUtempfactor >=  (50) ) {

    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(1, neo_BLUE);
  }

  if (CPUtempfactor >=  (60) ) {

    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(1, neo_RED);

  }

  if (CPUtempfactor >=  (70) ) {

    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(1, neo_RED);

  }

  if (CPUtempfactor >=  (80) ) {

    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(1, neo_RED);

  }

  pixels.show();

}

//---------------------- GPU--------------------

void GPU_loadGauge(int gpuUsage ) {

  //refreshNeopixels();

  float GPUloadfactor = gpuUsage ;

  if (GPUloadfactor >=  (0) ) {

    pixels.setPixelColor(2, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);
  }

  if (GPUloadfactor >=  (25) ) {

    pixels.setPixelColor(2, neo_GREEN);
    pixels.setPixelColor(3, neo_GREEN);
  }

  if (GPUloadfactor >=  (50) ) {

    pixels.setPixelColor(2, neo_GREEN);
    pixels.setPixelColor(3, neo_GREEN);
  }

  if (GPUloadfactor >=  (70) ) {

    pixels.setPixelColor(2, neo_DARKORANGE);
    pixels.setPixelColor(3, neo_DARKORANGE);
  }
  if (GPUloadfactor >=  (90) ) {

    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  pixels.show();

}



void GPU_tempGauge(int gpuDegree ) {

  //refreshNeopixels();

  float GPUtempfactor = gpuDegree ;

  if (GPUtempfactor >=  (50) ) {

    pixels.setPixelColor(2, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);

  }

  if (GPUtempfactor >=  (60) ) {

    pixels.setPixelColor(2, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);

  }

  if (GPUtempfactor >=  (70) ) {

    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  if (GPUtempfactor >=  (80) ) {

    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  pixels.show();

}

#endif

*/
