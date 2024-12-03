#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Wire.h"
#include "RTClib.h"

//Feito por Luis Otavio, prestando serviços à EEEP Dr Salomão Alves de Moura
//@_otavio.silveira
//use os pinos 2 e 3 para conectar-se com o arduino
static const uint8_t PIN_MP3_TX = 2; // Conecta ao RX do módulo
static const uint8_t PIN_MP3_RX = 3; // Conecta ao TX do módulo
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Cria o objeto do Player
DFRobotDFPlayerMini player;

// Cria o objeto RTC
RTC_DS3231 rtc;

// Variáveis para rastrear a última vez que uma música foi tocada
int lastPlayedHour = -1;
int lastPlayedMinute = -1;

void setup() {
  // Inicia a porta serial USB para depuração
  Serial.begin(9600);
  
  // Inicia a porta serial para o DFPlayer Mini
  softwareSerial.begin(9600);
  
  // Pequeno atraso para garantir a inicialização do DFPlayer Mini
  delay(1000);

  // Inicia a comunicação com o DFPlayer Mini
  if (player.begin(softwareSerial)) {
    Serial.println("DFPlayer Mini online.");
    player.volume(10);// Define o volume máximo (0 a 30).
    player.setTimeOut(5000); // Timeout de 5 segundos
  } 
    
  else {
    Serial.println("Falha ao conectar com o DFPlayer Mini!");
    while (1); // Pausa o código se falhar
  }

  // Inicializa o RTC
  if (!rtc.begin()) {
    Serial.println("RTC não encontrado");
    while (1); // Pausa se o RTC não for encontrado
  }

  // Opcionalmente, você pode ajustar o RTC aqui se ele não estiver ajustado:
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}
void loop() {
  DateTime now = rtc.now();
  int currentHour = now.hour();
  int currentMinute = now.minute();
  int dayOfWeek = now.dayOfTheWeek();
  int second = now.second();
  
  // Toca apenas se for de segunda a sexta-feira (1-5)
  if (now.dayOfTheWeek() >= 1 && now.dayOfTheWeek() <= 5) {
    // Verifica se já tocou no horário atual
    if (currentHour == lastPlayedHour && currentMinute == lastPlayedMinute) {
      return; // Sai da função loop, para evitar repetição
    }
    // Se quiser alterar os horários, modifique os IF's abaixo
    if (now.hour() == 6 && now.minute() == 59 ) {
      Serial.println("Tocando faixa 1 às 07:00, vamos estudar,galera!");
      player.play(1);
      delay(30000);
      player.stop();
      Serial.print("parou a musga");
      
    } if (now.hour() == 8 && now.minute() == 39 ) {
      Serial.println("Tocando faixa 2 às 08:40, hora do lanche.");
      player.play(1);
      delay(30000);
      player.stop();
    } 
    if (now.hour() == 9 && now.minute() == 9  ) {
      Serial.println("Tocando faixa 3 às 09:10, voltar para as jaulas.");
      player.play(1);
      delay(30000);
      player.stop();
    } 
    if (now.hour() == 11 && now.minute() == 39  ) {
      Serial.println("Tocando faixa 4 às 11:40, almoçar né pai");
      player.play(1);
      delay(30000);
      player.stop();
    } 
    if (now.hour() == 12 && now.minute() == 49 ) {
      Serial.println("Tocando faixa 5 às 12:50, ja foi metade do dia");
      player.play(1);
      delay(30000);
      player.stop();
    } 
    if (now.hour() == 14 && now.minute() == 29 ) {
      Serial.println("Tocando faixa 6 às 14:30, ta quase");
      player.play(1);
      delay(30000);
      player.stop();
    }
    if (now.hour() == 14 && now.minute() == 49 ) {
      Serial.println("Tocando faixa 7 às 14:50, últimas duas, o pai, so gratidao ");
      player.play(1);
      delay(30000);
      player.stop();
    } 
    if (now.hour() == 16 && now.minute() == 29) {
      Serial.println("Tocando faixa 8 às 16:30 , casa ne papai");
      player.play(1);
      delay(30000);
      player.stop();
    }

    // Atualiza a última hora e minuto tocado
    lastPlayedHour = currentHour;
    lastPlayedMinute = currentMinute;
  }
  // Serial.print(now.second());
  // Serial.print("Segundos acima");
 
  delay(1000); // Atraso entre as verificações
}
