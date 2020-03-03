#include "principal.h"

Principal::Principal(){
   aux_store = 0x00;
}
Principal::~Principal(){
}
//---------------------SET OBJETOS-----------------------
   void Principal::setAPI(API &objAPI)
   {
      this->objAPI = &objAPI;
   }
   void Principal::setRelogio(Relogio &objR)
   {
      this->objRe = &objR;
   }

//-------------------METODOS-----------------------------
   void Principal::setKeyPressValue(short value)
   {
      this->keyPressValue = value;
   }
   short Principal::getKeyPressValue()
   {
      return keyPressValue;
   }
   /*static*/ char Principal::aux_store;
   /*static*/ char Principal::getValorAuxStore()
   {
      return aux_store;
   }
   /*static*/ void Principal::resetValorAuxStore()
   {
      aux_store = 0;
   }

   void Principal::store(short value)
   {
      setKeyPressValue(value);
      switch (Tela::getAuxExi())
      {
      case 0x01: telaInicialStore(); break;
      case 0x02: digiteSenhaStore(); break;
      case 0x05: telaConfigStore(); break;
      case 0x07: digiteNovaSenhaStore(); break;
      case 0x08: digiteConfirmaNovaSenhaStore(); break;
      case 0x0A: telaConfigStore2(); break;
      case 0x0B: telaRFIDStore(); break;
      case 0x0C: telaWifiStore(); break;
      case 0x0E: telaLoginStore(); break;
      }
   }
//----------------------------Tela inicial-----------------------------------------------------------
   void Principal::telaInicialStore()
   {
      if(Tela::getAuxTelaInicial() == "inicial"){
         String option = (getKeyPressValue() != 12) ? "acesso" : "config";
         Tela::setAuxDigiteSenha(option);
         Tela::setAuxTroca(0x02);
      } else if(Tela::getAuxTelaInicial() == "data"){
         alterarData();
      } else if(Tela::getAuxTelaInicial() == "hora"){
         alterarHora();
      }
   }
   void Principal::alterarData()
   {
      aux_store++;
      if(getKeyPressValue() == 11) {
         aux_store=0x00;objRe->resetaData();
      } else if(getKeyPressValue() == 12) {
         aux_store=0x00;
         if(!validacaoDataHora("data")) objRe->resetaData();
         Tela::setValidacaoDataHora(validacaoDataHora("data"));
         Tela::setAuxTroca(0x06);
      }
      switch (aux_store)
      {
         case 0x01: objRe->setDia1(getKeyPressValue()); break; // armazena o primeiro algarismo do dia
         case 0x02: objRe->setDia2(getKeyPressValue()); break; // armazena o segundo algarismo do dia
         case 0x03: objRe->setMes1(getKeyPressValue()); break; // armazena o primeiro algarismo do mes
         case 0x04: objRe->setMes2(getKeyPressValue()); break; // armazena o segundo algarismo do mes
         case 0x05: objRe->setAno1(getKeyPressValue()); break; // armazena o terceiro algarismo do ano
         case 0x06: objRe->setAno2(getKeyPressValue()); break; // armazena o quarto algarismo do ano
      }
   }
   void Principal::alterarHora()
   {
      aux_store++;
      if(getKeyPressValue() == 11) {
         aux_store=0x00;objRe->resetaHoras();
      } else if(getKeyPressValue() == 12) {
         aux_store=0x00;
         if(!validacaoDataHora("hora")) objRe->resetaHoras();
         Tela::setValidacaoDataHora(validacaoDataHora("hora"));
         Tela::setAuxTroca(0x06);
      }
      switch (aux_store)
      {
         case 0x01: objRe->setHora1(getKeyPressValue()); break; // armazena o primeiro algarismo da hora
         case 0x02: objRe->setHora2(getKeyPressValue()); break; // armazena o segundo algarismo da hora
         case 0x03: objRe->setMin1(getKeyPressValue()); break;// armazena o primeiro algarismo dos minutos
         case 0x04: objRe->setMin2(getKeyPressValue()); break;// armazena o segundo algarismo dos minutos
      }
   }
   boolean Principal::validacaoDataHora(String dataHora)
   {
      if(dataHora == "data"){
         return (objRe->getDia() > 0 && objRe->getDia() <= 31 && objRe->getMes() > 0 && objRe->getMes() <= 12 ) ? true : false;
      } else if(dataHora == "hora"){
         return (objRe->getHora()<=23 && objRe->getMin()<=59) ? true : false;
      } else return false;
   }
//----------------------------Tela para digitar senha------------------------------------------------
   void Principal::digiteSenhaStore()
   {
      aux_store++;

      if(getKeyPressValue() == 11 && Senha::verificaValorNulo("number") &&
         (Tela::getAuxDigiteSenha() == "novaSenhaAcesso" || Tela::getAuxDigiteSenha() == "novaSenhaAcesso") ) {
         aux_store=0x00;Tela::setAutenticado(true);Tela::setAuxTroca(0x05);// volta para o menu
      } else if(getKeyPressValue() == 11 && Senha::verificaValorNulo("number")) {  // se for pressionada a tecla "*" e os valores sao 0 volta pra tela inicial
         aux_store = 0x00; Tela::setAuxTroca(0x01);// tela inicial
      } else if(getKeyPressValue() == 11){
         aux_store = 0x00; Senha::resetaNumber();
      } else if(getKeyPressValue() == 12){
         if(Tela::getAuxDigiteSenha() == "acesso"){ // senha para acesso
            Tela::setAutenticado(Senha::cofirmaSenhaAcesso());
            Tela::setAuxTroca(0x03);// tela para verificar liberação do sistema
         } else if(Tela::getAuxDigiteSenha() == "config"){ // senha para entrar no menu de configuração
            Tela::setAutenticado(Senha::cofirmaSenhaMenu());
            Tela::setAuxTroca(0x05);// tela para verificar liberação do sistema
         } else if(Tela::getAuxDigiteSenha() == "novaSenhaAcesso"){
            if(Senha::cofirmaSenhaAcesso()){
               Tela::setAuxTroca(0x07); // tela digitar nova senha
            } else {
               Tela::setAutenticado(Senha::cofirmaSenhaAcesso());
               Tela::setAuxTroca(0x03);// tela para verificar liberação do sistema
            }
         } else if(Tela::getAuxDigiteSenha() == "novaSenhaMenu"){
            if(Senha::cofirmaSenhaMenu()){
               Tela::setAuxTroca(0x07);
            } else {
               Tela::setAutenticado(Senha::cofirmaSenhaMenu());
               Tela::setAuxTroca(0x03);
            }
         }
         aux_store = 0x00;
         Senha::resetaNumber();
      }
      switch(aux_store)
      {
         case 0x01: Senha::setNumer1(getKeyPressValue()); break; // armazena o primeiro valor digitado na variavel
         case 0x02: Senha::setNumer2(getKeyPressValue()); break; // armazena o segundo valor digitado na variavel
         case 0x03: Senha::setNumer3(getKeyPressValue()); break; // armazena o terceiro valor digitado na variavel
         case 0x04: Senha::setNumer4(getKeyPressValue()); break; // armazena o quarto valor digitado na variavel
      }
   }

//----------------------------Tela para digitar nova senha------------------------------------------------
   void Principal::digiteNovaSenhaStore()
   {
      aux_store++;
      if(getKeyPressValue() == 11 && Senha::verificaValorNulo("novaSenha")) { // se for pressionada a tecla "*" apaga os valores digitados
         aux_store=0x00;Tela::setAutenticado(true);Tela::setAuxTroca(0x05);// volta para o menu
      }else if(getKeyPressValue() == 11) {                  // se pressionar a tecla "*" limpa os caracteres digitados para digitar novamente
         aux_store=0x00;Senha::resetaNSenha();
      }else if(getKeyPressValue() == 12 ) {                 // se pressionar a tecla "#" vai para a tela para confirmar a nova senha
         aux_store=0x00;Tela::setAuxTroca(0x08);// volta para o menu
      }
      switch(aux_store)
      {
         case 0x01: Senha::setNSenha1(getKeyPressValue()); break; // armazena o primeiro valor digitado na variavel
         case 0x02: Senha::setNSenha2(getKeyPressValue()); break; // armazena o segundo valor digitado na variavel
         case 0x03: Senha::setNSenha3(getKeyPressValue()); break; // armazena o terceiro valor digitado na variavel
         case 0x04: Senha::setNSenha4(getKeyPressValue()); break; // armazena o quarto valor digitado na variavel
      }
   }
//----------------------------Tela para confirmar nova senha------------------------------------------------
   void Principal::digiteConfirmaNovaSenhaStore()
   {
      aux_store++;
      if(getKeyPressValue() == 11 && Senha::verificaValorNulo("confirmaSenha")) { // se for pressionada a tecla "*" apaga os valores digitados
         aux_store=0x00;Tela::setAuxTroca(0x07); // volta para tela anterior
      }else if(getKeyPressValue() == 11) {                  // se pressionar a tecla "*" limpa os caracteres digitados para digitar novamente
         aux_store=0x00;Senha::resetaCSenha();
      }else if(getKeyPressValue() == 12 ) {                 // se pressionar a tecla "#" vai para a tela para confirmar a nova senha
         aux_store=0x00;
         if (Tela::getAuxDigiteSenha() == "novaSenhaAcesso") { Senha::trocaSenha(Senha::cofirmaNovaSenha()); }
         if (Tela::getAuxDigiteSenha() == "novaSenhaMenu") { Senha::trocaSenhaMenu(Senha::cofirmaNovaSenha()); }
         Tela::setAutenticado(Senha::cofirmaNovaSenha());
         Tela::setAuxTroca(0x09);
         Senha::resetaCSenha();
         Senha::resetaNSenha();
      }
      switch(aux_store)
      {
         case 0x01: Senha::setCSenha1(getKeyPressValue()); break; // armazena o primeiro valor digitado na variavel
         case 0x02: Senha::setCSenha2(getKeyPressValue()); break; // armazena o segundo valor digitado na variavel
         case 0x03: Senha::setCSenha3(getKeyPressValue()); break; // armazena o terceiro valor digitado na variavel
         case 0x04: Senha::setCSenha4(getKeyPressValue()); break; // armazena o quarto valor digitado na variavel
      }
   }

//----------------------------Tela de Login----------------------------------------------------------

   void Principal::telaLoginStore()
   {
      aux_store++;
      if(getKeyPressValue() == 11 && Senha::verificaValorNulo("login")) {  // se for pressionada a tecla "*" e os valores sao 0 volta pra tela inicial
         aux_store = 0x00; Tela::setAuxTroca(0x01);// tela inicial
      } else if(getKeyPressValue() == 11 && aux_store <= 0x05) {
         aux_store = 0x00; Senha::resetaLogin();
      } else if(getKeyPressValue() == 11) {
         aux_store = 0x04; Senha::resetaNumber(); return;
      } else if(getKeyPressValue() == 12) {
         String senha = String(Senha::getNumer1()) + String(Senha::getNumer2()) + String(Senha::getNumer3()) + String(Senha::getNumer4()); // junta em uma string os caractares que será armazenado o login
         String login = String(Senha::getLogin1()) + String(Senha::getLogin2()) + String(Senha::getLogin3()) + String(Senha::getLogin4()); // junta em uma string os caractares que será armazenada a senha
         Tela::setAuxTroca(0x15); // tela virificando conexao
         Tela::setAutenticado(objAPI->authByLogin(login,senha));
         Tela::setAuxTroca(0x03);// tela para verificar liberação do sistema
         aux_store = 0x00;
         Senha::resetaNumber();
         Senha::resetaLogin();
      }
      switch(aux_store)
      {
         case 0x01: Senha::setLogin1(getKeyPressValue()); break;   // armazena o primeiro valor digitado na variavel
         case 0x02: Senha::setLogin2(getKeyPressValue()); break;   // armazena o segundo valor digitado na variavel
         case 0x03: Senha::setLogin3(getKeyPressValue()); break;   // armazena o terceiro valor digitado na variavel
         case 0x04: Senha::setLogin4(getKeyPressValue()); break;   // armazena o quarto valor digitado na variavel
         case 0x05: Senha::setNumer1(getKeyPressValue()); break;   // armazena o primeiro valor digitado na variavel
         case 0x06: Senha::setNumer2(getKeyPressValue()); break;   // armazena o segundo valor digitado na variavel
         case 0x07: Senha::setNumer3(getKeyPressValue()); break;   // armazena o terceiro valor digitado na variavel
         case 0x08: Senha::setNumer4(getKeyPressValue()); break;   // armazena o quarto valor digitado na variavel
      }
   }

//----------------------------Tela de Configuração---------------------------------------------------

   void Principal::telaConfigStore()
   {
      switch(getKeyPressValue())
      {
         case 1: Tela::setAuxTelaInicial("data"); Tela::setAuxTroca(0x01);break; // habilita trocar a data
         case 2: Tela::setAuxTelaInicial("hora"); Tela::setAuxTroca(0x01); break;   // habilita trocar as horas
         case 3: Tela::setAuxDigiteSenha("novaSenhaAcesso"); Tela::setAuxTroca(0x02);break;   // habilita trocar a senha
         case 4: Tela::setAuxTroca(0x0A); break;   // vai para a segunda tela de configurações
         case 11: Tela::setAuxTroca(0x01); break; // volta para a tela inicial
      }
   }
   void Principal::telaConfigStore2()
   {
      switch(getKeyPressValue())
      {
         case 1: Tela::setAuxTroca(0x0C);break; // conectar ao wi-fi
         case 2: RFID::setOpcaoRFID(0x01);Tela::setAuxRfid("cadastrar");Tela::setAuxTroca(0x0B); break;   // cadastrar nova tag
         case 3: RFID::setOpcaoRFID(0x02);Tela::setAuxRfid("remover");Tela::setAuxTroca(0x0B); break;   // remover tag
         case 4: Tela::setAuxDigiteSenha("novaSenhaMenu"); Tela::setAuxTroca(0x02);break;   // habilita trocar a senha
         case 11: Tela::setAuxTroca(0x05); break; // volta para a tela config 1
      }
   }

//----------------------------Tela de Configuração Wifi----------------------------------------------

   void Principal::telaWifiStore()
   {
      switch (getKeyPressValue())
      {
         case 5: WiFi.begin(" ", " "); break; // reseta wifi
         case 11: Tela::setAuxTroca(0x01); break; // volta para a tela inicial
      }
   }

//----------------------------Tela de Aguardando leitura RFID-----------------------------------------

   void Principal::telaRFIDStore(){
      switch (getKeyPressValue())
      {
         case 11: Tela::setAuxTroca(0x0A); RFID::setOpcaoRFID(0x00); break;
      }
   }
