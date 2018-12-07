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
	return calloc(1,sizeof(airportCDT));
}

/*airportFormat newAirportFormat(){
    return calloc(1, sizeof(formNode));

 }
 */

static airNode insertAirportRec(airNode first, airportFormat elem, int* errorAdding){
	int result=0;
	if (first == NULL || (result == strcmp(first->data.oaci,elem.oaci)) > 0) {
		airNode newNode = malloc(sizeof(airportNode));
		if (newNode == NULL) {
			(*errorAdding)=1;
			return NULL;
		}
		newNode->data = elem;
		newNode->next= first;
		*errorAdding = 0;
		return newNode;
	}
	first->next = insertAirportRec(first->next,elem,errorAdding);
	return first;
}

airportFormat intoAirportFormat(char * data){
	char dataMatriz[MAX_CAMPOS][MAX_SIZE];
	int i=0;
	int j=0;
	char* token = strtok(data,";");
	while(token != NULL){
		if (i==OACI || i==DENOMINATION || i==PROVINCE) {
			strcpy(dataMatriz[j],token);
			j++;
		}
		token = strtok(NULL,";");
		i++;
	}
    airportFormat newAirport; /*= newAirportFormat();*/
	strcpy(newAirport.oaci,dataMatriz[0]);
	strcpy(newAirport.denomination,dataMatriz[1]);
	strcpy(newAirport.province,dataMatriz[2]);
	return newAirport;   
}

int insertAirport(airportADT airports, char * data, int* errorAdding){
	airportFormat elem = intoAirportFormat(data);
	if (*(elem.oaci)!= 0) {
		airports->first = insertAirportRec(airports->first,elem, errorAdding);
		return 1;
	}
	return 0;
}

void freeAirports(airportADT airports){
	airNode current = airports->first;
	airNode aux;
	while(current != NULL){
		aux = current->next;
		free(current);
		current = aux;
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
