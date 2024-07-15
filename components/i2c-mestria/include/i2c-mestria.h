// Definição para evitar repetição do arquivo
#ifndef I2C_MESTRIA_H
#define I2C_MESTRIA_H

// ?================================= HEADERS =================================

// Bibliotecas nativas do C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// Bibliotecas locais do esp
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

//? =================================== CONSTANTES =======================================

/**
 * @brief Pinos utilizados pelo I2C
*/
#define I2C_MASTER_SDA_IO           21
#define I2C_MASTER_SCL_IO           22

/**
 * @brief Buffers utilizados apenas em modo de slave
*/
#define I2C_MASTER_TX_BUF_DISABLE   0
#define I2C_MASTER_RX_BUF_DISABLE   0

/**
 * @brief Flags de envio
*/
#define BIT_TO_WRITE                0x00
#define BIT_TO_READ                 0x01

//? ===================================== FUNÇÕES ========================================

/**
 * @brief Envia mensagem para um dispositivo I2C
 *
 * @param i2c_num           Porta do I2C a ser utilizada
 * @param data_wr           Buffer a ser enviado
 * @param size              Número de bytes a serem enviados
 * @param i2c_register_addr Endereço do registrador utilizado
 * @param device_addr       Endereço do dispostivo para quem a mensagem vai ser enviada
 *
 * @return (esp_err_t) Resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
*/
esp_err_t i2c_master_write_slave(i2c_port_t i2c_num, uint8_t *data_wr, size_t size, uint8_t i2c_register_addr,
                                 uint8_t device_addr);

/**
 * @brief Lê mensagem de um dispositivo I2C
 *
 * @param i2c_num           Porta do I2C a ser utilizada
 * @param data_wr           Buffer a ser preenchido com o dado recebido
 * @param size              Número de bytes a serem lidos
 * @param i2c_register_addr Endereço do registrador utilizado
 * @param device_addr       Endereço do dispostivo para quem a mensagem vai ser enviada
 *
 * @return (esp_err_t) Resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
*/
esp_err_t i2c_master_read_slave(i2c_port_t i2c_num, uint8_t *data_rd, size_t size,
                                uint8_t i2c_register_addr, uint8_t device_addr);

/**
 * @brief Inicializa o controlador do I2C como master
 *
 * @param conf            Configuração do controlador do I2C
 * @param i2c_master_port Porta do I2C a ser utilizada
 *
 * @return (esp_err_t) Resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
*/
esp_err_t i2c_master_init(i2c_config_t conf, i2c_port_t i2c_master_port);

#endif /* I2C_MESTRIA_H */