#include <Wire.h>
#include <DHT.h>

#define UMIDADE A0
#define DHTPIN A1
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);

int state = 0;

float umidadeSolo = 0;
float temperatura = 0;
float umidadeAr = 0;
float luminosidade = 0;

void setup() {
    dht.begin();
    pinMode(UMIDADE,INPUT);            // leitura sensor umidade
    Serial.begin(9600);
    Wire.begin(8);                // join i2c bus with address #8
    Wire.onRequest(requestEvent); // register event
    Serial.print("Slave Ready");

}

void loop() {

    umidadeAr = dht.readHumidity();
    temperatura = dht.readTemperature();
    if (isnan(umidadeAr) || isnan(temperatura)) {
        Serial.println("Failed to read from DHT");
        umidadeAr = -1;
        temperatura = -1;
    } 

  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
    Serial.println("Request recebido");

    String str;
    float data;

    if (state == 4) {
        state = 0;
    }
    
    if (state == 0) {               // Sensor de umidade do solo
        state++;
        int umidadeAnalog = analogRead(UMIDADE);
        data = (100 - ((umidadeAnalog/1023.0) * 100));
        str = String(data) + 'X';   // 'X' = Fim de string
        Wire.write(str.c_str());    
    } else if (state == 1) {        // Sensor de temperatura
        state++;
        str = String(temperatura) + 'X';
        Wire.write(str.c_str());
    } else if (state == 2) {
        state++;
        str = String(umidadeAr) + 'X';
        Wire.write(str.c_str());
    } else if (state == 3) {
        state++;
        str = "3X";
        Wire.write(str.c_str());
    }

    delay(100);

}