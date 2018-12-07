#ifndef Airport_h
#define Airport_h
#define Max_Oaci 5
#define Max_Deno 70
#define Max_Prov 19

typedef struct airportNode* airNode;

typedef struct airportCDT* airportADT;

typedef struct airportFormat{
	char oaci[Max_Oaci];
	char denomination[Max_Deno];
	char province[Max_Prov];
}airportFormat;

typedef struct airportNode{
	airportFormat data;
	airNode next;
}airportNode;

typedef struct airportCDT{
	airNode first;
	airNode iterator;
}airportCDT;

airportADT newAirport(void);

airportFormat newAirportFormat(void);

int insertAirport(airportADT airports,char* data,int errorAdding);

void freeAirports(airportADT airports);

airportFormat intoAirportFormat(char* text);

void toBeginAirport(airportADT airports);

int hasNextAirport(airportADT airports);

airportFormat nextAirport(airportADT airports);

#endif /* Airport_h */
