/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
�            T A N Q U E S   1.0        1.996   BY  FEGOR                �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
�                                                                        �
� MODULO   > SERIE.C                                                     �
� AUTOR    > Fernando Gonz爈ez Ruano (FEGOR)                             �
� VERSION  > 1.0                                                         �
� LENGUAJE > Borland C/C++ versi 3.1                                   �
�                                                                        �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
�                                                                        �
� Funciones para transmisi de datos por el puerto serie                �
�                                                                        �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
�                   CLUB VIRTUAL ZONE    -1.996-                         �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/

#include<stdio.h>
#include<time.h>

#include"rs232.h"

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� variables externas                                                     �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
TipoSerie serie;

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� lee la configuraci de comunicaciones <TANQUES.REM>                   �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
void LeeCFGserie(const char nombre[])
{
  FILE *f;				// fichero
  int st;				// estado

  // abre el fichero de configuraci

  if ((f = fopen(nombre,"rt")) == NULL)
  {
    perror("\n\n\bERROR: fichero de configuraci de serie no encontrado");
    exit(1);
  }
  printf("+ Leyendo <%s>...\n",nombre);

  // puerto

  if((fscanf(f,"%c",&(serie.puerto))==EOF))
  {
    perror("\n\n\bERROR: no se ha podido leer el puerto");
    exit(1);
  }

  serie.puerto = serie.puerto-48;

  // velocidad

  if((fscanf(f,"%lu",&(serie.velocidad)))==EOF)
  {
    perror("\n\n\bERROR: no se ha podido leer la velocidad del puerto");
    exit(1);
  }

  // ATENCION
  // --------
  // Esta parte del cigo sobra debido a que ser para otra versi o
  // revisi del juego en el que se pudiese usar el modem para la
  // conexi.

/*
  // inicio

  if((fscanf(f,"%s",serie.inicio))==EOF)
  {
    perror("\n\n\bERROR: no se ha podido leer cadena de inicio del puerto");
    exit(1);
  }

  // marcado

  if((fscanf(f,"%s",serie.marcado)==EOF))
  {
    perror("\n\n\bERROR: no se ha podido leer cadena de marcado del puerto");
    exit(1);
  }

  // recibir

  if((fscanf(f,"%s",serie.recibir)==EOF))
  {
    perror("\n\n\bERROR: no se ha podido leer cadena de recibir del puerto");
    exit(1);
  }

  // colgar

  if((fscanf(f,"%s",serie.colgar)==EOF))
  {
    perror("\n\n\bERROR: no se ha podido leer cadena de colgar del puerto");
    exit(1);
  }
*/
  fclose(f);
}

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� desactivaci del registro IER, devolviendo su valor original          �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
char IER_off()
{
  char ier_old;
  ier_old = inportb(IER);
  outportb(IER,0);
  return ier_old;
}

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� activaci del registro IER                                            �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
void IER_on(char ier)
{
  outportb(IER, ier);
}

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� activaci del registro DLAB (bit 7 del LCR)                           �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
void DLAB_on()
{
  char dlab;
  dlab = inportb(LCR);
  outportb(LCR, dlab | 128);
}

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� desactivaci del registro DLAB (bit 7 del LCR)                        �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
void DLAB_off()
{
  char dlab;
  dlab = inportb(LCR);
  outportb(LCR, dlab & 127);
}

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� configuraci de la velocidad del puerto                               �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
void SpeedConfig(long speed)
{
  unsigned divisor;

  //                       1843200
  //        Divisor = ------------------
  //                    16 x Velocidad

  divisor = (unsigned)(1843200L / (16L*speed));
  DLAB_on();
  outportb(DLL, (char)divisor);
  outportb(DLM, (char)(divisor>>8));
  DLAB_off();
}

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� configuraci del LCR (Word/Stop/Parity)                               �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
void LCRConfig(char l, char s, char p )
{
  char lcr;
  lcr = inport(LCR);
  lcr = lcr & 224;                    /* m爏cara de bits 11100000 */
  s = s<<2;                           /* stop = bit 2             */
  p = p<<3;                           /* paridad = bits 3 y 4     */
  outport(LCR, lcr | l | s | p);      /* activar word+stop+parity */
}

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� borra el buffer del puerto serie                                       �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
void BorrarBufferCOM()
{
  while(inport(LSR) & DR)
    inport(RBR);
}

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� recibe un byte del puerto serie                                        �
�                                                                        �
� Nota: Esta funci no espera a que el DR est� activo                   �
�                                                                        �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
char RecibirByteCOM(unsigned char dato[1])
{
  char lsr;

  *dato = 0;
  if((lsr=inport(LSR)) & DR)		// si hay dato disponible...
    *dato = inport(RBR);		// ...recibe dato
  return lsr;				// retorna estado de lea
}

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� transmitir un byte del puerto serie                                    �
�                                                                        �
� Nota: Esta funci no espera a que el THRE est� activo                 �
�                                                                        �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
char EnviarByteCOM(unsigned char dato)
{
  char lsr;

  if((lsr=inport(LSR)) & THRE)
      outportb(THR,dato);		// enviamos el dato :-)
  return lsr;				// retorna estado de lea
}

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� env una cadena de caracteres al puerto serie                         �
�                                                                        �
� Nota: Esta funci utiliza la funci EnviarByteCOM()                  �
�                                                                        �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
int EnviarCadenaCOM(char* cadena)
{
  int i = 0;
  int estado = 0;

  for(i=0;i<strlen(cadena) && (!estado);++i)
  {
    if(cadena[i] == '|')
      EnviarByteCOM(13);
    else if(cadena[i] == 126)			// 126 = '~'
      delay(1000);
    else
      EnviarByteCOM(cadena[i]);
    delay(250);
  }
  return inport(LSR);
}

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� comprobaci del DCD (Data Carrier Detected)                           �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
int DCDActivo()
{
  if(inport(MSR) & 128)
    return 1;			// si
  else
    return 0;                   // no
}

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� esperar durante un tiempo (segundos) el DCD (Data Carrier Detected)    �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
int EsperaDCD(int seg)
{
  time_t seg_cero;				// cronetro

  seg_cero = time(NULL);			// "lapsus"

  while(((time(NULL)) - seg_cero) < seg)
    if(inport(MSR) & 128)			// � CDC ?
      return 0;					// ...si, ok!
  return 1;					// ...no, error!
}
