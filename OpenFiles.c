//
//  OpenFiles.c
//  TPFINALPI2018
//
//  Created by Igancio Grasso on 04/12/2018.
//

#include "OpenFiles.h"

airportADT fillAirports(chat* filename){
    FILE *fp = fopen(filename,"r");
    if (!fp) {
        Error(filename);
    }
    
    int errorAdding;
    airportAdt airports = newAirport();
    
    if (!airports) {
        fprintf(stderr,"ERROR CREANDO LA LISTA");
        return;
    }
    
    char* allData[MAX_LENGHT];
    fgets(allData,MAX_LENGHT,fp);
    int errorFound=0;
    
    while(fgets(allData,MAX_LENGHT,fp)){
        if (insertAirport(airports,allData,&errorAdding) && errorAdding == 0) {
            errorFound++;
        }
    }
    if (errorFound) {
        fprintf(stderr,"ERROR COPIANDO");
    }
    
    fclose(fp);
    return airports;
    
}

airportADT fillAirports(chat* filename){
    FILE *fp = fopen(filename,"r");
    if (!fp) {
        Error(filename);
    }
    
    int errorAdding;
    flightsADT flights = newFlights()
    
    if (!flights) {
        fprintf(stderr,"ERROR CREANDO LA LISTA");
        return;
    }
    
    char* allData[MAX_LENGHT];
    fgets(allData,MAX_LENGHT,fp);
    int errorFound=0;
    
    while(fgets(allData,MAX_LENGHT,fp)){
        if (insertAirport(flights,allData,&errorAdding) && errorAdding != 0) {
            errorFound++;
        }
    }
    if (errorFound) {
        fprintf(stderr,"ERROR COPIANDO");
    }
    
    fclose(fp);
    return flights;
    
}
