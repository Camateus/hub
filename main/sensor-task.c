#include "sensor-task.h"

bmx280_t *bmx280;

char *get_temp_press(void) {
	char *temper = (char *)malloc(10); // Aloca memória para a string de temperatura
	if(temper == NULL) {
		ESP_LOGE("sensor-task", "Memory allocation failed");
		return NULL;
	}

	ESP_ERROR_CHECK(bmx280_setMode(bmx280, BMX280_MODE_FORCE));
	do {
		vTaskDelay(pdMS_TO_TICKS(1));
	} while(bmx280_isSampling(bmx280));

	float temp = 0, pres = 0, hum = 0;
	ESP_ERROR_CHECK(bmx280_readoutFloat(bmx280, &temp, &pres, &hum));

	ESP_LOGI("sensor-task", "Read Values: temp = %0.2f, pres = %0.2f", temp, pres);
	sprintf(temper, "%0.2f", temp);

	return temper;
}

void init_sensor(void) {
	i2c_config_t conf = {
		.mode = I2C_MODE_MASTER,
		.sda_io_num = I2C_MASTER_SDA_IO,
		.sda_pullup_en = GPIO_PULLUP_ENABLE,
		.scl_io_num = I2C_MASTER_SCL_IO,
		.scl_pullup_en = GPIO_PULLUP_ENABLE,
		.master.clk_speed = I2C_MASTER_FREQ_HZ,
	};

	i2c_master_init(conf, I2C_NUM_0);

	bmx280 = bmx280_create(I2C_NUM_0);
	if(!bmx280) {
		ESP_LOGE("sensor-task", "Could not create bmx280 driver.");
		return;
	}

	ESP_ERROR_CHECK(bmx280_init(bmx280));

	bmx280_config_t bmx_cfg = BMX280_DEFAULT_CONFIG;
	ESP_ERROR_CHECK(bmx280_configure(bmx280, &bmx_cfg));
}
