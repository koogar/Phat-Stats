555555555555555555555
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

*/

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

    pixels.setPixelColor(0, BLUE);
    pixels.setPixelColor(3, BLUE);

  }
  if (CPUloadfactor >=  (25) ) {

    pixels.setPixelColor(0, GREEN);
    pixels.setPixelColor(3, GREEN);
  }

  if (CPUloadfactor >=  (50) ) {

    pixels.setPixelColor(0, DARKORANGE);
    pixels.setPixelColor(3, DARKORANGE);
  }

  if (CPUloadfactor >=  (90) ) {

    pixels.setPixelColor(0, RED);
    pixels.setPixelColor(3, RED);
  }

  pixels.show();

}



void CPU_tempGauge(int cpuDegree ) {

  //refreshNeopixels();

  float CPUtempfactor = cpuDegree ;

  if (CPUtempfactor >=  (50) ) {

    pixels.setPixelColor(0, BLUE);
    pixels.setPixelColor(3, BLUE);
  }

  if (CPUtempfactor >=  (60) ) {

    pixels.setPixelColor(0, RED);
    pixels.setPixelColor(3, RED);

  }

  if (CPUtempfactor >=  (70) ) {

    pixels.setPixelColor(0, RED);
    pixels.setPixelColor(3, RED);

  }

  if (CPUtempfactor >=  (80) ) {

    pixels.setPixelColor(0, RED);
    pixels.setPixelColor(3, RED);

  }

  pixels.show();

}

//---------------------- GPU--------------------

void GPU_loadGauge(int gpuUsage ) {

  //refreshNeopixels();

  float GPUloadfactor = gpuUsage ;

  if (GPUloadfactor >=  (0) ) {

    pixels.setPixelColor(2, BLUE);
    pixels.setPixelColor(1, BLUE);
  }

  if (GPUloadfactor >=  (25) ) {

    pixels.setPixelColor(2, GREEN);
    pixels.setPixelColor(1, GREEN);
  }

  if (GPUloadfactor >=  (50) ) {

    pixels.setPixelColor(2, GREEN);
    pixels.setPixelColor(1, GREEN);
  }

  if (GPUloadfactor >=  (70) ) {

    pixels.setPixelColor(2, DARKORANGE);
    pixels.setPixelColor(1, DARKORANGE);
  }
  if (GPUloadfactor >=  (90) ) {

    pixels.setPixelColor(2, RED);
    pixels.setPixelColor(1, RED);
  }

  pixels.show();

}



void GPU_tempGauge(int gpuDegree ) {

  //refreshNeopixels();

  float GPUtempfactor = gpuDegree ;

  if (GPUtempfactor >=  (50) ) {

    pixels.setPixelColor(2, BLUE);
    pixels.setPixelColor(1, BLUE);

  }

  if (GPUtempfactor >=  (60) ) {

    pixels.setPixelColor(2, BLUE);
    pixels.setPixelColor(1, BLUE);

  }

  if (GPUtempfactor >=  (70) ) {

    pixels.setPixelColor(2, RED);
    pixels.setPixelColor(1, RED);
  }

  if (GPUtempfactor >= (80) ) {

    pixels.setPixelColor(2, RED);
    pixels.setPixelColor(1, RED);
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

    pixels.setPixelColor(0, BLUE);
    pixels.setPixelColor(1, BLUE);

  }
  if (CPUloadfactor >= (25) ) {

    pixels.setPixelColor(0, GREEN);
    pixels.setPixelColor(1, GREEN);
  }

  if (CPUloadfactor >= (50) ) {

    pixels.setPixelColor(0, DARKORANGE);
    pixels.setPixelColor(1, DARKORANGE);
  }

  if (CPUloadfactor >= (90) ) {

    pixels.setPixelColor(0, RED);
    pixels.setPixelColor(1, RED);
  }

  pixels.show();

}



void CPU_tempGauge(int cpuDegree ) {

  //refreshNeopixels();

  float CPUtempfactor = cpuDegree ;

  if (CPUtempfactor >=  (50) ) {

    pixels.setPixelColor(0, BLUE);
    pixels.setPixelColor(1, BLUE);
  }

  if (CPUtempfactor >=  (60) ) {

    pixels.setPixelColor(0, RED);
    pixels.setPixelColor(1, RED);

  }

  if (CPUtempfactor >=  (70) ) {

    pixels.setPixelColor(0, RED);
    pixels.setPixelColor(1, RED);

  }

  if (CPUtempfactor >=  (80) ) {

    pixels.setPixelColor(0, RED);
    pixels.setPixelColor(1, RED);

  }

  pixels.show();

}

//---------------------- GPU--------------------

void GPU_loadGauge(int gpuUsage ) {

  //refreshNeopixels();

  float GPUloadfactor = gpuUsage ;

  if (GPUloadfactor >=  (0) ) {

    pixels.setPixelColor(2, BLUE);
    pixels.setPixelColor(3, BLUE);
  }

  if (GPUloadfactor >=  (25) ) {

    pixels.setPixelColor(2, GREEN);
    pixels.setPixelColor(3, GREEN);
  }

  if (GPUloadfactor >=  (50) ) {

    pixels.setPixelColor(2, GREEN);
    pixels.setPixelColor(3, GREEN);
  }

  if (GPUloadfactor >=  (70) ) {

    pixels.setPixelColor(2, DARKORANGE);
    pixels.setPixelColor(3, DARKORANGE);
  }
  if (GPUloadfactor >=  (90) ) {

    pixels.setPixelColor(2, RED);
    pixels.setPixelColor(3, RED);
  }

  pixels.show();

}



void GPU_tempGauge(int gpuDegree ) {

  //refreshNeopixels();

  float GPUtempfactor = gpuDegree ;

  if (GPUtempfactor >=  (50) ) {

    pixels.setPixelColor(2, BLUE);
    pixels.setPixelColor(3, BLUE);

  }

  if (GPUtempfactor >=  (60) ) {

    pixels.setPixelColor(2, BLUE);
    pixels.setPixelColor(3, BLUE);

  }

  if (GPUtempfactor >=  (70) ) {

    pixels.setPixelColor(2, RED);
    pixels.setPixelColor(3, RED);
  }

  if (GPUtempfactor >=  (80) ) {

    pixels.setPixelColor(2, RED);
    pixels.setPixelColor(3, RED);
  }

  pixels.show();

}

#endif
