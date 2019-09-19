#ifndef SENHA_H_
#define SENHA_H_

#include "libs.h"

class Senha{
   static short number1,number2,number3,number4;// variavel que armazena a senha digitada
   static short senha1,senha2,senha3,senha4;          // senha de acesso correta
   static short login1, login2, login3, login4;      // armazena login
   static short senha_config1, senha_config2, senha_config3, senha_config4; // senha menu de configuração
   static short nSenha1, nSenha2, nSenha3, nSenha4;      // nova senha
   static short cSenha1, cSenha2, cSenha3, cSenha4;      // cofirmação da nova senha
public:
   Senha();
   virtual ~Senha();

   static void setNumer1(short num);
   static void setNumer2(short num);
   static void setNumer3(short num);
   static void setNumer4(short num);
   static short getNumer1();
   static short getNumer2();
   static short getNumer3();
   static short getNumer4();

   static void setSenha1(short num);
   static void setSenha2(short num);
   static void setSenha3(short num);
   static void setSenha4(short num);
   static short getSenha1();
   static short getSenha2();
   static short getSenha3();
   static short getSenha4();

   static void setLogin1(short num);
   static void setLogin2(short num);
   static void setLogin3(short num);
   static void setLogin4(short num);
   static short getLogin1();
   static short getLogin2();
   static short getLogin3();
   static short getLogin4();

   static void setSenhaConfig1(short num);
   static void setSenhaConfig2(short num);
   static void setSenhaConfig3(short num);
   static void setSenhaConfig4(short num);
   static short getSenhaConfig1();
   static short getSenhaConfig2();
   static short getSenhaConfig3();
   static short getSenhaConfig4();

   static void setNSenha1(short num);
   static void setNSenha2(short num);
   static void setNSenha3(short num);
   static void setNSenha4(short num);
   static short getNSenha1();
   static short getNSenha2();
   static short getNSenha3();
   static short getNSenha4();

   static void setCSenha1(short num);
   static void setCSenha2(short num);
   static void setCSenha3(short num);
   static void setCSenha4(short num);
   static short getCSenha1();
   static short getCSenha2();
   static short getCSenha3();
   static short getCSenha4();

   static boolean cofirmaSenhaAcesso();
   static boolean cofirmaSenhaMenu();
   static boolean cofirmaNovaSenha();
   static boolean verificaValorNulo(String nomeSenha);
   static void trocaSenha(boolean vf);
   static void trocaSenhaMenu(boolean vf);

   static void resetaNumber();
   static void resetaLogin();
   static void resetaNSenha();
   static void resetaCSenha();
};

#endif /*SENHA_H_*/
