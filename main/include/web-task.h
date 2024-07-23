#ifndef WEB_TASK_H
#define WEB_TASK_H

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
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "event_groups.h"
#include "esp_wifi.h"
#include "esp_http_server.h"
#include "sensor-task.h"
#include "io-task.h"

// Definições de rede Wi-Fi
#define WIFI_SSID "CASA859"         // Nome da rede Wi-Fi
#define WIFI_PASS "87654321"        // Senha da rede Wi-Fi

// Prototipos das funções
const char *generate_html_page(const char *temperatura);
void init_web_interface(void);

#endif /* WEB_TASK_H */
