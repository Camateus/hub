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
#include "debug-colors.h"
#include "i2c-mestria.h"
#include "bmx280.h"


/**
 * @brief Clock do I2C
*/
#define I2C_MASTER_FREQ_HZ  100000


uint8_t get_temp_press(void);

void init_sensor();

#endif /* SENSOR_TASK */
