#ifndef IO_TASK
#define IO_TASK

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
#include "gpio-mestria.h"

#define rele1 26
#define rele2 27

#define RELAY_BITMASK ((1ULL << rele1) | (1ULL << rele2))

void inverte_rele_1();

void inverte_rele_2();

void init_config_pins();

#endif /* IO_TASK */
