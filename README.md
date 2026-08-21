# Smart Room Hub - ESP32

![ESP-IDF](https://img.shields.io/badge/ESP--IDF-FreeRTOS-red)
![C](https://img.shields.io/badge/Language-C-blue)
![Status](https://img.shields.io/badge/Status-Ativo-success)

Um sistema de automação residencial baseado em **ESP32**, desenvolvido para controlar a iluminação e uma tomada inteligente do quarto, além de realizar o monitoramento contínuo de temperatura. 

O firmware foi estruturado de forma modular utilizando **FreeRTOS** e o framework **ESP-IDF**, dividindo as responsabilidades em tarefas independentes para garantir alta performance e confiabilidade na automação de hardware.

## Funcionalidades

- **Controle de Iluminação e Tomada:** Acionamento de relés para controle da luz principal e de uma tomada do quarto.
- **Monitoramento Climático:** Leitura de temperatura e pressão utilizando o sensor **BMX280** (BME280/BMP280) via barramento I2C.
- **Interface Web (Wi-Fi):** Servidor web embarcado com uma interface HTML responsiva para controle e visualização dos dados em tempo real pela rede local.
- **Controle via Bluetooth (BLE):** Suporte a Bluetooth Low Energy para acionamento local alternativo.
- **Memória Persistente:** Salva o último estado da luz e da tomada na memória Flash (NVS) do ESP32. Em caso de queda de energia, o sistema retorna ao estado anterior automaticamente.

##  Arquitetura do Software

O projeto é dividido em **Tasks do FreeRTOS** e **Componentes customizados**:

### Tasks Principais (`main/`)
- `web-task`: Gerencia a conexão Wi-Fi e hospeda a página web (`esp32_web_page.html`).
- `ble-task`: Gerencia a stack do Bluetooth Low Energy para comandos sem fio.
- `sensor-task`: Faz a leitura periódica do sensor I2C.
- `io-task`: Controla fisicamente as saídas GPIO (relés/atuadores).
- `flash-memory-task`: Gerencia o salvamento e recuperação de estados na memória não-volátil (NVS).

### Componentes (`components/`)
- `bmx280`: Driver para o sensor de temperatura/pressão.
- `gpio`: Abstração para manipulação e configuração segura dos pinos de I/O.
- `i2C`: Interface simplificada para comunicação I2C.
- `flash`: Módulo dedicado para operações de leitura/escrita na memória Flash.
- `debug-colors`: Macros para formatação de logs coloridos no terminal, facilitando o debug da aplicação.

## Hardware Utilizado

*   1x Placa de Desenvolvimento **ESP32**
*   1x Módulo Relé de 2 Canais (para a luz e a tomada)
*   1x Sensor de Temperatura **BME280** ou **BMP280**
*   Fonte de alimentação (5V)
*   Jumpers e protoboard ou placa de circuito impresso

## Autor

Desenvolvido por **Mateus Giori Camargos**.
