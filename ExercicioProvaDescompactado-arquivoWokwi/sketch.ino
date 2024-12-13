#include <WiFi.h>
#include <HTTPClient.h>
//Variáveis da internet interna da simulação
#define ssid "Wokwi-GUEST"
#define password ""


#define led_azul 9 // Pino utilizado para controle do led azul
#define led_verde 2 // Pino utilizado para controle do led verda
#define led_vermelho 40 // Pino utilizado para controle do led vermelho
#define led_amarelo 9 // Pino utilizado para controle do led azul

const int botaoPin = 18;  // Número do pino de ativação do botão 
int estadoBotao = 0;  // variável que lê o estado do botão 

const int ldrPin = 4;  // Pino do ldr
int limite=600;

void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_azul,OUTPUT);
  pinMode(led_verde,OUTPUT);
  pinMode(led_vermelho,OUTPUT);
  pinMode(led_amarelo,OUTPUT);

  // Inicialização das entradas
  pinMode(botaoPin, INPUT); // Inicializa o botão como um input

  digitalWrite(led_azul, LOW);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600
  Serial.print("Conectando-se ao Wi-Fi");
  WiFi.begin("Wokwi-GUEST", "", 6); // Conexão à rede WiFi aberta com SSID Wokwi-GUEST

//  while (WiFi.status() != WL_CONNECT_FAILED) {
//    delay(100);
//    Serial.print(".");
//  }
//  Serial.println("Conectado ao WiFi com sucesso!"); // Considerando que saiu do loop acima, o ESP32 agora está conectado ao WiFi (outra opção é colocar este comando dentro do if abaixo)

  // Verifica estado do botão
  estadoBotao = digitalRead(botaoPin);
  if (estadoBotao == HIGH) {
    Serial.println("Botão pressionado!");
  } else {
    Serial.println("Botão não pressionado!");
  }

//  if(WiFi.status() == WL_CONNECTED){ // Se o ESP32 estiver conectado à Internet
//    HTTPClient http;
 // else {
 //   Serial.println("Wifi desconectado");
 // }
}

void loop() {
  int ldrstatus=analogRead(ldrPin);

  if(ldrstatus>=limite){
    Serial.print("Está escuro o LED está ligado");
    Serial.println(ldrstatus);
    digitalWrite(led_amarelo, HIGH);
    delay(100);
    digitalWrite(led_amarelo, LOW);
    delay(1000);

  }else{
    Serial.print("Está claro o LED foi desligado");
    Serial.println(ldrstatus);
    delay(100);

    digitalWrite(led_verde, HIGH);
    delay(3000);
    digitalWrite(led_verde, LOW);
    delay(100);

    digitalWrite(led_amarelo, HIGH);
    delay(2000);
    digitalWrite(led_amarelo, LOW);
    delay(100);

    digitalWrite(led_vermelho, HIGH);
    if (estadoBotao == HIGH) {
      delay(1000);
    }else {
      delay(2000);
    }
    digitalWrite(led_vermelho, LOW);
    delay(100);
  }
}