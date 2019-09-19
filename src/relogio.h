#ifndef RELOGIO_H_
#define RELOGIO_H_

#include "libs.h"
#include "api.h"

class Relogio{
   // API *objAPI = new API();
   int segundos;
   int dia1,dia2=1,mes1, mes2=1, ano1, ano2, hora1, hora2, min1, min2;
   String dia,mes,ano,hora,min;
public:
   Relogio();
   virtual ~Relogio();

   // void setAPI(API &objAPI);

   void setSegundos(int seg);	// incrementa os segundos
   int getSegundos();	// pega o valor dos segundos
   int getHora();	// pega o horario para atualizar com a internet
   int getMin();	// pega os minutos pra atualizar com a internet
   int getDia();
   int getMes();

   void setDia1(int num);
   void setDia2(int num);
   void setMes1(int num);
   void setMes2(int num);
   void setAno1(int num);
   void setAno2(int num);
   void setHora1(int num);
   void setHora2(int num);
   void setMin1(int num);
   void setMin2(int num);

   int getDia1();
   int getDia2();
   int getMes1();
   int getMes2();
   int getAno1();
   int getAno2();
   int getHora1();
   int getHora2();
   int getMin1();
   int getMin2();

   void resetaData();
	void resetaHoras();

	String getDataComp();

   void atualizaHorario(String horario);	// atualiza a data com internet
};

#endif /*RELOGIO_H_*/
