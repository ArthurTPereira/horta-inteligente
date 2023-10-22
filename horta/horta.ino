#include <Wire.h>
#include <ThingerESP8266.h>

// Conexão Wifi
const char* ssid = "CLARO AP 207";
const char* password = "33017490";

// Conexão Thinger.io
const char* username = "arthur_tpereira";
const char* deviceId = "esp8266";
const char* deviceCredential = "123456";

// Dados dos sensores
float umidadeSolo = 0;
float temperatura = 0;
float umidadeAr = 0;
float luminosidade = 0;

// Instancia do Thinger.io
ThingerESP8266 thing(username,deviceId,deviceCredential);

// Setup
// Configura o I2C e as saídas de dados para o Thinger.io
void setup() {
    Wire.begin(0,2);
    Serial.begin(9600);
    delay(100);
    thing.add_wifi(ssid,password);

    thing["umidade_solo"] >> outputValue(umidadeSolo);
    thing["temperatura"] >> outputValue(temperatura);
    thing["umidade_ar"] >> outputValue(umidadeAr);
    thing["luminosidade"] >> outputValue(luminosidade);
    
    Serial.print("Master configurado");
}

void loop() {

    String data = "";

    // Request umidade do solo
    Wire.requestFrom(8,10);
    while (Wire.available()) {
        char c = Wire.read();
        if (c == 'X') break;        // 'X' == Fim de string
        data+=c;
    }
    data.trim();
    umidadeSolo = data.toFloat();

    data = "";
    delay(100);

    // Request temperatura
    Wire.requestFrom(8,10);
    while (Wire.available()) {
        char c = Wire.read();
        if (c == 'X') break;        // 'X' == Fim de string
        data+=c;
    }
    data.trim();
    temperatura = data.toFloat();

    data = "";
    delay(100);

    // Request umidade do ar
    Wire.requestFrom(8,10);
    while (Wire.available()) {
        char c = Wire.read();
        if (c == 'X') break;        // 'X' == Fim de string
        data+=c;
    }
    data.trim();
    umidadeAr = data.toFloat();

    data = "";
    delay(100);

    // Request luminosidade
    Wire.requestFrom(8,10);
    while (Wire.available()) {
        char c = Wire.read();
        if (c == 'X') break;        // 'X' == Fim de string
        data+=c;
    }
    data.trim();
    luminosidade = data.toFloat();


    thing.handle();
    delay(2000);

}
