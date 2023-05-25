/*
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                                                                        ±
± PROGRAMA > CELTOPAL.EXE                                                ±
± AUTOR    > Fernando Gonz lez Ruano (FEGOR)                             ±
± VERSION  > 1.0/beta                                                    ±
± LENGUAJE > Borland C/C++ versi¢n 3.1                                   ±
±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
±                                                                        ±
±  Programa que pasa la paleta de colores de un fichero .CEL a otro      ±
±  TANQUES.PAL                                                           ±
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
    long c;
    char* pal;
    char paleta[768];
    char fich[13];
    int nfich;
    int anchura,altura;

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

    lseek(nfich,32,SEEK_SET);

    pal = malloc(768);
    read(nfich,pal,768);
    close(nfich);

    // escribimos fichero .pal

    memset(fich,0,13);
    memcpy(fich,"tanques.pal\0",12);
    printf("\nEscribiendo <%s> ...",fich);
    if((nfich = open(fich,O_BINARY|O_CREAT))==-1)
    {
      printf("\nError en fichero: %s\n",fich);
      exit(1);
    }
    write(nfich,pal,768);
    close(nfich);

    printf("\n\n");
    free(pal);
}
