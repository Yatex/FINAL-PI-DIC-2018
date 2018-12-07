#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Airport.h"
#include "Flights.h"
#include "OpenFiles.h"

int
dateToDay(dateType date)     //return 0 if its MONDAY, 1 TUESDAY, ... , 6 SUNDAY.
{
	int d=date.day, m=date.month, y=date.year, count=0;
	int month[]={31,28,31,30,31,30,31,31,30,31,30,31};
	for (size_t i = 0; i < m-1; i++)
		count+=month[i];
	if(y>2016 || (y==2016 && m>2))
		count+=1;
	count+=((y-2014)*365+d);
	return (count+1)%7;
}

void
freeAll(airportADT aeros, flightsADT vuelos){
	freeAirports(aeros);
	freeFlights(vuelos);
	return;
}

int
QuerryUNO(airNode a, fNode f){
	FILE * querry;
	querry=fopen("movimientos_aeropuerto.csv","wt");
	if (querry == NULL)
		return 1;
	while(a != NULL){
		int mov = 0;
		while(f != NULL){
			if(strcmp(a->data.oaci , f->data.origenOaci)==0 || strcmp(a->data.oaci , f->data.destinoOaci))
				mov += 1;
			f = f->next;
		}
		fputs(a->data.oaci , querry);
		fputs(";" , querry);
		fputs(a->data.denomination , querry);
		fputs(";" , querry);
		fprintf(querry , "%d\n" , mov);
		a = a -> next;
	}
	fclose(querry);
	return 0;
}

int
QuerryDOS(flightsADT f){
	FILE * querry;
	char* vec[7] = {"lunes","martes","miercoles","jueves","viernes","sabado","domingo"};
	querry=fopen("dia_semana.csv","wt");
	if (querry == NULL)
		return 1;
	for(int i=0; i<7; i++){
		fprintf(querry, "%s;%d;%d;%d \n", vec[i], f->week[i][0], f->week[i][1], (f->week[i][0] + f->week[i][1]));
	}
	fclose(querry);
	return 0;
}

int
QuerryTRES(flightsADT f){
	FILE * querry;
	char* vec[6] = {"Cabotaje;Regular;","Cabotaje;No Regular;","Cabotaje;Vuelo Privado;","Internacional;Regular;","Internacional;No Regular;","Internacional;Vuelo Privado;"};
	querry=fopen("dia_semana.csv","wt");
	if (querry == NULL)
		return 1;
	for(int i=0; i<7; i++){
		fprintf(querry, "%s ; %d \n", vec[i], f->composition[i]);
	}
	fclose(querry);
	return 0;
}

int
main(void)
{
	int error = 0;  //Depending in the number, its a different error. For example Error=1 will mean out of memory
	airportADT aeros = fillAirports("aeropuertos.csv", &error);
	flightsADT vuelos = NULL;
	if(error != 0){
		vuelos = fillFlights("movimientosR.csv", &error);
	}
	if(error != 0)
	{
		switch(error)
		{
			case 1:
				printf("No enough memory to continue");
			case 2:
				printf("Error creating list");
			case 3:
				printf("Error copying the information");
		}
		return 1;
	}
	if((aeros->first != NULL) && (vuelos ->first != NULL)){
		if (QuerryUNO(aeros->first, vuelos->first))
			printf("The file movimientos_aeropuerto.csv has been created succesfully\n");
		else
			printf("The file movimientos_aeropuerto.csv could not be created due to a lack of memory\n");
		if (QuerryDOS(vuelos))
			printf("The file dia_semana.csv has been created succesfully\n");
		else
			printf("The file dia_semana.csv could not be created due to a lack of memory\n");
		if (QuerryTRES(vuelos))
			printf("The file composicion.csv has been created succesfully\n");
		else
			printf("The file composicion.csv could not be created due to a lack of memory\n");
		freeAll(aeros, vuelos);
	}
	return 0;
}
