// Definição para evitar repetição do arquivo
#ifndef DEBUG_COLORS_H
#define DEBUG_COLORS_H

// ?================================= HEADERS =================================

// Bibliotecas nativas do C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>
// Bibliotecas locais do esp
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_vfs.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//? ====================================== CORES =========================================

// Códigos de cada cor definida
#define PRINT_COLOR_BLACK  "30"
#define PRINT_COLOR_RED    "31"
#define PRINT_COLOR_GREEN  "32"
#define PRINT_COLOR_BROWN  "33"
#define PRINT_COLOR_BLUE   "34"
#define PRINT_COLOR_PURPLE "35"
#define PRINT_COLOR_CYAN   "36"
#define PRINT_COLOR_YELLOW "33"
#define PRINT_COLOR_WHITE  "37"
#define PRINT_COLOR_ORANGE "38;5;208"
#define PRINT_COLOR(COLOR) "\033[0;" COLOR "m"
#define PRINT_RESET_COLOR  "\033[0m"
#define PRINT_BOLD         "\e[1m"

// Conversão do código das cores para caractere especial
#define COLOR_BLACK  PRINT_COLOR(PRINT_COLOR_BLACK)
#define COLOR_RED    PRINT_COLOR(PRINT_COLOR_RED)
#define COLOR_GREEN  PRINT_COLOR(PRINT_COLOR_GREEN)
#define COLOR_BROWN  PRINT_COLOR(PRINT_COLOR_BROWN)
#define COLOR_BLUE   PRINT_COLOR(PRINT_COLOR_BLUE)
#define COLOR_PURPLE PRINT_COLOR(PRINT_COLOR_PURPLE)
#define COLOR_CYAN   PRINT_COLOR(PRINT_COLOR_CYAN)
#define COLOR_YELLOW PRINT_COLOR(PRINT_COLOR_YELLOW)
#define COLOR_WHITE  PRINT_COLOR(PRINT_COLOR_WHITE)
#define COLOR_ORANGE PRINT_COLOR(PRINT_COLOR_ORANGE)

//? =================================== CONSTANTES =======================================

// Funções genéricas para o log de um buffer de hexadecimal
#define PRINT_LOG(tag, text, color) printf("%sMES (%s) %s: %s\n" PRINT_RESET_COLOR, color, str_esp_timestap(), tag, text);
#define LOG_ARRAY(tag, buffer, buff_len, color) array_log_buffer_hex_internal(tag, buffer, buff_len, color);

// Logs coloridos
#define LOG_BLACK(tag, text, ...)  printf("%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_BLACK, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_RED(tag, text, ...)    printf("%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_RED, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_GREEN(tag, text, ...)  printf("%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_GREEN, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_BROWN(tag, text, ...)  printf("%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_BROWN, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_BLUE(tag, text, ...)   printf("%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_BLUE, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_PURPLE(tag, text, ...) printf("%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_PURPLE, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_CYAN(tag, text, ...)   printf("%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_CYAN, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_YELLOW(tag, text, ...) printf("%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_YELLOW, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_WHITE(tag, text, ...)  printf("%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_WHITE, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_ORANGE(tag, text, ...) printf("%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_ORANGE, str_esp_timestap(), tag, ##__VA_ARGS__)

// Logs coloridos em negrito
#define LOG_BLACK_BOLD(tag, text, ...)  printf("%s%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_BLACK, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_RED_BOLD(tag, text, ...)    printf("%s%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_RED, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_GREEN_BOLD(tag, text, ...)  printf("%s%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_GREEN, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_BROWN_BOLD(tag, text, ...)  printf("%s%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_BROWN, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_BLUE_BOLD(tag, text, ...)   printf("%s%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_BLUE, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_PURPLE_BOLD(tag, text, ...) printf("%s%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_PURPLE, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_CYAN_BOLD(tag, text, ...)   printf("%s%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_CYAN, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_YELLOW_BOLD(tag, text, ...) printf("%s%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_YELLOW, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_WHITE_BOLD(tag, text, ...)  printf("%s%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_WHITE, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_ORANGE_BOLD(tag, text, ...) printf("%s%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_ORANGE, str_esp_timestap(), tag, ##__VA_ARGS__)

// Logs coloridos em itálico
#define LOG_BLACK_ITALIC(tag, text, ...)  printf("\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_BLACK, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_RED_ITALIC(tag, text, ...)    printf("\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_RED, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_GREEN_ITALIC(tag, text, ...)  printf("\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_GREEN, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_BROWN_ITALIC(tag, text, ...)  printf("\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_BROWN, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_BLUE_ITALIC(tag, text, ...)   printf("\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_BLUE, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_PURPLE_ITALIC(tag, text, ...) printf("\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_PURPLE, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_CYAN_ITALIC(tag, text, ...)   printf("\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_CYAN, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_YELLOW_ITALIC(tag, text, ...) printf("\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_YELLOW, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_WHITE_ITALIC(tag, text, ...)  printf("\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_WHITE, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_ORANGE_ITALIC(tag, text, ...) printf("\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", COLOR_ORANGE, str_esp_timestap(), tag, ##__VA_ARGS__)

// Logs coloridos em itálico e em negrito
#define LOG_BLACK_ITALIC_BOLD(tag, text, ...)  printf("%s\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_BLACK, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_RED_ITALIC_BOLD(tag, text, ...)    printf("%s\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_RED, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_GREEN_ITALIC_BOLD(tag, text, ...)  printf("%s\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_GREEN, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_BROWN_ITALIC_BOLD(tag, text, ...)  printf("%s\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_BROWN, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_BLUE_ITALIC_BOLD(tag, text, ...)   printf("%s\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_BLUE, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_PURPLE_ITALIC_BOLD(tag, text, ...) printf("%s\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_PURPLE, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_CYAN_ITALIC_BOLD(tag, text, ...)   printf("%s\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_CYAN, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_YELLOW_ITALIC_BOLD(tag, text, ...) printf("%s\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_YELLOW, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_WHITE_ITALIC_BOLD(tag, text, ...)  printf("%s\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_WHITE, str_esp_timestap(), tag, ##__VA_ARGS__)
#define LOG_ORANGE_ITALIC_BOLD(tag, text, ...) printf("%s\x1B[3m%sMES (%s) %s: " text PRINT_RESET_COLOR "\n", PRINT_BOLD, COLOR_ORANGE, str_esp_timestap(), tag, ##__VA_ARGS__)

//? ===================================== FUNÇÕES ========================================

/**
 * @brief Converte o tempo de execução em timestamp
 *
 * @param None
 *
 * @return Buffer com a string do timestamp
*/
char *str_esp_timestap(void);

/**
 * @brief Exibe um log com o conteúdo de um buffer em formato hexadecimal
 *
 * @param tag Tag a ser exibida no log
 * @param buffer Buffer que se deseja exibir
 * @param buff_len Tamanho do buffer
 * @param color Cor do log
 *
 * @return None
*/
void array_log_buffer_hex_internal(const char *tag, const void *buffer, uint16_t buff_len, const char *color);

#endif /* DEBUG_COLORS_H */