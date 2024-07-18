
//? ===================================== HEADERS ========================================
#include "flash-mestria.h"

//? ================================ VARIÁVEIS GLOBAIS ===================================

// Mutex de acesso à memória flash
SemaphoreHandle_t flash_mutex;

//? ===================================== LEITURA ========================================

/**
 * @brief Lê uma variável int8_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_int8_variables(char *storage, char *commit, int8_t *number) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Lê o valor associado à chave no espaço de armazenamento definido
			nvs_get_i8(my_handle, commit, number);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Lê uma variável uint8_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_uint8_variables(char *storage, char *commit, uint8_t *number) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Lê o valor associado à chave no espaço de armazenamento definido
			nvs_get_u8(my_handle, commit, number);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Lê uma variável int16_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_int16_variables(char *storage, char *commit, int16_t *number) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Lê o valor associado à chave no espaço de armazenamento definido
			nvs_get_i16(my_handle, commit, number);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Lê uma variável uint16_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_uint16_variables(char *storage, char *commit, uint16_t *number) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Lê o valor associado à chave no espaço de armazenamento definido
			nvs_get_u16(my_handle, commit, number);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Lê uma variável int32_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_int32_variables(char *storage, char *commit, int32_t *number) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Lê o valor associado à chave no espaço de armazenamento definido
			nvs_get_i32(my_handle, commit, number);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Lê uma variável uint32_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_uint32_variables(char *storage, char *commit, uint32_t *number) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Lê o valor associado à chave no espaço de armazenamento definido
			nvs_get_u32(my_handle, commit, number);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Lê uma variável int64_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_int64_variables(char *storage, char *commit, int64_t *number) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Lê o valor associado à chave no espaço de armazenamento definido
			nvs_get_i64(my_handle, commit, number);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Lê uma variável uint64_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit Nome da variável utilizada
 * @param number Ponteiro da variável onde o valor será retornado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t read_uint64_variables(char *storage, char *commit, uint64_t *number) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Lê o valor associado à chave no espaço de armazenamento definido
			nvs_get_u64(my_handle, commit, number);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

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
esp_err_t read_str_variables(char *storage, char *commit, char *string_to_save, size_t *string_length) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Lê o valor associado à chave no espaço de armazenamento definido
			nvs_get_str(my_handle, commit, string_to_save, string_length);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

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
esp_err_t read_blob_variables(char *storage, char *commit, void *value_to_save, size_t *value_length) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Lê o valor associado à chave no espaço de armazenamento definido
			nvs_get_blob(my_handle, commit, value_to_save, value_length);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

//? ===================================== ESCRITA ========================================

/**
 * @brief Salva uma variável int8_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_int8_variables(char *storage, int8_t number_to_save, char *commit) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Escreve o valor no espaço de armazenamento definido
			nvs_set_i8(my_handle, commit, number_to_save);

			// Confirma as alterações feitas na partição NVS
			nvs_commit(my_handle);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Salva uma variável uint8_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_uint8_variables(char *storage, uint8_t number_to_save, char *commit) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Escreve o valor no espaço de armazenamento definido
			nvs_set_u8(my_handle, commit, number_to_save);

			// Confirma as alterações feitas na partição NVS
			nvs_commit(my_handle);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Salva uma variável int16_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_int16_variables(char *storage, int16_t number_to_save, char *commit) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Escreve o valor no espaço de armazenamento definido
			nvs_set_i16(my_handle, commit, number_to_save);

			// Confirma as alterações feitas na partição NVS
			nvs_commit(my_handle);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Salva uma variável uint16_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_uint16_variables(char *storage, uint16_t number_to_save, char *commit) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Escreve o valor no espaço de armazenamento definido
			nvs_set_u16(my_handle, commit, number_to_save);

			// Confirma as alterações feitas na partição NVS
			nvs_commit(my_handle);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Salva uma variável int32_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_int32_variables(char *storage, int32_t number_to_save, char *commit) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Escreve o valor no espaço de armazenamento definido
			nvs_set_i32(my_handle, commit, number_to_save);

			// Confirma as alterações feitas na partição NVS
			nvs_commit(my_handle);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Salva uma variável uint32_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_uint32_variables(char *storage, uint32_t number_to_save, char *commit) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Escreve o valor no espaço de armazenamento definido
			nvs_set_u32(my_handle, commit, number_to_save);

			// Confirma as alterações feitas na partição NVS
			nvs_commit(my_handle);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Salva uma variável int64_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_int64_variables(char *storage, int64_t number_to_save, char *commit) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Escreve o valor no espaço de armazenamento definido
			nvs_set_i64(my_handle, commit, number_to_save);

			// Confirma as alterações feitas na partição NVS
			nvs_commit(my_handle);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Salva uma variável uint64_t na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param number Valor a ser salvo
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_uint64_variables(char *storage, uint64_t number_to_save, char *commit) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Escreve o valor no espaço de armazenamento definido
			nvs_set_u64(my_handle, commit, number_to_save);

			// Confirma as alterações feitas na partição NVS
			nvs_commit(my_handle);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Salva uma string na memória flash
 *
 * @param storage Nome do armazenamento utilizado
 * @param str_to_save String a ser salva
 * @param commit Nome da variável utilizada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t write_str_variables(char *storage, char *str_to_save, char *commit) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Escreve o valor no espaço de armazenamento definido
			nvs_set_str(my_handle, commit, str_to_save);

			// Confirma as alterações feitas na partição NVS
			nvs_commit(my_handle);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

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
esp_err_t write_blob_variables(char *storage, uint8_t *value_to_save, char *commit, size_t value_length) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Escreve o valor no espaço de armazenamento definido
			nvs_set_blob(my_handle, commit, value_to_save, value_length);

			// Confirma as alterações feitas na partição NVS
			nvs_commit(my_handle);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

//? ================================= INICIALIZAÇÕES =====================================

/**
 * @brief Limpa todos os dados em uma partição NVS
 *
 * @param storage Nome do armazenamento utilizado
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t clear_namespace(char *storage) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Apaga todos os dados na partição NVS
			nvs_erase_all(my_handle);

			// Confirma as alterações feitas na partição NVS
			nvs_commit(my_handle);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Apaga um item específico em uma partição NVS
 *
 * @param storage Nome do armazenamento utilizado
 * @param commit_to_delete Variável a ser apagada
 *
 * @return (esp_err_t) Resultado da tentativa de leitura
*/
esp_err_t erase_commit(char *storage, char *commit_to_delete) {
	// Obtem mutex para acessar a memória flash
	if(xSemaphoreTake(flash_mutex, portMAX_DELAY) == pdTRUE) {
		// Inicializa o subsistema NVS
		nvs_flash_init();

		// Declaração do handle usado para a partição NVS
		nvs_handle my_handle;

		// Abre a partição NVS em modo leitura e escrita
		esp_err_t err = nvs_open(storage, NVS_READWRITE, &my_handle);

		// Verifica se a abertura da partição NVS foi bem-sucedida
		if(err == ESP_OK) {
			// Apaga a variável armazenada na partição NVS
			nvs_erase_key(my_handle, commit_to_delete);

			// Confirma as alterações feitas na partição NVS
			nvs_commit(my_handle);
		}

		// Fecha a partição NVS
		nvs_close(my_handle);

		// Libera o mutex de acesso à flash
		xSemaphoreGive(flash_mutex);

		// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
		return err;
	}

	// Não conseguiu obter o mutex de acesso à flash
	return ESP_FAIL;
}

/**
 * @brief Inicializa o subsistema de NVS
 *
 * @param None
 *
 * @return None
*/
void initialize_flash(void) {
	// Cria o mutex para acessar a memória flash
	flash_mutex = xSemaphoreCreateMutex();

	// Inicializa o subsistema de NVS
	esp_err_t err = nvs_flash_init();

	// Verifica se não há mais espaços disponíveis na flash
	if(err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		// A partição NVS foi truncada e precisa ser apagada
		ESP_ERROR_CHECK(nvs_flash_erase()); // Apaga a partição NVS
		err = nvs_flash_init(); // Inicializa a NVS novamente
	}

	// Verifica se ocorreu algum erro durante a inicialização do subsistema flash NVS
	ESP_ERROR_CHECK(err);
}