#include "Airport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct airportNode{
    airportFormat data;
    airNode next;
}airportNode;

typedef struct airportCDT{
    airNode first;
    airNode iterator;
}airportCDT;


airportADT newAirport(){
	airportADT newAir = calloc(1,sizeof(airportCDT));
    return newAir;
}


static airNode insertAirportRec(airNode first, airportFormat elem, int* errorAdding){
	if (first == NULL || strcmp(elem.oaci,first->data.oaci) < 0) {
		airNode newNode = malloc(sizeof(airportNode));
		if (newNode == NULL) {
			(*errorAdding)=1;
			return first;
		}
		newNode->data = elem;
		newNode->next= first;
		*errorAdding = 0;
		return newNode;
	}
	first->next = insertAirportRec(first->next,elem,errorAdding);
	return first;
}
/*
void intoAirportFormat(char * data){
	char dataMatriz[MAX_CAMPOS][MAX_SIZE];
	int i=0;
	int j=0;
	char* token = strtok(data,";");
	while(token != NULL || i < 22){
		if (i==OACI || i==DENOMINATION || i==PROVINCE) {
			strcpy(dataMatriz[j],token);
			j++;
		}
		token = strtok(NULL,";");
		i++;
	}
    
	strncpy(newAir.oaci,dataMatriz[0],Max_Oaci);
	strncpy(newAir.denomination,dataMatriz[1],Max_Deno);
	strncpy(newAir.province,dataMatriz[2],Max_Prov);
}
*/

int insertAirport(airportADT airports, char * data, int* errorAdding){
    char dataMatriz[MAX_CAMPOS][MAX_SIZE];
    int i=0;
    int j=0;
    char* token;
    token = strtok(data,";");
    while(token != NULL){
        if (i==OACI || i==DENOMINATION || i==PROVINCE) {
            strcpy(dataMatriz[j],token);
            j++;
        }
        token = strtok(NULL,";");
        i++;
    }
    airportFormat newAir;
    strncpy(newAir.oaci,dataMatriz[0],Max_Oaci);
    strncpy(newAir.denomination,dataMatriz[1],Max_Deno);
    strncpy(newAir.province,dataMatriz[2],Max_Prov);
    
	if (*(newAir.oaci) != 0) {
		airports->first = insertAirportRec(airports->first,newAir, errorAdding);
		return 1;
	}
	return 0;
}


void freeAirports( airportADT airports )
{
    airNode aux;
    toBeginAirport(airports);
    
    while(hasNextAirport(airports))
    {
        aux = airports->iterator;
        nextAirport(airports);
        free(aux);
    }
    free(airports);
}

void toBeginAirport(airportADT airports){
	airports->iterator = airports->first;
}

int hasNextAirport(airportADT airports){
	return airports->iterator != NULL;
}

airportFormat nextAirport(airportADT airports){
	airportFormat aux = airports->iterator->data;
	airports->iterator = airports->iterator->next;
	return aux;
}
