/*
��������������������������������������������������������������������������
�            T A N Q U E S   1.0        1.996   BY  FEGOR                �
��������������������������������������������������������������������������
�                                                                        �
� PROGRAMA > TANQUES.EXE                                                 �
� AUTOR    > Fernando Gonz�lez Ruano (FEGOR)                             �
� VERSION  > 1.0                                                         �
� LENGUAJE > Borland C/C++ versi�n 3.1                                   �
�                                                                        �
��������������������������������������������������������������������������
�                   CLUB VIRTUAL ZONE    -1.996-                         �
��������������������������������������������������������������������������
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

#include"video.h"
#include"sonido.h"

/*
��������������������������������������������������������������������������
� variables externas                                                     �
��������������������������������������������������������������������������
*/
extern unsigned char far* pantfondo;            // video.c
extern unsigned char far* pantvirt;             //   "
extern TipoPaleta pal;                          //   "
extern TipoPaleta palaux;                       //   "
extern unsigned int CodigoLetra[128];		// teclado.c
extern TipoNotas musicapres;			// sonido.c
extern TipoNotas musicamenu;                    //   "
extern TipoNotas musicadisparo;                 //   "
extern TipoNotas musicatocado;                  //   "
extern TipoNotas musicabonus;                   //   "
extern char conexion_establecida;		// serie.c

/*
��������������������������������������������������������������������������
� variables p�blicas                                                     �
��������������������������������������������������������������������������
*/
int SONIDO  = 1;				// sonido activado
int EFECTOS = 1;				// efectos activados
TipoSprite sprite[MAXSPRT];			// sprites

/*
��������������������������������������������������������������������������
� presentaci�n del juego                                                 �
��������������������������������������������������������������������������
*/
void presenta()
{
  // limpia la pantalla y pone m�sica...

  LimpiaPantallas();
  ActualizaSonidos(musicapres);
  esperaretrazos(50);

  // virtual zone

  VisualizaSprite(89,42,sprite[PRES1]);
  RefrescaPantalla();
  esperaretrazos(100);
  EfectoHumo();

  // presenta

  VisualizaSprite(89,93,sprite[PRES2]);
  RefrescaPantalla();
  esperaretrazos(100);
  EfectoDifusion();

  // tanques

  VisualizaSprite(89,81,sprite[PRES3]);
  RefrescaPantalla();
  esperaretrazos(100);
  EfectoDifusion2();
  esperaretrazos(50);
}

/*
��������������������������������������������������������������������������
� creditos y agradecimientos...                                          �
��������������������������������������������������������������������������
*/
void creditos()
{
  inifontVGA(FONT_8x16);
  printstringVGA(10,0, "  T A N Q U E S   ",28);
  printstringVGA(30,0, "       v1.0       ",28);
  printstringVGA(60,0, "  Programado por  ",28);
  printstringVGA(80,0, "Fernando Gonzalez ",28);
  printstringVGA(100,0,"      Ruano       ",28);
  printstringVGA(120,0,"     (Fegor)      ",28);
  printstringVGA(140,0,"                  ",28);
  printstringVGA(160,0,"Club Virtual Zone ",28);
  printstringVGA(180,0,"      1.996       ",28);
  VisualizaSprite(0,160,sprite[FOTO]);
  RefrescaPantalla();
  esperaretrazos(300);
  EfectoDifusion2();
  memset(pantvirt,0,64000);
  printstringVGA(60,160, "  Agradecimientos  ",28);
  printstringVGA(90,160, "A Olga,Ivan,Legion,",28);
  printstringVGA(110,160,"  al CPV y a todos ",28);
  printstringVGA(130,160," los que leeis VZM ",28);
  VisualizaSprite(0,1,sprite[FOTO]);
  RefrescaPantalla();
  esperaretrazos(300);
  EfectoDifusion2();
}

/*
��������������������������������������������������������������������������
� men� principal del juego                                               �
��������������������������������������������������������������������������
*/
char menu()
{
  int  i,o;					// contadores, etc.
  unsigned char datoCOM;			// dato del puerto serie
  unsigned char tec;				// c�digo de teclado

  // prepara la pantalla para visualizar un men� bonito...

  LimpiaPantallas();
  InicializaPaleta();
  memcpy(palaux,pal,768);

  // para hacer un efecto persiana en el fondo

  for(i=1;i<198;i+=2)
    for(o=1;o<318;o++)
    {
      Punto(i,o,5);
      Punto(i+1,o,6);
    }

  // visualiza las opciones

  VisualizaSprite(5,78,sprite[PRES3]);
  inifontVGA(FONT_8x16);
  borrafondofont(0);
  printstringVGA(60,80, "1. Jugar",70);
  printstringVGA(80,80, "2. Conexion remota",70);
  printstringVGA(100,80,"3. Elegir campo",70);
  printstringVGA(120,80,"4. Creditos",70);
  printstringVGA(140,80,"5. Salir",70);
  inifontVGA(FONT_8x8);
  printstringVGA(190,72, "VIRTUAL ZONE -1.996-",70);
  ActualizaSonidos(musicamenu);
  EfectoCaida();

  while(kbhit())			// borra buffer de teclado
    getch();

  tec = 0;

  // hacer mientras no se tenga opci�n...
  // o no se reciba por el puerto serie...

  do{
      if(conexion_establecida)
      {
	RecibirByteCOM(&datoCOM);
	if(datoCOM == '1')
	  tec = datoCOM;
      }
      if(kbhit()) tec = getch();
      scrollpal(5,6);
      scrollpal(70,85);
      esperaretrazos(2);
  } while(tec<'1' || tec>'5');

  // si hay conexi�n, env�a la opci�n al otro terminal

  if(conexion_establecida && (datoCOM != '1') && (tec == '1'))
    EnviarByteCOM(tec);

  ActualizaSonidos(musicabonus);
  EfectoHumo();
  LimpiaPantallas();
  memcpy(pal,palaux,768);

  return tec;
}

/*
��������������������������������������������������������������������������
� salida del juego y cartelito de agradecimiento                         �
��������������������������������������������������������������������������
*/
void Terminar()
{
  _setcursortype(_NORMALCURSOR);
  video03h();
  textcolor(15);
  textbackground(0);
  clrscr();
  cputs("Gracias por jugar a TANQUES v1.0\n\r\n\r");
  textcolor(14);
  cputs("Este programa es 'CardWare' y esto significa que si te ha\n\r");
  cputs("gustado o quieres simplemente darme alg�n consejo sobre\n\r");
  cputs("el programa puedes mandarme una postal de tu ciudad.\n\r\n\r");
  cputs("Mi direcci�n es:\n\r");
  textcolor(12);
  cputs("                    Fernando Gonz�lez Ruano\n\r");
  cputs("                    C/Clavel, 12  Urb.Colinas Bermejas\n\r");
  cputs("                    18198,  Monachil\n\r");
  cputs("                    Granada   -ESPA�A-\n\r\n\r");
  textcolor(14);
  cputs("Correo electr�nico:\n\r");
  textcolor(12);
  cputs("                    NetMail: 2:345/801.15\n\r");
  cputs("                    E-Mail:  fgonru@arrakis.es\n\r");
  cputs("                             fernan@p15.atlantis.encomix.com\n\r");
  textcolor(10);
  cputs("\n\rVIRTUAL ZONE MAGAZINE\n\r");
  textcolor(7);
}

/*
��������������������������������������������������������������������������
� m�dulo principal del juego...                                          �
��������������������������������������������������������������������������
*/
int main(int narg,char* larg[])
{
  int i,c;
  char no_pres=0;		// no visualizar presentaciones
  char *ptr_str;		// puntero a cadena (para l�nea de comandos)
  char opc;			// opci�n del men�
  char strd[128];        	// cadena del directorio
  char straux[128];		// cadena auxiliar

  // borra pantalla y saca una peque�a etiqueta del juego...

  clrscr();
  printf("\nTANQUES v1.0");
  printf("\nVirtual Zone, 1.996\n");

  // directorio donde se est� ejecutando

  strnset(strd,0,sizeof(strd));
  memset(strd,0,sizeof(strd));
  memcpy(strd,larg[0],strlen(larg[0])-strlen(strrchr(larg[0],'\\'))+1);
  printf("\nDirectorio:  %s",strd);
  printf("\nMemoria   -> %lu\n",(unsigned long)coreleft());

  // par�metros

  if(narg>1)
    for(c=1;c<narg;c++)
      switch((larg[c][0]=='/'||larg[c][0]=='-')?larg[c][1]:larg[c][0])
      {
	case 's':
	case 'S': SONIDO = 0;		// sin sonido
		  break;
	case 'e':
	case 'E': EFECTOS = 0;		// sin efectos
		  break;
	case 'p':
	case 'P': no_pres = 1;		// sin presentaci�n
		  break;
	case 'h':
	case 'H':
	case '?':
	default : printf("\nsintaxis: TANQUES [-s] [-e] [-h]\n");
		  printf("\n          s -> sin sonido");
		  printf("\n          e -> sin algunos efectos");
		  printf("\n          p -> sin presentaci�n");
		  printf("\n          h -> esta ayuda\n");
		  return(0);
      }

  // inicializaci�n de pantallas y carga de sprites y pantallas

  strcpy(straux,strd);
  strcat(straux,"TANQUES.SPR");
  CargaSprites(straux);
  strcpy(straux,strd);
  strcat(straux,"TANQUES.PAL");
  LeePaleta(straux);
  strcpy(straux,strd);
  strcat(straux,"TANQUES.REM");
  LeeCFGserie(straux);

  printf("\nTotal     -> %lu",(unsigned long)coreleft());
  esperaretrazos(100);

  // inicializaciones

  InicializaPantallas();
  InicializaPaleta();
  _setcursortype(_NOCURSOR);

  CargaSonidos();			// carga lo sonidos
  InstalaSonidos();			// rutina de control de sonidos
  InstalaTeclado();			// rutina de control de teclado

  if(!no_pres)
  {
    presenta();                         // presentaci�n
  }

  // control del men�...

  opc = 0;

  while(opc != '5')
  {
    opc = menu();
    switch(opc)
    {
      case '1': Jugar();                // a jugaaaaaarr...
		break;
      case '2': JugarRemoto();		// establecer conexi�n
		break;
      case '3': ElijeCampo();           // elecci�n del campo de batalla
		break;
      case '4': creditos();		// cr�ditos y agradecimientos
		break;
    } // case(opc)
  } // while(opc)

  // preparando para salir

  DesInstalaSonidos();                  // desinstala rutina de sonidos
  DesInstalaTeclado();			// desinstala rutina de teclado

  // descargar sprites de memoria, pantallas, etc.

  LiberaSprites();
  LiberaPantallas();
  Terminar();				// terminando...

  return 0;				// salida, ok!.  :-)
}
