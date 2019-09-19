#include "libs.h"
#include "rfid.h"
#include "api.h"
#include "senha.h"
#include "telas.h"
#include "relogio.h"
#include "principal.h"

// ============== temporário ==============
const char *ssid     = " ";
const char *password = " ";
char leitura = 0;
//============================CONFIGURAÇÃO DOS ATUADORES===========================================

#define ledG 17   // Led verde - TX2
#define ledR 16   // Led vermelho - RX2
#define buzz 4    // buzzer - D4

//============================DECLARAÇÃO DE OBJETOS================================================

WiFiManager wifiManager;  // utilizado para configurar rede

//============================CONFIGURAÇÃO DO LCD==================================================

LiquidCrystal_I2C lcd(0x3F,16,2);   // configura o display 16x2 no endereço 0x3F, pinos esp 32 SDA-D21 e SCL-D22

//============================CONFIGURAÇÃO DO RFID ================================================

#define SS_PIN    2  // antes 21
#define RST_PIN   5  // antes 22
MFRC522 mfrc522(SS_PIN, RST_PIN); // instancia e configuração do modulo

//============================DECLARAÇÃO DE OBJETOS==================================================

RFID objRFID;
API objApi;
HTTPClient http;
Tela objTela;
Relogio objR;
Principal objMain;
Senha objSenha;

//===================================================================================================

void setObjetos();
void testeLeitura(char leitura);

//============================INCLUIR LIBS=========================================================

#include "mainFunction.h" // tem que incluir antes de rtosFunction.h
#include "rtosFunction.h"

//============================CONFIGURAÇÕES INICIAIS===============================================

void setup() {
   xTaskCreatePinnedToCore(keyboardReading, "keyboardReading", 10000, NULL, 3, NULL, 0); // cria a tarefa que faz a leitura do teclado
   xTaskCreatePinnedToCore(countSeconds, "countSeconds", 10000, NULL, 2, NULL, 0); // cria a tarefa que faz o incremente dos segundos

   Serial.begin(115200);

   SPI.begin();  // inicia comunicação SPI
   mfrc522.PCD_Init(); // Inicia MFRC522, RFID
   lcd.init();          // inicializa o display I2C
   lcd.backlight();

   lcd.createChar(0, wifiOff); // simbolo "X"
   lcd.createChar(1, wifiOn);  // simbolo de wifi conectado

   pinMode(ledG, OUTPUT);
   pinMode(ledR, OUTPUT);
   pinMode(buzz, OUTPUT);
   pinMode(12,OUTPUT); // Coluna 1 teclado
   pinMode(13,OUTPUT); // Coluna 2 teclado
   pinMode(14,OUTPUT); // Coluna 3 teclado
   pinMode(27,INPUT); // Linha 1 teclado
   pinMode(26,INPUT); // Linha 2 teclado
   pinMode(25,INPUT); // Linha 3 teclado
   pinMode(33,INPUT); // Linha 4 teclado

   setObjetos();

   Tela::setAuxTroca(0x0C);

   wifiManager.setAPCallback(configModeCallback);
   wifiManager.setSaveConfigCallback(saveConfigCallback);

   objTela.setServerOn(objApi.serverOn()); // verifica se possui conexão com servidor
   seconds = 0;
}

//============================LOOP=================================================================

void loop() {
   if((objTela.getAuxExi() == 0x01 && Tela::getAuxTelaInicial() == "inicial") || objTela.getAuxExi() == 0x0B)
      objRFID.leituraRFID();

   objTela.exibeTela();
   objTela.trocaTela();

   telaInativa();

   objR.getDataComp();  // função para o relogio funcionar
   atualizaHorario();

   if(Serial.available() > 0){
      leitura = Serial.read();
      testeLeitura(leitura);
   }
}

void testeLeitura(char leitura){
   if(leitura == '1'){
      WiFi.begin(ssid, password);//Conecta na rede
      Serial.println("Rede Resetada");
   }
   else if(leitura == '2'){
      if ( WiFi.status() != WL_CONNECTED ){
         Serial.println("initWifiManager: ");
         initWifiManager();
      }
   }
   else if(leitura == '3'){
      if ( WiFi.status() == WL_CONNECTED ){
         Serial.print("IP: ");
         Serial.println(WiFi.localIP());
      }
   }
   else if(leitura == '4'){
      Serial.println("Acesso Cartao");
      RFID::setOpcaoRFID(0x00);

   }
   else if(leitura == '5'){
      Serial.println("Cadastro Tag");
      RFID::setOpcaoRFID(0x01);
   }
   else if(leitura == '6'){
      Serial.println("Deleta Tag");
      RFID::setOpcaoRFID(0x02);
   }
   else if(leitura == '7'){
      Serial.println("Get hora.");
      objApi.getDate();
   }
   else if(leitura == '8'){
      Serial.println("Teste hora.");
      objR.atualizaHorario(objApi.getDate());
      Serial.println("getDataComp");
      Serial.println(objR.getDataComp());
   }
   else if(leitura == '9'){
      Serial.println("Server on ?");
      objTela.setServerOn(objApi.serverOn());
      String serverOn = objApi.serverOn() ? "Servidor Online" : "Servidor Offline";
      Serial.println(serverOn);
   }
   else if(leitura == '0'){
      Serial.println("authByLogin");
      if(objApi.authByLogin("1234","4321")) Serial.println("Autenticado");
       else Serial.println("Não Autenticado");
   }
   else if(leitura == 'a'){
      Serial.print("Teste Get https: ");
      objApi.getTesteHttps();
   }
}


//============================FUNÇÃO PARA SETAR OBJETOS======================================================

void setObjetos(){
   objRFID.setRFID(mfrc522);
   objRFID.setAPI(objApi);
   objRFID.setLcd(lcd);
   objApi.setHttp(http);
   objTela.setLcd(lcd);
   objTela.setRelogio(objR);
   objMain.setAPI(objApi);
   objMain.setRelogio(objR);
}
