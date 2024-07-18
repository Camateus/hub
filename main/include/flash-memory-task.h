#ifndef FLASH_MEMORY_TASK_H
#define FLASH_MEMORY_TASK_H

//? ====================================== HEADERS ===================================== */

//* ======================= Bibliotecas C ======================

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//* ====================== Bibliotecas esp =====================

#include "debug-colors.h"
#include "esp_err.h"
#include "esp_system.h"
#include "esp_vfs.h"
#include "flash-mestria.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"

//? ==================================== CONSTANTES ==================================== */

//? ====================================== LEITURA ====================================== /
/**
 * @brief Inicializa um valor padrão em caso de erro na leitura de uma variável.
 *
 * @param err O código de erro retornado pela operação de leitura.
 * @param clear_function A função a ser chamada para restaurar o valor padrão da variável.
 * @param key A chave identificadora da variável (usada para exibir na mensagem de erro).
 */
void init_value_on_error(esp_err_t err, esp_err_t (*clear_function)(void), const char *key);

/**
 * @brief Lê as variáveis de informações gerais armazenadas na memória flash.
 *
 * @return O código de erro resultante da leitura das variáveis. ESP_OK em caso de sucesso.
 */
esp_err_t read_general_info_variables(void);

//? ====================================== ESCRITA ====================================== /

//? ======================================= CLEAN ======================================= /

//? ================================== INICIALIZAÇÕES =================================== /

/**
 * @brief Inicializa a memória flash, lê as variáveis de configuração geral e exibe mensagens de log.
 *
 * @param None
 * @return None
 */
void init_flash_memory(void);

#endif /* FLASH_MEMORY_TASK_H */