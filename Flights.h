#ifndef Flights_h
#define Flights_h
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FECHA 0
#define CLASEDEVUELO 2
#define CLASIFICACION 3
#define TIPODEMOV 4
#define ORIGENOACI 5
#define DESTOACI 6
#define AERONAME 7
#define MAX_CAMPOS_F 7
#define MAX_SIZE_F 500
#define MAX_OACI 4
#define FALSE 0
#define TRUE !FALSE

typedef struct date{
	unsigned day;
	unsigned month;
	unsigned year;
}dateType;

typedef struct flight{
	dateType fecha;
	char *clase;
	char *clasificacion;
	char *tipo;
	char *origenOaci;
	char *destinoOaci;
	char *nombre;
}flightFormat;

typedef struct flightNode* fNode;

typedef struct flightNode{
    flightFormat data;
    fNode next;
}flightNode;

typedef struct flightsCDT{
    int week[7][2];
    int composition[6];
    fNode first;
    fNode iterator;
}flightsCDT;



typedef struct flightsCDT* flightsADT;


flightsADT newFlights(void);

fNode newFlight(void);

void checkOaci(char oaci[]);

int dateToDay(dateType date);

int insertFlight(flightsADT flights, char* movement, int*  errorAdding);

void freeFlights(flightsADT flights);

void toBeginFlights(flightsADT flights);

int hasNextFlight(flightsADT flights);

flightFormat nextFlight(flightsADT flights);

char* addIfSpace( char* data, int* spaceError);

flightFormat intoFlightFormat( char* data, int* errorAdding);

int getTypeComp( flightFormat elem);

#endif /* flights_h */
