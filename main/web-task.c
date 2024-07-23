#include "web-task.h"


// --- global_variables ---
static EventGroupHandle_t wifi_event_group;
char temperatura_sensor[4];                             //string de status do LED2


// --- Functions Prototypes ---
void start_webserver(void);                                        //inicializa o servidor web
esp_err_t root_get_handler(httpd_req_t *req);   //manipulador de solicitações HTTP GET para o URI raiz
esp_err_t led_get_handler(httpd_req_t
                          *req);    //manipulador de solicitações HTTP GET, controla LEDs e atualiza a webpage
void wifi_event_handler(void *arg, esp_event_base_t event_base,    //manipulador de eventos Wifi
                        int32_t event_id, void *event_data);
void wifi_init(void);                                              //inicializa o wifi do ESP32
void select_control(char *buf, char *out, char *param,             //seleciona a saída a ser controlada
                    uint8_t pin);


static const httpd_uri_t led_control = {
	.uri       = "/led",                                 //URI associado à estrutura
	.method    = HTTP_GET,                               //método GET (URI responderá a solicitações GET)
	.handler   = led_get_handler,                        //manipulador chamado quando uma solicitação é feita para esta URI
	.user_ctx  = NULL                                    //contexto de usuário. Não utilizado.
};

static const httpd_uri_t root = {
	.uri       = "/",                                    //apenas uma "/" que associa a URI à raiz do servidor
	.method    = HTTP_GET,                               //método GET (URI responderá a solicitações GET)
	.handler   = root_get_handler,                       //manipulador chamado quando uma solicitação é feita para esta URI
	.user_ctx  = NULL                                    //contexto de usuário. Não utilizado.
};


// ============================================================================
// --- start_webserver ---
void start_webserver(void) {
	httpd_config_t config = HTTPD_DEFAULT_CONFIG();      //estrutura config inicializada com os valores padrão do HTTP
	httpd_handle_t server =
	    NULL;                        //armazena o identificador do servidor web depois que ele for iniciado

	if(httpd_start(&server, &config) ==
	   ESP_OK) {        //inicializa o servidor HTTP com config. Se resultar em ESP_OK, a inicialização funcinou
		httpd_register_uri_handler(server,
		                           &led_control);  //registra um manipulador para o servidor web, que apresenta informações sobre URI, método e HTTP
		httpd_register_uri_handler(server,
		                           &root);         //registra um manipulador para o servidor web para lidar com solicitações para a raiz do servidor
	}

} //end start_webserver


// ============================================================================
// --- root_get_handler ---
esp_err_t root_get_handler(httpd_req_t *req) {

	const char *html_page = generate_html_page(get_temp_press());   //gera a página html de forma dinâmica

	if(html_page != NULL) {                                   //verifica se a página foi gerada com sucesso
		httpd_resp_send(req, html_page, strlen(html_page));    //envia a página HTML gerada como resposta à solicitação HTTP
		free((void *)html_page);                               //libera memória alocada para a página
	}

	else                                                      //senão, ocorreu um erro
		httpd_resp_send_500(req);                              //erro interno do servidor (HTTP 500)

	return ESP_OK;                                       //manipulação de solicitação HTTP concluída com sucesso

} //end root_get_handler


// ============================================================================
// --- led_get_handler ---
esp_err_t led_get_handler(httpd_req_t *req) {
	char  *buf;                                                        //buffer para os parâmetros da URL
	size_t buf_len;                                                    //tamanho do buffer

	buf_len = httpd_req_get_url_query_len(req) +
	          1;                    //armazena tamanho da string de consulta (query string) da URL

	if(buf_len > 1) {                                                  //verifica se a string de consulta não está vazia
		buf = malloc(
		          buf_len);                                          //aloca memória dinamicamente para string de consulta de acordo com buf_len

		if(httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {  //obtém a string de consulta da URL e a armazena em buf
			ESP_LOGI(__func__, "Found URL query => %s", buf);                 //registra a string de consulta no log do sistema
			char param[32];                                              //


			select_control(buf, "led1", param, 1);       //analisa a string de consulta para determinar o estado do LED1
			select_control(buf, "led2", param, 2);       //analisa a string de consulta para determinar o estado do LED2


		} //end if httpd_req_get_url_query_str

		free(buf);                                                     //libera memória alocada para a string de consulta

	} //end if buf_len


	const char *html_page = generate_html_page(temperatura_sensor);  //gera a página html dinamicamente

	if(html_page != NULL) {                                                //verifica se a página foi gerada com sucesso
		httpd_resp_send(req, html_page, strlen(
		                    html_page));                //envia a página HTML gerada como resposta à solicitação HTTP
		free((void *)html_page);                                           //libera memória alocada para a página
	}

	else                                                                   //senão, ocorreu um erro
		httpd_resp_send_500(req);                                          //erro interno do servidor (HTTP 500)

	return ESP_OK;                                                         //manipulação de solicitação HTTP concluída com sucesso

} //end led_get_handler


// ============================================================================
// --- wifi_event_handler ---
void wifi_event_handler(void *arg, esp_event_base_t event_base,
                        int32_t event_id, void *event_data) {
	if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)              //wifi inicializado com sucesso
		esp_wifi_connect();                                                       //inicia a conexão

	else if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) { //erro ao conectar
		esp_wifi_connect();                                                       //realiza nova tentativa de conexão
		xEventGroupClearBits(wifi_event_group, BIT0);                             //limpa bit de evento
	}

	else if(event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {          //obteve um endereço de IP válido?
		//sim
		xEventGroupSetBits(wifi_event_group, BIT0);                               //bit de obtenção de IP é setado
	}


} //end wifi_event_handler


// ============================================================================
// --- wifi_init ---
void wifi_init(void) {
	esp_log_level_set("wifi",
	                  ESP_LOG_NONE);                                     //define que os logs de wifi não serão impressos
	wifi_event_group =
	    xEventGroupCreate();                                      //grupo para lidar com eventos da conexão wifi
	esp_netif_init();                                                            //inicializa a camada de interface de rede (netif) do ESP32
	esp_event_loop_create_default();                                             //loop de eventos padrão para lidar com eventos do sistema
	esp_netif_create_default_wifi_sta();                                         //interface de rede padrão para a estação wifi
	wifi_init_config_t cfg =
	    WIFI_INIT_CONFIG_DEFAULT();                         //inicialização de estrura de configuração do Wi-Fi com os valores padrão
	esp_wifi_init(
	    &cfg);                                                         //subsistema wifi inicializa com as configurações da estrutura cfg
	esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler,
	                           NULL);  //registra um manipulador de eventos wifi
	esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler,
	                           NULL); //registra um manipulador de eventos de obtenção de IP

	wifi_config_t wifi_config = {                                                //configura as credenciais da rede
		.sta = {
			.ssid = WIFI_SSID,
			.password = WIFI_PASS,
		},
	};

	esp_wifi_set_mode(
	    WIFI_MODE_STA);                                            //modo Wi-Fi para estação (cliente) para que o ESP32 possa se conectar
	esp_wifi_set_config(ESP_IF_WIFI_STA,
	                    &wifi_config);                          //configura as credenciais da rede Wi-Fi para o modo estação
	esp_wifi_start();                                                            //inicia o modo wifi, onde o ESP32 tentará se conectar usando as credenciais

} //end wifi_init


// ============================================================================
// --- select_control ---
void select_control(char *buf, char *out, char *param, uint8_t pin) {

	if(httpd_query_key_value(buf, out, param,
	                         sizeof(param)) == ESP_OK) {          //verifica se é possível obter o valor do parâmetro especificado
		ESP_LOGI(__func__, "Found URL query parameter => %s=%s", param,
		         out);             //registra no log do sistema parâmetro encontrado na string de consulta
		if(pin == 1) {
			if(strcmp(param, "on") == 0) {                                               //se o parâmetro for "on"
				inverte_rele_1();                                                   //atualiza o status da página para "ON"
			}
		}
		else if(pin == 2) {
			if(strcmp(param, "on") == 0) {                                               //se o parâmetro for "on"
				inverte_rele_2();                                                   //atualiza o status da página para "ON"
			}
		}
	} //end if httpd_query_key_value
} //end select_control


const char *generate_html_page(const char *temperatura) {

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
	                          "<title>Controle Quarto </title>"
	                          "<style>"
	                          ".a{border: 8px solid black;padding: 10px;margin: 25px;border - radius: 10px;width: fit - content;flex-direction: column;align-items: center;margin: 0 auto;}"
	                          "html{font - family: Tahoma;margin: 0px auto;text - align: center;background - color: #FFFFFF;}"
	                          ".bts{border:none;color:#FFFFFF;padding: 14px 36px;text - decoration:none;font - size: 23px;margin: 1.5px;cursor:pointer;font - family:Verdana;}"
	                          ".btLED{border - radius: 10px;background - color:#0060ce;}"
	                          ".btPIN{border - radius: 10px;background - color:#0060ce;}"
	                          "</style>"
	                          "</head>"
	                          "<body class = \"a\">"
	                          "<h2>Controle Quarto </h2>;";


	const char *html_footer = "</body></html>";

	// Estimativa do tamanho necessário para a string HTML
	size_t html_size = strlen(html_header) + strlen(html_footer) +
	                   strlen("<p><b>Temperatura: </b></p>"
	                          "<button class=\"bts btLED\"  onclick=\"location.href = '/led?led1=on'\">Lâmpada</button>") + strlen(temperatura) +
	                   strlen("<button class=\"bts btPIN\" onclick=\"location.href = '/led?led1=off'\">Tomada</button>") + 1;



	char *html_page = (char *)malloc(html_size);   //aloca memória dinâmica

	if(html_page == NULL)
		return NULL;                                //falha na alocação de memória

	// Preenchendo a string HTML com o conteúdo dinâmico
	snprintf(html_page, html_size,
	         "%s"
	         "<p><b>Temperatura: %s</b></p>"
	         "<button class=\"bts btLED\"  onclick=\"location.href = '/led?led1=on'\">Lâmpada</button>"
	         "<button class=\"bts btPIN\" onclick=\"location.href = '/led?led1=off'\">Tomada</button>"
	         "%s",
	         html_header, temperatura, html_footer);

	return html_page;

} //end generate_html_page

void init_web_interface() {
	LOG_PURPLE(__func__, "================================ INIT WEB INTERFACE ================================");
	printf("\n");

	esp_err_t ret = nvs_flash_init();                    //armazena em ret configurações e dados persistentes do NVS

	if(ret == ESP_ERR_NVS_NO_FREE_PAGES ||
	   ret == ESP_ERR_NVS_NEW_VERSION_FOUND) { //verifica erros de inicialização do NVS
		ESP_ERROR_CHECK(nvs_flash_erase());              //apaga o NVS para tentar resolver o problema
		ret = nvs_flash_init();                          //realiza nova tentativa
	}

	ESP_ERROR_CHECK(ret);                                //imprime mensagem de erro caso houver e reinicia o dispositivo

	wifi_init();                                                                   //inicializa wifi do ESP32
	xEventGroupWaitBits(wifi_event_group, BIT0, false, true,
	                    portMAX_DELAY);       //aguarda indicação de conexão wifi bem sucedida
	start_webserver();                                                             //inicializa o servidor web

	LOG_PURPLE(__func__, "================================= END WEB INTERFACE ================================");
}