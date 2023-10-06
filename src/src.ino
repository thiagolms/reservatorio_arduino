#include "Ultrasonic.h" //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int echoPin = 7; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 6; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
LiquidCrystal_I2C lcd(0x27,16,2);
Ultrasonic ultrasonic(trigPin,echoPin); //INICIALIZANDO OS PINOS DO ARDUINO
int distancia_cm; //VARIÁVEL DO TIPO INTEIRO
//String distancia; //VARIÁVEL DO TIPO STRING
float volume_cm3;
float volume_litros;
float lado = 9.3;
float area_base_cm2;
float volume_litros_conversao;

void setup(){
  lcd.init();
  lcd.backlight();
  pinMode(echoPin, INPUT); //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT); //DEFINE O PINO COMO SAIDA (ENVIA)
  Serial.begin(9600); //INICIALIZA A PORTA SERIAL
  }

void medicao(){
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
    //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
    //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
    //NA VARIAVEL "distancia"
    distancia_cm = (ultrasonic.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
    //distancia = String(distancia); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    Serial.print("Distancia ");
    Serial.println(distancia_cm);

    float area_base_cm2 = lado * lado;
    float volume_cm3 = area_base_cm2 * distancia_cm;
    float volume_litros_total = volume_cm3 / 1000.0;
    float volume_litros_atual = 1.73 - volume_litros_total;
    float volume_litros_porcentagem = (volume_litros_atual / 1.73) * 100;
    Serial.print("Volume cm3: ");
    Serial.println(volume_cm3);
    Serial.print("Volume total de litros: ");
    Serial.println(volume_litros_total);
    Serial.print("Volume atual do reservatorio: ");
    Serial.println(volume_litros_porcentagem);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reservatorio em:");
    lcd.setCursor(0, 1);
    lcd.print(volume_litros_porcentagem);
    lcd.setCursor(4,1);
    lcd.print("%");
    delay(1000);
    lcd.clear();
 }

void loop(){

  medicao();
}