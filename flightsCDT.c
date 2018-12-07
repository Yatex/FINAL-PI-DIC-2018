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
    int week[7][2];
    int composition[6];
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
}flightFormat;

flightsADT newFlights(void){
  return calloc(1, sizeof(flightsCDT));
}

fNode newFlight(void){
  flightNode nodo = calloc(1, sizeof(flightNode));
  nodo.data = calloc(1, sizeof(flightFormat));
  return nodo;
}

void checkOaci(char oaci[]){
    for (int i =0; oaci[i] != NULL; i++) {
        if (isdigit(oaci[i]) || i > MAX_OACI) {
            strcpy(oaci,"N/A");
            return
        }
    }
}

int
dateToDay(dateType date)               //returns 0 if date provided is a monday, 1 if tuesday, untill 6 sunday
{
  int d=date->day, m=date->month, y=date->year, count=0;

  int month[]={31,28,31,30,31,30,31,31,30,31,30,31};
  for (size_t i = 0; i < m-1; i++)
    {
      count+=month[i];
    }
  if(y>2016 || (y==2016 && m>2))
    {
      count+=1;
    }
  count+=((y-2014)*365+d);
  return (count+1)%7;
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

    newFlight.fecha=date;

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


    return newFlight;

}

int insertFlights(flightsADT flights, char* data, int * errorAdding){
    flightFormat elem = calloc(1,sizeof(flightFormat));
    elem = intoFlightFormat(data,errorAdding);
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
    newNode->data = elem;
    fNode aux = flights->first;
    flights->first = newNode;
    newNode->next=aux;
    if(newNode.data->clasificacion!="N/A"){
      flights->week[dateToDay(newNode.data.fecha)][newNode.data->clasificacion == "Internacional"]+=1;
      if(newNode.data->clase!="N/A"){
        flights->composition[getTypeComp(elem)];
      }
    }
    return TRUE;
}

int getTypeComp(flightFormat elem){
  int aux = 0;
  if(elem->clasificacion=="Internacional"){
    aux = 3;
  }
    if(elem->clase=="Regular"){
      return 0+aux;
    }
    if(elem->clase=="No Regular"){
      return 1+aux;
    }
    if(elem->clase=="Vuelo Privado con Matricula Nacional" || elem->clase=="Vuelo Privado con Matricula Extranjera"){
      return aux 2+aux;
    }
}

void freeFlights(flightsADT flights){
    freeRecFlights(flights->first);
    free(flights);
}

static void freeRecFlight(fNode nodo){
  if(nodo!=NULL){
    freeRecFlight(nodo->next);
    freeFlightData(node->data);
    free(nodo);
  }
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
