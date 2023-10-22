# Horta Inteligente com Arduino e ESP8266

Este repositório contém o código e os recursos para criar uma horta inteligente que utiliza um Arduino como escravo e uma ESP8266 como mestre. Os dispositivos se comunicam via I2C para coletar dados de sensores de temperatura, umidade do ar, umidade do solo e luminosidade. Os dados são então enviados para um servidor Thinger.io para monitoramento e controle remoto da sua horta, além de contar com um sistema de rega automático.

## Conteúdo

- [Requisitos](#requisitos)
- [Montagem](#montagem)
- [Configuração](#configuração)
- [Uso](#uso)
- [Contribuição](#contribuição)
- [Licença](#licença)

## Requisitos

Para montar sua própria horta inteligente, você precisará dos seguintes componentes:

- Arduino compatível com I2C
- ESP8266
- Sensores de temperatura, umidade do ar, umidade do solo e luminosidade
- Bomba d'água

Certifique-se de instalar as bibliotecas necessárias para cada componente antes de continuar.

## Montagem

Siga as instruções de montagem para conectar os componentes e configurar a comunicação I2C entre o Arduino e a ESP8266. Certifique-se de que os sensores estejam corretamente conectados para que os dados sejam lidos com precisão.

## Configuração

Antes de usar o sistema, você deve configurar as seguintes variáveis no código:

- SSID e senha da rede Wi-Fi para a ESP8266
- Usuário, ID do dispositivo e credenciais para o Thinger.io
- Endereço I2C da ESP8266 e do Arduino

Depois de configurar essas variáveis, carregue o código correspondente para a ESP8266 e o Arduino.

## Uso

Assim que o sistema estiver montado e configurado, a ESP8266 enviará solicitações para o Arduino para coletar dados dos sensores. Os dados serão então enviados para o Thinger.io para monitoramento remoto. Você pode acessar o painel de controle do Thinger.io para visualizar e gerenciar os dados da sua horta inteligente.

## Contribuição

Este é um projeto de código aberto, e convidamos você a contribuir, seja relatando problemas, propondo melhorias ou enviando solicitações de pull. Sinta-se à vontade para colaborar e melhorar este projeto.

## Licença

Este projeto é licenciado sob a Licença MIT - consulte o arquivo [LICENSE](LICENSE) para obter detalhes.

---

Divirta-se construindo sua horta inteligente! Se tiver alguma dúvida ou precisar de ajuda, não hesite em entrar em contato.
