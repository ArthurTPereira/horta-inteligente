#include <Wire.h>
#include <DHT.h>

// Pinos para os sensores
#define UMIDADE A0
#define DHTPIN A1
#define DHTTYPE DHT11
#define LDR A2
#define BOMBA 4

#define MAX_LIGHT 1020
#define MIN_LIGHT 500   

#define LIMIAR 70       // Porcentagem de umidade do solo
#define TEMPO_REGA 10000    // 
// Instancia do DHT
DHT dht(DHTPIN,DHTTYPE);

// Sensor atual
int state = 0;

// Dados dos sensores
float umidadeSolo = 0;
float temperatura = 0;
float umidadeAr = 0;
float luminosidade = 0;

// Setup
// Configura o DHT, os pinos dos sensores e o I2C
void setup() {
    dht.begin();
    pinMode(UMIDADE,INPUT); 
    pinMode(LDR,INPUT);      
    pinMode(BOMBA,OUTPUT);
    digitalWrite(BOMBA, LOW);    
    Serial.begin(9600);
    Wire.begin(8);                // join i2c bus with address #8
    Wire.onRequest(requestEvent); // register event
    Serial.println("Slave configurado");
}

// Loop
// Leitura do sensor de umidade e temperatura
void loop() {

    umidadeAr = dht.readHumidity();
    temperatura = dht.readTemperature();
    if (isnan(umidadeAr) || isnan(temperatura)) {
        Serial.println("Failed to read from DHT");
        umidadeAr = -1;
        temperatura = -1;
    } 
    int ldrAnalog = analogRead(LDR);
    luminosidade = map(ldrAnalog, MIN_LIGHT, MAX_LIGHT, 0, 100);
    if (luminosidade < 0.0) luminosidade = 0;

    int umidadeAnalog = analogRead(UMIDADE);
    umidadeSolo = (100 - ((umidadeAnalog/1023.0) * 100));

    if (umidadeSolo < LIMIAR) {
        Serial.println("Regando");
        Regar();
        delay(30000); // 30s
        Serial.println("Terminou de esperar");
    }

  delay(100);
}

// Função executada ao receber um request pelo master
void requestEvent() {
    //Serial.println("Request recebido");

    String str;
    float data;

    // Reset do numero do sensor
    if (state == 4) {
        state = 0;
    }
    
    if (state == 0) {                       // Sensor de umidade do solo
        state++;
        str = String(umidadeSolo) + 'X';           // 'X' = Fim de string
        Wire.write(str.c_str());    
    } else if (state == 1) {                // Sensor de temperatura
        state++;
        str = String(temperatura) + 'X';    // 'X' = Fim de string
        Wire.write(str.c_str());
    } else if (state == 2) {                // Sensor de umidade do ar
        state++;
        str = String(umidadeAr) + 'X';      // 'X' = Fim de string
        Wire.write(str.c_str());
    } else if (state == 3) {                // Sensor de luminosidade
        state++;
        str = String(luminosidade) + 'X';      // 'X' = Fim de string
        Wire.write(str.c_str());
    }

    delay(100);

}




void Regar() {
    digitalWrite(BOMBA,HIGH);
    delay(TEMPO_REGA);
    Serial.println("Terminou de Regar");
    digitalWrite(BOMBA, LOW);
}
