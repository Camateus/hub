#!/usr/bin/env python3

import subprocess  # Permite executar processos no sistema
import sys  # Permite acesso a variáveis e caminhos do ambiente
import os  # Permite utilizar recursos dependentes do sistema operacional
import shutil  # Permite manipulação de arquivos

# Certifique-se de ter o módulo pyserial instalado
# pip install pyserial

#? ===================================== CONSTANTES ===================================== #

# Nome do projeto no CMakeLists
PROJECT = "controle-quarto"

# ID do usuário no sistema
CURRENT_ID = os.getlogin()
os.environ['CURRENT_ID'] = CURRENT_ID

# Porta USB disponível para gravação
DEVICE_USB_PORT = "COM3"  # Valor padrão para Windows

# Flag indicando se a gravação será feita utilizando o Docker
DOCKER_INSTALLED = False

#? ====================================== COMANDOS ====================================== #

def build_project() -> None:
    """Compila o código e cria uma cópia do arquivo com o nome completo do projeto"""

    # Verifica se o Docker está instalado
    if DOCKER_INSTALLED:
        command = f"docker run --rm -v {os.getcwd()}:/project -w /project -u {CURRENT_ID} -e HOME=/tmp esp-idf-v5.1:1.0 idf.py build"
    else:
        command = f"idf.py build"
    # Executa o comando desejado
    subprocess.run(command, shell=True, check=True)

    # -----------------

    # Obtém o diretório completo atual
    current_dir = os.getcwd()
    # Substitui os separadores de caminho por hífens e remove caracteres inválidos para nome de arquivo
    sanitized_dir = current_dir.replace("\\", "-").replace(":", "")

    # ---

    # Obtém a branch atual
    branch = subprocess.check_output(["git",
                                      "rev-parse",
                                      "--abbrev-ref",
                                      "HEAD"])
    # Converte o byte array obtido em string, removendo o "\n"
    branch = branch[:-1].decode()

    # ---

    # Obtém o hash do último commit
    hash_commit = subprocess.check_output(["git",
                                           "rev-parse",
                                           "--short",
                                           "HEAD"])
    # Converte o byte array obtido em string, removendo o "\n"
    hash_commit = hash_commit[:-1].decode()

    # ---

    # Obtém a versão de acordo com o commit
    version_commit = subprocess.check_output(["git",
                                           "log",
                                           "-1",
                                           "--pretty=%B"])
    # Converte o byte array obtido em string, removendo o "\n"
    version_commit = version_commit[:-1].decode()
    version_commit = version_commit.replace(" ", "_")
    version_commit = version_commit.replace("\n", "")

    # ---

    # Monta o nome do arquivo compilado .bin
    project_name = f"{PROJECT}-{sanitized_dir}-{branch}-{version_commit}-{hash_commit}"
    print("PROJECT_NAME: " + project_name)

    # ---

    # Copia o arquivo compilado com o nome completo do projeto
    shutil.copy(f"./build/{PROJECT}.bin", f"./build/{project_name}.bin")

def flash_project() -> None:
    """Grava o código através da porta serial escolhida"""

    # Verifica se o Docker está instalado
    if DOCKER_INSTALLED:
        command = f"docker run --rm -v {os.getcwd()}:/project --device={DEVICE_USB_PORT}:/dev/ttyUSB0 -w /project esp-idf-v5.1:1.0 idf.py flash -b 921600"
    else:
        command = f"idf.py flash -b 921600"

    # Executa o comando desejado
    subprocess.run(command, shell=True, check=True)

def monitor_project() -> None:
    """Abre o monitor serial com a porta serial escolhida"""

    # Verifica se o Docker está instalado
    if DOCKER_INSTALLED:
        command = f"docker run --rm -it -v {os.getcwd()}:/project --device={DEVICE_USB_PORT}:/dev/ttyUSB0 -w /project esp-idf-v5.1:1.0 idf.py monitor --port /dev/ttyUSB0 --no-reset --timestamps"
    else:
        command = f"idf.py monitor --port " + DEVICE_USB_PORT + " --no-reset --timestamps"

    # Executa o comando desejado
    subprocess.run(command, shell=True, check=True)

def open_menu_config() -> None:
    """Abre o menuconfig para a configuração do projeto"""

    # Verifica se o Docker está instalado
    if DOCKER_INSTALLED:
        command = f"docker run --rm -v {os.getcwd()}:/project -w /project -u {CURRENT_ID} -it esp-idf-v5.1:1.0 idf.py menuconfig"
    else:
        command = f"idf.py menuconfig"

    # Executa o comando desejado
    subprocess.run(command, shell=True, check=True)

def interactive_project() -> None:
    """Acessa o ambiente do projeto no container do Docker"""
    # Verifica se o Docker está instalado
    if DOCKER_INSTALLED:
        command = f"docker run --rm -v {os.getcwd()}:/project -w /project -u {CURRENT_ID} --device={DEVICE_USB_PORT}:/dev/ttyUSB0 -it esp-idf-v5.1:1.0 /bin/bash"

        # Executa o comando desejado
        subprocess.run(command, shell=True, check=True)

#? ================================= FUNÇÕES AUXILIARES ================================= #

def selec_serial_port() -> None:
    """Verifica as portas seriais disponíveis e permite ao usuário escolher qual utilizar"""
    
    import serial.tools.list_ports
    ports = list(serial.tools.list_ports.comports())
    ports_list = "\n".join([f"{i+1} - {port.device}" for i, port in enumerate(ports)])
    selected_port = input(f"Select the serial port to use:\n{ports_list}\n")
    if not selected_port.isdigit() or int(selected_port) > len(ports) or int(selected_port) < 1:
        print("Invalid input. The default port will be used (COM3).")
        return
    global DEVICE_USB_PORT
    DEVICE_USB_PORT = ports[int(selected_port) - 1].device
    print(f"Selected port: {DEVICE_USB_PORT}")

#? ======================================== MAIN ======================================== #

def main() -> None:
    # Verifica se o número de argumentos recebidos é válido
    if len(sys.argv) < 2:
        print("Usage: make <target> [target2] [target3] ...")
        print("Available targets: all, flash, monitor, menuconfig, open")
        print("1 - all: Build the project")
        print("2 - flash: Flash the project to the board")
        print("3 - monitor: Monitor the serial output of the board")
        print("4 - menuconfig: Open the menuconfig of the project")
        print("5 - open: Open a shell in the docker container")
        sys.exit(1)

    # Lê os argumentos recebidos
    targets = sys.argv[1:]

    # Verifica se algum dos argumentos envolve a utilização de portas seriais
    if any(target in targets for target in ["flash", "monitor", "open"]):
        selec_serial_port()

    # Executa todas as ações exigidas no comando
    for target in targets:
        if target == "all":
            build_project()
        elif target == "flash":
            flash_project()
        elif target == "monitor":
            monitor_project()
        elif target == "menuconfig":
            open_menu_config()
        elif target == "open":
            interactive_project()
        else:
            print(f"Invalid target: {target}. Available targets: all, flash, monitor, menuconfig, open")
            sys.exit(1)

if __name__ == "__main__":
    main()
