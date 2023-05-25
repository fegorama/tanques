/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±            T A N Q U E S   1.0-BETA   1.996   BY  FEGOR                ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                                                                        ±
± CABECERA > SONIDO.H                                                    ±
± AUTOR    > Fernando Gonz lez Ruano (FEGOR)                             ±
± VERSION  > 1.0/beta                                                    ±
± LENGUAJE > Borland C/C++ versi¢n 3.1                                   ±
±                                                                        ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                   CLUB VIRTUAL ZONE    -1.996-                         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

#if !defined(SONIDO_H)
#define SONIDO_H

#define IRQ0     0x1C

#define DO    261.63
#define RE    293.66
#define MI    329.63
#define FA    349.23
#define SOL   415.30
#define LA    440.00
#define SI    490.88

#define MAXNOTAS 25

  typedef struct{
		  long frecuencia;
		  int  tiempo;
		} NOTAS;

  typedef NOTAS TipoNotas[MAXNOTAS];

#endif
