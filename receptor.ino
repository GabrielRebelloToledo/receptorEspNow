#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
typedef struct message {
  boolean Botao_0;
  boolean Botao_1;
  boolean Botao_2;
  boolean Botao_3;
  boolean Botao_4;
  boolean Botao_5;
  boolean Botao_6;
  boolean Botao_7;
  boolean Botao_JoyA;
  boolean Botao_JoyB;
  byte Joystick_AX;
  byte Joystick_AY;
  byte Joystick_BX;
  byte Joystick_BY;
  byte Pot_A;
  byte Pot_B;
} message;
message myMessage;
void onDataReceiver(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
   Serial.println("Mensagem recebida.");
  // Não usamos mac para verificar o remetente
  // Vamos transformar os dados recebidos em nossa estrutura de mensagem
  memcpy(&myMessage, incomingData, sizeof(myMessage));
  
  Serial.print("Values:");
  Serial.print(myMessage.Joystick_AX, DEC);
  Serial.print(",");
  Serial.print(myMessage.Joystick_AY, DEC);
  Serial.print(",");
  Serial.print(myMessage.Joystick_BX, DEC);
  Serial.print(",");
  Serial.println(myMessage.Joystick_BY, DEC);
  
}
void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  ESP.eraseConfig();
 
  // Modo Wifi STA
  WiFi.mode(WIFI_STA);
  // Obter Mac Add
  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("\nReceptor ESP-Now");
  
  // Initializing the ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problema durante a inicialização ESP-NOW");
    return;
  }
  
  //esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  // Podemos registrar a função de retorno de chamada do receptor
  esp_now_register_recv_cb(onDataReceiver);
}
void loop() {
 // coloque seu código principal aqui, para executar repetidamente:
}