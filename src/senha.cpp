#include "senha.h"

Senha::Senha()
{
   number1 = 0x00;number2 = 0x00;number3 = 0x00;number4 = 0x00;
   senha1 = 0x04; senha2 = 0x03 ;senha3 = 0x02; senha4 = 0x01;
   login1 = 0x00; login2 = 0x00; login3 = 0x00; login4 = 0x00;
   senha_config1 = 0x01; senha_config2 = 0x02; senha_config3 = 0x03; senha_config4 = 0x04;
}
Senha::~Senha(){}

   /*static*/ short Senha::number1;short Senha::number2;short Senha::number3;short Senha::number4;
   /*static*/ void Senha::setNumer1(short num){ number1 = num; }
   /*static*/ void Senha::setNumer2(short num){ number2 = num; }
   /*static*/ void Senha::setNumer3(short num){ number3 = num; }
   /*static*/ void Senha::setNumer4(short num){ number4 = num; }
   /*static*/ short Senha::getNumer1(){ return number1; }
   /*static*/ short Senha::getNumer2(){ return number2; }
   /*static*/ short Senha::getNumer3(){ return number3; }
   /*static*/ short Senha::getNumer4(){ return number4; }

   /*static*/ short Senha::senha1;short Senha::senha2;short Senha::senha3;short Senha::senha4;
   /*static*/ void Senha::setSenha1(short num){ senha1 = num; }
   /*static*/ void Senha::setSenha2(short num){ senha2 = num; }
   /*static*/ void Senha::setSenha3(short num){ senha3 = num; }
   /*static*/ void Senha::setSenha4(short num){ senha4 = num; }
   /*static*/ short Senha::getSenha1(){ return senha1; }
   /*static*/ short Senha::getSenha2(){ return senha2; }
   /*static*/ short Senha::getSenha3(){ return senha3; }
   /*static*/ short Senha::getSenha4(){ return senha4; }

   /*static*/ short Senha::login1;short Senha::login2;short Senha::login3;short Senha::login4;
   /*static*/ void Senha::setLogin1(short num){ login1 = num; }
   /*static*/ void Senha::setLogin2(short num){ login2 = num; }
   /*static*/ void Senha::setLogin3(short num){ login3 = num; }
   /*static*/ void Senha::setLogin4(short num){ login4 = num; }
   /*static*/ short Senha::getLogin1(){ return login1; }
   /*static*/ short Senha::getLogin2(){ return login2; }
   /*static*/ short Senha::getLogin3(){ return login3; }
   /*static*/ short Senha::getLogin4(){ return login4; }

   /*static*/ short Senha::senha_config1;short Senha::senha_config2;short Senha::senha_config3;short Senha::senha_config4;
   /*static*/ void Senha::setSenhaConfig1(short num){ senha_config1 = num; }
   /*static*/ void Senha::setSenhaConfig2(short num){ senha_config2 = num; }
   /*static*/ void Senha::setSenhaConfig3(short num){ senha_config3 = num; }
   /*static*/ void Senha::setSenhaConfig4(short num){ senha_config4 = num; }
   /*static*/ short Senha::getSenhaConfig1(){ return senha_config1; }
   /*static*/ short Senha::getSenhaConfig2(){ return senha_config2; }
   /*static*/ short Senha::getSenhaConfig3(){ return senha_config3; }
   /*static*/ short Senha::getSenhaConfig4(){ return senha_config4; }

   /*static*/ short Senha::nSenha1;short Senha::nSenha2;short Senha::nSenha3;short Senha::nSenha4;
   /*static*/ void Senha::setNSenha1(short num){ nSenha1 = num; }
   /*static*/ void Senha::setNSenha2(short num){ nSenha2 = num; }
   /*static*/ void Senha::setNSenha3(short num){ nSenha3 = num; }
   /*static*/ void Senha::setNSenha4(short num){ nSenha4 = num; }
   /*static*/ short Senha::getNSenha1(){ return nSenha1; }
   /*static*/ short Senha::getNSenha2(){ return nSenha2; }
   /*static*/ short Senha::getNSenha3(){ return nSenha3; }
   /*static*/ short Senha::getNSenha4(){ return nSenha4; }

   /*static*/ short Senha::cSenha1;short Senha::cSenha2;short Senha::cSenha3;short Senha::cSenha4;
   /*static*/ void Senha::setCSenha1(short num){ cSenha1 = num; }
   /*static*/ void Senha::setCSenha2(short num){ cSenha2 = num; }
   /*static*/ void Senha::setCSenha3(short num){ cSenha3 = num; }
   /*static*/ void Senha::setCSenha4(short num){ cSenha4 = num; }
   /*static*/ short Senha::getCSenha1(){ return cSenha1; }
   /*static*/ short Senha::getCSenha2(){ return cSenha2; }
   /*static*/ short Senha::getCSenha3(){ return cSenha3; }
   /*static*/ short Senha::getCSenha4(){ return cSenha4; }

   /*static*/ boolean Senha::cofirmaSenhaAcesso()
   {
      return (getSenha1() == getNumer1() && getSenha2() == getNumer2() && getSenha3() == getNumer3() && getSenha4() == getNumer4()) ? true : false;
   }

   /*static*/ boolean Senha::cofirmaSenhaMenu()
   {
      return (getSenhaConfig1() == getNumer1() && getSenhaConfig2() == getNumer2() && getSenhaConfig3() == getNumer3() && getSenhaConfig4() == getNumer4()) ? true : false;
   }
   /*static*/ boolean Senha::cofirmaNovaSenha()
   {
      return (getNSenha1() == getCSenha1() && getNSenha2() == getCSenha2() && getNSenha3() == getCSenha3() && getNSenha4() == getCSenha4()) ? true : false;
   }


   /*static*/ boolean Senha::verificaValorNulo(String nomeSenha)
   {
      if(nomeSenha == "number"){
         return (getNumer1() == 0x00 && getNumer2() == 0x00 && getNumer3() == 0x00 && getNumer4() == 0x00) ? true : false;
      } else if(nomeSenha == "login"){
         return (getLogin1() == 0x00 && getLogin2() == 0x00 && getLogin3() == 0x00 && getLogin4() == 0x00) ? true : false;
      } else if(nomeSenha == "novaSenha"){
         return (getNSenha1() == 0x00 && getNSenha2() == 0x00 && getNSenha3() == 0x00 && getNSenha4() == 0x00) ? true : false;
      } else if(nomeSenha == "confirmaSenha"){
         return (getCSenha1() == 0x00 && getCSenha2() == 0x00 && getCSenha3() == 0x00 && getCSenha4() == 0x00) ? true : false;
      } else {
         return false;
      }

   }

   /*static*/ void Senha::trocaSenha(boolean vf)
   {
      if(vf){
         setSenha1(getCSenha1());setSenha2(getCSenha2());setSenha3(getCSenha3());setSenha4(getCSenha4());
      } else return;
   }

   /*static*/ void Senha::trocaSenhaMenu(boolean vf)
   {
      if(vf){
         setSenhaConfig1(getCSenha1());setSenhaConfig2(getCSenha2());setSenhaConfig3(getCSenha3());setSenhaConfig4(getCSenha4());
      } else return;
   }


   /*static*/ void Senha::resetaNumber()
   {
      setNumer1(0x00); setNumer2(0x00); setNumer3(0x00); setNumer4(0x00);
   }
   /*static*/ void Senha::resetaLogin()
   {
      setLogin1(0x00);setLogin2(0x00);setLogin3(0x00);setLogin4(0x00);
   }
   /*static*/ void Senha::resetaNSenha()
   {
      setNSenha1(0x00); setNSenha2(0x00); setNSenha3(0x00); setNSenha4(0x00);
   }
   /*static*/ void Senha::resetaCSenha()
   {
      setCSenha1(0x00); setCSenha2(0x00); setCSenha3(0x00); setCSenha4(0x00);
   }
