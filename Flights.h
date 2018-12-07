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
#define FALSE 0
#define TRUE !FALSE
#define MAX_FECHA 10
#define MAX_OACI 4
#define CLASIFVUELO 13
#define CLASEVUELO 38
#define TIPOVUELO 10
#define MAXNAME 150

typedef struct date{
	unsigned day;
	unsigned month;
	unsigned year;
}dateType;

typedef struct flight{
	dateType fecha;
	char clase[CLASEVUELO];
	char clasificacion[CLASIFVUELO];
	char tipo[TIPOVUELO];
	char origenOaci[MAX_OACI];
	char destinoOaci[MAX_OACI];
    char nombre[MAXNAME];
}flightFormat;

typedef struct flightNode* fNode;
typedef struct flightsCDT* flightsADT;
typedef struct flightsCDT{
    int week[7][2];
    int composition[6];
    fNode first;
    fNode iterator;
}flightsCDT;


flightsADT newFlights(void);

fNode newFlight(void);

void checkOaci(char oaci[]);

int dateToDay(dateType date);

int insertFlight(flightsADT flights, char* movement, int*  errorAdding);

void freeFlights(flightsADT flights);

void toBeginFlights(flightsADT flights);

int hasNextFlight(flightsADT flights);

flightFormat nextFlight(flightsADT flights);

/*char* addIfSpace( char* data, int* spaceError);*/

flightFormat intoFlightFormat( char* data, int* errorAdding);

int getTypeComp( flightFormat elem);

#endif /* flights_h */

