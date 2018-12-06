//
//  AirportADT.c
//  TPFINALPI2018
//
//  Created by Igancio Grasso on 04/12/2018.
//

#include "AirportADT.h"

#define OACI 1
#define DENOMINATION 4
#define PROVINCE 21

typedef struct airportNode{
    airportFormat data;
    struct airportNode* next;
}airportNode;

typedef airportNode* airNode;

typedef struct airportCDT{
    struct airportNode* first;
    struct airportNode* iterator;
}airportCDT;





airportADT newAirport(){
    return calloc(1,sizeof(airportCDT));
}


static airNode insertAirportRec(airNode first, airportFormat elem, int* errorAdding){
    int result;
    if (first == NULL || (result == strcmp(first.data.oaci,elem.oaci)) > 0) {
        airNode newNode = malloc(sizeof(struct airportNode));
        if (newNode == NULL) {
            (*errorAdding)=TRUE;
            return NULL;
        }
        newNode->data = elem;
        newNode->next= first;
        *errorAdding = FALSE;
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
            j++
        }
        token = strtok(NULL,";");
        i++;
    }
    airportFormat newAirport;
    strcpy(newAirport.oaci,dataMatriz[OACI]);
    strcpy(newAirport.denomination,dataMatriz[DENOMINATION]);
    strcpy(newAirport.province,dataMatriz[PROVINCE]);
    
    return newAirport;
    
}

int insertAirport(airportADT airports, char * data, int * errorAdding){
    airportFormat elem = intoAirportFormat(data);

    if (*(elem.oaci)!= 0) {
        airports->first = insertAirportRec(airports->first,elem, errorAdding);
        return TRUE;
    }
    return FALSE;
}


void freeAirports(airportADT airports){
    airNode current = airports->first;
    airnode aux;
    
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

