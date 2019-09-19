#ifndef PRINCIPAL_H_
#define PRINCIPAL_H_

#include "telas.h"
#include "rfid.h"

class Principal {
   API *objAPI = new API();
   Relogio *objRe = new Relogio();

   short keyPressValue;
   static char aux_store;
   // static char get_aux_store;
public:
   Principal();
   virtual ~Principal();

   void setAPI(API &objAPI);
   void setRelogio(Relogio &objR);

   void setKeyPressValue(short value);
   short getKeyPressValue();

   void store(short value);
   static char getValorAuxStore();
   static void resetValorAuxStore();

   void telaInicialStore();
   void digiteSenhaStore();
   void digiteNovaSenhaStore();
   void digiteConfirmaNovaSenhaStore();
   void telaLoginStore();
   void telaConfigStore();
   void telaConfigStore2();
   void telaWifiStore();
   void telaRFIDStore();

   void alterarData();
   void alterarHora();
   boolean validacaoDataHora(String dataHora);
};

#endif /*PRINCIPAL_H_*/
