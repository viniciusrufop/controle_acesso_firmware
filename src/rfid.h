#ifndef RFID_H_
#define RFID_H_

#include "libs.h"
#include "api.h"
#include "telas.h"

class RFID {
   MFRC522 *objRFID = new MFRC522();
   API *objAPI = new API();
   LiquidCrystal_I2C *lcd = new LiquidCrystal_I2C();

   static char opcaoRFID; // "0x00 - acesso" , "0x01 - cadastro" , "0x02 - remove"
public:
   RFID();
   virtual ~RFID();

   void setRFID(MFRC522 &objRFID);
   void setAPI(API &objAPI);
   void setLcd(LiquidCrystal_I2C &lcd);

   void telaConectando();

   static void setOpcaoRFID(char op);
   static char getOpcaoRFID();

   void leituraRFID();
   void acessoTag(String tag);
   void cadastroTag(String tag);
   void deletaTag(String tag);
};

#endif /*RFID_H_*/
