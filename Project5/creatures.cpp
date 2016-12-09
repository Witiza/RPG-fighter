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
		monster_data* active_goblin = goblins + i;
		active_goblin->combat.hp = 1 + rand() % 100;
		active_goblin->combat.attack_min = 1 + rand() % 14;
		active_goblin->combat.attack_max = 15 + rand() % 16;
		active_goblin->combat.armor = 1 + rand() % 5;
		active_goblin->coins = 1 + rand() % 20;
		active_goblin->xp = 1 + rand() % 10;
	}
}


int damage_calculator(int attacker_dmg, int defender_armor, int defender_hp)
{
	if (defender_armor > attacker_dmg)
	{
		return defender_hp;
	}

	else
	{
		defender_hp = defender_hp - (attacker_dmg - defender_armor);
			return defender_hp;
	}

}

int combat_calculator(hero_data * hero, monster_data goblins, int numof)
{
	int alive_goblins = numof;
	while (alive_goblins != 0)
	{
		monster_data* defender_goblin = &goblins[1 + rand() % numof];
		while (defender_goblin->combat.hp != 0)
		{
			int hero_attack = hero->combat.attack_min + rand() % hero->combat.attack_max;
			defender_goblin->combat.hp = damage_calculator(hero_attack, defender_goblin->combat.armor, defender_goblin->combat.hp);
			if (defender_goblin->combat.hp < 0)
			{
				defender_goblin->combat.hp = 0;
			}
		}
		alive_goblins - 1;
	}
}










