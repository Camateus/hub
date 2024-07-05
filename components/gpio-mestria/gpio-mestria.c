// ?================================= HEADERS =================================

// Bibliotecas
#include "gpio-mestria.h"

// ?================================== FUNÇÕES =================================

/**
 * @brief Configura um pino
 *
 * @param intr         Modo da interrupção do pino (tipo de borda invertida ou desabilitação)
 * @param mode         Modo do pino (entrada ou saída)
 * @param bit_mask     Bitmask dos pinos que se deseja configurar
 * @param pull_down_en Modo do pull-down interno do pino
 *
 * @return (esp_err_t) Retorna o sucesso da configuração
*/
esp_err_t gpio_configuration(gpio_int_type_t intr, gpio_mode_t mode, uint64_t bit_mask, gpio_pulldown_t pull_down_en) {
	// Inverte o tipo de borda da interrupção (inversão causada pelo circuito do optoacoplador)
	if(intr == GPIO_INTR_POSEDGE)
		intr = GPIO_INTR_NEGEDGE;
	else if(intr == GPIO_INTR_NEGEDGE)
		intr = GPIO_INTR_POSEDGE;

	// Estrutura com a configuração do pino
	gpio_config_t io_conf = {
		.intr_type = intr,
		.mode = mode,
		.pin_bit_mask = bit_mask,
		.pull_down_en = pull_down_en,
		.pull_up_en = GPIO_PULLUP_DISABLE,
	};

	// Configura o pino
	return gpio_config(&io_conf);
}

/**
 * @brief Altera o estado de um pino.
 *
 * @param gpio  Pino a ser lido
 * @param level Estado desejado
 *
 * @return (esp_err_t) Novo estado do pino
*/
esp_err_t gpio_digital_write(gpio_num_t gpio, uint8_t level) {
	return gpio_set_level(gpio, level);
}

/**
 * @brief Lê o estado de um pino. O valor é invertido pela presença do
 * circuito do optoacoplador, que utiliza de um pull-up para remover
 * flutuações do pino.
 *
 * @param gpio Pino a ser lido
 *
 * @return (esp_err_t) Estado invertido do pino
*/
int8_t gpio_digital_read(gpio_num_t gpio) {
	return (!gpio_get_level(gpio));
}