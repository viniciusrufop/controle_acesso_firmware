#include "rfid.h"

RFID::RFID(){
        opcaoRFID = 0x00;
}
RFID::~RFID(){
}

   void RFID::setRFID(MFRC522 &objRFID)
   {
      this->objRFID = &objRFID;
   }
   void RFID::setAPI(API &objAPI)
   {
      this->objAPI = &objAPI;
   }
   void RFID::setLcd(LiquidCrystal_I2C &lcd)
   {
      this->lcd = &lcd;
   }

   /*static*/ char RFID::opcaoRFID;

   /*static*/ void RFID::setOpcaoRFID(char op)
   {
           opcaoRFID = op;
   }
   /*static*/ char RFID::getOpcaoRFID()
   {
           return opcaoRFID;
   }

//============================FUNÇÃO RESPONSAVEL PELA LEITURA DO RFID================================

void RFID::leituraRFID()
{
        if ( !objRFID->PICC_IsNewCardPresent()) {   // Aguarda a aproximacao do cartao
                return;
        }
        if ( !objRFID->PICC_ReadCardSerial()) {   // Seleciona um dos cartoes
                return;
        }
        telaConectando();
        String tag = "";   // reseta variave paral armazenar novo valor
        for (byte i = 0; i < objRFID->uid.size; i++) {
                tag += (String(objRFID->uid.uidByte[i], HEX));   // pega o valor da TAG em hexadecimal
        }
        tag.toUpperCase();    // faz com que as letras fique em maiuscula
        Serial.println("Tag do cartão: "+tag);    // exibe no monitor serial o valor da tag sem codificação

        digitalWrite(4,HIGH); // aciona o buzzer
        delay(200);           // aguarda 200ms
        digitalWrite(4,LOW); // desliga o buzzer

        switch(opcaoRFID) {           // verifica qual opção foi selecionada
        case 0x00:            // opção de acesso
                delay(100);
                acessoTag(tag);            // chama função resposavel pelo acesso
                break;

        case 0x01:            // opção de cadastro de novas tags
                delay(100);
                cadastroTag(tag);            // chama função resposavel por cadastrar tag
                break;
        case 0x02:            // opção de remoção de tags cadastradas
                delay(100);
                deletaTag(tag);            // chama função resposavel por remover tag
                break;
        }
}

//============================FUNÇÃO RESPONSAVEL POR VERIFICAR AUTENTICIDADE========================

void RFID::acessoTag(String tag)
{
   Tela::setAutenticado(objAPI->authByTag(tag));
   Tela::setAuxTroca(0x03);// tela para verificar liberação do sistema
}

//============================FUNÇÃO RESPONSAVEL POR CADASTRAR NOVAS TAGS============================

void RFID::cadastroTag(String tag)
{
   String value = (objAPI->insertNewTag(tag)) ? "tagCadastrada" : "erro";
   Tela::setAuxRfid(value);
   Tela::setAuxTroca(0x0B);
   opcaoRFID = 0x00;
}

//============================FUNÇÃO RESPONSAVEL POR DELETAR TAG=====================================

void RFID::deletaTag(String tag)
{
   String value = (objAPI->desableTag(tag)) ? "tagRemovida" : "erro";
   Tela::setAuxRfid(value);
   Tela::setAuxTroca(0x0B);
   opcaoRFID = 0x00;
}

void RFID::telaConectando()
{
   lcd->clear();
   lcd->setCursor(3,0);
   lcd->print("Conectanto");
   lcd->setCursor(3,1);
   lcd->print("Aguarde...");
}
