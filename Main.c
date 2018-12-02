#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "TAD.h"
#include "TAD2.h"
#include "getnum.h"

int
dateToDay(char* str)     //This tell us what day this is.
{
	int d=0, m=0, y=0, count=0;
	d+=((str[0]-'0')*10+(str[1]-'0')-1);
	m+=((str[3]-'0')*10+(str[4]-'0'));
	y+=(2010+(str[9]-'0'));
	int month[]={31,28,31,30,31,30,31,31,30,31,30,31};
	for (size_t i = 1; i < m; i++)
		count+=month[i];
	if(y>2016 || (y==2016 && m>2))
		count+=1;
	count+=((y-2014)*365+d);
	return (count+2)%7;         //The first day of 2014 is Wednesday, so we +2, so 0 es monday, 1 tuesday...
}

int
main(void)
{
	int Error = 0;  //Depending in the number, its a different error. For example Error=1 will mean out of memory
	int year = getint("Insert a year between 2014-2018 inclusive: \n"); //AVERIGUAR SI HACE FALTA HACER ESTO, lo de preguntar el año xq no lo vi en el enunciado	
	ListADT2 list2=NULL;
	ListADT list=createListAir(year, &Error);
	if(Error == 0)
		addMov(list, list2, list3, &Error);
	if(Error != 0)
	{
		switch(Error)
		{
			case 1:
				printf("No enough memory to continue");
			case 2:
				printf("");                             //    ESTO        
			case 3:                                         //    SERIA
				printf("");                             //    FRONT 
			case 4:                                         //      -
				printf("");                             //     END
			case 5:
				printf("");
		}
		return 1;
	}
	QuerryUNO(list);
	QuerryDOS(list);
	freeList(list);
	QuerryTRES(list2);
	freeList(list2);
	return 0;
}

void
createListAir(year, *Error)
{
	//ESTE ES UNO DE LOS QUE LEEN LOS ARCHIVOS
}

void
addMov(list, list2, list3, *Error)
{
	//ESTE TAMBIEN LEE EL ARCHIVO MOV 
	//ESTE LE MANDA LOS DATOS EN UN FOR A LA LISTA, LISTA2
}
