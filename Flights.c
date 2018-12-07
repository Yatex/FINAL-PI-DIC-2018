#include "Flights.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct flightNode{
    flightFormat data;
    fNode next;
}flightNode;




flightsADT newFlights(void){
	flightsADT newFli = calloc(1, sizeof(flightsCDT));
    return newFli;
    
}


void checkOaci(char oaci[]){
	for (int i=0; oaci[i] != '\0'; i++) {
		if (isdigit(oaci[i]) || i >= MAX_OACI) {
			strcpy(oaci,"N/A");
			return;
		}
	}
}

int
dateToDay(dateType date) //returns 0 if date provided is a monday, 1 if tuesday, untill 6 sunday
{
	int d=date.day, m=date.month, y=date.year, count=0;
    printf("h\n");
	int month[]={31,28,31,30,31,30,31,31,30,31,30,31};
	for (int i = 0; i < (m-1); i++)
	{
		count+=month[i];
        printf("ho\n");
	}
	if(y>2016 || (y==2016 && m>2))
        printf("hola\n");
		count+=1;
	count+=((y-2014)*365+d);
    printf("holas\n");
	return (count+1)%7;
}
/*
char* addIfSpace( char* data, int * spaceError )
{
	char* aux = malloc(strlen(data)+ 1);
	if(aux == NULL)
		(*spaceError)=0;
    else{
		(*spaceError)=1;
        strcpy(aux,data);
    }
	return aux;
}
*/
/*
void freeFlightData(flightFormat elem){
    free(elem.clase);
    free(elem.clasificacion);
    free(elem.tipo);
    free(elem.origenOaci);
    free(elem.destinoOaci);
    free(elem.nombre);
}
*/
  /*
void intoFlightFormat(char * data, flightFormat elem){
	char dataMatriz[MAX_CAMPOS_F][MAX_SIZE_F];
	int i=0;
	int j=0;
	char* token = strtok(data,";");
	while(token != NULL || i < 10){
		if (i==FECHA || i==CLASEDEVUELO || i==CLASIFICACION || i==TIPODEMOV || i==ORIGENOACI || i==DESTOACI || i==AERONAME)
        {
			strcpy(dataMatriz[j],token);
			j++;
		}
		token = strtok(NULL,";");
		i++;
	}
    
    flightFormat newFlight;
	
    char * intoData = NULL;
    strncpy(intoData,dataMatriz[0],MAX_FECHA);
	dateType date;
	date.day = atoi(strtok(intoData,"/"));
	date.month = atoi(strtok(NULL,"/"));
	date.year = atoi(strtok(NULL,"/"));
    newFlight.fecha=date;
    
    strncpy(newFlight.clase,dataMatriz[1],CLASEVUELO);
    strncpy(newFlight.clasificacion,dataMatriz[2],CLASIFVUELO);
    strncpy(newFlight.tipo,dataMatriz[3],TIPOVUELO);
    strncpy(newFlight.origenOaci,dataMatriz[4],MAX_OACI);
    strncpy(newFlight.destinoOaci,dataMatriz[5],MAX_OACI);
    strncpy(newFlight.nombre,dataMatriz[6],MAXNAME);
    
  
     int spaceError;
     (*errorAdding) = 0;
    
	newFlight.clase = addIfSpace(dataMatriz[1],&spaceError);
	if(spaceError)
		(*errorAdding) = 1;
	newFlight.clasificacion = addIfSpace(dataMatriz[2],&spaceError);
	if(spaceError)
		(*errorAdding) = 1;
	newFlight.tipo = addIfSpace(dataMatriz[3],&spaceError);
	if(spaceError)
		(*errorAdding) = 1;
	newFlight.origenOaci = addIfSpace(dataMatriz[4],&spaceError);
	if(spaceError)
		(*errorAdding) = 1;
	checkOaci(dataMatriz[DESTOACI]);
	newFlight.destinoOaci = addIfSpace(dataMatriz[5],&spaceError);
	if(spaceError)
		(*errorAdding) = 1;
	newFlight.nombre = addIfSpace(dataMatriz[6],&spaceError);
	if(spaceError)
		(*errorAdding) = 1;
 
    
	return newFlight;
}
    */
int insertFlight(flightsADT flights, char* data){
    fNode newNode = malloc(sizeof(flightNode));
    printf("llegue6\n");
    if(newNode == NULL){
        return 1;
    }
    char dataMatriz[MAX_CAMPOS_F][MAX_SIZE_F];
    int i=0;
    int j=0;
    char* token = strtok(data,";");
    while(token != NULL){
            printf("llegue7\n");
        if (i==FECHA || i==CLASEDEVUELO || i==CLASIFICACION || i==TIPODEMOV || i==ORIGENOACI || i==DESTOACI || i==AERONAME)
        {
            strcpy(dataMatriz[j],token);
            j++;
        }
        token = strtok(NULL,";");
        i++;
    }
        printf("llegue8\n");
    
    
    char intoData[MAX_FECHA];
    strncpy(intoData,dataMatriz[0],MAX_FECHA);
    dateType date;
    char * aux = strtok(intoData,"/");
    if (aux != NULL) {
        printf("llegue60\n");
        date.day = atoi(aux);
    }
    aux = strtok(NULL,"/");
    if (aux != NULL) {
        printf("llegue61\n");
        date.month = atoi(aux);
    }
    aux = strtok(NULL,"/");
    if (aux != NULL) {
        printf("llegue62\n");
        date.year = atoi(aux);
    }
    printf("llegue63\n");
    
    /*date.month = atoi(strtok(NULL,"/"));
    printf("llegue62\n");
    date.year = atoi(strtok(NULL,"/"));
    newNode->data.fecha=date;
    printf("llegue63\n");
     */
    strncpy(newNode->data.clase,dataMatriz[1],CLASEVUELO);
    strncpy(newNode->data.clasificacion,dataMatriz[2],CLASIFVUELO);
    strncpy(newNode->data.tipo,dataMatriz[3],TIPOVUELO);
    strncpy(newNode->data.origenOaci,dataMatriz[4],MAX_OACI);
    strncpy(newNode->data.destinoOaci,dataMatriz[5],MAX_OACI);
    strncpy(newNode->data.nombre,dataMatriz[6],MAXNAME);
    printf("llegue6\n");


    newNode->next = flights->first;
    flights->first = newNode;
    printf("llegue69\n");
	if(strcmp(newNode->data.clasificacion,"N/A") != 0){
        printf("llegue69\n");
        int answer = strcmp(newNode->data.clasificacion,"Internaciona");
        int pos;
        if (answer == 0) {
            printf("llegue69\n");
             pos = 1;
        }
        else{
            pos = 0;
        }
        printf("llegue70\n");
        int dia = dateToDay(newNode->data.fecha);
        printf("%d\n",dia);
        flights->week[dia][pos]+=1;
        printf("llegue69\n");
		if(strcmp(newNode->data.clase,"N/A") != 0){
			flights->composition[getTypeComp(newNode->data)]+=1;
            printf("llegue6\n");
		}
        printf("llegue6\n");
	}
    printf("llegue8\n");
	return 0;
}

int getTypeComp(flightFormat elem){
	int aux = 0;
	if(strcmp(elem.clasificacion,"Internacional") == 0){
		aux = 3;
	}
	if(strcmp(elem.clase,"Regular") == 0){
		return 0+aux;
	}
	if(strcmp(elem.clase,"No Regular") == 0){
		return 1+aux;
	}
	/*if(strcmp(elem.clase,"Vuelo Privado con Matricula Nacional") == 0 || strcmp(elem.clase,"Vuelo Privado con Matricula Extranjera") == 0){*/
	return 2+aux;
	
    
}


void freeFlights(flightsADT flights)
{
    toBeginFlights(flights);
    fNode aux;
    
    while(hasNextFlight(flights))
    {
        aux = flights->iterator;
        nextFlight(flights);
        free(aux);
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
