
#ifndef GAUGE_H
#define GAUGE_H

#include "Arduino.h"
#include "freertos/FreeRTOS.h"

void beginGauge(int mpin, float *mmTotal);
void getRainMmTotal(void *mmTotal);


const float mmPerPulse = 0.173;

#endif /* MODULE_H */

/*** end of file ***/

