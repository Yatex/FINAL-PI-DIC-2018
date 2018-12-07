#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Airport.h"
#include "Flights.h"
#include "OpenFiles.h"


void
freeAll(airportADT aeros, flightsADT vuelos){
	freeAirports(aeros);
	freeFlights(vuelos);
	return;
}


int QuerryUNO(airportADT aerop, flightsADT vuelos)
{
    int movs=0;
    FILE * archivo = fopen("movs_aeropuerto.csv", "w");
    if(archivo == NULL){
        printf("Error generando fichero en query 1...\n");
        return 0 ;
    }
    toBeginAirport(aerop);
    
    while( hasNextAirport(aerop) )
    {
        airportFormat auxAirport= nextAirport(aerop);
        
        toBeginFlights(vuelos);
        
        while( hasNextFlight(vuelos) )
        {
            flightFormat auxFlight = nextFlight(vuelos);
            
            if( ( (strcmp(auxFlight.origenOaci, auxAirport.oaci)) == 0 ) || ((strcmp(auxFlight.destinoOaci, auxAirport.oaci)) == 0 ))
            {
                movs++;
            }
            
        }
        
        if(movs != 0 )
        {
            fprintf(archivo, "%s;%s;%d \n", auxAirport.oaci,auxAirport.denomination,movs);
        }
        
    }
    
    
    fclose(archivo);
    return 1;
}


int
QuerryDOS(flightsADT f){
	FILE * querry;
	char* vec[7] = {"lunes","martes","miercoles","jueves","viernes","sabado","domingo"};
	querry=fopen("dia_semana.csv","wt");
	if (querry == NULL)
		return 1;
    
    /*int aux[7][2];
    for (int i=0; i<7; i++) {
        for (int j=0; j<2; j++) {
            aux[i][j] = f->week[i][j];
        }
    }
     */
     
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
	if((aeros != NULL) && (vuelos != NULL)){
		if (QuerryUNO(aeros, vuelos))
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

