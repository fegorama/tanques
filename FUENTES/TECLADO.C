/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±            T A N Q U E S   1.0        1.996   BY  FEGOR                ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                                                                        ±
± MODULO   > TECLADO.C                                                   ±
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

#include <dos.h>
#include <stdlib.h>

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± defines                                                                ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
#define INTER_KEYB_BIOS 0x16
#define IRQ9            0x9

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± variables p£blicas o generales                                         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
unsigned int CodigoLetra[128];			// tabla de c¢d. de teclas
unsigned char CodigoActual;			// c¢digo actual
void interrupt (*IRQ9Anterior)(void);		// interr. IRQ 9 (teclado)

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± funci¢n de control del teclado                                         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
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

  CodigoActual = inportb(0x60);		// lectura del c¢digo scan

  if(CodigoActual < 0x80)		// ¨make?
    CodigoLetra[CodigoActual]=1;	// si
  else
    CodigoLetra[CodigoActual-0x80]=0;	// no (resta 128)

  enable();				// activaci¢n de interrupciones
  IRQ9Anterior();			// llamamos al vector original
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± instalaci¢n de rutina de teclado                                       ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void InstalaTeclado()
{
  int i;				// contador

  for(i=1;i<127;i++)
    CodigoLetra[i] = 0;         	// inicializa tabla

  IRQ9Anterior = getvect(IRQ9);		// recoge vector original
  setvect(IRQ9,ControlaTeclado);	// nueva funci¢n
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± restaura la IRQ 9 antigua                                              ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void DesInstalaTeclado()
{
  setvect(IRQ9,IRQ9Anterior);
}
