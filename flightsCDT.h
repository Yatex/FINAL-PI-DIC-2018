//
//  flights.h
//  TPFINALPI2018
//
//  Created by Igancio Grasso on 04/12/2018.
//

#ifndef flightsCDT_h
#define flightsCDT_h
#define FALSE 0
#define TRUE !FALSE

#include <stdio.h>

typedef struct flightsCDT* flightsADT;

typedef struct date{
    unsigned day;
    unsigned month;
    unsigned year;
}dateType;

typedef struct flight{
    dateType fecha;
    char *clase;
    char *clasificacion
    char *tipo
    char *origenOaci
    char *destinoOaci
    char *nombre
    int diaSemana;
}flightFormat;

flightsADT newFlights(void);
void insertFlight(flightsADT flights, flightFormat movement, int *errorAdding);
void freeFlights(flightsADT flights);
void toBeginFlights(flightsADT flights);
int hasNextFlight(flightsADT flights);
flightFormat nextFlight(flightsADT flights);


#endif /* flightsCDT_h */
