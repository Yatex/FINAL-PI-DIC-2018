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



flightsADT newFlights(void);
void insertFlight(flightsADT flights, flightFormat movement, int *errorAdding);
void freeFlights(flightsADT flights);
void toBeginFlights(flightsADT flights);
int hasNextFlight(flightsADT flights);
flightFormat nextFlight(flightsADT flights);


#endif /* flightsCDT_h */
