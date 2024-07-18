#ifndef BLE_TASK_H
#define BLE_TASK_H

//? ====================================== HEADERS ===================================== */

// Bibliotecas nativas do C
#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include <math.h>
#include <string.h>

// Bibliotecas locais do esp
#include "esp_err.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_nimble_hci.h"
#include "freertos/event_groups.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "host/ble_hs.h"
#include "modlog/modlog.h"
#include "nimble/ble.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
// #include "sdkconfig.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include "sensor-task.h"
#include "nvs_flash.h"

//? =================================== CONSTANTES =======================================

typedef uint16_t time_envio_t;

#define TAM_MAX_NUM_SERIE 5

/**
 * @brief Tempo (em microssegundos) sem interação via Bluetooth para que ele seja desligado
*/
#define TEMPO_DESLIGA_BLE (300*1000000) // 300 seg = 5 minutos

/**
 * @brief Tempo (em microssegundos) que o botão externo ou o farolete devem permanecer ligados para religar o Bluetooth
*/
#define TEMPO_BOTAO_PRESSIONADO (3*1000000) // 3 segundos

/**
 * @brief Handle padrão para indicar que não dispositivos conectados
*/
#define CONN_HANDLE_DEFAULT 100

/**
 * @brief Número de caracteres do nome no Bluetooth
 */
#define TAM_MAX_ADV_NAME 10 // "Portal-tx" ou "ABC1D34"

/**
 * @brief Tamanho do pacote com as informações do RTC
 */
#define TAM_PACOTE_RTC 6

/**
 * @brief Tamanho do pacote com as informações dos horarios de envio de pacote
 */
#define TAM_PACOTE_CHECK_TIME 6

//? ==================================== VARIÁVEIS =======================================

/**
 * @brief Tipo de endereço do BLE
*/
typedef uint8_t ble_addr_type_t;

/**
 * @brief Handle de canal de notificação do BLE
*/
typedef uint16_t notify_handle_t;

/**
 * @brief Handle da conexão BLE
*/
typedef uint16_t conn_handle_t;

/**
 * @brief Estrutura do buffer com o dado a ser enviado na notificação do BLE
*/
typedef struct os_mbuf ble_buffer_t;

/**
 * @brief Tipo de variável para representar timers de debounce
*/
typedef uint64_t timeout_t;

/**
 * @brief Ações a serem tomadas com os registros recebidas pelo BLE
 *
 */
typedef enum {
	IDLE_REGISTROS_BLE = 0x0, // Não faz nada
	LIMPA_REGISTROS_BLE = 0x01, // Limpa os registros
	CRIA_REGISTROS_BLE = 0x10, // Gera uma quantidade MAX_REGISTERS de registros
} ble_log_action_t;

//? ===================================== FUNÇÕES ========================================

/**
 * @brief Obtém o valor da conexão atual
 *
 * @param None
 *
 * @return (conn_handle_t) Handle da conexão
 */
conn_handle_t get_conn_handle(void);

/**
 * @brief Para o advertising, desconecta do dispositivo atual e desativa o Bluetooth
 *
 * @param None
 *
 * @return None
 */
void stop_ble(void);

/**
 * @brief Ativa o Bluetooth e recomeça o advertising
 *
 * @param None
 *
 * @return None
 */
void reinit_ble(void);

/**
 * @brief Verifica as condições para colocar o chip em modo de deep-sleep
 *
 * @param None
 *
 * @return None
 */
void check_ble_to_sleep(void);

/**
 * @brief Inicializa o BLE, com seus serviços e características
 *
 * @param None
 *
 * @return None
 */
void init_ble_communication(void);

bool get_ble_ligado(void);

#endif /* BLE_TASK_H */
