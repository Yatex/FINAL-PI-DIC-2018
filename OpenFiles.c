#include "OpenFiles.h"
#include "Flights.h"
#include "Airport.h"

airportADT fillAirports(char* filename,int* error){
	FILE *fp = fopen(filename,"rt");
	airportADT airports = newAirport();
	if (!airports) {
		*error=2;  //ERROR 2 ERROR CREATING LIST
		return;
	}
	char* allData[MAX_LENGHT];
	fgets(allData,MAX_LENGHT,fp);
	while(fgets(allData,MAX_LENGHT,fp)){
		if (insertAirport(airports,allData,&error) && error != 0) {
			*error=3; //ERROR 3 ERROR COPYING
		}
	}
	if (error>0) {
		*error=3;  //ERROR 3 ERROR COPYING
	}
	fclose(fp);
	return airports;
}

flightsADT fillFlights(char* filename, int* error){
	FILE *fp = fopen(filename,"rt");
	flightsADT flights = newFlights();
	if (!flights) {
		*error=2; //ERROR 2 ERROR CREATING LIST
		return;
	}
	char* allData[MAX_LENGHT];
	fgets(allData,MAX_LENGHT,fp);
	int errorFound=0;
	while(fgets(allData,MAX_LENGHT,fp)){
		if (insertFlights(flights,allData,&errorAdding) && errorAdding != 0) {
			*error=3;  //ERROR 3 ERROR COPYING
		}
	}
	if (errorFound) {
		*error=3;//ERROR 3 ERROR COPYING
	}
	fclose(fp);
	return flights;
}
