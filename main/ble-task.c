//? ====================================== HEADERS ====================================== /
#include "ble-task.h"
#include "esp_nimble_hci.h"
#include "esp_phy_init.h"

//? ============================ VARIAVEIS GLOBAIS =========================== */
// Handle de conexão BLE

extern TaskHandle_t receive_task_handle;

// Tipo de endereço BLE
static ble_addr_type_t ble_addr_type;

conn_handle_t conn_handle;

// Flag para indicar se o Bluetooth está ligado
static flag_t ble_ligado = false;

// Timer para armazenar o tempo que recebeu a útlima mensagem no Bluetooth
static timeout_t ultima_msg_ble_time = 0;

bool dispositivo_conectado = 0;
//? ========================== DECLARAÇÃO DE FUNÇÕES ========================= */

/**
 * @brief Inicia o advertising do BLE. Configura os parâmetros como o nome do dispositivo
 * e os modos de conectividade. Após configurar os parâmetros, inicia o advertising.
 *
 * @param None
 *
 * @return None
 */
static void ble_app_advertise(void);

/**
 * @brief Inicializa o BLE, com seus serviços e características
 *
 * @param None
 *
 * @return None
 */
void init_ble_communication(void);

//? ================================= FUNÇÕES ================================ */

/**
 * @brief Obtém o valor da conexão atual
 *
 * @param None
 *
 * @return (conn_handle_t) Handle da conexão
 */
conn_handle_t get_conn_handle(void) {
	return conn_handle;
}

/**
 * @brief Obtém o estado atual da flag que indica se o BLE está ligado.
 *
 * @return O valor da flag `ble_ligado`.
 */
flag_t get_ble_ligado(void) {
	return ble_ligado;
}

//? =========================== CALLBACKS - CARACTERISTICAS ==============================/

/**
 * @brief Trata a leitura e a escrita da característica do Tempo de envio do central no BLE
 *
 * @param conn_handle  Handle da conexão
 * @param attr_handle  Handle do atributo acessado recebido
 * @param ctxt         Dados relativos à comunicação
 * @param arg          Argumentos adicionais - não usados nesta função
 *
 * @return (int) 0 para indicar sucesso.
 */
static int read_write_tempo_envio_rastreador(uint16_t conn_handle,
                                             uint16_t attr_handle,
                                             struct ble_gatt_access_ctxt *ctxt,
                                             void *arg) {

	// Verifica se recebeu um request para leitura da característica
	if(ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR) {
		time_envio_t tempo_local = get_send_time_central();

		// Preenche o buffer de resposta com os dados desejados
		os_mbuf_append(ctxt->om, (const void *)&tempo_local, sizeof(uint16_t));

		LOG_PURPLE("BLE - Leitura", "Tempo de envio do central -> %d", tempo_local);


	} // Verifica se recebeu um novo valor para a característica
	else if(ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {

		// Verifica se o dado recebido cabe na variável desejada
		if(ctxt->om->om_len == sizeof(time_envio_t)) {

			// Variável auxiliar para armazenar o valor recebido
			time_envio_t time_aux = 0;

			// Copia o conteúdo do array recebido (little-endian) em número inteiro
			memcpy(&time_aux, ctxt->om->om_data, ctxt->om->om_len);

			if(time_aux > 15) {
				// Define o novo valor do tempo de envio
				save_time_on_flash(time_aux);

				// Verifica se a flag de debug está habilitada
				LOG_CYAN("BLE - Escrita", "Tempo de envio do central -> %d", time_aux);

			}
			else {
				// Verifica se a flag de debug está habilitada
				LOG_CYAN("BLE - Escrita", "Tempo deve ter mais que 15 minutos");

			}


		}
	}
	// Atualiza o tempo da última interação pelo Bluetooth
	ultima_msg_ble_time = esp_timer_get_time();

	// Retorna 0 para indicar sucesso.
	return 0;
}

//? ==================================== SERVIÇOS ========================================

// Serviços e características GATT do BLE do dispositivo
static const struct ble_gatt_svc_def gatt_svcs[] = {
	{
		// Serviço Primário
		.type = BLE_GATT_SVC_TYPE_PRIMARY,
		.uuid = BLE_UUID16_DECLARE(0xA100), // Define o UUID do serviço
		// Características do serviço primário
		.characteristics = (struct ble_gatt_chr_def[]) {
			{
				//* --------- Característica 1 - Tempo de envio do central
				.uuid = BLE_UUID16_DECLARE(0xA101), // Define o UUID da característica
				.flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_WRITE, // Modo da cacterística
				.access_cb = read_write_tempo_envio_rastreador // Callback para enviar dado

			},
			// Terminador do array de características
			{0}
		}

	},
	// Terminador do array de serviços GATT
	{0}
};

//? ================================= EVENTOS ================================ */

/**
 * @brief Função chamada para tratar eventos relacionados ao GAP (Generic Access Profile)
 * do BLE. Trata eventos de conexão, desconexão e eventos de conclusão de advertising.
 *
 * @param event Evento ocorrido
 * @param arg   Argumentos adicionais opcionais
 *
 * @return (int) 0 para indicar sucesso no tratamento do evento.
 */
static int ble_gap_event(struct ble_gap_event *event, void *arg) {
	// Verifica o evento recebido
	switch(event->type) {
		// Evento de conexão
		case BLE_GAP_EVENT_CONNECT: {
				LOG_YELLOW(__func__, "BLE - Evento de Conexao: %s", event->connect.status == 0 ? "OK!" : "FAILED!");
				dispositivo_conectado = 1;

				// Armazena o handle da conexão
				conn_handle = event->connect.conn_handle;

				// Se a conexão não foi bem sucedida, reinicia o advertising
				if(event->connect.status != 0) {
					ble_app_advertise();
				}
				break;
			}
		// Evento de desconexão
		case BLE_GAP_EVENT_DISCONNECT: {
				LOG_YELLOW(__func__, "BLE - Evento de Desconexao");
				dispositivo_conectado = 0;
				// Volta o handle da conexão para um valor padrão, indicando que não há dispositivos conectados
				conn_handle = CONN_HANDLE_DEFAULT;

				// Verifica se o Bluetooth está ligado para começar o advertising
				if(ble_ligado) {
					// Verifica se o dispostivo realmente desconectou e reinicia o advertising
					if(event->connect.status != 0) {
						ble_app_advertise();
					}
				}
				break;

			}
		// Finalizou o processo de advertising
		case BLE_GAP_EVENT_ADV_COMPLETE: {
				LOG_RED(__func__, "BLE - Evento de fim de advertising");

				// Reinicia o advertising
				ble_app_advertise();
				break;
			}
		//Evento desconhecido
		default: {
				break;
			}
			// Indica que o tratamento de eventos ocorreu corretamente
	}
	return 0;
}

//? ================================== TASKS ================================= */

/**
 * @brief Tarefa responsável pela execução contínua do NimBLE.
 *
 * @param None
 *
 * @return None
 */
static void host_task(void *) {
	// Execução do NimBLE, verificando eventos
	nimble_port_run();
}

//? ============================= INICIALIZAÇÕES ============================= */

/**
 * @brief Inicia o advertising do BLE. Configura os parâmetros como o nome do dispositivo
 * e os modos de conectividade. Após configurar os parâmetros, inicia o advertising.
 *
 * @param None
 *
 * @return None
 */
static void ble_app_advertise(void) {
	// Dados exibidos no advertising do BLE
	struct ble_hs_adv_fields fields;

	// Limpeza da memória dos dados
	memset(&fields, 0, sizeof(fields));

	// Obtém o nome do dispositivo
	const char *device_name = ble_svc_gap_device_name();

	// Preenche o campo com o nome
	fields.name = (uint8_t *)device_name;
	fields.name_len = strlen(device_name);
	fields.name_is_complete = 1;
	fields.flags = 0xAB; // Flag para indicar que é um produto do tipo IoT Cargo

	// Configuração dos campos de avertising
	ble_gap_adv_set_fields(&fields);

	// --------------------

	// Configuração dos parâmetros de avertising
	struct ble_gap_adv_params adv_params;

	// Limpeza da memória dos dados
	memset(&adv_params, 0, sizeof(adv_params));

	// Modo conectável
	adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
	// Modo descobrível
	adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;

	// --------------------

	// Inicia o avertising com os parâmetros configurados
	ble_gap_adv_start(ble_addr_type, // O tipo de endereço usado pelo BLE
	                  NULL, // O endereço do peer para advertising direta
	                  BLE_HS_FOREVER, // Duração do procedimento de advertising em milissegundos
	                  &adv_params, // Especificidades do procedimento de advertising
	                  ble_gap_event, // Função de callback para tratar os eventos do BLE
	                  NULL); // Argumentos passados para a função de callback
}

/**
 * @brief Callback chamado quando configuração do BLE acabar.
 * Determina o melhor tipo de endereço e inicia o avertising.
 *
 * @param None
 *
 * @return None
 */
static void ble_app_on_sync(void) {
	// Determina automaticamente o melhor tipo de endereço
	ble_hs_id_infer_auto(0, &ble_addr_type);

	// Inicia o advertising
	ble_app_advertise();
}

/**
 * @brief Para o advertising, desconecta do dispositivo atual e desativa o Bluetooth
 *
 * @param None
 *
 * @return None
 */
void stop_ble(void) {
	// Altera a flag que indica se o Bluetooth está ligado
	ble_ligado = false;

	// Finaliza o advertising
	ble_gap_adv_stop();

	// Verifica se está conectado antes de desligar o BLE
	if(get_conn_handle() != CONN_HANDLE_DEFAULT) {
		// Desconecta do dispositivo
		ble_gap_terminate(get_conn_handle(), BLE_ERR_REM_USER_CONN_TERM);
	}

	vTaskDelay(pdMS_TO_TICKS(3000));

	// Verifica se o host do BLE está ativo
	if(ble_hs_is_enabled()) {
		// Desativa o nimBLE
		ble_hs_deinit();
	}

	nimble_port_freertos_deinit();

	LOG_BROWN(__func__, "Desligou o BLE");
}

/**
 * @brief Ativa o Bluetooth e recomeça o advertising
 *
 * @param None
 *
 * @return None
 */
void reinit_ble(void) {
	// Inicializa o serviço GAP que gerencia a visibilidade e a conexão do dispositivo
	ble_svc_gap_init();

	// Inicializa o serviço GATT que gerencia as características do dispositivo
	ble_svc_gatt_init();

	// Configura os serviços GATT
	ble_gatts_count_cfg(gatt_svcs);

	// Adiciona os serviços configurados acima
	ble_gatts_add_svcs(gatt_svcs);

	// --------------------

	// Determina automaticamente o melhor tipo de endereço
	ble_hs_id_infer_auto(0, &ble_addr_type);

	// --------------------

	// Ativa o nimBLE
	ble_hs_init();

	// --------------------

	// Inicializa o NimBLE no FreeRTOS, com a task para gerenciar o BLE
	nimble_port_freertos_init(host_task);

	// Inicia o advertising
	ble_app_advertise();

	// Atualiza o tempo da última interação pelo Bluetooth
	ultima_msg_ble_time = esp_timer_get_time();

	// Altera a flag
	ble_ligado = true;

	LOG_GREEN(__func__, "Religou o BLE");
}

/**
 * @brief Inicializa o BLE, com seus serviços e características
 *
 * @param None
 *
 * @return None
 */
void init_ble_communication(void) {
	LOG_PURPLE(__func__, "\n=================================== BLE CONFIG =======================================");
	printf("\n");
	ble_ligado = false;

	esp_phy_erase_cal_data_in_nvs();

	// Inicializa o NVS flash (Non-Volatile Storage)
	nvs_flash_init();

	// --------------------

	// Inicializa o protocolo NimBLE
	nimble_port_init();

	// --------------------

	// String para armazenar o tempo de envio do equipamento para exibir no Bluetooth
	char num_serie[TAM_MAX_NUM_SERIE] = {};
	sprintf(num_serie, "MES-CENT.");

	// Define o nome do dispositivo no serviço GAP
	ble_svc_gap_device_name_set((const char *)num_serie);

	// Inicializa o serviço GAP que gerencia a visibilidade e a conexão do dispositivo
	ble_svc_gap_init();

	// Inicializa o serviço GATT que gerencia as características do dispositivo
	ble_svc_gatt_init();

	// --------------------

	// Configura os serviços GATT
	ble_gatts_count_cfg(gatt_svcs);

	// Adiciona os serviços configurados acima
	ble_gatts_add_svcs(gatt_svcs);

	// --------------------

	// Definição do callback chamado quando a configuração BLE acabar
	ble_hs_cfg.sync_cb = ble_app_on_sync;

	// --------------------

	// Inicializa o NimBLE no FreeRTOS, com a task para gerenciar o BLE
	nimble_port_freertos_init(host_task);

	// --------------------

	// Altera a flag
	ble_ligado = true;

	LOG_GREEN(__func__, "Terminou de configurar o BLE \n");
}
