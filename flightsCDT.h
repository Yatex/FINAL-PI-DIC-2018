#ifndef Flights_h
#define Flights_h

typedef struct date{
	unsigned day;
	unsigned month;
	unsigned year;
}dateType;

typedef struct flight{
	dateType fecha;
	char *clase;
	char *clasificacion;
	char *tipo;
	char *origenOaci;
	char *destinoOaci;
	char *nombre;
}flightFormat;

typedef struct flightNode* fNode;

typedef struct flightNode{
	flightFormat data;
	fNode next;
}flightNode;

typedef struct flightsCDT* flightsADT;

typedef struct flightsCDT{
	int week[7][2];
	int composition[6];
	fNode first;
	fNode iterator;
}flightsCDT;

flightsADT newFlights(void);

fNode newFlight(void);

void checkOaci(char oaci[]);

int dateToDay(dateType date);

void insertFlight(flightsADT flights, flightFormat movement, int *errorAdding);

void freeFlights(flightsADT flights);

void toBeginFlights(flightsADT flights);

int hasNextFlight(flightsADT flights);

flightFormat nextFlight(flightsADT flights);

char* addIfSpace( char* data, int* spaceError);

fNode intoFlightFormat( char* data, int* errorAdding);

int getTypeComp( flightFormat elem);

#endif /* flights_h */
