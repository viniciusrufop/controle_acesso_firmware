#include "relogio.h"

Relogio::Relogio(){}

Relogio::~Relogio(){}

// void Relogio::setAPI(API &objAPI)
// {
//    this->objAPI = &objAPI;
// }

void Relogio::setSegundos(int seg){ this -> segundos = seg; }
int Relogio::getSegundos(){ return segundos; }
int Relogio::getHora(){ return hora.toInt(); }
int Relogio::getMin(){ return min.toInt(); }
int Relogio::getDia(){ return dia.toInt(); }
int Relogio::getMes(){ return mes.toInt(); }

void Relogio::setDia1(int num){ this->dia1 = num; }
void Relogio::setDia2(int num){ this->dia2 = num; }
void Relogio::setMes1(int num){ this->mes1 = num; }
void Relogio::setMes2(int num){ this->mes2 = num; }
void Relogio::setAno1(int num){ this->ano1 = num; }
void Relogio::setAno2(int num){ this->ano2 = num; }
void Relogio::setHora1(int num){ this->hora1 = num; }
void Relogio::setHora2(int num){ this->hora2 = num; }
void Relogio::setMin1(int num){ this->min1 = num; }
void Relogio::setMin2(int num){ this->min2 = num; }

int Relogio::getDia1(){ return dia1; }
int Relogio::getDia2(){ return dia2; }
int Relogio::getMes1(){ return mes1; }
int Relogio::getMes2(){ return mes2; }
int Relogio::getAno1(){ return ano1; }
int Relogio::getAno2(){ return ano2; }
int Relogio::getHora1(){ return hora1; }
int Relogio::getHora2(){ return hora2; }
int Relogio::getMin1(){ return min1; }
int Relogio::getMin2(){ return min2; }

String Relogio::getDataComp(){
   if(segundos > 59) {                       // se o tempo for maior que 59 segundo acrescenta 1 min
      segundos = 0;                     // reseta os segundos
      min2 = min2+1;                    // acrescenta 1 min
      if(min2 > 9) {                    // se o segundo algarismo dos minutos for maior que 9 entra no bloco
         min2 = 0;                 // reseta o segundo algarismo dos minutos
         min1 = min1 + 1;          // acrescenta 1 no primeiro algarismo dos minutos
         if(min1 > 5) {            // se o primeiro algarismo dos minutos for maior que 5 entra no bloco, ex: 00:"59"
            min1 = 0;         // reseta do primeiro algarismo dos minutos
            hora2 = hora2 + 1;                              // acrescenta 1 no segundo algarismo das horas
            if(hora2 > 9 && hora1 < 2) {                    // se for ate "19": 59 entra no bloco
               hora2 = 0;                              // reseta o segundo algarismo das horas
               hora1 = hora1 + 1;                      // acresceta 1 no primeiro algarismo das horas
               }
               if(hora2 > 3 && hora1 == 2) {                   // se for ate "23": 59 entra no bloco
                  hora2 = 0;                              // reseta o segundo algarismo das horas
                  hora1 = 0;                              // reseta o primeiro algarismo das horas
                  dia2 = dia2 +1;                         // acrescenta 1 no segundo algarismo dos dias
                  if(dia2 > 9 && dia1 <4) {               // se os dias for menor que "31" entra no bloco
                     dia2 = 0;                       // reseta o segundo algarismo dos dias
                     dia1 = dia1 + 1;                // acrescenta 1 no primeiro algarismo dos dias
                     }
                     if(dia2 > 1 && dia1 == 3) {             // se dos dias for maior que "31" entra no bloco
                        dia2 = 1;                       // o segundo algarismo dos dias será "1"
                        dia1 = 0;                       // reseta o primeiro algarismo dos dias
                        mes2 = mes2 +1;                 // acrescenta 1 no segundo algarismo do mes
                        if(mes2 > 9 && mes1 < 1) {                // se o mes for menor que "09" entra no bloco
                        mes2 = 0;                         // reseta o segundo algarismo do mes
                        mes1 = mes1 + 1;                  // acrescenta 1 no primeiro algarismo do mes
                        }
                        if(mes2 > 2 && mes1 == 1) {               // se o mes for maior que "12" entra no bloco
                        mes2 = 1;                         // o segundo algarismo do mes será "1"
                        mes1 = 0;                         // reseta o primeiro algarismo do mes
                        ano2 = ano2 + 1;                  // acrescenta 1 no ultimo algarismo do ano
                        if(ano2 > 9) {                    // se o ultimo algarismo do ano for maior que 9 entra no bloco
                        ano2 = 0;                 // reseta o ultimos algarismo do ano
                        ano1 = ano1 + 1;          // acrescenta 1 no terceiro algarismo do ano
                     }
                  }
               }
            }
         }
      }
   }
   this -> dia = String(dia1) + String(dia2);   // faz a junção do primeiro algarismo do dia com o segundo
   this -> mes = String(mes1) + String(mes2);   // faz a junção do primeiro algarismo do mes com o segundo
   this -> ano = String(ano1) + String(ano2);   // faz a junção dos dois ultimos algarismos que compõe o ano
   this -> hora = String(hora1) + String(hora2);// faz a junção do primeiro algarismo da hora com o segundo
   this -> min = String(min1) + String(min2);   // faz a junção do primeiro algarismo dos minutos com o segundo

   char sep = '/', year[] = "20", esp =' ', watch = ':';
   return String(dia)+String(sep)+String( mes)+String(sep)+String(year)+String(ano)+String(esp)+String(hora)+String(watch)+String(min);
}

void Relogio::resetaData()
{
	this->dia1=0; this->dia2=1; this->mes1=0; this->mes2=1; this->ano1=0; this->ano2=0; // limpa caracteres da data
}
void Relogio::resetaHoras()
{
	this->hora1=0; this->hora2=0; this->min1=0; this->min2=0;
}

void Relogio::atualizaHorario(String horario)
{
   if(horario != "erro"){
      this -> hora1 = horario[49] - 48; // atualiza o primeiro algarismo da hora
   	this -> hora2 = horario[50] - 48; // atualiza o segundo algarismo da hora
   	this -> min1 = horario[52] - 48; // atualiza o primeiro algarismo dos minutos
   	this -> min2 = horario[53] - 48; // atualiza o primeiro algarismo dos minutos
   	this -> dia1 = horario[38] - 48; // atualiza o primeiro algarismo do dia
   	this -> dia2 = horario[39] - 48; // atualiza o primeiro algarismo do dia
   	this -> mes1 = horario[41] - 48; // atualiza o primeiro algarismo do mes
   	this -> mes2 = horario[42] - 48; // atualiza o primeiro algarismo do mes
   	this -> ano1 = horario[46] - 48; // atualiza o penultimo algarismo do ano
   	this -> ano2 = horario[47] - 48; // atualiza o ultimo algarismo do ano
   }
}
