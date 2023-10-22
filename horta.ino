#include <Wire.h>
#include <ThingerESP8266.h>

const char* ssid = "CLARO AP 207";
const char* password = "33017490";

const char* username = "arthur_tpereira";
const char* deviceId = "esp8266";
const char* deviceCredential = "123456";

float umidadeSolo = 0;
float temperatura = 0;
float umidadeAr = 0;
float luminosidade = 0;


ThingerESP8266 thing(username,deviceId,deviceCredential);

void setup() {
    Wire.begin(0,2);
    Serial.begin(9600);
    delay(100);
    Serial.print("Master Ready");
    thing.add_wifi(ssid,password);

    thing["umidade_solo"] >> outputValue(umidadeSolo);
    thing["temperatura"] >> outputValue(temperatura);
    thing["umidade_ar"] >> outputValue(umidadeAr);
    thing["luminosidade"] >> outputValue(luminosidade);
}

void loop() {

    String data = "";

    Wire.requestFrom(8,10);         // Request umidade do solo

    while (Wire.available()) {
        char c = Wire.read();
        if (c == 'X') break;
        data+=c;
    }
    data.trim();
    umidadeSolo = data.toFloat();

    data = "";
    delay(100);
    Wire.requestFrom(8,10);         // Request temperatura

    while (Wire.available()) {
        char c = Wire.read();
        if (c == 'X') break;
        data+=c;
    }
    data.trim();
    temperatura = data.toFloat();

    data = "";
    delay(100);
    Wire.requestFrom(8,10);         // Request umidade do ar

    while (Wire.available()) {
        char c = Wire.read();
        if (c == 'X') break;
        data+=c;
    }
    data.trim();
    umidadeAr = data.toFloat();

    data = "";
    delay(100);
    Wire.requestFrom(8,10);         // Request luminosidade

    while (Wire.available()) {
        char c = Wire.read();
        if (c == 'X') break;
        data+=c;
    }
    data.trim();
    luminosidade = data.toFloat();

    thing.handle();
    delay(2000);

}
