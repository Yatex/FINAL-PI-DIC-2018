#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "TAD.h"

typedef struct flightsToAirport * flightsToAirportADT;

typedef struct airport * aiportADT;

typedef struct listCDT * listADT;

typedef struct listCDT
{
	size_t week[7][2]; //una matriz de 7 lugares para la semana y los 2 para el cabotaje e iternacional
	size_t composition[6];
	aiportADT firstAirport;
}listCDT;

typedef struct flightsToAirport
{
	char * oaci;
	size_t takeoffs;
	size_t landings;
	flightsToAirportADT nextFlights;
}flightsToAirport;

typedef struct airport
{
	char * oaci;
	size_t from;
	size_t to;
	char * name;
	airportADT nextAirport;
	flightsToAirportADT firstFlight;
}airport;

