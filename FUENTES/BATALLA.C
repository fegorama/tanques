/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±            T A N Q U E S   1.0        1.996   BY  FEGOR                ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                                                                        ±
± MODULO   > BATALLA.C                                                   ±
± AUTOR    > Fernando Gonz lez Ruano (FEGOR)                             ±
± VERSION  > 1.0                                                         ±
± LENGUAJE > Borland C/C++ versi¢n 3.1                                   ±
±                                                                        ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                                                                        ±
± Funciones de v¡deo                                                     ±
±                                                                        ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                   CLUB VIRTUAL ZONE    -1.996-                         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

#pragma inline

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<io.h>
#include<fcntl.h>
#include<alloc.h>
#include<mem.h>
#include<string.h>
#include<time.h>

#include"video.h"
#include"sonido.h"
#include"rs232.h"
#include"batalla.h"
#include"campos.h"

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± variables externas                                                     ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
extern unsigned char far* pantfondo;		// video.c
extern unsigned char far* pantvirt;             //   "
extern TipoPaleta pal;                          //   "
extern TipoPaleta palaux;                       //   "

extern unsigned int CodigoLetra[128];           // teclado.c

extern TipoNotas musicamenu;			// sonido.c
extern TipoNotas musicamenu2;                   //   "
extern TipoNotas musicadisparo;                 //   "
extern TipoNotas musicatocado;                  //   "
extern TipoNotas musicabonus;                   //   "

extern TipoSprite sprite[MAXSPRT];              // tanques.c

extern TipoSerie serie;                         // serie.c

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± variables p£blicas o generales                                         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
char conexion_establecida = 0;		// si se ha establecido conexi¢n
					// 1 = servidor (tanque verde)
					// 2 = cliente  (tanque azul)

// variables para c¢digos de teclas

unsigned char tec_n_verde, tec_s_verde, tec_e_verde, tec_o_verde, tec_d_verde;
unsigned char tec_n_azul,  tec_s_azul,  tec_e_azul,  tec_o_azul, tec_d_azul;

// estructuras con coordenadas para el control de choques

TipoCoordenadas RTverde,RTazul;
TipoCoordenadas BalaTverde,BalaTazul;

// sobre las balas

unsigned int dir_verde,dir_azul;
unsigned char bala_verde, bala_azul, dist_bala_verde, dist_bala_azul;
unsigned char vel_bala_verde, vel_bala_azul;
unsigned int dir_bala_verde, dir_bala_azul;

// vidas (impactos), tanques, cargador y fuel

unsigned char vidas_verde,vidas_azul,tanques_verde,tanques_azul;
unsigned char cargador_verde,cargador_azul;
unsigned int  fuel_verde,fuel_azul;

// Objetos (cruz roja, armamento y fuel)

TipoCoordenadas CruzRoja1,CruzRoja2,Municion1,Municion2;
TipoCoordenadas Fuel1,Fuel2;
unsigned char ImpactoCruzRoja1,ImpactoCruzRoja2;
unsigned char ImpactoMunicion1,ImpactoMunicion2;
unsigned char ImpactoFuel1,ImpactoFuel2;

// Bases

TipoCoordenadas BaseVerde,BaseAzul;
unsigned char ImpactoBaseVerde,ImpactoBaseAzul;

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± comprueba si hay un muro delante                                       ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
int HayMuro(TipoCoordenadas tanque)
{
  return EsColor(tanque,14) || EsColor(tanque,25);
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± inicializa el campo de batalla                                         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void IniCampo()
{
  unsigned char i,c;			// contadores

  LimpiaPantallas();

  // muros...

  for(i=0;i<11;i++)			// filas
    for(c=0;c<20;c++)                   // columnas
      if(campo_actual[i][c]==1)
	VisualizaSprite(i*16,c*16,sprite[LADRILLO]);

  memcpy(pantfondo,pantvirt,64000);

  // objetos...

  for(i=0;i<11;i++)			// cruces rojas
    for(c=0;c<20;c++)
    {
      if(campo_actual[i][c]==2)
      {
	VisualizaSprite(i*16,c*16,sprite[CRUZROJA]);
	if(CruzRoja1.y1 == 0)
	{
	  CruzRoja1.y1 = i*16;
	  CruzRoja1.x1 = c*16;
	}
	else
	{
	  CruzRoja2.y1 = i*16;
	  CruzRoja2.x1 = c*16;
	}
      }
      else if(campo_actual[i][c]==3)	// munici¢n
      {
	VisualizaSprite(i*16,c*16,sprite[MUNICION]);
	if(Municion1.y1 == 0)
	{
	  Municion1.y1 = i*16;
	  Municion1.x1 = c*16;
	}
	else
	{
	  Municion2.y1 = i*16;
	  Municion2.x1 = c*16;
	}
      }
      else if(campo_actual[i][c]==4)	// fuel / gasolina
      {
	VisualizaSprite(i*16,c*16,sprite[FUEL]);
	if(Fuel1.y1 == 0)
	{
	  Fuel1.y1 = i*16;
	  Fuel1.x1 = c*16;
	}
	else
	{
	  Fuel2.y1 = i*16;
	  Fuel2.x1 = c*16;
	}
      }
      else if(campo_actual[i][c]==5)	// bases
      {
	VisualizaSprite(i*16,c*16,sprite[BASEVERDE]);
	BaseVerde.y1 = i*16;
	BaseVerde.x1 = c*16;
      }
      else if(campo_actual[i][c]==6)
      {
	VisualizaSprite(i*16,c*16,sprite[BASEAZUL]);
	BaseAzul.y1 = i*16;
	BaseAzul.x1 = c*16;
      }
      else if(campo_actual[i][c]==7)	// tanques
      {
	VisualizaSprite(i*16,c*16,sprite[T1E1]);
	RTverde.y1 = i*16;
	RTverde.x1 = c*16;
      }
      else if(campo_actual[i][c]==8)
      {
	VisualizaSprite(i*16,c*16,sprite[T2O1]);
	RTazul.y1 = i*16;
	RTazul.x1 = c*16;
      }
    }

    EfectoCaida();
    memset(ImpactoMuros,0,sizeof(ImpactoMuros));	// impactos a cero
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± inicializa marcadores                                                  ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void IniMarcadores()
{
  inifontVGA(FONT_8x8);
  borrafondofont(0);
  printstringVGA(181,2, "VERDE  Impactos     Bombas     Fuel",200);
  printstringVGA(191,2,"AZUL   Impactos     Bombas     Fuel",207);
  borrafondofont(1);
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± actualiza marcadores                                                   ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void ActualizaMarcadores()
{
  unsigned char cadaux[128];		// cadena auxiliar

  // del tanque verde

  printstringVGA(181,136,"  ",200);
  printstringVGA(181,136,itoa(MAX_VIDAS-vidas_verde,cadaux,10),200);
  printstringVGA(181,218,"  ",200);
  printstringVGA(181,218,itoa(cargador_verde,cadaux,10),200);
  printstringVGA(181,294,"   ",200);
  printstringVGA(181,294,itoa(fuel_verde,cadaux,10),200);

  // del tanque azul

  printstringVGA(191,136,"  ",207);
  printstringVGA(191,136,itoa(MAX_VIDAS-vidas_azul,cadaux,10),207);
  printstringVGA(191,218,"  ",207);
  printstringVGA(191,218,itoa(cargador_azul,cadaux,10),207);
  printstringVGA(191,294,"   ",207);
  printstringVGA(191,294,itoa(fuel_azul,cadaux,10),207);
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± elecci¢n del campo de batalla                                          ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void ElijeCampo()
{
  int tec = 0;				// c¢digo de tecla
  unsigned char datoCOM;		// dato del puerto serie
  unsigned char campant;		// campo de batalla anterior

  campant = n_campo;			// campo anterior = campo actual
  inifontVGA(FONT_8x8);

  do{

    // actualiza m£sica y campo

    memcpy(campo_actual,campo[n_campo],11*20*sizeof(char));
    ActualizaSonidos(musicatocado);
    IniCampo();

    printstringVGA(181,0,"ESPACIO  <=>  Otro",200);
    printstringVGA(191,0,"ENTER    <=>  Aceptar",200);
    RefrescaPantalla();

    do
    {
      tec = 0;

      // si se pulsa la opci¢n desde teclado local

      if(kbhit()) tec = getch();

      // si es <espacio> siguiente campo

      if(tec == 32 && n_campo < MAX_CAMPOS-1)
	n_campo++;
      else if(tec == 32 && n_campo == MAX_CAMPOS-1)
	n_campo=0;

    } while(tec != 32 && tec != 13 && tec != 27);

  } while(tec != 13 && tec != 27);

  // si es <ESC>, el campo es el campo anterior (el inicial)

  if(tec == 27)
    n_campo = campant;
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± batalla, control de todo el juego...                                   ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
int Batalla()
{
  int  i,c;				// contadores
  unsigned char cadaux[128];		// cadena auxiliar
  unsigned int salir = 0;		// salida
  unsigned char color_cambio = 0;	// color de cambio
  unsigned char dato_remoto = 0;	// dato del puerto serie

  // mientras no se tenga que salir por tanque destruido, base, etc.

  while(!salir)
  {
      ActualizaMarcadores();

      // parpadeos y cambios de color (para la cruz roja)

      if((pal[68].rojo)>=62)
	color_cambio = 0;
      else if((pal[68].rojo)<=40)
	color_cambio = 1;

      if(color_cambio==0)
	pal[68].rojo--;
      else if(color_cambio==1)
	pal[68].rojo++;

      // cambio del color para el bombeo de la cruz roja

      esperaretrazo();
      outportb(0x3C8,68);
      outportb(0x3C9,pal[68].rojo);
      outportb(0x3C9,pal[68].verde);
      outportb(0x3C9,pal[68].azul);

      scrollpal(200,205);
      scrollpal(207,212);

      // control de la conexi¢n y recepci¢n de datos por puerto serie

      if(conexion_establecida)  		// teclas del remoto...
      {
	CodigoLetra[dato_remoto] = 0;
	RecibirByteCOM(&dato_remoto);
	CodigoLetra[dato_remoto] = 1;
      }

      // si se aborta mediante teclado

      if(CodigoLetra[1])
      {
	if(conexion_establecida)
	  EnviarByteCOM(1);

	salir = ABORTADO;
      }

      // tanque verde (control de disparo y movimiento)

      // disparo...

      if(CodigoLetra[tec_d_verde] && !bala_verde && cargador_verde)
      {
	if(conexion_establecida == 1)
	  EnviarByteCOM(tec_d_verde);

	bala_verde      = 1;			// 1 = disparada
	dist_bala_verde = 0;
	dir_bala_verde  = dir_verde;
	cargador_verde--;
	ActualizaSonidos(musicadisparo);

	// direcci¢n de la bala...

	switch(dir_bala_verde)
	{
	  case DIR_NORTE:
	       BalaTverde.y1   = RTverde.y1-8;
	       BalaTverde.x1   = RTverde.x1+5;
	       break;
	  case DIR_ESTE:
	       BalaTverde.y1   = RTverde.y1+5;
	       BalaTverde.x1   = RTverde.x1+19;
	       break;
	  case DIR_SUR:
	       BalaTverde.y1   = RTverde.y1+18;
	       BalaTverde.x1   = RTverde.x1+5;
	       break;
	  case DIR_OESTE:
	       BalaTverde.y1   = RTverde.y1+4;
	       BalaTverde.x1   = RTverde.x1-8;
	       break;
	} // switch
      } // if

      // direcci¢n del tanque...

      if(CodigoLetra[tec_n_verde])
      {
	if(conexion_establecida == 1)
	  EnviarByteCOM(tec_n_verde);

	fuel_verde -= fuel_verde>0?1:0;
	  FondoVirtual(RTverde.y1,RTverde.x1,RTverde.y1+ALTO_TAN,
					     RTverde.x1+ANCHO_TAN);
	  RTverde.y1--;

	  if(RTverde.y1<LIMITE_ARRIBA || Interseccion(RTverde,RTazul)
	     || HayMuro(RTverde) || !fuel_verde)
	    RTverde.y1++;

	  dir_verde = DIR_NORTE;
      }
      else if(CodigoLetra[tec_s_verde])
      {
	if(conexion_establecida == 1)
	  EnviarByteCOM(tec_s_verde);

	fuel_verde -= fuel_verde>0?1:0;
	  FondoVirtual(RTverde.y1,RTverde.x1,RTverde.y1+ALTO_TAN,
					     RTverde.x1+ANCHO_TAN);
	  RTverde.y1++;

	  if(RTverde.y1>LIMITE_ABAJO || Interseccion(RTverde,RTazul)
	     || HayMuro(RTverde) || !fuel_verde)
	    RTverde.y1--;

	  dir_verde = DIR_SUR;
      }
      else if(CodigoLetra[tec_o_verde])
      {
	if(conexion_establecida == 1)
	  EnviarByteCOM(tec_o_verde);

	fuel_verde -= fuel_verde>0?1:0;
	  FondoVirtual(RTverde.y1,RTverde.x1,RTverde.y1+ALTO_TAN,
					     RTverde.x1+ANCHO_TAN);
	  RTverde.x1--;

	  if(RTverde.x1<LIMITE_IZQUIERDA || Interseccion(RTverde,RTazul)
	     || HayMuro(RTverde) || !fuel_verde)
	    RTverde.x1++;

	  dir_verde = DIR_OESTE;
      }
      else if(CodigoLetra[tec_e_verde])
      {
	if(conexion_establecida == 1)
	  EnviarByteCOM(tec_e_verde);

	fuel_verde -= fuel_verde>0?1:0;
	  FondoVirtual(RTverde.y1,RTverde.x1,RTverde.y1+ALTO_TAN,
					     RTverde.x1+ANCHO_TAN);
	  RTverde.x1++;

	  if(RTverde.x1>LIMITE_DERECHA || Interseccion(RTverde,RTazul)
	     || HayMuro(RTverde) || !fuel_verde)
	    RTverde.x1--;

	  dir_verde = DIR_ESTE;
      }

      // tanque azul (control de movimiento y disparo)

      // disparo...

      if(CodigoLetra[tec_d_azul] && !bala_azul && cargador_azul)
      {
	if(conexion_establecida == 2)
	  EnviarByteCOM(tec_d_azul);

	bala_azul      = 1;
	dist_bala_azul = 0;
	dir_bala_azul  = dir_azul;
	cargador_azul--;
	ActualizaSonidos(musicadisparo);

	// direcci¢n de la bala...

	switch(dir_bala_azul)
	{
	  case DIR_NORTE:
	       BalaTazul.y1   = RTazul.y1-8;
	       BalaTazul.x1   = RTazul.x1+5;
	       break;
	  case DIR_ESTE:
	       BalaTazul.y1   = RTazul.y1+5;
	       BalaTazul.x1   = RTazul.x1+19;
	       break;
	  case DIR_SUR:
	       BalaTazul.y1   = RTazul.y1+18;
	       BalaTazul.x1   = RTazul.x1+5;
	       break;
	  case DIR_OESTE:
	       BalaTazul.y1   = RTazul.y1+4;
	       BalaTazul.x1   = RTazul.x1-8;
	       break;
	} // switch
      } // if

      // control de movimiento del tanque...

      if(CodigoLetra[tec_n_azul])
      {
	if(conexion_establecida == 2)
	  EnviarByteCOM(tec_n_azul);

	fuel_azul -= fuel_azul>0?1:0;
	  FondoVirtual(RTazul.y1,RTazul.x1,RTazul.y1+ALTO_TAN,
					   RTazul.x1+ANCHO_TAN);
	  RTazul.y1--;

	  if(RTazul.y1<LIMITE_ARRIBA || Interseccion(RTazul,RTverde)
	     || HayMuro(RTazul) || !fuel_azul)
	    RTazul.y1++;

	  dir_azul = DIR_NORTE;
      }
      else if(CodigoLetra[tec_s_azul])
      {
	if(conexion_establecida == 2)
	  EnviarByteCOM(tec_s_azul);

	fuel_azul -= fuel_azul>0?1:0;
	  FondoVirtual(RTazul.y1,RTazul.x1,RTazul.y1+ALTO_TAN,
					   RTazul.x1+ANCHO_TAN);
	  RTazul.y1++;

	  if(RTazul.y1>LIMITE_ABAJO || Interseccion(RTazul,RTverde)
	     || HayMuro(RTazul) || !fuel_azul)
	    RTazul.y1--;

	  dir_azul = DIR_SUR;
      }
      else if(CodigoLetra[tec_o_azul])
      {
	if(conexion_establecida == 2)
	  EnviarByteCOM(tec_o_azul);

	fuel_azul -= fuel_azul>0?1:0;
	  FondoVirtual(RTazul.y1,RTazul.x1,RTazul.y1+ALTO_TAN,
					   RTazul.x1+ANCHO_TAN);
	  RTazul.x1--;

	  if(RTazul.x1<LIMITE_IZQUIERDA || Interseccion(RTazul,RTverde)
	     || HayMuro(RTazul) || !fuel_azul)
	    RTazul.x1++;

	  dir_azul = DIR_OESTE;
      }
      else if(CodigoLetra[tec_e_azul])
      {
	if(conexion_establecida == 2)
	  EnviarByteCOM(tec_e_azul);

	fuel_azul -= fuel_azul>0?1:0;
	  FondoVirtual(RTazul.y1,RTazul.x1,RTazul.y1+ALTO_TAN,
					   RTazul.x1+ANCHO_TAN);
	  RTazul.x1++;

	  if(RTazul.x1>LIMITE_DERECHA || Interseccion(RTazul,RTverde)
	     || HayMuro(RTazul) || !fuel_azul)
	    RTazul.x1--;

	  dir_azul = DIR_ESTE;
      }

      // choques, refresco de sprites y control de disparo

      // si hay impacto... impacto, si no resiste, lo quitamos :-)

      if(bala_verde &&
	(campo_actual[(BalaTverde.y1+4)>>4][(BalaTverde.x1+4)>>4]==1))
      {
	FondoVirtual(BalaTverde.y1,BalaTverde.x1,
		     BalaTverde.y1+ALTO_BAL,BalaTverde.x1+ANCHO_BAL);
	ImpactoMuros[(BalaTverde.y1+4)>>4][(BalaTverde.x1+4)>>4]++;
	if((ImpactoMuros[(BalaTverde.y1+4)>>4][(BalaTverde.x1+4)>>4]) >
	    MAX_MUROS)
	{
	  campo_actual[(BalaTverde.y1+4)>>4][(BalaTverde.x1+4)>>4] = 0;

	  VisualizaSprite(((BalaTverde.y1+4)>>4)*16,((BalaTverde.x1+4)>>4)*16,
			  sprite[DESTROZO]);
	  VirtualFondo(((BalaTverde.y1+4)>>4)*16,((BalaTverde.x1+4)>>4)*16,
		       ((BalaTverde.y1+4)>>4)*16+ALTO_DEST,
		       ((BalaTverde.x1+4)>>4)*16+ANCHO_DEST);
	}
	bala_verde = 0;
	BalaTverde.y1 = 0;
	BalaTverde.x1 = 0;
	ActualizaSonidos(musicatocado);
      }

      if(bala_azul &&
	(campo_actual[(BalaTazul.y1+4)>>4][(BalaTazul.x1+4)>>4]==1))
      {
	FondoVirtual(BalaTazul.y1,BalaTazul.x1,
		     BalaTazul.y1+ALTO_BAL,BalaTazul.x1+ANCHO_BAL);
	ImpactoMuros[(BalaTazul.y1+4)>>4][(BalaTazul.x1+4)>>4]++;
	if((ImpactoMuros[(BalaTazul.y1+4)>>4][(BalaTazul.x1+4)>>4]) >
	    MAX_MUROS)
	{
	  campo_actual[(BalaTazul.y1+4)>>4][(BalaTazul.x1+4)>>4] = 0;

	  VisualizaSprite(((BalaTazul.y1+4)>>4)*16,((BalaTazul.x1+4)>>4)*16,
			  sprite[DESTROZO]);
	  VirtualFondo(((BalaTazul.y1+4)>>4)*16,((BalaTazul.x1+4)>>4)*16,
		       ((BalaTazul.y1+4)>>4)*16+ALTO_DEST,
		       ((BalaTazul.x1+4)>>4)*16+ANCHO_DEST);
	}
	bala_azul = 0;
	BalaTazul.y1 = 0;
	BalaTazul.x1 = 0;
	ActualizaSonidos(musicatocado);
      }

      // con cruz roja...

      if(ImpactoCruzRoja1)
	VisualizaSprite(CruzRoja1.y1,CruzRoja1.x1,sprite[CRUZROJA]);
      else
	FondoVirtual(CruzRoja1.y1,CruzRoja1.x1,
		     CruzRoja1.y1+ALTO_CR,CruzRoja1.x1+ANCHO_CR);

      if(ImpactoCruzRoja2)
	VisualizaSprite(CruzRoja2.y1,CruzRoja2.x1,sprite[CRUZROJA]);
      else
	FondoVirtual(CruzRoja2.y1,CruzRoja2.x1,
		     CruzRoja2.y1+ALTO_CR,CruzRoja2.x1+ANCHO_CR);

      // con munici¢n...

      if(ImpactoMunicion1)
	VisualizaSprite(Municion1.y1,Municion1.x1,sprite[MUNICION]);
      else
	FondoVirtual(Municion1.y1,Municion1.x1,
		     Municion1.y1+ALTO_MUN,Municion1.x1+ANCHO_MUN);

      if(ImpactoMunicion2)
	VisualizaSprite(Municion2.y1,Municion2.x1,sprite[MUNICION]);
      else
	FondoVirtual(Municion2.y1,Municion2.x1,
		     Municion2.y1+ALTO_MUN,Municion2.x1+ANCHO_MUN);

      // con fuel...

      if(ImpactoFuel1)
	VisualizaSprite(Fuel1.y1,Fuel1.x1,sprite[FUEL]);
      else
	FondoVirtual(Fuel1.y1,Fuel1.x1,
		     Fuel1.y1+ALTO_FUEL,Fuel1.x1+ANCHO_FUEL);

      if(ImpactoFuel2)
	VisualizaSprite(Fuel2.y1,Fuel2.x1,sprite[FUEL]);
      else
	FondoVirtual(Fuel2.y1,Fuel2.x1,
		     Fuel2.y1+ALTO_FUEL,Fuel2.x1+ANCHO_FUEL);

      // con bases...

      if(ImpactoBaseVerde)
	VisualizaSprite(BaseVerde.y1,BaseVerde.x1,sprite[BASEVERDE]);
      else
	FondoVirtual(BaseVerde.y1,BaseVerde.x1,
		     BaseVerde.y1+ALTO_BASE,BaseVerde.x1+ANCHO_BASE);

      if(ImpactoBaseAzul)
	VisualizaSprite(BaseAzul.y1,BaseAzul.x1,sprite[BASEAZUL]);
      else
	FondoVirtual(BaseAzul.y1,BaseAzul.x1,
		     BaseAzul.y1+ALTO_BASE,BaseAzul.x1+ANCHO_BASE);

      // refresco de tanques

      // verde...

      switch(dir_verde)
      {
	case DIR_NORTE:
	     VisualizaSprite(RTverde.y1,RTverde.x1,
			    (RTverde.y1%2?sprite[T1N1]:sprite[T1N2]));
	     break;
	case DIR_ESTE:
	     VisualizaSprite(RTverde.y1,RTverde.x1,
			    (RTverde.x1%2?sprite[T1E1]:sprite[T1E2]));
	     break;
	case DIR_SUR:
	     VisualizaSprite(RTverde.y1,RTverde.x1,
			    (RTverde.y1%2?sprite[T1S1]:sprite[T1S2]));
	     break;
	case DIR_OESTE:
	     VisualizaSprite(RTverde.y1,RTverde.x1,
			    (RTverde.x1%2?sprite[T1O1]:sprite[T1O2]));
	     break;
      } // switch

      // azul...

      switch(dir_azul)
      {
	case DIR_NORTE:
	     VisualizaSprite(RTazul.y1,RTazul.x1,
			    (RTazul.y1%2?sprite[T2N1]:sprite[T2N2]));
	     break;
	case DIR_ESTE:
	     VisualizaSprite(RTazul.y1,RTazul.x1,
			    (RTazul.x1%2?sprite[T2E1]:sprite[T2E2]));
	     break;
	case DIR_SUR:
	     VisualizaSprite(RTazul.y1,RTazul.x1,
			    (RTazul.y1%2?sprite[T2S1]:sprite[T2S2]));
	     break;
	case DIR_OESTE:
	     VisualizaSprite(RTazul.y1,RTazul.x1,
			    (RTazul.x1%2?sprite[T2O1]:sprite[T2O2]));
	     break;
      } // switch

      // impacto de bala en tanque azul

      if(bala_verde && Interseccion(BalaTverde,RTazul))
      {
	vidas_azul--;
	if(!vidas_azul)
	  salir=GANA_VERDE;
	ActualizaSonidos(musicatocado);
      }

      // impacto de bala en tanque verde

      if(bala_azul && Interseccion(BalaTazul,RTverde))
      {
	vidas_verde--;
	if(!vidas_verde)
	  salir=GANA_AZUL;
	ActualizaSonidos(musicatocado);
      }

      // pasa por la cruz roja (sanea impactos)

      if(((Interseccion(RTverde,CruzRoja1) && ImpactoCruzRoja1 != 0)||
	  (Interseccion(RTverde,CruzRoja2) && ImpactoCruzRoja2 != 0))&&
	  vidas_verde != MAX_VIDAS)
      {
	vidas_verde = MAX_VIDAS;
	ActualizaSonidos(musicabonus);
      }

      if(((Interseccion(RTazul,CruzRoja1) && ImpactoCruzRoja1 != 0)||
	  (Interseccion(RTazul,CruzRoja2) && ImpactoCruzRoja2 != 0))&&
	  vidas_azul != MAX_VIDAS)
      {
	vidas_azul = MAX_VIDAS;
	ActualizaSonidos(musicabonus);
      }

      // pasa por la munici¢n (recarga el cargador)

      if(((Interseccion(RTverde,Municion1) && ImpactoMunicion1 != 0)||
	  (Interseccion(RTverde,Municion2) && ImpactoMunicion2 != 0))&&
	  cargador_verde != MAX_BALAS)
      {
	cargador_verde = MAX_BALAS;
	ActualizaSonidos(musicabonus);
      }

      if(((Interseccion(RTazul,Municion1) && ImpactoMunicion1 != 0)||
	  (Interseccion(RTazul,Municion2) && ImpactoMunicion2 != 0))&&
	  cargador_azul != MAX_BALAS)
      {
	cargador_azul = MAX_BALAS;
	ActualizaSonidos(musicabonus);
      }

      // pasa por fuel (recarga el dep¢sito de fuel del tanque)

      if(((Interseccion(RTverde,Fuel1) && ImpactoFuel1 != 0)||
	  (Interseccion(RTverde,Fuel2) && ImpactoFuel2 != 0))&&
	  fuel_verde < MAX_FUEL-30)
      {
	fuel_verde = MAX_FUEL;
	ActualizaSonidos(musicabonus);
      }

      if(((Interseccion(RTazul,Fuel1) && ImpactoFuel1 != 0)||
	  (Interseccion(RTazul,Fuel2) && ImpactoFuel2 != 0))&&
	  fuel_azul < MAX_FUEL-30)
      {
	fuel_azul = MAX_FUEL;
	ActualizaSonidos(musicabonus);
      }

      // impacto de bala en cruz roja

      if(((Interseccion(BalaTverde,CruzRoja1) && bala_verde) ||
	  (Interseccion(BalaTazul,CruzRoja1) && bala_azul))  &&
	 ImpactoCruzRoja1 != 0)
      {
	ImpactoCruzRoja1--;
	ActualizaSonidos(musicatocado);
      }

      if(((Interseccion(BalaTverde,CruzRoja2) && bala_verde) ||
	  (Interseccion(BalaTazul,CruzRoja2) && bala_azul))  &&
	 ImpactoCruzRoja2 != 0)
      {
	ImpactoCruzRoja2--;
	ActualizaSonidos(musicatocado);
      }

      // impacto de bala en munici¢n

      if(((Interseccion(BalaTverde,Municion1) && bala_verde) ||
	  (Interseccion(BalaTazul,Municion1) && bala_azul))  &&
	 ImpactoMunicion1 != 0)
      {
	ImpactoMunicion1--;
	ActualizaSonidos(musicatocado);
      }

      if(((Interseccion(BalaTverde,Municion2) && bala_verde) ||
	  (Interseccion(BalaTazul,Municion2) && bala_azul))  &&
	 ImpactoMunicion2 != 0)
      {
	ImpactoMunicion2--;
	ActualizaSonidos(musicatocado);
      }

      // impacto de bala en fuel

      if(((Interseccion(BalaTverde,Fuel1) && bala_verde) ||
	  (Interseccion(BalaTazul,Fuel1) && bala_azul))  &&
	 ImpactoFuel1 != 0)
      {
	ImpactoFuel1--;
	ActualizaSonidos(musicatocado);
      }

      if(((Interseccion(BalaTverde,Fuel2) && bala_verde) ||
	  (Interseccion(BalaTazul,Fuel2) && bala_azul))  &&
	 ImpactoFuel2 != 0)
      {
	ImpactoFuel2--;
	ActualizaSonidos(musicatocado);
      }

      // impacto de bala en bases

      if(((Interseccion(BalaTverde,BaseVerde) && bala_verde) ||
	  (Interseccion(BalaTazul,BaseVerde) && bala_azul))  &&
	 ImpactoBaseVerde != 0)
      {
	ImpactoBaseVerde--;
	ActualizaSonidos(musicatocado);
	if(!ImpactoBaseVerde)
	  salir = BASE_VERDE;
      }

      if(((Interseccion(BalaTverde,BaseAzul) && bala_verde) ||
	  (Interseccion(BalaTazul,BaseAzul) && bala_azul))  &&
	 ImpactoBaseAzul != 0)
      {
	ImpactoBaseAzul--;
	ActualizaSonidos(musicatocado);
	if(!ImpactoBaseAzul)
	  salir = BASE_AZUL;
      }

      // control de la bala

      if(bala_verde)				// ¨bala verde activa?
      {
	switch(dir_bala_verde)
	{
	  case DIR_NORTE:
	       if(BalaTverde.y1 >= 3 && dist_bala_verde < ALCANCE_BALA &&
		  !(Interseccion(BalaTverde,BalaTazul) && bala_azul) &&
		  !Interseccion(BalaTverde,RTazul) &&
		  !((Interseccion(BalaTverde,CruzRoja1)&&ImpactoCruzRoja1) ||
		    (Interseccion(BalaTverde,CruzRoja2)&&ImpactoCruzRoja2) ||
		    (Interseccion(BalaTverde,Municion1)&&ImpactoMunicion1) ||
		    (Interseccion(BalaTverde,Municion2)&&ImpactoMunicion2) ||
		    (Interseccion(BalaTverde,Fuel1)    &&ImpactoFuel1    ) ||
		    (Interseccion(BalaTverde,Fuel2)    &&ImpactoFuel2    ) ||
		    (Interseccion(BalaTverde,BaseVerde)&&ImpactoBaseVerde) ||
		    (Interseccion(BalaTverde,BaseAzul) &&ImpactoBaseAzul )) )
	       {
		 FondoVirtual(BalaTverde.y1,BalaTverde.x1,
			      BalaTverde.y1+ALTO_BAL,BalaTverde.x1+ANCHO_BAL);
		 BalaTverde.y1 = BalaTverde.y1 - vel_bala_verde;
		 VisualizaSprite(BalaTverde.y1,BalaTverde.x1,sprite[BALAN]);
		 dist_bala_verde++;
	       }
	       else
	       {
		 FondoVirtual(BalaTverde.y1,BalaTverde.x1,
			      BalaTverde.y1+ALTO_BAL,BalaTverde.x1+ANCHO_BAL);
		 bala_verde = 0;
		 BalaTverde.y1 = 0;
		 BalaTverde.x1 = 0;
	       }
	       break;
	  case DIR_ESTE:
	       if(BalaTverde.x1 <= 306 && dist_bala_verde < ALCANCE_BALA &&
		 (!(Interseccion(BalaTverde,BalaTazul) && bala_azul) &&
		  !Interseccion(BalaTverde,RTazul) &&
		  !((Interseccion(BalaTverde,CruzRoja1)&&ImpactoCruzRoja1) ||
		    (Interseccion(BalaTverde,CruzRoja2)&&ImpactoCruzRoja2) ||
		    (Interseccion(BalaTverde,Municion1)&&ImpactoMunicion1) ||
		    (Interseccion(BalaTverde,Municion2)&&ImpactoMunicion2) ||
		    (Interseccion(BalaTverde,Fuel1)    &&ImpactoFuel1    ) ||
		    (Interseccion(BalaTverde,Fuel2)    &&ImpactoFuel2    ) ||
		    (Interseccion(BalaTverde,BaseVerde)&&ImpactoBaseVerde) ||
		    (Interseccion(BalaTverde,BaseAzul) &&ImpactoBaseAzul ))))
	       {
		 FondoVirtual(BalaTverde.y1,BalaTverde.x1,
			      BalaTverde.y1+ALTO_BAL,BalaTverde.x1+ANCHO_BAL);
		 BalaTverde.x1 = BalaTverde.x1 + vel_bala_verde;
		 VisualizaSprite(BalaTverde.y1,BalaTverde.x1,sprite[BALAE]);
		 dist_bala_verde++;
	       }
	       else
	       {
		 FondoVirtual(BalaTverde.y1,BalaTverde.x1,
			      BalaTverde.y1+ALTO_BAL,BalaTverde.x1+ANCHO_BAL);
		 bala_verde = 0;
		 BalaTverde.y1 = 0;
		 BalaTverde.x1 = 0;
	       }
	       break;
	  case DIR_SUR:
	       if(BalaTverde.y1 <= 164 && dist_bala_verde < ALCANCE_BALA &&
		  !(Interseccion(BalaTverde,BalaTazul) && bala_azul) &&
		  !Interseccion(BalaTverde,RTazul) &&
		  !((Interseccion(BalaTverde,CruzRoja1)&&ImpactoCruzRoja1) ||
		    (Interseccion(BalaTverde,CruzRoja2)&&ImpactoCruzRoja2) ||
		    (Interseccion(BalaTverde,Municion1)&&ImpactoMunicion1) ||
		    (Interseccion(BalaTverde,Municion2)&&ImpactoMunicion2) ||
		    (Interseccion(BalaTverde,Fuel1)    &&ImpactoFuel1    ) ||
		    (Interseccion(BalaTverde,Fuel2)    &&ImpactoFuel2    ) ||
		    (Interseccion(BalaTverde,BaseVerde)&&ImpactoBaseVerde) ||
		    (Interseccion(BalaTverde,BaseAzul) &&ImpactoBaseAzul )) )
	       {
		 FondoVirtual(BalaTverde.y1,BalaTverde.x1,
			      BalaTverde.y1+ALTO_BAL,BalaTverde.x1+ANCHO_BAL);
		 BalaTverde.y1 = BalaTverde.y1 + vel_bala_verde;
		 VisualizaSprite(BalaTverde.y1,BalaTverde.x1,sprite[BALAS]);
		 dist_bala_verde++;
	       }
	       else
	       {
		 FondoVirtual(BalaTverde.y1,BalaTverde.x1,
			      BalaTverde.y1+ALTO_BAL,BalaTverde.x1+ANCHO_BAL);
		 bala_verde = 0;
		 BalaTverde.y1 = 0;
		 BalaTverde.x1 = 0;
	       }
	       break;
	  case DIR_OESTE:
	       if(BalaTverde.x1 >= 3 && dist_bala_verde < ALCANCE_BALA &&
		  !(Interseccion(BalaTverde,BalaTazul) && bala_azul) &&
		  !Interseccion(BalaTverde,RTazul) &&
		  !((Interseccion(BalaTverde,CruzRoja1)&&ImpactoCruzRoja1) ||
		    (Interseccion(BalaTverde,CruzRoja2)&&ImpactoCruzRoja2) ||
		    (Interseccion(BalaTverde,Municion1)&&ImpactoMunicion1) ||
		    (Interseccion(BalaTverde,Municion2)&&ImpactoMunicion2) ||
		    (Interseccion(BalaTverde,Fuel1)    &&ImpactoFuel1    ) ||
		    (Interseccion(BalaTverde,Fuel2)    &&ImpactoFuel2    ) ||
		    (Interseccion(BalaTverde,BaseVerde)&&ImpactoBaseVerde) ||
		    (Interseccion(BalaTverde,BaseAzul) &&ImpactoBaseAzul )) )
	       {
		 FondoVirtual(BalaTverde.y1,BalaTverde.x1,
			      BalaTverde.y1+ALTO_BAL,BalaTverde.x1+ANCHO_BAL);
		 BalaTverde.x1 = BalaTverde.x1 - vel_bala_verde;
		 VisualizaSprite(BalaTverde.y1,BalaTverde.x1,sprite[BALAO]);
		 dist_bala_verde++;
	       }
	       else
	       {
		 FondoVirtual(BalaTverde.y1,BalaTverde.x1,
			      BalaTverde.y1+ALTO_BAL,BalaTverde.x1+ANCHO_BAL);
		 bala_verde = 0;
		 BalaTverde.y1 = 0;
		 BalaTverde.x1 = 0;
	       }
	       break;
	} // switch (dir_bala_verde)
      } // if (bala_verde)

      if(bala_azul)				// hay bala activa
      {
	switch(dir_bala_azul)
	{
	  case DIR_NORTE:
	       if(BalaTazul.y1 >= 3 && dist_bala_azul < ALCANCE_BALA &&
		  !(Interseccion(BalaTazul,BalaTverde) && bala_verde) &&
		  !Interseccion(BalaTazul,RTverde) &&
		  !((Interseccion(BalaTazul,CruzRoja1)&&ImpactoCruzRoja1) ||
		    (Interseccion(BalaTazul,CruzRoja2)&&ImpactoCruzRoja2) ||
		    (Interseccion(BalaTazul,Municion1)&&ImpactoMunicion1) ||
		    (Interseccion(BalaTazul,Municion2)&&ImpactoMunicion2) ||
		    (Interseccion(BalaTazul,Fuel1)    &&ImpactoFuel1     )||
		    (Interseccion(BalaTazul,Fuel2)    &&ImpactoFuel2     )||
		    (Interseccion(BalaTazul,BaseVerde)&&ImpactoBaseVerde) ||
		    (Interseccion(BalaTazul,BaseAzul) &&ImpactoBaseAzul )) )
	     {
	       FondoVirtual(BalaTazul.y1,BalaTazul.x1,
			    BalaTazul.y1+ALTO_BAL,BalaTazul.x1+ANCHO_BAL);
	       BalaTazul.y1 = BalaTazul.y1 - vel_bala_azul;
	       VisualizaSprite(BalaTazul.y1,BalaTazul.x1,sprite[BALAN]);
	       dist_bala_azul++;
	     }
	     else
	     {
	       FondoVirtual(BalaTazul.y1,BalaTazul.x1,
			    BalaTazul.y1+ALTO_BAL,BalaTazul.x1+ANCHO_BAL);
	       bala_azul = 0;
	       BalaTazul.y1     = 0;
	       BalaTazul.x1     = 0;
	     }
	     break;
	case DIR_ESTE:
	     if(BalaTazul.x1 <= 306 && dist_bala_azul < ALCANCE_BALA &&
		!(Interseccion(BalaTazul,BalaTverde) && bala_verde) &&
		!Interseccion(BalaTazul,RTverde) &&
		!((Interseccion(BalaTazul,CruzRoja1) && ImpactoCruzRoja1) ||
		  (Interseccion(BalaTazul,CruzRoja2) && ImpactoCruzRoja2) ||
		  (Interseccion(BalaTazul,Municion1) && ImpactoMunicion1) ||
		  (Interseccion(BalaTazul,Municion2) && ImpactoMunicion2) ||
		  (Interseccion(BalaTazul,Fuel1)     &&ImpactoFuel1     ) ||
		  (Interseccion(BalaTazul,Fuel2)     &&ImpactoFuel2     ) ||
		  (Interseccion(BalaTazul,BaseVerde)&&ImpactoBaseVerde  ) ||
		  (Interseccion(BalaTazul,BaseAzul) &&ImpactoBaseAzul   )) )
	     {
	       FondoVirtual(BalaTazul.y1,BalaTazul.x1,
			    BalaTazul.y1+ALTO_BAL,BalaTazul.x1+ANCHO_BAL);
	       BalaTazul.x1 = BalaTazul.x1 + vel_bala_azul;
	       VisualizaSprite(BalaTazul.y1,BalaTazul.x1,sprite[BALAE]);
	       dist_bala_azul++;
	     }
	     else
	     {
	       FondoVirtual(BalaTazul.y1,BalaTazul.x1,
			    BalaTazul.y1+ALTO_BAL,BalaTazul.x1+ANCHO_BAL);
	       bala_azul = 0;
	       BalaTazul.y1     = 0;
	       BalaTazul.x1     = 0;
	     }
	     break;
	case DIR_SUR:
	     if(BalaTazul.y1 <= 164 && dist_bala_azul < ALCANCE_BALA &&
		!(Interseccion(BalaTazul,BalaTverde) && bala_verde) &&
		!Interseccion(BalaTazul,RTverde) &&
		!((Interseccion(BalaTazul,CruzRoja1) && ImpactoCruzRoja1) ||
		  (Interseccion(BalaTazul,CruzRoja2) && ImpactoCruzRoja2) ||
		  (Interseccion(BalaTazul,Municion1) && ImpactoMunicion1) ||
		  (Interseccion(BalaTazul,Municion2) && ImpactoMunicion2) ||
		  (Interseccion(BalaTazul,Fuel1)     &&ImpactoFuel1     ) ||
		  (Interseccion(BalaTazul,Fuel2)     &&ImpactoFuel2     ) ||
		  (Interseccion(BalaTazul,BaseVerde)&&ImpactoBaseVerde  ) ||
		  (Interseccion(BalaTazul,BaseAzul) &&ImpactoBaseAzul   )) )
	     {
	       FondoVirtual(BalaTazul.y1,BalaTazul.x1,
			    BalaTazul.y1+ALTO_BAL,BalaTazul.x1+ANCHO_BAL);
	       BalaTazul.y1 = BalaTazul.y1 + vel_bala_azul;
	       VisualizaSprite(BalaTazul.y1,BalaTazul.x1,sprite[BALAS]);
	       dist_bala_azul++;
	     }
	     else
	     {
	       FondoVirtual(BalaTazul.y1,BalaTazul.x1,
			    BalaTazul.y1+ALTO_BAL,BalaTazul.x1+ANCHO_BAL);
	       bala_azul = 0;
	       BalaTazul.y1     = 0;
	       BalaTazul.x1     = 0;
	     }
	     break;
	case DIR_OESTE:
	     if(BalaTazul.x1 >= 3 && dist_bala_azul < ALCANCE_BALA &&
		!(Interseccion(BalaTazul,BalaTverde) && bala_verde) &&
		!Interseccion(BalaTazul,RTverde) &&
		!((Interseccion(BalaTazul,CruzRoja1) && ImpactoCruzRoja1) ||
		  (Interseccion(BalaTazul,CruzRoja2) && ImpactoCruzRoja2) ||
		  (Interseccion(BalaTazul,Municion1) && ImpactoMunicion1) ||
		  (Interseccion(BalaTazul,Municion2) && ImpactoMunicion2) ||
		  (Interseccion(BalaTazul,Fuel1)     && ImpactoFuel1    ) ||
		  (Interseccion(BalaTazul,Fuel2)     && ImpactoFuel2    ) ||
		  (Interseccion(BalaTazul,BaseVerde)&&ImpactoBaseVerde  ) ||
		  (Interseccion(BalaTazul,BaseAzul) &&ImpactoBaseAzul   )) )
	     {
	       FondoVirtual(BalaTazul.y1,BalaTazul.x1,
			    BalaTazul.y1+ALTO_BAL,BalaTazul.x1+ANCHO_BAL);
	       BalaTazul.x1 = BalaTazul.x1 - vel_bala_azul;
	       VisualizaSprite(BalaTazul.y1,BalaTazul.x1,sprite[BALAO]);
	       dist_bala_azul++;
	     }
	     else
	     {
	       FondoVirtual(BalaTazul.y1,BalaTazul.x1,
			    BalaTazul.y1+ALTO_BAL,BalaTazul.x1+ANCHO_BAL);
	       bala_azul = 0;
	       BalaTazul.y1     = 0;
	       BalaTazul.x1     = 0;
	     }
	     break;
	} // switch
      } // if

    // comprueba si hay un empate

    if((!bala_verde && !bala_azul && !cargador_verde && !cargador_azul &&
	!ImpactoMunicion1 && !ImpactoMunicion2) ||
	(!bala_verde && !bala_azul && !fuel_verde && !fuel_azul))
      salir=EMPATE;

    RefrescaPantalla();

  } // si salir...

  return salir;
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± a jugaaaarrrr...                                                       ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void Jugar()
{
  int  i,c;					// contadores
  unsigned char cadaux[128];			// cadena auxiliar
  unsigned char fin_partida,salir;		// fin de partida y salida

  // definici¢n de teclas por defecto...

  tec_n_verde = 16;		// tec. Q
  tec_s_verde = 30;             // tec. A
  tec_e_verde = 37;             // tec. K
  tec_o_verde = 36;             // tec. J
  tec_d_verde = 57;             // tec. <SPC>

  tec_n_azul = 72;		// curs. arr.
  tec_s_azul = 80;		// curs. abj.
  tec_e_azul = 77;		// curs. der.
  tec_o_azul = 75;		// curs. izq.
  tec_d_azul = 29;		// tec.  <CTRL>

  fin_partida = 0;				// fin de partida = no

  tanques_verde  = MAX_TANQUES;			// m x. tanques en base
  tanques_azul   = MAX_TANQUES;			// m x. tanques en base

  // inicializaciones

  memcpy(palaux,pal,768);
  memcpy(campo_actual,campo[n_campo],11*20*sizeof(char));

  // bucle que controla si se han terminado los tanques para jugar...

  while(!fin_partida)
  {
    // inicializaci¢n de variables

    // datos para armamento y cruz roja

    CruzRoja1.y1     = 0;
    CruzRoja1.x1     = 0;
    CruzRoja1.alto   = ALTO_CR;
    CruzRoja1.ancho  = ANCHO_CR;
    ImpactoCruzRoja1 = 3;

    CruzRoja2.y1     = 0;
    CruzRoja2.x1     = 0;
    CruzRoja2.alto   = ALTO_CR;
    CruzRoja2.ancho  = ANCHO_CR;
    ImpactoCruzRoja2 = 3;

    Municion1.y1     = 0;
    Municion1.x1     = 0;
    Municion1.alto   = ALTO_MUN;
    Municion1.ancho  = ANCHO_MUN;
    ImpactoMunicion1 = 3;

    Municion2.y1     = 0;
    Municion2.x1     = 0;
    Municion2.alto   = ALTO_MUN;
    Municion2.ancho  = ANCHO_MUN;
    ImpactoMunicion2 = 3;

    Fuel1.y1         = 0;
    Fuel1.x1         = 0;
    Fuel1.alto       = ALTO_FUEL;
    Fuel1.ancho      = ANCHO_FUEL;
    ImpactoFuel1     = 3;

    Fuel2.y1         = 0;
    Fuel2.x1         = 0;
    Fuel2.alto       = ALTO_FUEL;
    Fuel2.ancho      = ANCHO_FUEL;
    ImpactoFuel2     = 3;

    BaseVerde.y1     = 0;
    BaseVerde.x1     = 0;
    BaseVerde.alto   = ALTO_BASE;
    BaseVerde.ancho  = ANCHO_BASE;
    ImpactoBaseVerde = MAX_BASE;

    BaseAzul.y1      = 0;
    BaseAzul.x1      = 0;
    BaseAzul.alto    = ALTO_BASE;
    BaseAzul.ancho   = ANCHO_BASE;
    ImpactoBaseAzul  = MAX_BASE;

    // datos sobre los tanques (posici¢n, etc.)

    RTverde.y1    = 0;
    RTverde.x1    = 0;
    RTverde.alto  = ALTO_TAN;
    RTverde.ancho = ANCHO_TAN;
    RTazul.y1     = 0;
    RTazul.x1     = 0;
    RTazul.alto   = ALTO_TAN;
    RTazul.ancho  = ANCHO_TAN;

    dir_verde = DIR_ESTE;
    dir_azul  = DIR_OESTE;

    // datos sobre las balas

    BalaTverde.y1    = 0;
    BalaTverde.x1    = 0;
    BalaTverde.alto  = ALTO_BAL;
    BalaTverde.ancho = ANCHO_BAL;
    BalaTazul.y1     = 0;
    BalaTazul.x1     = 0;
    BalaTazul.alto   = ALTO_BAL;
    BalaTazul.ancho  = ANCHO_BAL;
    bala_verde = 0;				  // 0 = no disparada
    bala_azul  = 0;                               // "    "    "
    vel_bala_verde  = 3;                          // velocidad
    vel_bala_azul   = 3;                          //    "
    dist_bala_verde = 0;                          // distancia actual de bala
    dist_bala_azul  = 0;                          //    "        "    "   "

    salir = 0;					  // 0 = no salir

    // vidas (impactos permitidos), cargador y fuel

    vidas_verde    = MAX_VIDAS;
    vidas_azul     = MAX_VIDAS;
    cargador_verde = MAX_BALAS;
    cargador_azul  = MAX_BALAS;
    fuel_verde     = MAX_FUEL;
    fuel_azul      = MAX_FUEL;

    // preparados...

    if(tanques_verde == MAX_TANQUES && tanques_azul == MAX_TANQUES)
    {
      printstringVGA(100,120,"PREPARADOS",32);
      EfectoCaida();
      esperaretrazos(50);
      parpadeopal();
      InicializaPaleta();
    }

    // inicializaci¢n de campo y marcadores...

    if(conexion_establecida)
    {
      n_campo = 0;
      memcpy(campo_actual,campo[n_campo],11*20*sizeof(char));
    }

    IniCampo();
    IniMarcadores();

    while(kbhit())			// borra buffer de teclado
      getch();

    // batalla, mientras no haya empate, destrucci¢n de tanque, base, ...

    salir = Batalla();

    // control de la salida...

    parpadeopal();			// parpadeo (efecto)

    switch(salir)
    {
    case ABORTADO:   fin_partida = ABORTADO;
		     break;
    case EMPATE:     fin_partida = EMPATE;
		     break;
    case BASE_VERDE: tanques_verde = 0;
		     fin_partida = GANA_AZUL;
		     break;
    case BASE_AZUL:  tanques_azul = 0;
		     fin_partida = GANA_VERDE;
		     break;
    case GANA_VERDE: tanques_azul--;
		     if(tanques_azul == 0)
		       fin_partida = GANA_VERDE;
		     break;
    case GANA_AZUL:  tanques_verde--;
		     if(tanques_verde == 0)
		       fin_partida = GANA_AZUL;
		     break;
    }

    // inventario de tanques...

    LimpiaPantallas();
    InicializaPaleta();
    printstringVGA(60,60,"TANQUES VERDES:",31);
    printstringVGA(60,250,itoa(tanques_verde,cadaux,10),31);
    printstringVGA(80,60,"TANQUES AZULES:",31);
    printstringVGA(80,250,itoa(tanques_azul,cadaux,10),31);
    EfectoCaida();
    esperaretrazos(100);
    parpadeopal();

  } // si fin_partida...

  // ganadooooorrrrr...

  LimpiaPantallas();
  InicializaPaleta();
  inifontVGA(FONT_8x8);

  switch(fin_partida)
  {
    case ABORTADO:   printstringVGA(60,60,"    >> ABORTADO <<",64);
		     EfectoCaida();
		     break;
    case GANA_VERDE: printstringVGA(60,60,">> GANADOR: TANQUE VERDE <<",64);
		     EfectoCaida();
		     break;
    case GANA_AZUL:  printstringVGA(60,60,">> GANADOR: TANQUE AZUL <<",64);
		     EfectoCaida();
		     break;
    case EMPATE:
    default:         printstringVGA(60,60,"    >> EMPATADOS <<",64);
		     EfectoCaida();

  }

  // esperamos un poco...

  for(c=0;c<100;c++)
  {
    scrollpal(64,78);
    esperaretrazo();
  }
  parpadeopal();
  parpadeopal();

  memcpy(pal,palaux,768);			// paleta de color anterior
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± men£ y control de enlace remoto                                        ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void JugarRemoto()
{
  // registros del ACE 8250

  char ier;
  char lsr;
  char mcr;
  char msr;

  char dato = 0;			// dato
  int tec = 0;				// c¢digo de tecla
  time_t seg_cero;			// contador de segundos

  // se configura el puerto...

  serie.puerto_base = peek(0x40,(serie.puerto-1)*2);
  if(serie.puerto<1 || serie.puerto>4)
  {
    perror("\n\n\bERROR: los puertos serie son de 1 a 4");
    exit(1);
  }
  else if(!serie.puerto_base)
  {
    perror("\n\n\bERROR: el puerto especificado no existe");
    exit(1);
  }
  if(serie.velocidad<50 || serie.velocidad>115200L)
  {
    perror("\n\n\bERROR: la velocidad es un valor entre 50 y 115200");
    exit(1);
  }

  outportb(IER,0);			// fuera interrupciones
  lsr = inport(LSR);
  mcr = inport(MCR);
  msr = inport(MSR);

  SpeedConfig(serie.velocidad);		// velocidad
  LCRConfig(3,1,4);  		        // configuraci¢n (8,n,1)

  outportb(LSR,lsr);
  outportb(MCR,mcr);
  outportb(MSR,msr);

  // men£ para la comunicaci¢n

  memcpy(palaux,pal,768);
  inifontVGA(FONT_8x16);
  printstringVGA(10,10,"TANQUES v1.0 -> MENU DE CONEXION <-",25);
  inifontVGA(FONT_8x16);
  printstringVGA(60,10, "1. Llamar al oponente  (tanque verde)",41);
  printstringVGA(80,10, "2. Recibir al oponente (tanque azul) ",41);
  printstringVGA(100,10,"3. Cortar conexion                   ",41);
  printstringVGA(120,10,"4. Volver al menu principal          ",41);

  ActualizaSonidos(musicamenu2);

  EfectoCaida();

  while(kbhit())			// borra buffer de teclado
    getch();

  tec = 0;
  dato = 0;

  // control del men£

  do{
    if(kbhit()) tec = getch();
    scrollpal(25,40);
    scrollpal(41,48);
    esperaretrazos(2);
  } while(tec<'1' || tec>'4');

  ActualizaSonidos(musicabonus);
  LimpiaPantallas();

  switch(tec)
  {
      case '1':  printstringVGA(100,60,"ESTABLECIENDO CONEXION...",41);
		 EfectoCaida();

		   seg_cero = time(NULL);

		   // comprueba si al enviar una T recibe una R o
		   // pasan 15 segundos...

		   EnviarByteCOM('T');		// env¡a una T

		   do
		   {
		       dato = 0;
		       EnviarByteCOM('T');		// env¡a una T
		       RecibirByteCOM(&dato);           // recibe dato
		   }
		   while(((time(NULL))-seg_cero)<15 && dato != 'R');

		   // si el dato NO es una R, hay alg£n problema...

		   if(dato != 'R')
		   {
		     LimpiaPantallas();
		     printstringVGA(100,60,"ERROR, NO ENLAZA",41);
		     EfectoCaida();
		     esperaretrazos(400);
		     EnviarCadenaCOM(serie.colgar);
		   }
		   else
		     conexion_establecida = 1;	// conect¢ :-)
		 break;
      case '2':  printstringVGA(100,60,"ESPERANDO ENLACE...",41);
		 EfectoCaida();

		 // ahora espera recibir una T mientras no se pulse
		 // la tecla ESC

		 do
		 {
		   dato = 0;
		   RecibirByteCOM(&dato);
		   if(dato == 'T')
		   {
		     EnviarByteCOM('R');
		     conexion_establecida = 2;	// conect¢ :-)
		   }
		   if(kbhit()) tec = getch();
		 } while(tec!=27 && dato!='T');

		 // si se puls¢ escape...

		 if(tec == 27)
		 {
		   LimpiaPantallas();
		   printstringVGA(100,60,"ABORTADO POR EL USUARIO",41);
		   EfectoCaida();
		   esperaretrazos(400);
		 }
		 break;
      case '3':  conexion_establecida = 0;
		 break;
  } // fin del switch-case

  memcpy(pal,palaux,768);
  LimpiaPantallas();
}
