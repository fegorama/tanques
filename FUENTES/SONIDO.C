/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±            T A N Q U E S   1.0        1.996   BY  FEGOR                ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                                                                        ±
± MODULO   > SERIE.C                                                     ±
± AUTOR    > Fernando Gonz lez Ruano (FEGOR)                             ±
± VERSION  > 1.0                                                         ±
± LENGUAJE > Borland C/C++ versi¢n 3.1                                   ±
±                                                                        ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                                                                        ±
± Funciones de sonido (actualmente solo por el speaker)                  ±
±                                                                        ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                   CLUB VIRTUAL ZONE    -1.996-                         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

#include<dos.h>

#include"sonido.h"

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± variables externas                                                     ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
extern int SONIDO;

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± variables p£blicas o globales                                          ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
TipoNotas musicaactual;			// m£sica que est  sonando
TipoNotas musicapres;			//   "    de presentaci¢n
TipoNotas musicamenu;			//   "    del men£
TipoNotas musicamenu2;			//   "    del men£ 2
TipoNotas musicadisparo;		//   "    de disparo
TipoNotas musicatocado;			//   "    de tocado
TipoNotas musicabonus;			//   "    recargas, curas, etc.
char sonando;				// si est  sonando
char notaactual;			// nota que est  sonando en el momento
void interrupt (*IRQ0Anterior)(void);	// interrupci¢n IRQ 0

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± control de sonidos mediante interrupciones                             ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void interrupt ControlaSonidos()
{
  disable();				// desactiva interrupciones

  if(sonando)				// si est  sonando
  {
    musicaactual[notaactual].tiempo --;
    if(musicaactual[notaactual].tiempo == 0)
    {
      notaactual++;
      if((notaactual==MAXNOTAS) || (musicaactual[notaactual].tiempo==0))
      {
	sonando = 0;
	notaactual=0;
	nosound();
      }
      else
	sound(musicaactual[notaactual].frecuencia);
    }
  }
  else
    if(musicaactual[notaactual].tiempo!=0)
    {
      sonando=1;
      sound(musicaactual[notaactual].frecuencia);	// sonannnndoo..
    }

  enable();                        	// activamos interrupciones
  IRQ0Anterior();			// llamada a la IRQ 0 anterior
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± instala la rutina de interrupci¢n que controla los sonidos             ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void InstalaSonidos()
{
  int c;			// un contador

  if(SONIDO)			// solo si est  activo...
  {
    for(c=0;c<MAXNOTAS;c++)	// pone todo a cero
      musicaactual[c].tiempo=0;
    sonando = 0;
    notaactual = 0;

    IRQ0Anterior = getvect(IRQ0);	// recoge vector original
    setvect(IRQ0,ControlaSonidos);	// nueva funci¢n
  }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± restaura la IRQ 0 antigua                                              ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void DesInstalaSonidos()
{
  if(SONIDO)			// solo si est  activo...
  {
    nosound();
    setvect(IRQ0,IRQ0Anterior);
  }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± cambio de sonidao                                                      ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void ActualizaSonidos(TipoNotas musica)
{
  if(SONIDO)				// solo si est  activo...
  {
    asm{ CLI };
    memcpy(musicaactual,musica,sizeof(musicaactual));
    notaactual = 0;
    sonando = 0;
    asm{ STI };
  }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± carga los sonidos, melod¡as, canciones, etc.                           ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void CargaSonidos()
{
  int c;				// como siempre, un contador ;-)

  // musica de presentaci¢n

  musicapres[0].tiempo = 5;
  musicapres[0].frecuencia = MI;
  musicapres[1].tiempo = 5;
  musicapres[1].frecuencia = FA;
  musicapres[2].tiempo = 5;
  musicapres[2].frecuencia = SOL;
  musicapres[3].tiempo = 5;
  musicapres[3].frecuencia = MI;
  musicapres[4].tiempo = 5;
  musicapres[4].frecuencia = MI;
  musicapres[5].tiempo = 5;
  musicapres[5].frecuencia = RE;
  musicapres[6].tiempo = 5;
  musicapres[6].frecuencia = MI;
  musicapres[7].tiempo = 9;
  musicapres[7].frecuencia = RE;
  musicapres[8].tiempo = 5;
  musicapres[8].frecuencia = MI;
  musicapres[9].tiempo = 9;
  musicapres[9].frecuencia = FA;
  musicapres[10].tiempo = 5;
  musicapres[10].frecuencia = SOL;
  musicapres[11].tiempo = 5;
  musicapres[11].frecuencia = SOL;
  musicapres[12].tiempo = 5;
  musicapres[12].frecuencia = LA;
  musicapres[13].tiempo = 9;
  musicapres[13].frecuencia = SOL;
  musicapres[14].tiempo = 5;
  musicapres[14].frecuencia = LA;
  musicapres[15].tiempo = 5;
  musicapres[15].frecuencia = SOL;
  musicapres[16].tiempo = 5;
  musicapres[16].frecuencia = LA;
  musicapres[17].tiempo = 5;
  musicapres[17].frecuencia = SI;
  musicapres[18].tiempo = 15;
  musicapres[18].frecuencia = SI;

  // musica del men£ ...

  musicamenu[0].tiempo = 5;
  musicamenu[0].frecuencia = DO;
  musicamenu[1].tiempo = 5;
  musicamenu[1].frecuencia = DO;
  musicamenu[2].tiempo = 5;
  musicamenu[2].frecuencia = DO;
  musicamenu[3].tiempo = 5;
  musicamenu[3].frecuencia = RE;
  musicamenu[4].tiempo = 5;
  musicamenu[4].frecuencia = MI;
  musicamenu[5].tiempo = 5;
  musicamenu[5].frecuencia = FA;
  musicamenu[6].tiempo = 5;
  musicamenu[6].frecuencia = SOL;
  musicamenu[7].tiempo = 9;
  musicamenu[7].frecuencia = LA;
  musicamenu[8].tiempo = 5;
  musicamenu[8].frecuencia = SOL;
  musicamenu[9].tiempo = 9;
  musicamenu[9].frecuencia = FA;
  musicamenu[10].tiempo = 5;
  musicamenu[10].frecuencia = MI;
  musicamenu[11].tiempo = 5;
  musicamenu[11].frecuencia = RE;
  musicamenu[12].tiempo = 5;
  musicamenu[12].frecuencia = DO;
  musicamenu[13].tiempo = 9;
  musicamenu[13].frecuencia = 1;
  musicamenu[14].tiempo = 5;
  musicamenu[14].frecuencia = MI;
  musicamenu[15].tiempo = 5;
  musicamenu[15].frecuencia = SOL;
  musicamenu[16].tiempo = 5;
  musicamenu[16].frecuencia = LA;
  musicamenu[17].tiempo = 5;
  musicamenu[17].frecuencia = SOL;
  musicamenu[18].tiempo = 5;
  musicamenu[18].frecuencia = FA;
  musicamenu[19].tiempo = 5;
  musicamenu[19].frecuencia = RE;
  musicamenu[20].tiempo = 15;
  musicamenu[20].frecuencia = DO;

  // musica del men£ 2...

  musicamenu2[0].tiempo = 2;
  musicamenu2[0].frecuencia = DO;
  musicamenu2[1].tiempo = 2;
  musicamenu2[1].frecuencia = RE;
  musicamenu2[2].tiempo = 2;
  musicamenu2[2].frecuencia = MI;
  musicamenu2[3].tiempo = 2;
  musicamenu2[3].frecuencia = FA;
  musicamenu2[4].tiempo = 2;
  musicamenu2[4].frecuencia = RE;
  musicamenu2[5].tiempo = 2;
  musicamenu2[5].frecuencia = MI;
  musicamenu2[6].tiempo = 2;
  musicamenu2[6].frecuencia = FA;
  musicamenu2[7].tiempo = 2;
  musicamenu2[7].frecuencia = SOL;
  musicamenu2[8].tiempo = 2;
  musicamenu2[8].frecuencia = MI;
  musicamenu2[9].tiempo = 2;
  musicamenu2[9].frecuencia = FA;
  musicamenu2[10].tiempo = 2;
  musicamenu2[10].frecuencia = SOL;
  musicamenu2[11].tiempo = 2;
  musicamenu2[11].frecuencia = LA;
  musicamenu2[12].tiempo = 2;
  musicamenu2[12].frecuencia = FA;
  musicamenu2[13].tiempo = 2;
  musicamenu2[13].frecuencia = SOL;
  musicamenu2[14].tiempo = 2;
  musicamenu2[14].frecuencia = LA;
  musicamenu2[15].tiempo = 10;
  musicamenu2[15].frecuencia = SI;
  musicamenu2[16].tiempo = 2;
  musicamenu2[16].frecuencia = LA;
  musicamenu2[17].tiempo = 2;
  musicamenu2[17].frecuencia = SOL;
  musicamenu2[18].tiempo = 2;
  musicamenu2[18].frecuencia = FA;
  musicamenu2[19].tiempo = 2;
  musicamenu2[19].frecuencia = MI;
  musicamenu2[20].tiempo = 2;
  musicamenu2[20].frecuencia = RE;

  // disparo

  for(c=0;c<5;c++)
  {
    musicadisparo[c].tiempo = 1;
    musicadisparo[c].frecuencia = 100+25*c;
  }

  // tocado

  musicatocado[0].tiempo = 1;
  musicatocado[0].frecuencia = 1000;
  musicatocado[1].tiempo = 2;
  musicatocado[1].frecuencia = 500;

  // bonificaciones, cargas, curas, ...

  for(c=0;c<5;c++)
  {
    musicabonus[c].tiempo = 1;
    musicabonus[c].frecuencia = 500+10*c;
    musicabonus[c+5].tiempo = 1;
    musicabonus[c+5].frecuencia = 500-10*c;
  }
}
