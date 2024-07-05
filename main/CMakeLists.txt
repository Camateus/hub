idf_component_register(SRCS "main.c"
                            "sensor-task.c"

                    # ---
                    REQUIRES bme280
                             
                    
                    INCLUDE_DIRS "./include")
