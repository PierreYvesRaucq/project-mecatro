#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

//#include <wiringPiSPI.h>  // Ne pas oublier de (dé)commenter wiringspi pour compilation
#include "IO/COM/CAN/CAN.hh"
#include "IO/COM/SPI/Specific/SPI_CAN.hh"
#include "IO/COM/SPI/SPI.hh"
#include "IO/COM/SPI/Specific/SPI_DE0.hh"
#include <math.h>


#include "struct.h"
#include "positionctrl.h"
#include "ia.h"
#include "speedctrl.h"
#include "pathplanning.h"


#define CAN_BR 125e3

//Pour analyser ce code commencer ici à la fonction main et suivre avec fichier structure code

//plus propre si on mettait ça dans un fichier à part avec toutes les fonctions "supplémentaires"
void writeDataToFile (double data)  // by example "DataPath" = "C:\\program.txt"
{

    FILE *fptr;

    // use appropriate location if you are using MacOS or Linux
    fptr = fopen("error.txt","a");

    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    fprintf(fptr,"%f \n",data);
    fclose(fptr);

    //return 0;
}

int main()
{
    printf("####################################\n");
    printf("\t\t\t Titatronic ready to test pathplanning !!! \n");
    printf("####################################\n");


    CtrlStruct* structure = init();

    //path and map initialization (see pathplanning algorithm.c to understand how it works)
    Map* mymap = initmap();

    structure->theUserStruct->state = 2;

    for(int i = 0; i < mymap->mypath->objnb; i++)
      printf("%d ", mymap->mypath->obj[i]);
}
