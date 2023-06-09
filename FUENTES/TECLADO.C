/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
�            T A N Q U E S   1.0        1.996   BY  FEGOR                �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
�                                                                        �
� MODULO   > TECLADO.C                                                   �
� AUTOR    > Fernando Gonz爈ez Ruano (FEGOR)                             �
� VERSION  > 1.0                                                         �
� LENGUAJE > Borland C/C++ versi 3.1                                   �
�                                                                        �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
�                                                                        �
� Funciones de veo                                                     �
�                                                                        �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
�                   CLUB VIRTUAL ZONE    -1.996-                         �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/

#pragma inline

#include <dos.h>
#include <stdlib.h>

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� defines                                                                �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
#define INTER_KEYB_BIOS 0x16
#define IRQ9            0x9

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� variables plicas o generales                                         �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
unsigned int CodigoLetra[128];			// tabla de c. de teclas
unsigned char CodigoActual;			// cigo actual
void interrupt (*IRQ9Anterior)(void);		// interr. IRQ 9 (teclado)

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� funci de control del teclado                                         �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
void interrupt ControlaTeclado()
{
  disable();				// fuera interrupciones

lazo:                   		// limpia buffer de teclado
      asm{
	   mov	ah,0x11
	   int	0x16
	   jz	fuera
	   mov	ah,0x10
	   int	0x16
	   jmp	lazo
      }
fuera:

  CodigoActual = inportb(0x60);		// lectura del cigo scan

  if(CodigoActual < 0x80)		// ╩ake?
    CodigoLetra[CodigoActual]=1;	// si
  else
    CodigoLetra[CodigoActual-0x80]=0;	// no (resta 128)

  enable();				// activaci de interrupciones
  IRQ9Anterior();			// llamamos al vector original
}

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� instalaci de rutina de teclado                                       �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
void InstalaTeclado()
{
  int i;				// contador

  for(i=1;i<127;i++)
    CodigoLetra[i] = 0;         	// inicializa tabla

  IRQ9Anterior = getvect(IRQ9);		// recoge vector original
  setvect(IRQ9,ControlaTeclado);	// nueva funci
}

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� restaura la IRQ 9 antigua                                              �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
void DesInstalaTeclado()
{
  setvect(IRQ9,IRQ9Anterior);
}
