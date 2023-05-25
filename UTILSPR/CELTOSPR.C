/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                                                                        ±
± PROGRAMA > CELTOSPR.EXE                                                ±
± AUTOR    > Fernando Gonz lez Ruano (FEGOR)                             ±
± VERSION  > 1.0/beta                                                    ±
± LENGUAJE > Borland C/C++ versi¢n 3.1                                   ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                                                                        ±
±  Programa que pasa un fichero .CEL a otro .SPR                         ±
±                                                                        ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                   CLUB VIRTUAL ZONE    -1.996-                         ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
*/


#include<stdio.h>
#include<dos.h>
#include<io.h>
#include<fcntl.h>
#include<alloc.h>

void main(int narg,char** larg)
{
    int nfich,anchura,altura;
    long c;
    char* sprt;
    char cab[32];
    char fich[13];

    // leemos fichero .cel

    memset(fich,0,13);
    memcpy(fich,larg[1],8);
    memcpy(fich+(strlen(fich)),".cel\0",5);
    printf("\nLeyendo <%s> ...",fich);
    if((nfich = open(fich,O_BINARY|O_RDONLY))==-1)
    {
      printf("\nError en fichero: %s\n",fich);
      exit(1);
    }

    read(nfich,cab,32);
    anchura = (unsigned char) cab[2];
    altura = (unsigned char) cab[4];
    lseek(nfich,768,SEEK_CUR);

    sprt = malloc(anchura*altura+2);
    sprt[0] = (unsigned char)anchura;
    sprt[1] = (unsigned char)altura;
    read(nfich,sprt+2,anchura*altura);
    close(nfich);

    // escribimos fichero .spr

    memset(fich,0,13);
    memcpy(fich,larg[1],8);
    memcpy(fich+(strlen(fich)),".spr\0",5);
    printf("\nEscribiendo <%s> ...",fich);
    if((nfich = open(fich,O_BINARY|O_CREAT))==-1)
    {
      printf("\nError en fichero: %s\n",fich);
      exit(1);
    }
    write(nfich,sprt,anchura*altura+2);
    close(nfich);

    printf("\n\n");
    free(sprt);
}
