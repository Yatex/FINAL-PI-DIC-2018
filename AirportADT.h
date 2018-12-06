//
//  AirportADT.h
//  TPFINALPI2018
//
//  Created by Igancio Grasso on 04/12/2018.
//

#ifndef AirportADT_h
#define AirportADT_h
#define FALSE 0
#define TRUE !FALSE
#define Max_Oaci 5
#define Max_Deno 70
#define Max_Prov 19 

#include <stdio.h>

typedef struct airpData{
    char oaci[Max_Oaci];
    char denomination[Max_Deno];
    char province[Max_Prov];
}airportFormat;

typedef struct airportCDT* airportADT;

airportADT newAirport(void 	);
int insertAirport(airportADT airports,char* data,int* errorAdding);
void freeAirports(airportADT airports);
airportFormat StoreAsAirData(char* text);
void toBeginAirport(airportADT airports);
int hasNextAirport(airportADT airports);
airportFormat nextAirport(airportADT airports);

#endif /* AirportADT_h */
