//? ===================================== HEADERS ========================================
#include "debug-colors.h"
#include "soc/soc_memory_layout.h"

//? ===================================== FUNÇÕES ========================================

/**
 * @brief Converte o tempo de execução em timestamp
 *
 * @param None
 *
 * @return Buffer com a string do timestamp
*/
char *str_esp_timestap(void) {
	// Buffer para armazenar o timestamp
	static char buffer[18] = {0};

	// Variável de trava para proteger o acesso ao buffer em ambientes concorrentes
	static _lock_t bufferLock = 0;

	// Verifica se o gerenciador de tarefas ainda não foi iniciado
	if(xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED) {
		// Obtém o timestamp inicial durante a inicialização
		uint32_t timestamp = esp_log_early_timestamp();

		// Loop para preencher o buffer com dígitos do timestamp
		for(uint8_t i = 0; i < sizeof(buffer); i++) {
			if((timestamp > 0) || (i == 0)) {
				// Move os dígitos para a direita no buffer
				for(uint8_t j = sizeof(buffer) - 1; j > 0; j--) {
					buffer[j] = buffer[j - 1];
				}

				// Adiciona o dígito menos significativo ao início do buffer
				buffer[0] = (char)(timestamp % 10) + '0';
				timestamp /= 10;
			}
			else {
				// Preenche o restante do buffer com zeros e sai do loop
				buffer[i] = 0;
				break;
			}
		}
		// Retorna o buffer com o timestamp
		return buffer;
	}
	else {
		// Se o gerenciador de tarefas estiver iniciado, obtém o timestamp atual
		struct timeval tv;
		struct tm timeinfo;

		gettimeofday(&tv, NULL);
		localtime_r(&tv.tv_sec, &timeinfo);

		// Adquire a trava para proteger o acesso ao buffer durante a formatação
		_lock_acquire(&bufferLock);
		// Formata o timestamp no formato HH:MM:SS.sss
		snprintf(buffer, sizeof(buffer),
		         "%02d:%02d:%02d.%03ld",
		         timeinfo.tm_hour,
		         timeinfo.tm_min,
		         timeinfo.tm_sec,
		         tv.tv_usec / 1000);
		// Libera a trava após a formatação
		_lock_release(&bufferLock);

		// Retorna o buffer com o timestamp formatado
		return buffer;
	}
}

/**
 * @brief Exibe um log com o conteúdo de um buffer em formato hexadecimal
 *
 * @param tag Tag a ser exibida no log
 * @param buffer Buffer que se deseja exibir
 * @param buff_len Tamanho do buffer
 * @param color Cor do log
 *
 * @return None
*/
void array_log_buffer_hex_internal(const char *tag, const void *buffer, uint16_t buff_len, const char *color) {
	// Verifica se o comprimento do buffer é zero, e se for, retorna sem fazer nada
	if(buff_len == 0)
		return;

	// Buffer temporário para lidar com casos em que o acesso não é feito byte a byte
	char temp_buffer[16 + 3];
	// Buffer para armazenar a representação hexadecimal do conteúdo
	char hex_buffer[3 * 16 + 1];
	// Ponteiro para a linha atual no buffer
	const char *ptr_line;
	// Número de bytes a serem processados na linha atual
	int bytes_cur_line;

	do {
		// Define o número de bytes a serem processados na linha atual (máximo de 16)
		if(buff_len > 16) {
			bytes_cur_line = 16;
		}
		else {
			bytes_cur_line = buff_len;
		}

		// Verifica se o buffer não é acessível por byte
		if(!esp_ptr_byte_accessible(buffer)) {
			// Usa memcpy para contornar problemas de alinhamento
			memcpy(temp_buffer, buffer, (bytes_cur_line + 3) / 4 * 4);
			// Atualiza o ponteiro para a linha para o buffer temporário
			ptr_line = temp_buffer;
		}
		else {
			// O buffer é acessível por byte, então o ponteiro para a linha permanece o mesmo
			ptr_line = buffer;
		}

		// Converte os bytes da linha atual para a representação hexadecimal e armazena no hex_buffer
		for(int i = 0; i < bytes_cur_line; i++) {
			sprintf(hex_buffer + 3 * i, "%02x ", ptr_line[i]);
		}

		// Imprime a linha formatada no log
		PRINT_LOG(tag, hex_buffer, color);

		// Atualiza o ponteiro para o buffer e o comprimento restante
		buffer += bytes_cur_line;
		buff_len -= bytes_cur_line;

	} while(buff_len);
}