#ifndef TELA_H_
#define TELA_H_

#include "libs.h"
#include "relogio.h"
#include "senha.h"
#include "principal.h"
//============================CONFIGURAÇÃO DOS ATUADORES=============================================

#define ledG 17   // Led verde - TX2
#define ledR 16   // Led vermelho - RX2
#define buzz 4    // buzzer - D4

class Tela {
   LiquidCrystal_I2C *lcd = new LiquidCrystal_I2C();
   Relogio *objRe = new Relogio();
   WiFiManager *wifiManager = new WiFiManager();

   static boolean validacaoDataHora;
   static boolean autenticado;
   static char aux_exi;
   static char aux_troca;
   static String aux_telaInicial;   // "inicial","data","hora"
   static String aux_digiteSenha;   // "acesso","config"
   static String aux_rfid;          // "cadastrar","tagCadastrada","erro","remover","tagRemovida"
   static int aux_telaInativa;      // volta pra tela inicial se ficar sem apertar nenhuma tecla

   static boolean sistemaBloqueado;
   static int tempoBloqueio;        // tempo que o sistema fica bloqueado se errar a senha muitas vezes
   static int tentativasAcesso;     // quantidade de vezes que pode errar a senha
   // const int aux_tentativas = 3;

   boolean serverOn;
   int cont_scroll=0;

public:
   Tela();
   virtual ~Tela();

   void setLcd(LiquidCrystal_I2C &lcd);
   void setRelogio(Relogio &objR);
   void setWifiManager(WiFiManager &wifiManager);

   static void setAutenticado(boolean vf);
   static boolean getAutenticado();
   static void setValidacaoDataHora(boolean vf);
   static boolean getValidacaoDataHora();

   static void resetTempoBloqueio();
   static void decrementaTempoBloqueio();
   static int getTempoBloqueio();
   static void resetTentativasAcesso();
   static int getTentativasAcesso();
   static void setSistemaBloqueado(boolean vf);
   static boolean getSistemaBloqueado();

   static void incrementaAuxTelaInativa();
   static void resetAuxTelaInativa();
   static int getAuxTempoTelaInativa();
   static void setAuxDigiteSenha(String qualSenha);
   static String getAuxDigiteSenha();
   static void setAuxTelaInicial(String tela);
   static String getAuxTelaInicial();
   static void setAuxExi(char auxExi);
   static char getAuxExi();
   static void setAuxTroca(char at);
   static char getAuxTroca();
   static void setAuxRfid(String value);
   static String getAuxRfid();
   void setServerOn(boolean server);
   boolean getServerOn();

   void exibeTela();
   void trocaTela();


   void telaInicial();              // 0x01
   void digiteSenha();              // 0x02
   void liberacaoSistema();         // 0x03
   void telaConfig();               // 0x05
   void telaValidacaoDataHora();    // 0x06
   void digiteNovaSenha();          // 0x07
   void digiteConfirmaNovaSenha();  // 0x08
   void telaValidacaoNovaSenha();   // 0x09
   void telaConfig2();              // 0x0A
   void telaRFID();                 // 0x0B
   void telaWifi();                 // 0x0C
   void telaSistemaBloqueado();     // 0x0D
   void telaLogin();                // 0x0E
   void telaAguardaLogin();         // 0x15
};

#endif /*TELA_H_*/
