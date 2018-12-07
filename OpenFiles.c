#include "OpenFiles.h"
#include "Flights.h"
#include "Airport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 150

airportADT fillAirports(char* filename,int* error){
	FILE *fp = fopen(filename,"r");
	airportADT airports = newAirport();
	if (!airports) {
		(*error)=2;  //ERROR 2 ERROR CREATING LIST
		return NULL;
	}
	char allData[MAX_LENGTH];
	fgets(allData,MAX_LENGTH,fp);
	while(fgets(allData,MAX_LENGTH,fp)){
		if (insertAirport(airports,allData,error) && error != 0) {
			(*error)=3; //ERROR 3 ERROR COPYING
		}
	}
	if (*error>0) {
		(*error)=3;  //ERROR 3 ERROR COPYING
	}
	fclose(fp);
	return airports;
}

flightsADT fillFlights(char* filename, int* error){
	FILE *fp = fopen(filename,"r");
	flightsADT flights = newFlights();
	if (!flights) {
		(*error)=2; //ERROR 2 ERROR CREATING LIST
		return NULL;
	}
	char allData[MAX_LENGTH];
	fgets(allData,MAX_LENGTH,fp);
	while(fgets(allData,MAX_LENGTH,fp)){
		if (insertFlight(flights,allData,error) && error != 0){
			(*error)=3;  //ERROR 3 ERROR COPYING
		}
	}
	if (*error!=0) {
		(*error)=3;//ERROR 3 ERROR COPYING
	}
	fclose(fp);
	return flights;
}
