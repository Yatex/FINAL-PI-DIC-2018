#include "Flights.h"






flightsADT newFlights(void){
	return calloc(1, sizeof(flightsCDT));
    
}

/*flightFormat newFlight(void){
	flightNode nodo = calloc(1, sizeof(flightNode));
	nodo.data = calloc(1, sizeof(flightFormat));
	return nodo;
}
*/

void checkOaci(char oaci[]){
	for (int i =0; oaci[i] != '\0'; i++) {
		if (isdigit(oaci[i]) || i > MAX_OACI) {
			strcpy(oaci,"N/A");
			return;
		}
	}
}

int
dateToDay(dateType date) //returns 0 if date provided is a monday, 1 if tuesday, untill 6 sunday
{
	int d=date.day, m=date.month, y=date.year, count=0;
	int month[]={31,28,31,30,31,30,31,31,30,31,30,31};
	for (size_t i = 0; i < m-1; i++)
	{
		count+=month[i];
	}
	if(y>2016 || (y==2016 && m>2))
		count+=1;
	count+=((y-2014)*365+d);
	return (count+1)%7;
}

char* addIfSpace( char* data, int * spaceError )
{
	char* aux = malloc( strlen( data ) + 1 );
	if(aux == NULL)
		(*spaceError)=0;
	else
		(*spaceError)=1;
	strcpy( aux, data );
	return aux;
}

/*static void freeFlightData( flightFormat flight )

	free(flight.clase);
	free(flight.clasificacion);
	free(flight.tipo);
	free(flight.origenOaci);
	free(flight.destinoOaci);
	free(flight.nombre);
}
 */

flightFormat intoFlightFormat(char* data, int *errorAdding){
	char dataMatriz[MAX_CAMPOS_F][MAX_SIZE_F];
	int i=0;
	int j=0;
	char* token = strtok(data,";");
	while(token != NULL){
		if (i==FECHA || i==CLASEDEVUELO || i==CLASIFICACION || i==TIPODEMOV || i==ORIGENOACI || i==DESTOACI || i==AERONAME) {
			strcpy(dataMatriz[j],token);
			j++;
		}
		token = strtok(NULL,";");
		i++;
	}
    flightFormat newFlight; /*= newFlight(void);*/
	int spaceError;
	(*errorAdding) = 0;
	char * intoData = dataMatriz[FECHA];
	dateType date;
	date.day = atoi(strtok(intoData,"/"));
	date.month = atoi(strtok(intoData,"/"));
	date.year = atoi(strtok(intoData,"/"));
	newFlight.fecha=date;
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

int insertFlight(flightsADT flights, char* data, int * errorAdding){
	flightFormat elem /*= calloc(1,sizeof(flightFormat))*/;
	elem = intoFlightFormat(data,errorAdding);
	if ((*errorAdding)==1) {
		return 1;
	}
	fNode newNode = malloc(sizeof(flightNode));
	if(newNode == NULL){
		*errorAdding = 1;
        free(elem.clase);
        free(elem.clasificacion);
        free(elem.tipo);
        free(elem.origenOaci);
        free(elem.destinoOaci);
        free(elem.nombre);
		return 1;
	}
	*errorAdding = 0;
	newNode->data = elem;
	fNode aux = flights->first;
	flights->first = newNode;
	newNode->next=aux;
	if(strcmp(newNode->data.clasificacion,"N/A") != 0){
		flights->week[dateToDay(newNode->data.fecha)][strcmp(newNode->data.clasificacion,"Nacional")+1]+=1;
		if(strcmp(newNode->data.clase,"N/A") != 0){
			flights->composition[getTypeComp(elem)]+=1;
		}
	}
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


static void freeRecFlight(fNode nodo){
	if(nodo!=NULL){
		freeRecFlight(nodo->next);
        free(nodo->data.clase);
        free(nodo->data.clasificacion);
        free(nodo->data.tipo);
        free(nodo->data.origenOaci);
        free(nodo->data.destinoOaci);
        free(nodo->data.nombre);
		free(nodo);
	}
}


void freeFlights(flightsADT flights){
    freeRecFlight(flights->first);
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
