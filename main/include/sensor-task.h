#ifndef SENSOR_TASK_H
#define SENSOR_TASK_H

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

// Definições para o clock do I2C
#define I2C_MASTER_FREQ_HZ  100000

// Prototipos das funções
char *get_temp_press(void); // Atualizado para retornar um ponteiro para char

uint8_t get_temp_press_int(void);

void init_sensor(void);

#endif /* SENSOR_TASK_H */
