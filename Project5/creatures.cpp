#include"creatures.h"
#include "String.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

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
void herostats_selector(hero_data* hero)
{
	fflush(stdin);

	printf("\n	hp (100-1000): ");
	scanf("%i", &(hero->combat.hp));
	printf("\n	minimum dmg (10-25): ");
	scanf("%i", &(hero->combat.attack_min));
	printf("\n	maximum dmg (26-50 ");
	scanf("%i", &(hero->combat.attack_max));
	printf("\n	armor (10-20): ");
	scanf("%i", &(hero->combat.armor));
}

void goblinstats_generator(monster_data * goblins, int numof)
{
	for (int i = 0; i < numof; i++)
	{
		goblins->combat.hp = 1 + rand() % 100;
		goblins->combat.attack_min = 1 + rand() % 14;
		goblins->combat.attack_max = 15 + rand() % 14;
		goblins->combat.armor = 1 + rand() % 5;
	}
}




