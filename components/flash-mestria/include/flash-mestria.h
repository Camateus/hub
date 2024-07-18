// Definição para evitar repetição do arquivo
#ifndef FLASH_MESTRIA_H
#define FLASH_MESTRIA_H

// ?================================= HEADERS =================================

// Bibliotecas nativas do C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// Bibliotecas locais do esp
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "nvs_flash.h"

//? ===================================== FUNÇÕES ========================================
/**
 * @brief Lê uma variável int8_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_int8_variables(char *storage, char *commit, int8_t *number);

/**
 * @brief Lê uma variável uint8_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_uint8_variables(char *storage, char *commit, uint8_t *number);

/**
 * @brief Lê uma variável int16_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_int16_variables(char *storage, char *commit, int16_t *number);

/**
 * @brief Lê uma variável uint16_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_uint16_variables(char *storage, char *commit, uint16_t *number);

/**
 * @brief Lê uma variável int32_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_int32_variables(char *storage, char *commit, int32_t *number);

/**
 * @brief Lê uma variável uint32_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_uint32_variables(char *storage, char *commit, uint32_t *number);

/**
 * @brief Lê uma variável int64_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_int64_variables(char *storage, char *commit, int64_t *number);

/**
 * @brief Lê uma variável uint64_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_uint64_variables(char *storage, char *commit, uint64_t *number);

/**
 * @brief Lê uma string na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param string_to_save Buffer onde a string será retornada
 * @param string_length Tamanho da string a ser armazenada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_str_variables(char *storage, char *commit, char *string_to_save, size_t *string_length);

/**
 * @brief Lê um blob na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param value_to_save Buffer onde o blob será retornado
 * @param value_length Tamanho do buffer
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_blob_variables(char *storage, char *commit, void *value_to_save, size_t *value_length);

/**
 * @brief Salva uma variável int8_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_int8_variables(char *storage, int8_t number_to_save, char *commit);

/**
 * @brief Salva uma variável uint8_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_uint8_variables(char *storage, uint8_t number_to_save, char *commit);

/**
 * @brief Salva uma variável int16_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_int16_variables(char *storage, int16_t number_to_save, char *commit);

/**
 * @brief Salva uma variável uint16_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_uint16_variables(char *storage, uint16_t number_to_save, char *commit);

/**
 * @brief Salva uma variável int32_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_int32_variables(char *storage, int32_t number_to_save, char *commit);

/**
 * @brief Salva uma variável uint32_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_uint32_variables(char *storage, uint32_t number_to_save, char *commit);

/**
 * @brief Salva uma variável int64_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_int64_variables(char *storage, int64_t number_to_save, char *commit);

/**
 * @brief Salva uma variável uint64_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_uint64_variables(char *storage, uint64_t number_to_save, char *commit);

/**
 * @brief Salva uma string na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param str_to_save String a ser salva
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_str_variables(char *storage, char *str_to_save, char *commit);

/**
 * @brief Salva um blob na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param value_to_save Blob a ser salvo
 * @param commit Nome da variável utilizada
 * @param value_length Tamanho do blob
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_blob_variables(char *storage, uint8_t *value_to_save, char *commit, size_t value_length);

/**
 * @brief Limpa todos os dados em uma partição NVS
 *
 * @param storage Nome do armazenamento utilizado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t clear_namespace(char *storage);

/**
 * @brief Apaga um item específico em uma partição NVS
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit_to_delete Variável a ser apagada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t erase_commit(char *storage, char *commit_to_delete);

/**
 * @brief Inicializa o subsistema de NVS
 *
 * @param None
 *
 * @return None
*/
void initialize_flash(void);

#endif /* FLASH_MESTRIA_H */
