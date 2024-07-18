idf_component_register(SRCS "main.c"
			    "ble-task.c"
                            "flash-memory-task.c"
                            "sensor-task.c"

                    # ---
                    REQUIRES bmx280
                             debug-colors
                             bt
                             driver
                             i2c-mestria
                             flash-mestria
                             vfs
                             nvs_flash
                 
                             
                    
                    INCLUDE_DIRS "./include")
