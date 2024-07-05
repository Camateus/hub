#ifndef SENSOR_TASK
#define SENSOR_TASK

// ?================================= HEADERS =================================

// Bibliotecas nativas do C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// Bibliotecas locais do esp
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/gpio_struct.h"
#include "i2c-mestria.h"

void init_sensor();

#endif /* SENSOR_TASK */
