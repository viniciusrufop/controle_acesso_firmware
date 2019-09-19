#include "telas.h"

   Tela::Tela(){
      aux_telaInicial = "inicial";
      tempoBloqueio = 25;
      tentativasAcesso = 3;
      sistemaBloqueado = false;
   }
   Tela::~Tela(){}

   void Tela::setRelogio(Relogio &objR)
   {
      this->objRe = &objR;
   }
   void Tela::setLcd(LiquidCrystal_I2C &lcd)
   {
      this->lcd = &lcd;
   }
   void Tela::setWifiManager(WiFiManager &wifiManager)
   {
      this->wifiManager = &wifiManager;
   }

   /*static*/ boolean Tela::validacaoDataHora;
   /*static*/ void Tela::setValidacaoDataHora(boolean vf)
   {
      validacaoDataHora = vf;
   }
   /*static*/ boolean Tela::getValidacaoDataHora()
   {
      return validacaoDataHora;
   }
   /*static*/ int Tela::aux_telaInativa;
   /*static*/ void Tela::incrementaAuxTelaInativa()
   {
      aux_telaInativa++;
   }
   /*static*/ void Tela::resetAuxTelaInativa()
   {
      aux_telaInativa = 0;
   }
   /*static*/ int Tela::getAuxTempoTelaInativa()
   {
      return aux_telaInativa;
   }
   /*static*/ String Tela::aux_digiteSenha;   // "acesso","config", "novaSenhaAcesso", "novaSenhaMenu"
   /*static*/ void Tela::setAuxDigiteSenha(String qualSenha)
   {
      aux_digiteSenha = qualSenha;
   }
   /*static*/ String Tela::getAuxDigiteSenha()
   {
      return aux_digiteSenha;
   }
   /*static*/ String Tela::aux_telaInicial;
   /*static*/ void Tela::setAuxTelaInicial(String tela)
   {
      aux_telaInicial = tela;
   }
   /*static*/ String Tela::getAuxTelaInicial()
   {
      return aux_telaInicial;
   }
   /*static*/ boolean Tela::autenticado;
   /*static*/ void Tela::setAutenticado(boolean vf)
   {
      autenticado = vf;
   }
   /*static*/ boolean Tela::getAutenticado()
   {
      return autenticado;
   }
   /*static*/ char Tela::aux_exi;
   /*static*/ void Tela::setAuxExi(char auxExi)
   {
      aux_exi = auxExi;
   }
   /*static*/ char Tela::getAuxExi()
   {
      return aux_exi;
   }
   /*static*/ char Tela::aux_troca;
   /*static*/ void Tela::setAuxTroca(char at)
   {
      aux_troca = at;
   }
   /*static*/ char Tela::getAuxTroca()
   {
      return aux_troca;
   }
   /*static*/ String Tela::aux_rfid;
   /*static*/ void Tela::setAuxRfid(String value)
   {
      aux_rfid = value;
   }
   /*static*/ String Tela::getAuxRfid()
   {
      return aux_rfid;
   }
   /*static*/ int Tela::tempoBloqueio;
   /*static*/ void Tela::decrementaTempoBloqueio()
   {
      tempoBloqueio--;
   }
   /*static*/ void Tela::resetTempoBloqueio()
   {
      tempoBloqueio = 25;
   }
   /*static*/ int Tela::getTempoBloqueio()
   {
      return tempoBloqueio;
   }
   /*static*/ int Tela::tentativasAcesso;
   /*static*/ void Tela::resetTentativasAcesso()
   {
      tentativasAcesso = 3;
   }
   /*static*/ int Tela::getTentativasAcesso()
   {
      return tentativasAcesso;
   }
   /*static*/ boolean Tela::sistemaBloqueado;
   /*static*/ void Tela::setSistemaBloqueado(boolean vf)
   {
      sistemaBloqueado = vf;
   }
   /*static*/ boolean Tela::getSistemaBloqueado()
   {
      return sistemaBloqueado;
   }
   void Tela::setServerOn(boolean server)
   {
      this->serverOn = server;
   }
   boolean Tela::getServerOn()
   {
      return serverOn;
   }

   void Tela::exibeTela()
   {
      switch (getAuxExi())
      {
         case 0x01: telaInicial(); break;
         case 0x02: digiteSenha();break;
         case 0x03: liberacaoSistema();break;
         case 0x05: telaConfig();break;
         case 0x06: telaValidacaoDataHora();break;
         case 0x07: digiteNovaSenha();break;
         case 0x08: digiteConfirmaNovaSenha();break;
         case 0x09: telaValidacaoNovaSenha();break;
         case 0x0A: telaConfig2();break;
         case 0x0B: telaRFID(); break;
         case 0x0C: telaWifi(); break;
         case 0x0D: telaSistemaBloqueado(); break;
         case 0x0E: telaLogin();break;
         case 0x15: telaAguardaLogin();break;
      }
   }

   void Tela::trocaTela()
   {
      if(getAuxTroca() != 0x00){
         lcd->clear();
         resetAuxTelaInativa();
         setAuxExi(getAuxTroca());
         setAuxTroca(0x00);
      } else return;
   }

   void Tela::liberacaoSistema()
   {
      if(getAutenticado()){
         resetTentativasAcesso();
         lcd->setCursor(0,0);            // coloca o cursor do lcd na posição definida
         lcd->print("Sistema Liberado");   // mostra mensagem para o usuario
         digitalWrite(ledG,HIGH);             // liga o led verde
         digitalWrite(buzz,HIGH);             // liga o buzzer
         delay(1500);
         digitalWrite(ledG,LOW);             // desliga o led verde
         digitalWrite(buzz,LOW);             // desliga o buzzer
         setAuxTroca(0x01);
      } else {
         if(getServerOn()){
            tentativasAcesso--;
            lcd->setCursor(0,0);            // coloca o cursor do lcd na posição definida
            lcd->print("Sist. Bloqueado");   // mostra mensagem para o usuario
            lcd->setCursor(0,1);             // coloca o cursor do lcd na posição definida
            lcd->print(String(getTentativasAcesso())+" Tentativas"); // exibe a quantidade de vezes que o usuario pode errar a senha
            for(int i = 0; i < 3; i++) {
               digitalWrite(ledR,HIGH);
               digitalWrite(buzz,HIGH);       // liga o buzzer
               delay(200);
               digitalWrite(ledR,LOW);
               digitalWrite(buzz,LOW);       // liga o buzzer
               delay(200);
            }
         } else {
            lcd->setCursor(0,0);
            lcd->print("Falha de Conexao");
            lcd->setCursor(0,1);
            lcd->print("Com Servidor");
            delay(1500);
         }
         if(getTentativasAcesso() > 0){
            setAuxTroca(0x01);
         } else {
            setSistemaBloqueado(true);
            setAuxTroca(0x0D);
         }

      }
   }
//============================TELA INICIAL============================================================

   void Tela::telaInicial()
   {
      lcd->setCursor(0,0);
      if(getAuxTelaInicial() == "inicial"){
         if (objRe->getHora() >=6 && objRe->getHora() <=11) {lcd->print("Bom Dia");} // mostra mensagem para o usuario
         if (objRe->getHora() >=12 && objRe->getHora()<=17) {lcd->print("Boa Tarde");} // mostra mensagem para o usuario
         if (objRe->getHora() >=18 || objRe->getHora()<=5) {lcd->print("Boa Noite");} // mostra mensagem para o usuario
      } else if(getAuxTelaInicial() == "data"){
         lcd->print("Nova Data");
      } else if(getAuxTelaInicial() == "hora"){
         lcd->print("Nova Hora");
      }
      lcd->setCursor(0,1);
      lcd->print(objRe->getDataComp());

      if(WiFi.status() == WL_CONNECTED && !getServerOn()){
         lcd->setCursor(15,0);
         lcd->write(byte(1));
         lcd->setCursor(14,0);
         lcd->print("?");
      } else if (WiFi.status() == WL_CONNECTED && getServerOn()){
         lcd->setCursor(15,0);
         lcd->write(byte(1));
         lcd->setCursor(14,0);
         lcd->print(" ");
      } else {
         lcd->setCursor(15,0);
         lcd->write(byte(0));
         lcd->setCursor(14,0);
         lcd->print(" ");
      }
   }

//============================TELA PARA DIGITAR SENHA=================================================

   void Tela::digiteSenha()
   {

      if(getAuxDigiteSenha()=="acesso"){
         lcd->setCursor(1,0);
         lcd->print("Digite a senha");
      } else if(getAuxDigiteSenha()=="config"){
         lcd->setCursor(1,0);
         lcd->print("Menu de Config");
      } else if(getAuxDigiteSenha()=="novaSenhaAcesso"){
         lcd->setCursor(3,0);
         lcd->print("Senha Atual");
      } else if(getAuxDigiteSenha()=="novaSenhaMenu"){
         lcd->setCursor(3,0);
         lcd->print("Senha Menu");
      }

      String senha = String(Senha::getNumer1()) + String(Senha::getNumer2()) + String(Senha::getNumer3()) + String(Senha::getNumer4()); // junta em uma string os caractares que será armazenada a senha

      lcd->setCursor(6,1); // coloca o cursor do lcd na posição definida
      lcd->print(senha); // mostra no lcd a senha digitada
   }

//============================TELA PARA DIGITAR SENHA NOVA SENHA=============================================

   void Tela::digiteNovaSenha()
   {
      lcd->setCursor(3,0);
      lcd->print("Nova Senha");

      String novaSenha = String(Senha::getNSenha1()) + String(Senha::getNSenha2()) + String(Senha::getNSenha3()) + String(Senha::getNSenha4());

      lcd->setCursor(6,1); // coloca o cursor do lcd na posição definida
      lcd->print(novaSenha); // mostra no lcd a senha digitada
   }

//============================TELA PARA DIGITAR CONFIRMAÇÃO DA NOVA SENHA======================================

   void Tela::digiteConfirmaNovaSenha()
   {
      lcd->setCursor(1,0);
      lcd->print("Confirma Senha");

      String confirmaSenha = String(Senha::getCSenha1()) + String(Senha::getCSenha2()) + String(Senha::getCSenha3()) + String(Senha::getCSenha4());

      lcd->setCursor(6,1); // coloca o cursor do lcd na posição definida
      lcd->print(confirmaSenha); // mostra no lcd a senha digitada
   }

//============================TELA DE VALIDAÇÃO DA NOVA SENHA======================================
   void Tela::telaValidacaoNovaSenha()
   {
      if(getAutenticado()){
         lcd->setCursor(6,0); // coloca o cursor do lcd na posição definida
         lcd->print("Senha"); // mostra mensagem para o usuario
         lcd->setCursor(5,1); // coloca o cursor do lcd na posição definida
         lcd->print("Gravada"); // mostra mensagem para o usuario
         delay(1000);
         setAuxTroca(0x05);
      } else {
         lcd->setCursor(6,0); // coloca o cursor do lcd na posição definida
         lcd->print("Senha"); // mostra mensagem para o usuario
         lcd->setCursor(4,1); // coloca o cursor do lcd na posição definida
         lcd->print("Incorreta"); // mostra mensagem para o usuario
         delay(1000);
         setAutenticado(true);
         setAuxTroca(0x05);
      }
   }

//============================TELA LOGIN=====================================================================

   void Tela::telaLogin()
   {
      String senha = String(Senha::getNumer1()) + String(Senha::getNumer2()) + String(Senha::getNumer3()) + String(Senha::getNumer4()); // junta em uma string os caractares que será armazenado o login
      String login = String(Senha::getLogin1()) + String(Senha::getLogin2()) + String(Senha::getLogin3()) + String(Senha::getLogin4()); // junta em uma string os caractares que será armazenada a senha
      if(Principal::getValorAuxStore()>=4) {
         lcd->setCursor(7,1);
         lcd->print("->");
         lcd->setCursor(7,0);
         lcd->print("  ");
      } else {
         lcd->setCursor(7,0);
         lcd->print("->");
         lcd->setCursor(7,1);
         lcd->print("  ");
      }
      lcd->setCursor(0,0);
      lcd->print("Login:");
      lcd->setCursor(10,0);
      lcd->print(login);
      lcd->setCursor(0,1);
      lcd->print("Senha:");
      lcd->setCursor(10,1);
      lcd->print(senha);
   }
   void Tela::telaAguardaLogin()
   {
      lcd->setCursor(3,0);
      lcd->print("Conectanto");
      lcd->setCursor(3,1);
      lcd->print("Aguarde...");
   }

//============================TELA DE CONFIGURAÇÃO====================================================

   void Tela::telaConfig(){
      if(getAutenticado()){
         lcd->setCursor(0,0);             // coloca o cursor do lcd na posição definida
         lcd->print(" 1-Alterar Data  3-Alterar Senha"); // mostra mensagem para o usuario
         lcd->setCursor(0,1);             // coloca o cursor do lcd na posição definida
         lcd->print(" 2-Alterar Hora  4-Proximo");        // mostra mensagem para o usuario
         lcd->scrollDisplayLeft();        // faz a menssagem passar em movimento no lcd
         delay(350);
         cont_scroll++;                  // acrescenta uma unidade na variavel
         if(cont_scroll == 17) {         // se a variavel chegar ao valor de 17 entra no bloco
            cont_scroll = 0;        // reseta variavel
            lcd->clear();            // lampa o lcd para a menssagem passar novamente
         }
      } else {
         liberacaoSistema(); // sist. bloqueado
      }
   }

   void Tela::telaConfig2(){
      lcd->setCursor(0,0);                   // coloca o cursor do lcd na posição definida
      lcd->print(" 1-Conecatar Wifi  3-Remover TAG");       // mostra mensagem para o usuario
      lcd->setCursor(0,1);                   // coloca o cursor do lcd na posição definida
      lcd->print(" 2-Cadastrar TAG   4-Alterar Senha Menu");              // mostra mensagem para o usuario
      lcd->scrollDisplayLeft();              // faz a menssagem passar em movimento no lcd
      delay(350);
      cont_scroll++;                           // acrescenta uma unidade na variavel
      if(cont_scroll == 19) {                  // se a variavel chegar ao valor de 17 entra no bloco
         cont_scroll = 0;              // reseta variavel
         lcd->clear();                  // lampa o lcd para a menssagem passar novamente
      }
   }

//============================TELA DE VALIDAÇÃO DE DATA E HORA===============================================
   void Tela::telaValidacaoDataHora()
   {
      if(getValidacaoDataHora()){
         if(getAuxTelaInicial() == "data") {
            lcd->setCursor(6,0);    // coloca o cursor do lcd na posição definida
            lcd->print("Data"); // mostra mensagem para o usuario
         } else if(getAuxTelaInicial() == "hora") {
            lcd->setCursor(6,0);    // coloca o cursor do lcd na posição definida
            lcd->print("Hora"); // mostra mensagem para o usuario
         }
         lcd->setCursor(4,1);
         lcd->print("Gravada");  // mostra mensagem para o usuario
         setAuxTelaInicial("inicial");
         delay(1000);
         setAuxTroca(0x05);
      } else {
         lcd->setCursor(6,0);    // coloca o cursor do lcd na posição definida
         lcd->print("Valor"); // mostra mensagem para o usuario
         lcd->setCursor(4,1);    // coloca o cursor do lcd na posição definida
         lcd->print("Invalido"); // mostra mensagem para o usuario
         delay(1000);
         setAuxTroca(0x01);
      }
   }
//============================TELA PARA CADASTRAR NOVA TAG===============================================
   void Tela::telaRFID()
   {
      if(getAuxRfid() == "cadastrar"){
         lcd->setCursor(0,0);
         lcd->print("Cadastrar TAG");
         lcd->setCursor(0,1);
         lcd->print("Aproxime Cartao");
      } else if(getAuxRfid() == "tagCadastrada"){
         lcd->clear();
         lcd->setCursor(0,0);
         lcd->print("TAG Cadastrada");
         delay(1000);
         setAuxTroca(0x0A);
      } else if(getAuxRfid() == "erro"){
         lcd->clear();
         lcd->setCursor(0,0);
         lcd->print("Erro na operacao");
         delay(1000);
         setAuxTroca(0x0A);
      } else if(getAuxRfid() == "remover"){
         lcd->setCursor(0,0);
         lcd->print("Remover TAG");
         lcd->setCursor(0,1);
         lcd->print("Aproxime Cartao");
      } else if(getAuxRfid() == "tagRemovida"){
         lcd->clear();
         lcd->setCursor(0,0);
         lcd->print("TAG Removida");
         delay(1000);
         setAuxTroca(0x0A);
      }
   }
//============================TELA QUE EXIBE AS CONFIGURAÇÕES DO WIFI========================================

   void Tela::telaWifi()
   {
      if ( WiFi.status() != WL_CONNECTED ) { // o que fazer enquanto não conectar
         lcd->setCursor(0,0);lcd->write(byte(1));
         lcd->setCursor(2,0);lcd->print(":Rochaut       ");   // rede para configurar wifi
         lcd->setCursor(0,1);lcd->print("IP:");
         lcd->setCursor(3,1);lcd->print("192.168.4.1   ");     // ip para digitar no navegador
         wifiManager->setConnectTimeout(7); // 7 segundos para se conectar a uma rede salva
         wifiManager->setConfigPortalTimeout(120); // 120 segundos para configurar a conexão wifi do esp
         if(!wifiManager->autoConnect("Rochaut")){
            WiFi.begin(" ", " ");
         }
         // wifiManager->autoConnect("Rochaut"); // se já existir uma rede configurada vai conectar sozinho
         delay(1000);  // debug
         setAuxTroca(0x01); // chama tela inicial
      }
      lcd->setCursor(0,0);lcd->write(byte(1));
      lcd->setCursor(2,0);lcd->print(":"+WiFi.SSID());   // exibe o nome da rede em que a esp está conectada
      lcd->setCursor(0,1);lcd->print("IP:");
      lcd->setCursor(3,1);lcd->print(WiFi.localIP());  // exibe o ip adquirido na rede
   }

//============================TELA QUE IDENTIFICA QUE SE O SISTEMA FOI BLOQUEADO=============================

   void Tela::telaSistemaBloqueado()
   {
      lcd->setCursor(0,0);
      lcd->print("Sist. Bloq.   ");
      if(getTempoBloqueio() > 9) {
         lcd->setCursor(14,0); // coloca o cursor do lcd na posição definida
         lcd->print(String(getTempoBloqueio()));
      } else{
         lcd->setCursor(14,0); // coloca o cursor do lcd na posição definida
         lcd->print(" "); // limpa posição de conexão com servidor
         lcd->setCursor(15,0); // coloca o cursor do lcd na posição definida
         lcd->print(String(getTempoBloqueio()));
      }
      lcd->setCursor(0,1);            // coloca o cursor do lcd na posição definida
      lcd->print(objRe->getDataComp());// exibe na tela a data e as horas
   }
