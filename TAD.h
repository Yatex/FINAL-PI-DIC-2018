#ifndef TAD_h
#define TAD_h

typedef struct flightsToAirport * flightsToAirportADT;

typedef struct airport * aiportADT;

typedef struct listCDT * listADT;

listADT newList(void);

void freeList(listADT list);

int addAirport(listADT l, char * oaci, char * info);

int addflight(listADT l, char * Origin, char * Destiny); //es mejor tener separado este con addWeek y addComp. HAY Q MODULARIZAR!!

int addWeekInfo(int day);//agrega el viaje a la semana para el querry 2

int addCompInfo(int type); //que el type sea 0 es Cabotaje Regular, 1 Cabotaje No Regular, 2 Cabotaje Viaje Privado, 3 Internacional Regular, 4 Interacional No Regular, 5 Internacional Viaje Privado.

int QuerryUNO(listADT list); //they return 0 if they were created with no problems, 1 if there were.

int QuerryDOS(listADT list);

int QuerryTRES(listADT list); 

#endif
