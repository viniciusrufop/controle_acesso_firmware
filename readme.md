# Trabalho de Conclusão de curso

## Sistema de controle de acesso utilizando autenticação por RFID e gerenciamento por meio de software WEB

[Link para download do arquivo PDF de todo o projeto](https://www.monografias.ufop.br/handle/35400000/2222).

# Passos de configuração

Abrir arqivo `src/api.h` e alterar valor das variáveis `authToken` e `hostServer`.

A variável `hostServer` é o link para o redirecionamento da API.

A variável `authToken` é obtida por um usuário administrador do sistema, basta executar o [Front-end](https://github.com/viniciusrufop/controle_acesso_angular.git) da aplicação, fazer o login com um usuário admin, abrir a página do perfil do usuário e copiar o Token que é exibido nas informções.

# Compilar

Para compilar o projeto e carrega-lo em uma placa de desenvolvimento ESP32, bata utilizar o editor de texto `VS Code` instalar a extensão [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide), carregar um projeto existente e selecionar a pasta onde foi feito o git clone deste repositório.