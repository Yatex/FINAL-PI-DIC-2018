#ifndef OpenFiles_h
#define OpenFiles_h
#include "Airport.h"
#include "Flights.h"

airportADT fillAirports(char* filename, int* error);

flightsADT fillFlights(char* filename, int* error);

#endif /* OpenFiles_h */
