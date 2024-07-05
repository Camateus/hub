//? ===================================== HEADERS ========================================

#include "i2c-mestria.h"

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
                                 uint8_t device_addr) {
	// Cria o handle de comandos I2C
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();

	// Adiciona a sequência de comandos para iniciar a comunicação I2C
	i2c_master_start(cmd);

	// Envia o endereço do dispositivo I2C com o bit de escrita
	i2c_master_write_byte(cmd, device_addr | BIT_TO_WRITE, true);
	// Envia o endereço do registrador no dispositivo I2C
	i2c_master_write_byte(cmd, i2c_register_addr, true);
	// Envia os dados a serem escritos no registrador do dispositivo I2C
	i2c_master_write(cmd, data_wr, size, true);

	// Adiciona a sequência de comandos para parar a comunicação I2C
	i2c_master_stop(cmd);

	// Executa a sequência de comandos I2C e aguarda o término por até 1000 ms
	esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);

	// Deleta o handle de comando I2C
	i2c_cmd_link_delete(cmd);

	// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
	return ret;
}

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
                                uint8_t i2c_register_addr, uint8_t device_addr) {

	// Cria o handle de comandos I2C
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();

	// Adiciona a sequência de comandos para iniciar a comunicação I2C
	i2c_master_start(cmd);

	// Envia o endereço do dispositivo I2C com o bit de escrita
	i2c_master_write_byte(cmd, device_addr | BIT_TO_WRITE, true);
	// Envia o endereço do registrador no dispositivo I2C
	i2c_master_write_byte(cmd, i2c_register_addr, true);

	// Adiciona a sequência de comandos para reiniciar a comunicação I2C em modo de leitura
	i2c_master_start(cmd);

	// Envia o endereço do dispositivo I2C com o bit de leitura
	i2c_master_write_byte(cmd, device_addr | BIT_TO_READ, true);
	// Lê os dados do dispositivo I2C
	i2c_master_read(cmd, data_rd, size, I2C_MASTER_LAST_NACK);

	// Adiciona a sequência de comandos para parar a comunicação I2C
	i2c_master_stop(cmd);

	// Executa a sequência de comandos I2C e aguarda o término por até 1000 ms
	esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);

	// Deleta a alça de comando I2C
	i2c_cmd_link_delete(cmd);

	// Retorna o resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
	return ret;
}

//? ================================= INICIALIZAÇÕES =====================================

/**
 * @brief Inicializa o controlador do I2C como master
 *
 * @param conf            Configuração do controlador do I2C
 * @param i2c_master_port Porta do I2C a ser utilizada
 *
 * @return (esp_err_t) Resultado da operação (ESP_OK se bem-sucedido, código de erro caso contrário)
*/
esp_err_t i2c_master_init(i2c_config_t conf, i2c_port_t i2c_master_port) {
	// Configuração dos parâmetros do controlador mestre I2C
	i2c_param_config(i2c_master_port, &conf);

	// Instala o driver I2C mestre no controlador especificado
	return i2c_driver_install(i2c_master_port, // Porta do I2C a ser utilizada
	                          conf.mode, // Modo (master ou slave)
	                          I2C_MASTER_RX_BUF_DISABLE, // Tamanho do buffer de recebimento (apenas em slave)
	                          I2C_MASTER_TX_BUF_DISABLE,// Tamanho do buffer de envio (apenas em slave)
	                          0); // Flags alocados para interrupção
}