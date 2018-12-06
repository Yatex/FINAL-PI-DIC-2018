//
//  flights.c
//  TPFINALPI2018
//
//  Created by Igancio Grasso on 04/12/2018.
//

#include "flightsCDT.h"

#define FECHA 0
#define CLASEDEVUELO 2
#define CLASIFICACION 3
#define TIPODEMOV 4
#define ORIGENOACI 5
#define DESTOACI 6
#define AERONAME 7

typedef struct flightNode{
    flightFormat data;
    struct flightNode * next;

}flightNode;

typedef struct flightsCDT{
    flightNode * first;
    flightNode * iterator;
}flightsCDT;

typedef flightNode * fNode;

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


void checkOaci(char oaci[]){
    for (int i =0; oaci[i] != NULL; i++) {
        if (isdigit(oaci[i]) || i > MAX_OACI) {
            strcpy(oaci,"N/A");
            return
        }
    }
}

int weekDay(dateType date)
{
    int c, g, d=date.day, m=date.month, y=date.year;
    static int eLookUpTable[]={0,3,2,5,0,3,5,1,4,6,2,4};
    static int fLookUpTable[]={0,5,3,1};
    
    if(m<3)
        y--;
    
    c=y/CENTURY;
    g=y-CENTURY*c;
    
    return ((int)(d+eLookUpTable[m-1]+fLookUpTable[c%4]+g+(g/4)))%7;
}

char* addIfSpace( char* data, int * spaceError )
{
    char* aux = malloc( strlen( data ) + 1 );
    if(aux == NULL)
        (*spaceError)=FALSE;
    else
        (*spaceError)=TRUE;
    
    strcpy( aux, data );
    
    return aux;
}

static void freeFlightData( flightFormat flight )
{
    free(flight.fecha);
    free(flight.clase);
    free(flight.clasification);
    free(flight.tipo);
    free(flight.origenOaci);
    free(flight.destinoOaci);
    free(flight.nombre);
    free(flight.diaSemana);
}



flightFormat intoFlightFormat(char* data, int *errorAdding){
    char dataMatriz[MAX_CAMPOS_F][MAX_SIZE_F];
    int i=0;
    int j=0;
    char* token = strtok(data,";");
    while(token != NULL){
        if (i==FECHA || i==CLASEDEVUELO || i==CLASIFICACION || i==TIPODEMOV || i==ORIGENOACI || i==DESTOACI || i==AERONAME) {
            strcpy(dataMatriz[j],token);
            j++
        }
        token = strtok(NULL,";");
        i++;
    }
    flightFormat newFlight;
    
    int spaceErro;
    
    (*errorAdding) = FALSE;
    
    char * intoData = dataMatriz[FECHA];
    dateType date;
    date.day = atoi(strtok(intoData,"/"));
    data.month = atoi(strtok(intoData,"/"));
    data.year = atoi(strtok(intoData,"/"));
    
    strcpy(newFlight.fecha,date);
    newFlight.diaSemana = weekDay(newFlight.fecha);
    
    newFlight.clase = addIfSpace(dataMatriz[CLASEVUELO],&spaceError)
    if(spaceError)
        (*errorAdding) = TRUE;
    
    newFlight.clasificacion = addIfSpace(dataMatriz[CLASIFICACION],&spaceError)
    if(spaceError)
        (*errorAdding) = TRUE;
    
    newFlight.tipo = addIfSpace(dataMatriz[TIPODEMOV],&spaceError)
    if(spaceError)
        (*errorAdding) = TRUE;
    
    newFlight.origenOaci = addIfSpace(dataMatriz[ORIGENOACI],&spaceError)
    if(spaceError)
        (*errorAdding) = TRUE;
    
    checkOaci(dataMatriz[DESTOACI]);
    
    newFlight.destinoOaci = addIfSpace(dataMatriz[DESTOACI],&spaceError)
    if(spaceError)
        (*errorAdding) = TRUE;
    
    newFlight.nombre = addIfSpace(dataMatriz[AERONAME],&spaceError)
    if(spaceError)
        (*errorAdding) = TRUE;
    
    
    return newAirport;
    
}

int insertFlights(flightsADT flights, char* data, int * errorAdding){
    flightFormat elem = intoFlightFormat(data,errorAdding);
    if ((*errorAdding)==TRUE) {
        return TRUE;
    }
    fnode newNode = malloc(sizeof(flightNode));
    if(newNode == NULL){
        *errorAdding = TRUE;
        freeFlightData(elem);
        return TRUE
    }
    *errorAdding = FALSE;
    newNode->data = movement;
    newNode->next = flights->first;
    flights->>first = newNode;
    return TRUE;
}

void freeFlights(flightsADT flights){
    fNode current = flights->first;
    fNode aux;
    
    while(current != NULL){
        aux = current->next;
        free(current);
        current = aux;
    }
    free(flights);
}


void toBeginFlights(flightsADT flights){
    flights->iterator = flights->first;
}



int hasNextFlight(flightsADT flights){
    return flights->iterator != NULL;
}


flightFormat nextFlight(flightsADT flights){
    flightFormat answer = flights->iterator->data;
    flights->iterator = flights->iterator->next;
    return answer;
}
