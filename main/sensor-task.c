#include "sensor-task.h"

TaskHandle_t bme_280_task_handle;

static void bme_280_task(void *) {
	while(1) {
		bmx280_t *bmx280 = bmx280_create(I2C_NUM_0);

		if(!bmx280) {
			ESP_LOGE("test", "Could not create bmx280 driver.");
			return;
		}

		ESP_ERROR_CHECK(bmx280_init(bmx280));

		bmx280_config_t bmx_cfg = BMX280_DEFAULT_CONFIG;
		ESP_ERROR_CHECK(bmx280_configure(bmx280, &bmx_cfg));

		while(1) {
			ESP_ERROR_CHECK(bmx280_setMode(bmx280, BMX280_MODE_FORCE));
			do {
				vTaskDelay(pdMS_TO_TICKS(1));
			} while(bmx280_isSampling(bmx280));

			float temp = 0, pres = 0, hum = 0;
			ESP_ERROR_CHECK(bmx280_readoutFloat(bmx280, &temp, &pres, &hum));

			ESP_LOGI("test", "Read Values: temp = %0.2f, pres = %0.2f", temp, pres);
			vTaskDelay(pdMS_TO_TICKS(100));
		}

	}
}

void init_sensor() {
	i2c_config_t conf = {
		.mode = I2C_MODE_MASTER, // Modo (master ou slave)
		.sda_io_num = I2C_MASTER_SDA_IO, // Pino utilizado para o sinal SDA
		.sda_pullup_en = GPIO_PULLUP_ENABLE, // Modo do pullup interno do pino de SDA
		.scl_io_num = I2C_MASTER_SCL_IO, // Pino utilizado para o sinal SCL
		.scl_pullup_en = GPIO_PULLUP_ENABLE, // Modo do pullup interno do pino de SCL
		.master.clk_speed = 1000000, // Frequência do clock utilizada
	};

	i2c_master_init(conf, I2C_NUM_0);


	// Criação da task de leitura dos pinos de entrada
	esp_err_t bme_280_init_error = xTaskCreatePinnedToCore(bme_280_task, // Função que implementa a task
	                                                       "bme_280_task", // Nome da task
	                                                       48000, // Tamanho da memória stack
	                                                       NULL, // Parâmetros de entrada da função
	                                                       5, // Prioridade da task
	                                                       &bme_280_task_handle, // Handle da task
	                                                       0); // Núcleo onde a task será executada

	if(bme_280_init_error != pdTRUE) {
		LOG_RED(__func__, "Erro ao criar a task de envio da telemetria");
		esp_restart();
	}
}