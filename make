#!/usr/bin/env python3

import subprocess # Permite executar processos no sistema
import sys # Permite acesso a variáveis e caminhos do ambiente
import os # Permite utilizar recursos dependentes do sistema operacional
import shutil # Permite manipulação de arquivos

#? ===================================== CONSTANTES ===================================== #

# Nome do projeto no CMakeLists
PROJECT = "area-iot"

# ID do usuário no sistema
CURRENT_ID = str(os.getuid())
os.environ['CURRENT_ID'] = CURRENT_ID

# Porta USB disponível para gravação
DEVICE_USB_PORT = "/dev/ttyUSB0" # Valor padrão

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
    current_dir = subprocess.check_output(["pwd"])
    # Obtém apenas o diretório onde o código está
    current_dir = os.path.basename(os.path.normpath(current_dir[:-1]))
    # Converte o byte array obtido em string
    current_dir = current_dir.decode()

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
    project_name = f"{PROJECT}-{current_dir}-{branch}-{version_commit}-{hash_commit}"
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
    
    # Verifica todas as portas seriais disponíveis (USB e ACM)
    ports = subprocess.check_output("ls /dev/ttyUSB*", shell=True).decode().split()
    try:
        ports += subprocess.check_output("ls /dev/ttyACM*", shell=True).decode().split()
    except:
        pass

    # Cria uma lista com todas as portas em cores diferentes para cada uma
    ports_list = "\n".join([f"{i+1} - \033[1;3{i+1}m{port}\033[0m" for i, port in enumerate(ports)])

    # Aguarda o usuário escolher alguma das portas
    selected_port = input(f"Select the serial port to use:\n{ports_list}\n")

    # Valida a porta escolhida
    if not selected_port.isdigit() or int(selected_port) > len(ports_list) or int(selected_port) < 0:
        print("Invalid input. the default port will be used (/dev/ttyUSB0).")
        return

    # Obtém o nome da porta escolhida
    selected_port = ports[int(selected_port) - 1]

    print(f"Selected port: {selected_port}")

    # Define a porta a ser usada nos comandos
    global DEVICE_USB_PORT
    DEVICE_USB_PORT = selected_port

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
