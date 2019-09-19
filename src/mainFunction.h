int seconds = 0;   // variavel que armazena o tempo em segundos

//============================CARACTERES WIFI========================================================

byte wifiOn[8] = {    // wifi ON, 0
        B00000,
        B00000,
        B11111,
        B00000,
        B01110,
        B00000,
        B00100,
        B00000,
};
byte wifiOff[8] = {   // wifi OFF, 1
        B00000,
        B00000,
        B10001,
        B01010,
        B00100,
        B01010,
        B10001,
        B00000,
};

//============================FUNÇÃO QUE INDICA QUE O ESP ENTROU NO MODO AP========================

void configModeCallback (WiFiManager *myWiFiManager) {
        Serial.println("Entrou no modo de configuração");
        Serial.println(WiFi.softAPIP()); //imprime o IP do AP
        Serial.println(myWiFiManager->getConfigPortalSSID()); //imprime o SSID criado da rede
}

//============================FUNÇÃO QUE INDICA QUE UMA NOVA REDE FOI SALVA========================

void saveConfigCallback () {
        Serial.println("Configuração salva");
        Serial.println(WiFi.softAPIP()); //imprime o IP do AP
}

//============================FUNÇÃO QUE INICIA A CONEXÃO COM UMA REDE ============================

void initWifiManager(){
   wifiManager.setConnectTimeout(7); // 7 segundos para se conectar a uma rede salva
   wifiManager.setConfigPortalTimeout(120); // 120 segundos para configurar a conexão wifi do esp
   wifiManager.autoConnect("Rochaut"); // se já existir uma rede configurada vai conectar sozinho
   delay(1000);  // debug
   Tela::setAuxTroca(0x01);
}

//============================FUNÇÃO QUE ATIVA O BUZZER============================================

void buzzer(){  // usada ao pressionar uma tecla
        digitalWrite(buzz,HIGH); // aciona o buzzer
        delay(200);           // aguarda 200ms
        digitalWrite(buzz,LOW); // aciona o buzzer
}

//============================FUNÇÃO QUE VERIFICA SE ESTÁ CONECTADO NO WIFI PARA ATUALIZAR A DATA============

void atualizaHorario(){
   if((objR.getHora() == 0 || objR.getHora() == 6 || objR.getHora() == 12 ||
      objR.getHora() == 18) && objR.getMin() == 0 && (seconds == 5 || seconds == 10))
   {
      objTela.setServerOn(objApi.serverOn());
      objR.atualizaHorario(objApi.getDate());
   }
}

//============================FUNÇÃO QUE RETORNA PARA TELA INICIAL SE TIVER INATIVIDADE NA TELA==============

void telaInativa(){
   if((objTela.getAuxExi() != 0x01 && Tela::getAuxTempoTelaInativa() > 1 )
      || (objTela.getAuxExi() == 0x01 && Tela::getAuxTelaInicial() != "inicial" && Tela::getAuxTempoTelaInativa() > 1)){
         Principal::resetValorAuxStore();
         Tela::resetAuxTelaInativa();
         Tela::setAuxTelaInicial("inicial");
         Senha::resetaNumber();
         Senha::resetaLogin();
         Senha::resetaNSenha();
         Senha::resetaCSenha();
         Tela::setAuxTroca(0x01);
   } else {
      return;
   }
}
