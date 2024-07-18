idf_component_register( SRCS "flash-mestria.c"
                        PRIV_REQUIRES nvs_flash vfs driver
                        INCLUDE_DIRS "./include")
