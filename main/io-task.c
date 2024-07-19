#include "io-task.h"

bool estado_rele_1 = 0;
bool estado_rele_2 = 0;

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

}