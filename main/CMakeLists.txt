idf_component_register(SRCS "main.c"
			    "ble-task.c"
                            "flash-memory-task.c"
                            "io-task.c"
                            "sensor-task.c"
                            "web-task.c"

                    # ---
                    REQUIRES bmx280
                             debug-colors
                             esp_http_server
                             bt
                             driver
                             gpio-mestria
                             i2c-mestria
                             flash-mestria
                             vfs
                             nvs_flash
                             esp_event
                 
                             
                    
                    INCLUDE_DIRS "./include"
                     /home/mestria/esp/esp-idf/components/freertos/FreeRTOS-Kernel-SMP/include/freertos)
