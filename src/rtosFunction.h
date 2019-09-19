//============================TAREFA QUE FAZ A LEITURA DO TECLADO FÍSICO=============================

// bool keyboardOnOff = true;
void keyboardReading(void *pvParameters){
   for (;;) {   // loop infinito da tarefa
      // if(keyboardOnOff) {
      if(!Tela::getSistemaBloqueado()) {
         for(int coluna = 12; coluna <= 14; coluna++) {
            digitalWrite(12,HIGH);
            digitalWrite(13,HIGH);
            digitalWrite(14,HIGH);
            digitalWrite(coluna,LOW); // fica alternando entre os pinos o sinal logico baixo LOW a cada 10ms
            //===============================LINHA 1===============================
            if(digitalRead(27) == LOW && digitalRead(12) == LOW)  {objMain.store(1); while(digitalRead(27) == LOW) {buzzer();}; Serial.print("1");}// armazenha o valor 1
            if(digitalRead(27) == LOW && digitalRead(13) == LOW)  {objMain.store(2); while(digitalRead(27) == LOW) {buzzer();}; Serial.print("2");}// armazenha o valor 2
            if(digitalRead(27) == LOW && digitalRead(14) == LOW)  {objMain.store(3); while(digitalRead(27) == LOW) {buzzer();}; Serial.print("3");}// armazenha o valor 3
            //===============================LINHA 2===============================
            if(digitalRead(26) == LOW && digitalRead(12) == LOW)  {objMain.store(4); while(digitalRead(26) == LOW) {buzzer();}; Serial.print("4");}// armazenha o valor 4
            if(digitalRead(26) == LOW && digitalRead(13) == LOW)  {objMain.store(5); while(digitalRead(26) == LOW) {buzzer();}; Serial.print("5");}// armazenha o valor 5
            if(digitalRead(26) == LOW && digitalRead(14) == LOW)  {objMain.store(6); while(digitalRead(26) == LOW) {buzzer();}; Serial.print("6");}// armazenha o valor 6
            //===============================LINHA 3===============================
            if(digitalRead(25) == LOW && digitalRead(12) == LOW)  {objMain.store(7); while(digitalRead(25) == LOW) {buzzer();}; Serial.print("7");}// armazenha o valor 7
            if(digitalRead(25) == LOW && digitalRead(13) == LOW)  {objMain.store(8); while(digitalRead(25) == LOW) {buzzer();}; Serial.print("8");}// armazenha o valor 8
            if(digitalRead(25) == LOW && digitalRead(14) == LOW)  {objMain.store(9); while(digitalRead(25) == LOW) {buzzer();}; Serial.print("9");}// armazenha o valor 9
            //===============================LINHA 4===============================
            if(digitalRead(33) == LOW && digitalRead(12) == LOW)  {objMain.store(11); while(digitalRead(33) == LOW) {buzzer();}; Serial.print("*");}// armazenha o valor 11
            if(digitalRead(33) == LOW && digitalRead(13) == LOW)  {objMain.store(0); while(digitalRead(33) == LOW)  {buzzer();}; Serial.print("0");}// armazenha o valor 0
            if(digitalRead(33) == LOW && digitalRead(14) == LOW)  {objMain.store(12); while(digitalRead(33) == LOW) {buzzer();}; Serial.print("#");}// armazenha o valor 12
            delay(10);
         }
      }else{delay(10);}
   }
}

//============================TAREFA QUE FAZ O INCREMENTO DOS SEGUNDOS===============================
int aux_telaLogin = 0;  // verifica o tempo com a tecla pressionada
void countSeconds(void *pvParameters){
   TickType_t init;
   init = xTaskGetTickCount();
   for (;;) { // loop infinito da tarefa
      seconds++; // incremeneta 1 segundo
      objR.setSegundos(seconds);
      if(objR.getSegundos()>59){
         objTela.setServerOn(objApi.serverOn()); // verifica se possui conexão com servidor
         Tela::incrementaAuxTelaInativa();
         seconds=0;
      }
      if(digitalRead(33) == LOW && digitalRead(12) == LOW) {
         // segura botao * na tela inicial por 3 segundos
         aux_telaLogin++;
         if(aux_telaLogin > 2) {
            Tela::setAuxTroca(0x0E);
            aux_telaLogin = 0;
         }
      } else {
         aux_telaLogin = 0;
      }
      if(Tela::getSistemaBloqueado()){
         Tela::decrementaTempoBloqueio();
         if(Tela::getTempoBloqueio() == 0){
            Tela::resetTempoBloqueio();
            Tela::resetTentativasAcesso();
            Tela::setSistemaBloqueado(false);
            Tela::setAuxTroca(0x01);
         }
      }
      // Serial.print("tempo: ");    // exibe no monitor serial a mensagem
      // Serial.println(seconds);   // exibe os segundos no monitor serial
      vTaskDelayUntil(&init,pdMS_TO_TICKS(1000)); // aguarda 1 segundo para rodar o loop da tarefa novamente
   }
}
