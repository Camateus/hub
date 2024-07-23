#ifndef WEB_TASK
#define WEB_TASK

// ?================================= HEADERS =================================

// Bibliotecas nativas do C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// Bibliotecas locais do esp
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/gpio_struct.h"
#include "debug-colors.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_http_server.h"


const char *generate_html_page(const char *temperatura, const char *led2_status) {

	// Partes estáticas do HTML
	const char *html_header = "<!DOCTYPE html>"
	                          "<html>"
	                          "<head>"
	                          "<title>WR Kits ESP32 Server</title>"
	                          "<style>"
	                          "html{font-family: Tahoma;margin: 0px auto;text-align: center;background-color: #FEFFFF;}"
	                          ".bts{border: none;color: #FFFFFF;padding: 14px 36px;text-decoration: none;font-size: 23px;margin: 1.5px;cursor: pointer;font-family: Verdana;}"
	                          ".btOn{background-color: #33A590;}"
	                          ".btOff{background-color: #777777;}"
	                          "</style>"
	                          "</head>"
	                          "<body>"
	                          "<h2>WR Kits ESP32 Web Server</h2>"
	                          "< !DOCTYPE html >"
	                          "<html>"
	                          "<head>"
	                          "<title>Controle Quarto < / title >"
	                          "<style>"
	                          ".a{border: 8px solid black;padding: 10px;margin: 25px;border - radius: 10px;width: fit - content;flex-direction: column;align-items: center;margin: 0 auto;}"
	                          "html{font - family: Tahoma;margin: 0px auto;text - align: center;background - color: #FFFFFF;}"
	                          ".bts{border:none;color:#FFFFFF;padding: 14px 36px;text - decoration:none;font - size: 23px;margin: 1.5px;cursor:pointer;font - family:Verdana;}"
	                          ".btLED{border - radius: 10px;background - color:#0060ce;}"
	                          ".btPIN{border - radius: 10px;background - color:#0060ce;}"
	                          "</style>"
	                          "</head>"
	                          "<body class = "a">"
	                          "<h2>Controle Quarto < / h2 >;";


	const char *html_footer = "</body></html>";

	// Estimativa do tamanho necessário para a string HTML
	size_t html_size = strlen(html_header) + strlen(html_footer) +
	                   strlen("<p><b>Temperatura: </b></p>"
	                          "<button class="bts btLED"  onclick="location.href='/led?led1=on'">Lâmpada</button>") + strlen(temperatura) +
	                   strlen("<p>LED 2 Status: </p>"
	                          "<button class=\"bts btOn\"  onclick=\"location.href='/led?led2=on'\">Turn LED On</button>"
	                          "<button class=\"bts btOff\" onclick=\"location.href='/led?led2=off'\">Turn LED Off</button>") + 1;



<p><b>Relés:
	< / b > < / p >
	<button class = "bts btLED"  onclick = "location.href='/led?led1=on'">Lâmpada < / button >
		                                       <button class = "bts btPIN" onclick = "location.href='/led?led1=off'">Tomada < / button >

			                                                                             char *html_page = (char *)malloc(html_size);   //aloca memória dinâmica

	if(html_page == NULL)
		return NULL;                                //falha na alocação de memória


	// Preenchendo a string HTML com o conteúdo dinâmico
	snprintf(html_page, html_size,
	         "%s"
	         "<p>LED 1 Status: %s</p>"
	         "<button class=\"bts btOn\"  onclick=\"location.href='/led?led1=on'\">Turn LED On</button>"
	         "<button class=\"bts btOff\" onclick=\"location.href='/led?led1=off'\">Turn LED Off</button>"
	         "<p>LED 2 Status: %s</p>"
	         "<button class=\"bts btOn\"  onclick=\"location.href='/led?led2=on'\">Turn LED On</button>"
	         "<button class=\"bts btOff\" onclick=\"location.href='/led?led2=off'\">Turn LED Off</button>"
	         "%s",
	         html_header, temperatura, led2_status, html_footer);

	return html_page;

} //end generate_html_page




// ============================================================================
// --- End interface.h ---


void init_web_interface();

#endif /* WEB_TASK */
