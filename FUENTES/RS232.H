/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±            T A N Q U E S   1.0-BETA   1.996   BY  FEGOR                ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                                                                        ±
± CABECERA > RS232.H                                                     ±
± AUTOR    > Fernando Gonz lez Ruano (FEGOR)                             ±
± VERSION  > 1.0/beta                                                    ±
± LENGUAJE > Borland C/C++ versi¢n 3.1                                   ±
±                                                                        ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                   CLUB VIRTUAL ZONE    -1.996-                         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

#if !defined(RS232_H)
#define RS232_H

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± registros                                                              ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
#define RBR  (serie.puerto_base + 0)  // registro de recepci¢n
#define THR  (serie.puerto_base + 0)  // registro de transmisi¢n
#define DLL  (serie.puerto_base + 0)  // Divisor de Velocidad, bajo
#define DLM  (serie.puerto_base + 1)  // Divisor de Velocidad, alto
#define IER  (serie.puerto_base + 1)  // Registro de activ. de interrupciones
#define IIR  (serie.puerto_base + 2)  // Registro identificaci¢n de interrup.
#define LCR  (serie.puerto_base + 3)  // registro de control de l¡nea
#define MCR  (serie.puerto_base + 4)  // registro de control del modem
#define LSR  (serie.puerto_base + 5)  // registro de estado de l¡nea
#define MSR  (serie.puerto_base + 6)  // registro de estado del modem

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± bits de estado del LCR                                                 ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
#define BRKCTRL  64           // "break control"
#define DLAB    128           // bit 7 del LCR => DLAB

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± bits de estado del LSR                                                 ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
#define  DR   1               // dato disponible
#define  OE   2               // overrun error
#define  PE   4               // parity error
#define  FE   8               // framing error
#define  BI   0x10            // break interrupt
#define  THRE 0x20            // THR vac¡o

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± bits de estado del MCR                                                 ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
#define DTR    1              // Data Terminal Ready
#define RTS    2              // Request To Send
#define OUT1   4
#define OUT2   8
#define LOOP  16              // Lazo (test)

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± tipo de datos para la configuraci¢n del puerto serie                   ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
typedef struct {
		 unsigned char puerto;
		 unsigned unsigned puerto_base;
		 unsigned long velocidad;
		 unsigned char inicio[128];
		 unsigned char marcado[128];
		 unsigned char recibir[128];
		 unsigned char colgar[128];
		} TipoSerie;

#endif
