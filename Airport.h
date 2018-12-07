#ifndef Airport_h
#define Airport_h
#define Max_Oaci 5
#define Max_Deno 70
#define Max_Prov 19

#define MAX_CAMPOS 3
#define MAX_SIZE 150
#define FALSE 0
#define TRUE !FALSE
#define OACI 1
#define DENOMINATION 4
#define PROVINCE 21
#define DELIM ';'
#define suc(elem) elem + 1 

typedef struct airportNode* airNode;

typedef struct airportFormat{
	char oaci[Max_Oaci];
	char denomination[Max_Deno];
	char province[Max_Prov];
}airportFormat;

typedef struct airportCDT* airportADT;

airportADT newAirport(void);

airportFormat newAirportFormat(void);

int insertAirport(airportADT airports,char* data,int* errorAdding);

void freeAirports(airportADT airports);

/*void intoAirportFormat(char* text,airportFormat newAir);*/

void toBeginAirport(airportADT airports);

int hasNextAirport(airportADT airports);

airportFormat nextAirport(airportADT airports);

#endif /* Airport_h */
