
#include"rain_gauge.h"

void beginGauge(int mpin, float *mmTotal){
  pinMode(mpin, INPUT);
  //pin_rain_gauge=mpin;
  mmTotal = (float*) malloc(sizeof(float));
  
  xTaskCreate(
    getRainMmTotal,    // Função a ser chamada
    "Toggle LED",   // Nome da tarefa
    1000,            // Tamanho (bytes)
    mmTotal,            // Parametro a ser passado
    1,               // Prioridade da Tarefa
    NULL             // Task handle
  );
}

void getRainMmTotal(void *mmTotal){
  int pastStatus = 0;
  while(1) {
    int rain_gauge_hall_effect_sensor = digitalRead(17);
    
  
  if (rain_gauge_hall_effect_sensor != pastStatus) {
    *(float *) &mmTotal = *(float *) mmTotal + mmPerPulse;
  }
  
  vTaskDelay(pdMS_TO_TICKS(500));
  pastStatus = rain_gauge_hall_effect_sensor;
  }
};