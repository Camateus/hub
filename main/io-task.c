#include "io-task.h"

bool estado_rele_1 = 1;
bool estado_rele_2 = 1;

void inverte_rele_1() {
	estado_rele_1 = !estado_rele_1;
	gpio_digital_write(rele1, estado_rele_1);
}

void inverte_rele_2() {
	estado_rele_2 = !estado_rele_2;
	gpio_digital_write(rele2, estado_rele_2);
}

void init_config_pins() {
	gpio_configuration(GPIO_INTR_DISABLE,
	                   GPIO_MODE_OUTPUT,
	                   RELAY_BITMASK,
	                   GPIO_PULLUP_DISABLE);
	gpio_digital_write(rele1, estado_rele_1);
	gpio_digital_write(rele2, estado_rele_2);
}