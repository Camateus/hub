idf_component_register(SRCS "main.c"
                            "sensor-task.c"

                    # ---
                    REQUIRES bmx280
                             debug-colors
                             driver
                             i2c-mestria
                    
                             
                    
                    INCLUDE_DIRS "./include")
