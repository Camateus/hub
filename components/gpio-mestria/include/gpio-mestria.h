// Definição para evitar repetição do arquivo
#ifndef GPIO_MESTRIA_H
#define GPIO_MESTRIA_H

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

// ?================================ CONSTANTES ===============================

/**
 * @brief Modos dos pinos de saída
*/
#define ON  1
#define OFF 0

// ?================================= FUNÇÕES =================================

/**
 * @brief Configura um pino
 *
 * @param intr         Modo da interrupção do pino (tipo de borda invertida ou desabilitação)
 * @param mode         Modo do pino (entrada ou saída)
 * @param bit_mask     Bitmask dos pinos que se deseja configurar
 * @param pull_down_en Modo do pull-down interno do pino
 *
 * @return (esp_err_t) Retorna o sucesso da configuração
*/
esp_err_t gpio_configuration(gpio_int_type_t intr, gpio_mode_t mode, uint64_t bit_mask, gpio_pulldown_t pull_down_en);

/**
 * @brief Altera o estado de um pino.
 *
 * @param gpio Pino a ser lido
 * @param level Estado desejado
 *
 * @return (esp_err_t) Novo estado do pino
*/
esp_err_t gpio_digital_write(gpio_num_t gpio, uint8_t level);

/**
 * @brief Lê o estado de um pino. O valor é invertido pela presença do
 * circuito do optoacoplador, que utiliza de um pull-up para remover
 * flutuações do pino.
 *
 * @param gpio Pino a ser lido
 *
 * @return (esp_err_t) Estado invertido do pino
*/
int8_t gpio_digital_read(gpio_num_t gpio);

#endif /* GPIO_MESTRIA_H */