/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
�            T A N Q U E S   1.0-BETA   1.996   BY  FEGOR                �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
�                                                                        �
� CABECERA > VIDEO.H                                                     �
� AUTOR    > Fernando Gonz爈ez Ruano (FEGOR)                             �
� VERSION  > 1.0/beta                                                    �
� LENGUAJE > Borland C/C++ versi 3.1                                   �
�                                                                        �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
�                   CLUB VIRTUAL ZONE    -1.996-                         �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/


#if !defined(VIDEO_H)
#define VIDEO_H

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� defines                                                                �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
#define RETRAZO 	0x3DA
#define VIDEO   	0xA000
#define INT_TICK 	0x8

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� fuentes                                                                �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
#define FONT_8x14   0x02
#define FONT_8x8    0x03
#define FONT_8x16   0x06
#define FONT_9x16   0x07

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� sprites                                                                �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
#define MAXSPRT	31

#define PRES1     0
#define PRES2     1
#define PRES3     2
#define BALAN     3
#define BALAE     4
#define BALAS     5
#define BALAO     6
#define T1N1      7
#define T1E1      8
#define T1S1      9
#define T1O1     10
#define T1N2     11
#define T1E2     12
#define T1S2     13
#define T1O2     14
#define T2N1     15
#define T2E1	 16
#define T2S1     17
#define T2O1     18
#define T2N2     19
#define T2E2     20
#define T2S2     21
#define T2O2     22
#define CRUZROJA 23
#define MUNICION 24
#define FUEL     25
#define DESTROZO 26
#define LADRILLO 27
#define BASEVERDE 28
#define BASEAZUL  29
#define FOTO      30

/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
� tipos de datos nuevos                                                  �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
*/
typedef  struct {
		  unsigned char rojo;
		  unsigned char verde;
		  unsigned char azul;
		} Color_RGB;

typedef Color_RGB TipoPaleta[256];

typedef unsigned char far* TipoSprite;

typedef struct{
		unsigned int y1,x1,y2,x2;
		unsigned int alto,ancho;
	} TipoCoordenadas;

#endif
