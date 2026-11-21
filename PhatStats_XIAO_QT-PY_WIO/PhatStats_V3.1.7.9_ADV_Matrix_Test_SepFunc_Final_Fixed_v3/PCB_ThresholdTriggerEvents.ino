

/*
    
  New PCB Rotate States,0,1,2,3 Trigger functions when CPU or GPU thresholds are met 

*/

#ifdef enable_Thresholdtriggers_PCB

// ------------------- CPU load / Temp Event  --------------------

void PCB_TriggerCPU_load_LS180(int cpuUsage ) {  // Landscape Flipped 180

  float CPUloadfactor = cpuUsage ;

  if (CPUloadfactor >= 0 ) {
    pixels.setPixelColor(1, neo_BLUE);
    pixels.setPixelColor(2, neo_BLUE);

  }
  if (CPUloadfactor >= 25 ) {
    pixels.setPixelColor(1, neo_BLUE);
    pixels.setPixelColor(2, neo_BLUE);
  }

  if (CPUloadfactor >= (50) ) {
    pixels.setPixelColor(1, neo_RED);
    pixels.setPixelColor(2, neo_RED);
  }

  if (CPUloadfactor >= (90) ) {
    pixels.setPixelColor(1, neo_RED);
    pixels.setPixelColor(2, neo_RED);
  }

  pixels.show();

}


void PCB_TriggerCPU_temp_LS180(int cpuDegree ) {  // Landscape Flipped 180

  float CPUtempfactor = cpuDegree ;

  if (CPUtempfactor >=  50) {
    pixels.setPixelColor(1, neo_BLUE);
    pixels.setPixelColor(2, neo_BLUE);
  }

  if (CPUtempfactor >= 60 ) {
    pixels.setPixelColor(1, neo_RED);
    pixels.setPixelColor(2, neo_RED);

  }

  if (CPUtempfactor >= (70) ) {
    pixels.setPixelColor(1, neo_RED);
    pixels.setPixelColor(2, neo_RED);

  }

  if (CPUtempfactor >= (80) ) {
    pixels.setPixelColor(1, neo_RED);
    pixels.setPixelColor(2, neo_RED);

  }

  pixels.show();

}

// -------------------  GPU Load / Temp Event  --------------------


void PCB_TriggerGPU_load_LS180(int gpuUsage ) {  // Landscape Flipped 180

  float GPUloadfactor = gpuUsage ;

  if (GPUloadfactor >= 0 ) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(2, neo_BLUE);  
  }

  if (GPUloadfactor >= 25 ) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);
  }

  if (GPUloadfactor >= (50) ) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);
  }
  
if (GPUloadfactor >= (70) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }
  if (GPUloadfactor >= (90) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  pixels.show();

}


void PCB_TriggerGPU_temp_LS180(int gpuDegree ) {  // Landscape Flipped 180

  float GPUtempfactor = gpuDegree ;

  if (GPUtempfactor >=  50) {

    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);

  }

  if (GPUtempfactor >= 60 ) {

    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);

  }

  if (GPUtempfactor >= (70) ) {

    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  if (GPUtempfactor >= (80) ) {

    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  pixels.show();

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ------------------- CPU load / Temp Event  --------------------

void PCB_TriggerCPU_load_LS(int cpuUsage ) {  // Landscape

  float CPUloadfactor = cpuUsage ;

  if (CPUloadfactor >= 0 ) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);

  }
  if (CPUloadfactor >= 25 ) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);
  }

  if (CPUloadfactor >= (50) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  if (CPUloadfactor >= (90) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  pixels.show();

}


void PCB_TriggerCPU_temp_LS(int cpuDegree ) {  // Landscape

  float CPUtempfactor = cpuDegree ;

  if (CPUtempfactor >=  50) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);
  }

  if (CPUtempfactor >= 60 ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(3, neo_RED);

  }

  if (CPUtempfactor >= (70) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(3, neo_RED);

  }

  if (CPUtempfactor >= (80) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(3, neo_RED);

  }

  pixels.show();

}

// -------------------  GPU Load / Temp Event  --------------------


void PCB_TriggerGPU_load_LS(int gpuUsage ) {  // Landscape

  float GPUloadfactor = gpuUsage ;

  if (GPUloadfactor >= 0 ) {
    pixels.setPixelColor(1, neo_BLUE);
    pixels.setPixelColor(2, neo_BLUE);  
  }

  if (GPUloadfactor >= 25 ) {
    pixels.setPixelColor(1, neo_BLUE);
    pixels.setPixelColor(2, neo_BLUE);
  }

  if (GPUloadfactor >= (50) ) {
    pixels.setPixelColor(1, neo_BLUE);
    pixels.setPixelColor(2, neo_BLUE);
  }
  
if (GPUloadfactor >= (70) ) {
    pixels.setPixelColor(1, neo_RED);
    pixels.setPixelColor(2, neo_RED);
  }
  if (GPUloadfactor >= (90) ) {
    pixels.setPixelColor(1, neo_RED);
    pixels.setPixelColor(2, neo_RED);
  }

  pixels.show();

}


void PCB_TriggerGPU_temp_LS(int gpuDegree ) {  // Landscape

  float GPUtempfactor = gpuDegree ;

  if (GPUtempfactor >=  50) {

    pixels.setPixelColor(1, neo_BLUE);
    pixels.setPixelColor(2, neo_BLUE);

  }

  if (GPUtempfactor >= 60 ) {

    pixels.setPixelColor(1, neo_BLUE);
    pixels.setPixelColor(2, neo_BLUE);

  }

  if (GPUtempfactor >= (70) ) {

    pixels.setPixelColor(1, neo_RED);
    pixels.setPixelColor(2, neo_RED);
  }

  if (GPUtempfactor >= (80) ) {

    pixels.setPixelColor(1, neo_RED);
    pixels.setPixelColor(2, neo_RED);
  }

  pixels.show();

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ------------------- CPU load / Temp Event  --------------------

void PCB_TriggerCPU_load_Port(int cpuUsage ) {  // Portrait

  float CPUloadfactor = cpuUsage ;

  if (CPUloadfactor >= 0 ) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(1, neo_BLUE);

  }
  if (CPUloadfactor >= 25 ) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(1, neo_BLUE);
  }

  if (CPUloadfactor >= (50) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(1, neo_RED);
  }

  if (CPUloadfactor >= (90) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(1, neo_RED);
  }

  pixels.show();

}


void PCB_TriggerCPU_temp_Port(int cpuDegree ) {  // Portrait

  float CPUtempfactor = cpuDegree ;

  if (CPUtempfactor >=  50) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(1, neo_BLUE);
  }

  if (CPUtempfactor >= 60 ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(1, neo_RED);

  }

  if (CPUtempfactor >= (70) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(1, neo_RED);

  }

  if (CPUtempfactor >= (80) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(1, neo_RED);

  }

  pixels.show();

}

// -------------------  GPU Load / Temp Event  --------------------


void PCB_TriggerGPU_load_Port(int gpuUsage ) {  // Portrait

  float GPUloadfactor = gpuUsage ;

  if (GPUloadfactor >= 0 ) {
    pixels.setPixelColor(2, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);  
  }

  if (GPUloadfactor >= 25 ) {
    pixels.setPixelColor(2, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);
  }

  if (GPUloadfactor >= (50) ) {
    pixels.setPixelColor(2, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);
  }
  
if (GPUloadfactor >= (70) ) {
    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }
  if (GPUloadfactor >= (90) ) {
    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  pixels.show();

}


void PCB_TriggerGPU_temp_Port(int gpuDegree ) {  // Portrait

  float GPUtempfactor = gpuDegree ;

  if (GPUtempfactor >=  50) {

    pixels.setPixelColor(2, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);

  }

  if (GPUtempfactor >= 60 ) {

    pixels.setPixelColor(2, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);

  }

  if (GPUtempfactor >= (70) ) {

    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  if (GPUtempfactor >= (80) ) {

    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  pixels.show();

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PCB_TriggerCPU_load_Port180(int cpuUsage ) {  // Portrait Flipped 180

  float CPUloadfactor = cpuUsage ;

  if (CPUloadfactor >= 0 ) {
    pixels.setPixelColor(2, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);

  }
  if (CPUloadfactor >= 25 ) {
    pixels.setPixelColor(2, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);
  }

  if (CPUloadfactor >= (50) ) {
    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  if (CPUloadfactor >= (90) ) {
    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(3, neo_RED);
  }

  pixels.show();

}


void PCB_TriggerCPU_temp_Port180(int cpuDegree ) { // Portrait Flipped 180

  float CPUtempfactor = cpuDegree ;

  if (CPUtempfactor >=  50) {
    pixels.setPixelColor(2, neo_BLUE);
    pixels.setPixelColor(3, neo_BLUE);
  }

  if (CPUtempfactor >= 60 ) {
    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(3, neo_RED);

  }

  if (CPUtempfactor >= (70) ) {
    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(3, neo_RED);

  }

  if (CPUtempfactor >= (80) ) {
    pixels.setPixelColor(2, neo_RED);
    pixels.setPixelColor(3, neo_RED);

  }

  pixels.show();

}

// -------------------  GPU Load / Temp Event  --------------------


void PCB_TriggerGPU_load_Port180(int gpuUsage ) { // Portrait Flipped 180

  float GPUloadfactor = gpuUsage ;

  if (GPUloadfactor >= 0 ) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(1, neo_BLUE);  
  }

  if (GPUloadfactor >= 25 ) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(1, neo_BLUE);
  }

  if (GPUloadfactor >= (50) ) {
    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(1, neo_BLUE);
  }
  
if (GPUloadfactor >= (70) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(1, neo_RED);
  }
  if (GPUloadfactor >= (90) ) {
    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(1, neo_RED);
  }

  pixels.show();

}


void PCB_TriggerGPU_temp_Port180(int gpuDegree ) { // Portrait Flipped 180

  float GPUtempfactor = gpuDegree ;

  if (GPUtempfactor >=  50) {

    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(1, neo_BLUE);

  }

  if (GPUtempfactor >= 60 ) {

    pixels.setPixelColor(0, neo_BLUE);
    pixels.setPixelColor(1, neo_BLUE);

  }

  if (GPUtempfactor >= (70) ) {

    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(1, neo_RED);
  }

  if (GPUtempfactor >= (80) ) {

    pixels.setPixelColor(0, neo_RED);
    pixels.setPixelColor(1, neo_RED);
  }

  pixels.show();

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif
