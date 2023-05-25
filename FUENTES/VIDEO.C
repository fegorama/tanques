/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±            T A N Q U E S   1.0        1.996   BY  FEGOR                ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                                                                        ±
± MODULO   > VIDEO.C                                                     ±
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
#include<dos.h>
#include<io.h>
#include<sys\stat.h>
#include<fcntl.h>
#include<alloc.h>
#include<mem.h>
#include<string.h>

#include"video.h"

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± valores de y para sumar en lugar de multiplicar                        ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
unsigned tabla_y[200] = {0,320,640,960,1280,1600,1920,2240,2560,2880,3200,3520,
	      3840,4160,4480,4800,5120,5440,5760,6080,6400,6720,7040,
	      7360,7680,8000,8320,8640,8960,9280,9600,9920,10240,10560,
	      10880,11200,11520,11840,12160,12480,12800,13120,13440,
	      13760,14080,14400,14720,15040,15360,15680,16000,16320,
	      16640,16960,17280,17600,17920,18240,18560,18880,19200,
	      19520,19840,20160,20480,20800,21120,21440,21760,22080,22400,
	      22720,23040,23360,23680,24000,24320,24640,24960,25280,25600,
	      25920,26240,26560,26880,27200,27520,27840,28160,28480,28800,
	      29120,29440,29760,30080,30400,30720,31040,31360,31680,32000,
	      32320,32640,32960,33280,33600,33920,34240,34560,34880,35200,
	      35520,35840,36160,36480,36800,37120,37440,37760,38080,38400,
	      38720,39040,39360,39680,40000,40320,40640,40960,41280,41600,
	      41920,42240,42560,42880,43200,43520,43840,44160,44480,44800,
	      45120,45440,45760,46080,46400,46720,47040,47360,47680,48000,
	      48320,48640,48960,49280,49600,49920,50240,50560,50880,51200,
	      51520,51840,52160,52480,52800,53120,53440,53760,54080,54400,
	      54720,55040,55360,55680,56000,56320,56640,56960,57280,57600,
	      57920,58240,58560,58880,59200,59520,59840,60160,60480,60800,
	      61120,61440,61760,62080,62400,62720,63040,63360,63680};

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± variables externas                                                     ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
extern int EFECTOS;
extern TipoSprite sprite[MAXSPRT];

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± variables p£blicas o generales                                         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
char far* pantalla  = MK_FP(VIDEO,0);		// puntero a pantalla
char far* pantvirt  = NULL;			// pantalla virtual
char far* pantfondo = NULL;			// pantalla (fondo)
char far* ptr_tabla = NULL;			// puntero a tabla
unsigned char alt_font = 16;			// altura de fuente
unsigned char anc_font =  8;			// anchura de fuente
unsigned char fondo_font = 0;			// borrar o no fondo
TipoPaleta pal;					// paleta de color
TipoPaleta palaux;				// paleta auxiliar

void interrupt (*Int8Anterior)(void);		// ptr a funcion (video)
int  Refresco = 0;				// refrescos de v¡deo

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± cambio a modo 13h, 320x200x256 colores                                 ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void video13h()
{
asm{
	mov	ah,0;
	mov 	al,0x13;
	int 	0x10;
}
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± cambio a modo 03h, texto de 80x25x16 colores                           ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void video03h()
{
asm{
	mov 	ah,0;
	mov 	al,0x3;
	int 	0x10;
}
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± retrazo vertical del monitor                                           ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void esperaretrazo()
{
asm	mov	dx,RETRAZO	// dx <- 3DA
retrz1:
asm{
	in	al,dx	 	// mira el puerto 3DA
	and	al,9 		// deja solo el bit 9
	jnz	retrz1          // !=0 -> sigue en el lazo...
}
retrz2:
asm{
	in	al,dx	        // mira el puerto 3DA
	and	al,8            // deja solo el bit 8
	jz	retrz2          // ==0 -> sigue en el lazo...
}
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± espera un n£mero determinado de retrazos (sirve como retardador)       ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void esperaretrazos(int n)
{
  int c;
  for(c=0;c<n;c++)
    esperaretrazo();
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± visualiza un punto de color en la pantalla virtual                     ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void Punto(int y, int x, unsigned char color)
{
asm{
	mov es,WORD PTR pantvirt+2      // ES = desplz. de pantvirt
	mov bx,y			// bx = y
	shl bx,1                        // bx * 2  (son enteros 2 bytes)
	mov di,tabla_y[bx]		// di = y * 320
	add di,WORD PTR pantvirt	// di + offset de pantvirt
	add di,x			// di + x  (y*320+x)
	mov al,color			// al = color
	mov es:[di],al			// pantvirt:y*320+x = color
}
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± lee el color de un punto en la pantalla                                ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
unsigned char CogePunto(int y, int x)
{
asm{
	mov es,WORD PTR pantvirt+2      // es = desplz. pantvirt
	mov bx,y			// bx = y
	shl bx,1			// bx * 2
	mov di,tabla_y[bx]		// di = tabla_y(y)
	add di,WORD PTR pantvirt	// di + offset de pantvirt
	add di,x			// di + x
	mov al,es:[di]			// al = [desp.pantvirt:320*y+x]
}
  return _AL;
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± pasa la pantalla virtual a la f¡sica                                   ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void RefrescaPantalla()
{
asm{
	push ds				// salvamos DS
	lds si,pantvirt                 // DS:SI = pantvirt
	mov ax,VIDEO                    // AX = VIDEO
	xor di,di                       // DI = 0
	mov es,ax                       // ES = VIDEO
	mov bx,64000                    // BX = 64000 bytes de pantalla
}
LAZO:
asm{
	mov  ecx,ds:[si+bx]             // CX = [pantvirt]+BX
	mov  es:[di+bx],ecx             // [VIDEO] = CX
	sub  bx,4                       // BX = BX - 2 (bytes)
	jnz  LAZO                       // si no cero, arriba...
	pop  ds                         // recuperamos DS
}
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± funci¢n de interrupci¢n para refrescar la pantalla                     ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void interrupt Tick(void)
{
  disable();
  if(Refresco)
    RefrescaPantalla();
  enable();
  Int8Anterior();
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± visualizar un sprite en pantalla virtual                               ±
±                                                                        ±
± NOTA: Esta funci¢n no ha sido optimizada y es una adaptaci¢n de la     ±
±       funci¢n utilizada por el CPV (Curso de Programaci¢n de Videojue- ±
±       gos).                                                            ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void VisualizaSprite(int y, int x, TipoSprite spr)
{
asm{
	push ds
	push es
	les  di, pantvirt 	// es:di = pantalla virtual
	lds  si, spr           	// ds:si = sprite
	mov  ax,320             // anchura de la pantalla
	mul  y                  // ax = y*320
	add  ax,x 		// ax = ax + x
	add  di,ax              // di = ax
	xor  dx,dx              // dx = 0
	xor  bx,bx              // bx = 0
	cld                     // incrementa desplazamientos
	lodsw                   // primer word
	mov  dl,al              // dl = anchura del sprite
	mov  bl,ah              // bl = altura del sprite
	mov  cx,bx              // cx = altura (contador)
}
lazo1:
asm{
	mov  bx,cx              // bx = contador (cx)
	mov  cx,dx              // cx = anchura  (contador)
}
lazo2:
asm{
	lodsb                   // recupera un byte del sprite
	or  al,al               // ¨es cero?...
	jz  incdi               // ...si, transparente
	stosb                   // ...no, lo visualizamos
	jmp seguir
}
incdi:
asm{
	inc  di
}
seguir:
asm{
	loop lazo2              // anchura
	sub  di,dx              // l¡nea siguiente
	add  di,320
	mov  cx,bx              // recuperamos contador de altura
	loop lazo1              // altura
	pop  es
	pop  ds
}
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± mueve un bloque de memoria (pantalla) origen a la destino              ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void MueveBloque(int y1,int x1,int y2,int x2,char far* dest,char far* orig)
{
asm{
	push	ds
	push 	es

	// esquina superior izquierda (320*y1+x1)

	mov  	ax,320		// ax = 320 (anchura)
	mul  	y1    		// ax = ax * y1
	add  	ax,x1		// ax = ax + x1

	// altura y anchura

	mov  	dx,x2           // dx = x2
	sub  	dx,x1           // dx = x2 - x1 (anchura)
	mov  	bx,y2           // bx = y2
	sub  	bx,y1           // bx = y2 - y1 (altura)
	lds  	si,orig         // di = origen
	les  	di,dest         // si = destino
	add  	si,ax           // si = orig + (320*y1+x1)
	add  	di,ax           // di = dest + (320*y1+x1)
	mov  	ax,320          // ax = 320
	sub  	ax,dx           // ax = 320 - anchura del bloque
	mov  	cx,bx           // cx = bx (altura)
}
lazo1:
asm{
	mov  	bx,cx           // bx = contador
	mov  	cx,dx           // cx = anchura
	rep  	movsb           // mueve fila
	add  	di,ax           // siguiente l¡nea
	add  	si,ax           //     "       "
	mov  	cx,bx           // cx = contador
	loop 	lazo1           // seguimos ...
	pop  	es
	pop  	ds
}
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± cambia la paleta de colores                                            ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void CambiaPaleta(TipoPaleta paleta)
{
  int c;

  // control de retrazo

asm	mov	dx,RETRAZO	// dx = 3DA
retrz1:
asm{
	in	al,dx	 	// mira el puerto 3DA
	and	al,9 		// deja solo el bit 9
	jnz	retrz1          // !=0 = sigue en el lazo...
}
retrz2:
asm{
	in	al,dx	        // mira el puerto 3DA
	and	al,8            // deja solo el bit 8
	jz	retrz2          // si 0 sigue en el lazo...
}
	// cambio de paleta (­ojo!, este algoritmo solo sirve para 386)
asm{
	push  ds		// ds al caj¢n... :-)
	lds   si,paleta		// si = paleta
	mov   cx,768		// contador, cx = 256x3 (RGB)
	mov   dx,0x3C8		// dx = 3C8 hex.
	xor   al,al		// al = 0 (color inicial a cambiar)
	out   dx,al             // cambia la paleta
	inc   dx		// incrementa dx, dx = 3C9 hex.
	rep   outsb             // rellena la paleta
	pop   ds		// recupera ds...
}
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± lee del disco un fichero .CEL directamente                             ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void CargaSprite(const char nombre[],int cpal,int numsprt)
{
  TipoSprite sprt;			// punt. a sprite
  TipoPaleta paleta;			// paleta
  int nfich;				// "handle" de fichero
  char cab[32];				// cabecera del .CEL
  int anchura,altura;			// anchura y altura del sprite

  // abrimos el fichero .CEL

  if((nfich = open(nombre,O_BINARY|O_RDONLY))==-1)
  {
    perror("\n\n\bERROR: abriendo fichero .CEL\n");
    exit(1);
  }

  read(nfich,cab,32);                   // lectura de cabecera
  read(nfich,paleta,768);		// lectura de paleta de color
  anchura = (unsigned char) cab[2];	// anchura
  altura = (unsigned char) cab[4];	// altura

  // asignaci¢n de memoria para el sprite

  if((sprt = (TipoSprite)malloc(anchura*altura+2))==NULL)
  {
    perror("\n\n\bERROR: asignando memoria a sprites");
    exit(1);
  }

  // rellenamos la memoria asignada al sprite...

  sprt[0] = (unsigned char) anchura; // cab[2];
  sprt[1] = (unsigned char) altura;  // cab[4];
  read(nfich,sprt+2,(anchura*altura));
  close(nfich);

  // si hay cambio de paleta, se cambia :-)

  if(cpal)				// ¨cambio paleta?
  {
    memcpy(pal,paleta,768);
    CambiaPaleta(pal);
  }

  sprite[numsprt] = sprt;		// asignamos sprite a los dem s
  free(sprt);				// liberamos memoria asignada
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± carga en memoria un fichero de sprites (.SPR)                          ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void CargaSprites(const char nombre[])
{
  int nfich;				// fichero
  unsigned char tam[2]="";		// tama¤o
  int anchura,altura;			// anchura, altura
  int n;				// n£mero de sprite
  long m;				// memoria ocupada

  // abrir el fichero

  if((nfich = open(nombre,O_BINARY|O_RDONLY))==-1)
  {
    perror("\n\n\bERROR: fichero de sprites no encontrado");
    exit(1);
  }

  lseek(nfich,0,SEEK_SET);		// al principio

  printf("\n+ Leyendo <%s>...\n",nombre);

  n = 0;
  m = 0;

  while(!eof(nfich))
  {
    // tama¤o del sprite

    read(nfich,tam,2);		// tama¤o del sprite
    anchura = tam[0];		// anchura
    altura  = tam[1];		// altura

    // asignaci¢n de memoria...

    if((sprite[n] = (TipoSprite)malloc(anchura*altura+2))==NULL)
    {
	perror("\n\n\bERROR: asignando memoria a sprites");
	exit(1);
    }

    sprite[n][0] = tam[0];
    sprite[n][1] = tam[1];

    // lectura del sprite

    read(nfich,sprite[n]+2,(anchura*altura)*sizeof(char));

    n++;			// otro sprite m s...
    m+=anchura*altura+2;	// memoria...
  }

  close(nfich);			// cerramos el fichero
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± lee la paleta de color de un fichero .PAL                              ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void LeePaleta(const char nombre[])
{
  TipoPaleta paleta;			// paleta
  int nfich;				// fichero

  // abrimos el fichero...

  if((nfich = open(nombre,O_BINARY|O_RDONLY))==-1)
  {
    perror("\n\n\bERROR: fichero de paleta de color no encontrado");
    exit(1);
  }

  lseek(nfich,0,SEEK_SET);			// al principio
  printf("+ Leyendo <%s>...\n",nombre);
  read(nfich,paleta,768);			// lectura de la paleta
  close(nfich);					// cierre del fichero

  // asignaci¢n de paleta de color a paleta general y auxiliar

  memcpy(pal,paleta,768);
  memcpy(palaux,paleta,768);
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± fundido (fade out)                                                     ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void FundidoFuera(TipoPaleta pal,int pasos)
{
  int        c,i;			// contadores
  TipoPaleta auxpal;			// paleta auxiliar

  for(c=1;c<pasos;c++)
  {
    for(i=0;i<255;i++)
    {
      auxpal[i].rojo  = ((pal[i].rojo)  * c) / pasos;
      auxpal[i].verde = ((pal[i].verde) * c) / pasos;
      auxpal[i].azul  = ((pal[i].azul)  * c) / pasos;
    }
    CambiaPaleta(auxpal);
  }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± fundido (fade in)                                                      ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void FundidoDentro(TipoPaleta pal,int pasos)
{
  int        c,i;			// contadores
  TipoPaleta auxpal;			// paleta auxiliar

  for(c=pasos;c>1;c--)
  {
    for(i=0;i<255;i++)
    {
      auxpal[i].rojo  = ((pal[i].rojo)  * c) / pasos;
      auxpal[i].verde = ((pal[i].verde) * c) / pasos;
      auxpal[i].azul  = ((pal[i].azul)  * c) / pasos;
    }
    CambiaPaleta(auxpal);
  }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± devuelve los valores de la paleta actual                               ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void RecogePaleta(TipoPaleta paleta)
{
  int i;				// contador

  outportb(0x3C8,0);     		// primer color a cambiar
  for(i=0;i<255;i++)			// de 0 a 255 (256 colores)
  {
    paleta[i].rojo  = inportb(0x3C9);
    paleta[i].verde = inportb(0x3C9);
    paleta[i].azul  = inportb(0x3C9);
  }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± parpadeo de paleta (hace parpadear en blanco y negro 25 veces)         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void parpadeopal()
{
  TipoPaleta paux;
  TipoPaleta p1;
  TipoPaleta p2;
  unsigned char c;

  if(EFECTOS)				// si activados los efectos...
  {
    memcpy(paux,pal,768);
    memset(p1,0,768);
    memset(p2,63,768);
    for(c=1;c<25;c++)
      CambiaPaleta((c%2?p1:p2));
    memcpy(pal,paux,768);
  }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± scroll de paleta                                                       ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void scrollpal(colini,colfin)
{
  int k,c,c1,c2,c3;

  if(EFECTOS)				// si activados los efectos...
  {
    c1 = pal[colfin].rojo;
    c2 = pal[colfin].verde;
    c3 = pal[colfin].azul;

    for(c=colfin;c>=colini;c--)
    {
      pal[c+1].rojo  = pal[c].rojo;
      pal[c+1].verde = pal[c].verde;
      pal[c+1].azul  = pal[c].azul;
    }

    pal[colini].rojo  = c1;
    pal[colini].verde = c2;
    pal[colini].azul  = c3;

    CambiaPaleta(pal);
  }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± realiza un filtrado de medias                                          ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void filtromedia()
{
asm{
	mov  es,WORD PTR pantvirt+2     // es = seg. de pantvirt
	xor  ax, ax                     // ax = 0
	xor  dx, dx                     // dx = 0
	mov  bx, 2               	// y
}
L2:
asm{
	mov  cx, 1               	// x
}
L1:
asm{
	// coge punto  (y-1)

	mov di,tabla_y[bx-2]
	add di,WORD PTR pantvirt
	add di,cx
	mov dl,es:[di]

	mov ax,dx

	// coge punto (y+1)

	mov di,tabla_y[bx+2]
	add di,WORD PTR pantvirt
	add di,cx
	mov dl,es:[di]

	add ax,dx

	// coge punto (x+1)

	mov di,tabla_y[bx]
	add di,WORD PTR pantvirt
	add di,cx
	mov dl,es:[di+1]
	add ax,dx

	// coge punto (x-1)

	mov di,tabla_y[bx]
	add di,WORD PTR pantvirt
	add di,cx
	mov dl,es:[di-1]

	// (y+1)+(y-1) / 2

	add ax,dx
	shr ax,2

	// ponemos el punto

	mov di,tabla_y[bx]
	add di,WORD PTR pantvirt
	add di,cx
	mov es:[di],al

	// incrementamos valores de bucles y seguimos

	inc cx
	cmp cx,318  			// si x != 318...
	jnz short L1                    // sigue (a L1)
	inc bx
	inc bx
	cmp bx,398                      // si y != 199...
	jnz short L2                    // sigue (a L2)
}
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± efecto difusi¢n (lo mismo que el de medias pero solo con y+1 e y-1)    ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void difumina()
{
asm{
	mov  es,WORD PTR pantvirt+2
	xor  ax, ax
	xor  dx, dx
	mov  bx, 2               	// y
}
L2:
asm{
	mov  cx, 0               	// x
}
L1:
asm{
	// coge punto  (y-1)

	mov di,tabla_y[bx-2]
	add di,WORD PTR pantvirt
	add di,cx
	mov dl,es:[di]

	mov ax,dx

	// coge punto (y+1)

	mov di,tabla_y[bx+2]
	add di,WORD PTR pantvirt
	add di,cx
	mov dl,es:[di]

	// (y+1)+(y-1) / 2

	add ax,dx
	shr ax,1

	// ponemos el punto

	mov di,tabla_y[bx]
	add di,WORD PTR pantvirt
	add di,cx
	mov es:[di],al

	inc cx
	cmp cx,319
	jnz short L1
	inc bx
	inc bx
	cmp bx,396
	jnz short L2
}
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± efecto difusi¢n2 (lo mismo que el de medias pero solo con x+1 e x-1)   ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void difumina2()
{
asm{
	mov  es,WORD PTR pantvirt+2
	xor  ax, ax
	xor  dx, dx
	mov  bx, 0               	// y
}
L2:
asm{
	mov  cx, 1               	// x
}
L1:
asm{
	// coge punto (x-1)

	mov di,tabla_y[bx]
	add di,WORD PTR pantvirt
	add di,cx
	mov dl,es:[di-1]
	mov ax,dx

	// coge punto (x+1)

	mov di,tabla_y[bx]
	add di,WORD PTR pantvirt
	add di,cx
	mov dl,es:[di+1]

	// (x+1)+(x-1) / 2

	add ax,dx
	shr ax,1

	// ponemos punto...

	mov di,tabla_y[bx]
	add di,WORD PTR pantvirt
	add di,cx
	mov es:[di],al

	// control de bucles...

	inc cx
	cmp cx,318
	jnz short L1
	inc bx
	inc bx
	cmp bx,398
	jnz short L2
}
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± prepara las pantallas, virtual, fondo y real                           ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void InicializaPantallas()
{
  video13h();

  // fondo

  if((pantfondo = malloc(64000))==NULL)
  {
    perror("ERROR: no encuentro memoria.");
    exit(1);
  }

  memset(pantfondo,0,64000);

  // virtual

  if((pantvirt = malloc(64000))==NULL)
  {
    perror("ERROR: no encuentro memoria.");
    exit(1);
  }

  memcpy(pantvirt,pantfondo,64000);

  // real

  RefrescaPantalla();
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± libera la memoria ocupada por las pantallas                            ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void LiberaPantallas()
{
  free(pantvirt);
  free(pantfondo);
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± libera la memoria ocupada por los sprites                              ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void LiberaSprites()
{
  int i;

  for(i=MAXSPRT-1;i>=0;i--)
    free(sprite[i]);
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± limpia las pantalla (en negro)                                         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void LimpiaPantallas()
{
  memset(pantvirt,0,64000);
  memset(pantfondo,0,64000);
  RefrescaPantalla();
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± mueve un trozo de fondo a pantalla virtual                             ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void FondoVirtual(y1,x1,y2,x2)
{
  MueveBloque(y1,x1,y2,x2,pantvirt,pantfondo);
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± mueve un trozo de pantalla virtual a fondo                             ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void VirtualFondo(y1,x1,y2,x2)
{
  MueveBloque(y1,x1,y2,x2,pantfondo,pantvirt);
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± lee el fondo de la pantalla                                            ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void CargaFondo(const char fondo[])
{
  int nfich;

  nfich = open(fondo,O_BINARY|O_RDONLY);
  lseek(nfich,32,SEEK_SET);
  read(nfich,pal,768);
  CambiaPaleta(pal);
  read(nfich,pantfondo,64000);
  close(nfich);
  memcpy(pantvirt,pantfondo,64000);
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± comprueba una intersecci¢n (colisi¢n) entre coordenadas                ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
char Interseccion(TipoCoordenadas r1, TipoCoordenadas r2)
{
  int AnchoMayor, AltoMayor;

  // mayor altura y anchura

  AnchoMayor = r2.x1>r1.x1?r1.ancho:r2.ancho;
  AltoMayor  = r2.y1>r1.y1?r1.alto:r2.alto;

  // ¨colisi¢n?

  return (abs(r1.x1-r2.x1)<AnchoMayor) && (abs(r1.y1-r2.y1)<AltoMayor);
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± comprueba si en el recuadro de coordenadas se "pisa" el color          ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
int EsColor(TipoCoordenadas r, unsigned char color)
{
  unsigned char c[8];

  // los 8 puntos del contorno del recuadro de las coordenadas...

  c[0] = CogePunto(r.y1,r.x1);
  c[1] = CogePunto(r.y1,r.x1+(r.ancho>>1));
  c[2] = CogePunto(r.y1,r.x1+r.ancho);
  c[3] = CogePunto(r.y1+(r.alto-1>>1),r.x1+r.ancho);
  c[4] = CogePunto(r.y1+r.alto-1,r.x1+r.ancho);
  c[5] = CogePunto(r.y1+r.alto-1,r.x1+(r.ancho>>1));
  c[6] = CogePunto(r.y1+r.alto-1,r.x1);
  c[7] = CogePunto(r.y1+(r.alto-1>>1),r.x1);

  // si se "pisa"...

  if(c[0] == color || c[1] == color || c[2] == color || c[3] == color ||
     c[4] == color || c[5] == color || c[6] == color || c[7] == color)
    return 1;
  else			// no hay color "pisado"...
    return 0;
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± efecto de caida de pantalla                                            ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void EfectoCaida()
{
asm	mov  bl,199;		// bl = filas
lazo:
asm{
	push ds

	// ds:si = pantvirt+(320*fila)

	xor  ah,ah
	mov  al,bl
	mov  dx,320
	mul  dx
	lds  si,pantvirt
	add  si,ax

	// es:di = VIDEO

	mov  ax,VIDEO
	mov  es,ax
	xor  di,di

	// cx = 320*(200-fila)

	xor  ah,ah
	mov  al,200
	sub  al,bl
	mov  dx,160
	mul  dx
	mov  cx,ax

	cld
	rep  movsw

	pop  ds

	dec  bl
	cmp  bl,0
	jne  lazo               // si fila <> 0... ve a <lazo>
}
  RefrescaPantalla();
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± devuelve el puntero del juego de caracteres de la VGA                  ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
char far* ptrVGA(unsigned char mfuente)
{
asm{
	mov  ax,0x1130
	mov  bh,mfuente
	int  0x10
}
  return MK_FP(_ES,_BP);
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± inicializa las fuentes VGA                                             ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void inifontVGA(unsigned char mfuente)
{
  ptr_tabla = ptrVGA(mfuente);

  switch(mfuente)
  {
    case FONT_8x14: alt_font = 14;
		    anc_font =  8;
		    break;
    case FONT_8x8:  alt_font =  8;
		    anc_font =  8;
		    break;
    case FONT_8x16: alt_font = 16;
		    anc_font =  8;
		    break;
    case FONT_9x16: alt_font = 16;
		    anc_font =  9;
		    break;
  }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± borra fondo de fuentes al visualizarlas                                ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void borrafondofont(unsigned char i)
{
  fondo_font = i?1:0;
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± visualiza una cadena de caracteres en VGA                              ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void printstringVGA(int y, int x, char cad[], unsigned char col)
{
  int c,altura,anchura;			// contador, ancho y alto
  unsigned char mascara;		// m scara de bits
  unsigned char colaux;			// color auxiliar

  colaux = col;

  // si no hay puntero definido, se coge...

  if(ptr_tabla==NULL)
  {
    ptr_tabla = ptrVGA(FONT_8x16);
    alt_font = 16;
    anc_font =  8;
  }

  // control de impresi¢n de cada caracter de la cadena

  for(c=0;c<strlen(cad);c++)
  {
    for(altura=1;altura<alt_font;altura++)
    {
      mascara=*(ptr_tabla+(cad[c]*alt_font+altura-1));
      for(anchura=1;anchura<8;anchura++)
      {
	if((mascara & 128) != 0)
	  Punto(y+altura,x+anchura,colaux);
	else
	  if(fondo_font)
	    Punto(y+altura,x+anchura,0);
	mascara = (mascara<<1);
      }
      colaux++;
    }
    x+=8;
    colaux = col;
  }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± EFECTOS GENERALES UTILIZANDO LAS FUNCIONES ANTERIORES                  ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± efecto difusi¢n                                                        ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void EfectoDifusion()
{
  unsigned char i;

  if(EFECTOS)
  {
    for(i=0;i<100;i++)
    {
      esperaretrazo();
      difumina();
      RefrescaPantalla();
    }
  }
  else
  {
    FundidoDentro(pal,50);
    memset(pantvirt,0,64000);
    RefrescaPantalla();
    CambiaPaleta(pal);
  }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± efecto difusi¢n2                                                       ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void EfectoDifusion2()
{
  unsigned char i;

  if(EFECTOS)
  {
    for(i=0;i<100;i++)
    {
      esperaretrazo();
      difumina2();
      RefrescaPantalla();
    }
  }
  else
  {
    FundidoDentro(pal,50);
    memset(pantvirt,0,64000);
    RefrescaPantalla();
    CambiaPaleta(pal);
  }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± efecto humo                                                            ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void EfectoHumo()
{
  unsigned char i;

  if(EFECTOS)
  {
    for(i=0;i<100;i++)
    {
      esperaretrazo();
      filtromedia();
      RefrescaPantalla();
    }
  }
  else
  {
    FundidoDentro(pal,50);
    memset(pantvirt,0,64000);
    RefrescaPantalla();
    CambiaPaleta(pal);
  }
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± efecto de fade-out + fade-in                                           ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void EfectoFundidos(int espera)
{
  // paleta auxiliar a negro

  memset(palaux,0,768);
  CambiaPaleta(palaux);
  RefrescaPantalla();

  // funde hacia fuera y espera

  FundidoFuera(pal,100);
  esperaretrazos(espera);

  // funde hacia dentro... y restaura la paleta original

  FundidoDentro(pal,50);
  memset(pantvirt,0,64000);
  RefrescaPantalla();
  CambiaPaleta(pal);
}

/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
± restaura paleta de color desde la variable pal                         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/
void InicializaPaleta()
{
  CambiaPaleta(pal);
}
