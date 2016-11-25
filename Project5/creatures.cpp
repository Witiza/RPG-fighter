#include"creatures.h"
#include<stdio.h>

typedef struct hero_data hero_data;
typedef struct combat_data combat_data;
typedef struct monster_data monster_data;


void name_selector(hero_data* hero)
{
	char temp_char[20];
	int counter = 0;
	fflush(stdin);
	scanf("%s", temp_char);

	while(temp_char[counter-1] != '\0' )
	{
		hero->name[counter] = temp_char[counter];
		counter++;
	}
}
void herostats_selector(combat_data* herostats)
{

	/*scanf("%i", herostats->hp);
	scanf("%i", herostats->attack_min);
	scanf("%i", herostats->attack_max);
	scanf("%i", herostats->armor);*/
	fflush(stdin);
	printf("\n	hp: ");
	scanf("%i", &(herostats->hp));
	printf("\n	minimum dmg: ");
	scanf("%i", &(herostats->attack_min));
	printf("\n	maximum dmg: ");
	scanf("%i", &(herostats->attack_max));
	printf("\n	armor: ");
	scanf("%i", &(herostats->armor));



}
