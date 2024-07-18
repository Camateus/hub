//? ================================= HEADERS ================================ */

#include "flash-memory-task.h"

//? ============================ VARIÁVEIS GLOBAIS =========================== */


//? ================================= FUNÇÕES ================================ */
//* ============================= LEITURA ============================

/**
 * @brief Inicializa um valor padrão em caso de erro na leitura de uma variável.
 *
 * @param err O código de erro retornado pela operação de leitura.
 * @param clear_function A função a ser chamada para restaurar o valor padrão da variável.
 * @param key A chave identificadora da variável (usada para exibir na mensagem de erro).
 */
void init_value_on_error(esp_err_t err, esp_err_t (*clear_function)(void), const char *key) {
	// Verifica se houve erro na leitura da variável
	if(err != ESP_OK) {
		// Exibe mensagem de erro
		LOG_RED(__func__, "Erro ao ler %s: %s", key, esp_err_to_name(err));

		// Chama a função que salva o valor default da variável
		clear_function();
	}
}

/**
 * @brief Lê as variáveis de informações gerais armazenadas na memória flash.
 *
 * @return O código de erro resultante da leitura das variáveis. ESP_OK em caso de sucesso.
 */
esp_err_t read_general_info_variables(void) {
	// Erro a ser retornado pela função, ele é atualizado caso o erro retornado em cada gravação de variável seja diferente de ESP_OK
	esp_err_t err = ESP_OK;
	// --------------------

	// // Lê o número de série do equipamento
	// init_value_on_error(read_uint16_variables("variables", // Partição da flash onde ler a variável
	//                                           "type_number", // Nome da variável na flash
	//                                           &type_transmissor), // Variável onde armazenar a leitura
	//                     clear_type_on_flash, // Função a ser chamada caso a leitura falhe
	//                     "tipo do equipamento"); // Nome a ser exibido na mensagem de erro

	// --------------------

	// Exibe os valores no terminal
	LOG_GREEN(__func__, "***********************************************");
	LOG_GREEN(__func__, "Valores lidos corretamente na flash:");
	// LOG_GREEN(__func__, "  - Numero de Serie:\tMES-%3d", id_transmissor);
	LOG_GREEN(__func__, "***********************************************\n");

	// --------------------

	return err;
}

//? ================================ Escrita ================================

//? ================================= APAGAR =================================

//? ============================= INICIALIZAÇÕES =============================
/**
 * @brief Inicializa a memória flash, lê as variáveis de configuração geral e exibe mensagens de log.
 *
 * @param None
 * @return None
 */
void init_flash_memory(void) {
	LOG_PURPLE(__func__, "\n================================== MEMORIA FLASH =====================================");
	printf("\n");

	// --------------------

	// Inicializa a memória flash
	initialize_flash();

	// --------------------

	// Lê variáveis referente à configuração geral
	read_general_info_variables();

	LOG_GREEN(__func__, "Terminou de configurar a memoria flash\n");
}