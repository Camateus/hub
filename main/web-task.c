#include "web-task.h"

// --- global_variables ---
static EventGroupHandle_t wifi_event_group;
static char temperatura_sensor[10]; // string de status do sensor de temperatura

// --- Functions Prototypes ---
void start_webserver(void);
esp_err_t root_get_handler(httpd_req_t *req);
esp_err_t led_get_handler(httpd_req_t *req);
esp_err_t temperatura_get_handler(httpd_req_t *req);
void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
void wifi_init(void);
void select_control(char *buf, char *out, char *param, uint8_t pin);
void temperatura_task(void *pvParameter);

// --- URI Handlers ---
static const httpd_uri_t led_control = {
    .uri = "/led",
    .method = HTTP_GET,
    .handler = led_get_handler,
    .user_ctx = NULL
};

static const httpd_uri_t root = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = root_get_handler,
    .user_ctx = NULL
};

// Novo manipulador para a requisição de temperatura
static const httpd_uri_t temperatura = {
    .uri = "/temperatura",
    .method = HTTP_GET,
    .handler = temperatura_get_handler,
    .user_ctx = NULL
};

// ============================================================================
// --- start_webserver ---
void start_webserver(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &led_control);
        httpd_register_uri_handler(server, &root);
        httpd_register_uri_handler(server, &temperatura); // Registre o manipulador de temperatura
    }
} // end start_webserver

// ============================================================================
// --- root_get_handler ---
esp_err_t root_get_handler(httpd_req_t *req) {
    const char *html_page = generate_html_page(temperatura_sensor);
    if (html_page != NULL) {
        httpd_resp_send(req, html_page, strlen(html_page));
        free((void *)html_page);
    } else {
        httpd_resp_send_500(req);
    }
    return ESP_OK;
}

// ============================================================================
// --- temperatura_get_handler ---
esp_err_t temperatura_get_handler(httpd_req_t *req) {
    httpd_resp_send(req, temperatura_sensor, strlen(temperatura_sensor));
    return ESP_OK;
}

// ============================================================================
// --- led_get_handler ---
esp_err_t led_get_handler(httpd_req_t *req) {
    char *buf;
    size_t buf_len;

    buf_len = httpd_req_get_url_query_len(req) + 1;
    if (buf_len > 1) {
        buf = malloc(buf_len);
        if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
            ESP_LOGI(__func__, "Found URL query => %s", buf);
            char param[32];

            select_control(buf, "led1", param, 1);
            select_control(buf, "led2", param, 2);
        }
        free(buf);
    }

    const char *html_page = generate_html_page(temperatura_sensor); // Atualize a página HTML com a temperatura
    if (html_page != NULL) {
        httpd_resp_send(req, html_page, strlen(html_page));
        free((void *)html_page);
    } else {
        httpd_resp_send_500(req);
    }

    return ESP_OK;
}

// ============================================================================
// --- wifi_event_handler ---
void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, BIT0);
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        xEventGroupSetBits(wifi_event_group, BIT0);
    }
} // end wifi_event_handler

// ============================================================================
// --- wifi_init ---
void wifi_init(void) {
    esp_log_level_set("wifi", ESP_LOG_NONE);
    wifi_event_group = xEventGroupCreate();
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL);

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        },
    };

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    esp_wifi_start();
} // end wifi_init

// ============================================================================
// --- select_control ---
void select_control(char *buf, char *out, char *param, uint8_t pin) {
    if (httpd_query_key_value(buf, out, param, sizeof(param)) == ESP_OK) {
        ESP_LOGI(__func__, "Found URL query parameter => %s=%s", param, out);
        if (pin == 1) {
            if (strcmp(param, "on") == 0) {
                inverte_rele_1();
            }
        }
        else if (pin == 2) {
            if (strcmp(param, "on") == 0) {
                inverte_rele_2();
            }
        }
    }
} // end select_control

// ============================================================================
// --- generate_html_page ---
const char *generate_html_page(const char *temperatura) {
    // Partes estáticas do HTML
    const char *html_header = "<!DOCTYPE html>"
                              "<html>"
                              "<head>"
                              "<title>Controle Quarto</title>"
                              "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                              "<style>"
                              "html{font-family: Tahoma;margin: 0px auto;text-align: center;background-color: #FEFFFF;}"
                              "body{margin: 0; padding: 0; box-sizing: border-box;}"
                              ".container{width: 90%; max-width: 800px; margin: 0 auto;}"
                              ".bts{border: none;color: #FFFFFF;padding: 14px 36px;text-decoration: none;font-size: 23px;margin: 1.5px;cursor: pointer;font-family: Verdana;}"
                              ".btOn{background-color: #33A590;}"
                              ".btOff{background-color: #777777;}"
                              "@media (max-width: 600px) {"
                              "    .bts {font-size: 18px; padding: 10px 20px;} "
                              "}"
                              "</style>"
                              "<script>"
                              "function atualizaTemperatura() {"
                              "    fetch('/temperatura')"
                              "        .then(response => response.text())"
                              "        .then(data => {"
                              "            document.getElementById('temperatura').innerText = data;"
                              "        });"
                              "}"
                              "setInterval(atualizaTemperatura, 30000);"
                              "</script>"
                              "</head>"
                              "<body>"
                              "<div class=\"container\">"
                              "<h2>Controle Quarto</h2>";

    const char *html_footer = "</div></body></html>";

    // Estimativa do tamanho necessário para a string HTML
    size_t html_size = strlen(html_header) + strlen(html_footer) +
                       strlen("<p><b>Temperatura: </b><span id=\"temperatura\">") + strlen(temperatura) +
                       strlen("</span></p>"
                              "<button class=\"bts btOn\"  onclick=\"location.href = '/led?led1=on'\">Lampada</button>"
                              "<button class=\"bts btOff\" onclick=\"location.href = '/led?led2=on'\">Tomada</button>") + 1;

    char *html_page = (char *)malloc(html_size);
    if (html_page == NULL) {
        ESP_LOGE("web-task", "Memory allocation failed for HTML page");
        return NULL;
    }

    snprintf(html_page, html_size,
             "%s"
             "<p><b>Temperatura: </b><span id=\"temperatura\">%s</span></p>"
             "<button class=\"bts btOn\"  onclick=\"location.href = '/led?led1=on'\">Lampada</button>"
             "<button class=\"bts btOff\" onclick=\"location.href = '/led?led2=on'\">Tomada</button>"
             "%s",
             html_header, temperatura, html_footer);

    return html_page;
}

// ============================================================================
// --- temperatura_task ---
void temperatura_task(void *pvParameter) {
    while (1) {
        // Atualize a temperatura
        char *nova_temperatura = get_temp_press();
        if (nova_temperatura != NULL) {
            snprintf(temperatura_sensor, sizeof(temperatura_sensor), "%s", nova_temperatura);
            free(nova_temperatura);
        }
        // Aguarde 30 segundos antes de atualizar novamente
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// ============================================================================
// --- init_web_interface ---
void init_web_interface(void) {
    ESP_LOGI(__func__, "================================ INIT WEB INTERFACE ================================");
    printf("\n");

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    wifi_init();
    xEventGroupWaitBits(wifi_event_group, BIT0, false, true, portMAX_DELAY);
    start_webserver();

    // Crie a tarefa de atualização periódica
    xTaskCreate(temperatura_task, "temperatura_task", 4096, NULL, 5, NULL);

    ESP_LOGI(__func__, "================================= END WEB INTERFACE ================================");
}
