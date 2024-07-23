#include "sensor-task.h"

bmx280_t *bmx280;

char get_temp_press(void) {
	char temper[10];

	ESP_ERROR_CHECK(bmx280_setMode(bmx280, BMX280_MODE_FORCE));
	do {
		vTaskDelay(pdMS_TO_TICKS(1));
	} while(bmx280_isSampling(bmx280));

	float temp = 0, pres = 0, hum = 0;
	ESP_ERROR_CHECK(bmx280_readoutFloat(bmx280, &temp, &pres, &hum));

	ESP_LOGI("test", "Read Values: temp = %d, pres = %0.2f", (uint8_t)temp, pres);
	vTaskDelay(pdMS_TO_TICKS(100));
	sprintf(temper, "%d", (uint8_t)temp);
	return temper;
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

	bmx280 = bmx280_create(I2C_NUM_0);

	if(!bmx280) {
		ESP_LOGE("test", "Could not create bmx280 driver.");
		return;
	}

	ESP_ERROR_CHECK(bmx280_init(bmx280));

	bmx280_config_t bmx_cfg = BMX280_DEFAULT_CONFIG;
	ESP_ERROR_CHECK(bmx280_configure(bmx280, &bmx_cfg));

}