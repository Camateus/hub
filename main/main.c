// Token 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

#include <stdio.h>
#include "sensor-task.h"
#include "flash-memory-task.h"
#include "ble-task.h"
#include "io-task.h"

void app_main(void) {
	init_flash_memory();

	init_config_pins();

	init_sensor();

	init_ble_communication();

}
