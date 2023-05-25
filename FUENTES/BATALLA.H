/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±            T A N Q U E S   1.0-BETA   1.996   BY  FEGOR                ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                                                                        ±
± CABECERA > BATALLA.H                                                   ±
± AUTOR    > Fernando Gonz lez Ruano (FEGOR)                             ±
± VERSION  > 1.0/beta                                                    ±
± LENGUAJE > Borland C/C++ versi¢n 3.1                                   ±
±                                                                        ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                   CLUB VIRTUAL ZONE    -1.996-                         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± defines                                                                ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
#define DIR_NORTE  1
#define DIR_ESTE   2
#define DIR_SUR    3
#define DIR_OESTE  4

#define ALCANCE_BALA 20

#define ANCHO_TAN  18
#define ALTO_TAN   18
#define ANCHO_BAL   8
#define ALTO_BAL    8
#define ANCHO_CR   16
#define ALTO_CR    16
#define ANCHO_MUN  16
#define ALTO_MUN   16
#define ANCHO_FUEL 16
#define ALTO_FUEL  16
#define ANCHO_DEST 16
#define ALTO_DEST  16
#define ALTO_BASE  32
#define ANCHO_BASE 32

#define LIMITE_ARRIBA    16
#define LIMITE_DERECHA   303 - ANCHO_TAN
#define LIMITE_ABAJO     160 - ALTO_TAN
#define LIMITE_IZQUIERDA 16

#define MAX_MUROS   2
#define MAX_VIDAS   5
#define MAX_BASE   15
#define MAX_BALAS  10
#define MAX_TANQUES 3
#define MAX_FUEL  999

#define ABORTADO   1
#define GANA_VERDE 2
#define GANA_AZUL  3
#define EMPATE     4
#define BASE_VERDE 5
#define BASE_AZUL  6
