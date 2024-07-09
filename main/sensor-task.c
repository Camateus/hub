#include "sensor-task.h"

void init_sensor() {
    i2c_config_t conf = {
		.mode = I2C_MODE_MASTER, // Modo (master ou slave)
		.sda_io_num = I2C_MASTER_SDA_IO, // Pino utilizado para o sinal SDA
		.sda_pullup_en = GPIO_PULLUP_DISABLE, // Modo do pullup interno do pino de SDA
		.scl_io_num = I2C_MASTER_SCL_IO, // Pino utilizado para o sinal SCL
		.scl_pullup_en = GPIO_PULLUP_DISABLE, // Modo do pullup interno do pino de SCL
		.master.clk_speed = I2C_MASTER_FREQ_HZ, // Frequência do clock utilizada
	};

    i2c_master_init(conf, I2C_NUM_0);


	// Criação da task de leitura dos pinos de entrada
	esp_err_t telemetry_init_error = xTaskCreatePinnedToCore(send_telemetry_task, // Função que implementa a task
	                                                         "send_telemetry_task", // Nome da task
	                                                         48000, // Tamanho da memória stack
	                                                         NULL, // Parâmetros de entrada da função
	                                                         5, // Prioridade da task
	                                                         &send_rs232_task_handle, // Handle da task
	                                                         CORE0); // Núcleo onde a task será executada
	if(telemetry_init_error != pdTRUE) {
		LOG_RED(__func__, "Erro ao criar a task de envio da telemetria");
		esp_restart();
	}

    
}