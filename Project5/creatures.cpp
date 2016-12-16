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
	printf("\n	maximum dmg (26-50): ");
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

void combat_calculator(hero_data * hero, monster_data* goblins, int numof)
{
	int alive_goblins = numof;
	while (alive_goblins != 0 || hero->combat.hp <= 0)
	{
		int goblin_attacked = 1 + rand() % numof;
		monster_data* defender_goblin = &goblins[goblin_attacked];
		if (defender_goblin->combat.hp != 0)
		{
			int hero_attack = hero->combat.attack_min + rand() % hero->combat.attack_max;
			defender_goblin->combat.hp = damage_calculator(hero_attack, defender_goblin->combat.armor, defender_goblin->combat.hp);
			printf("You attack goblin #%i \n\n", goblin_attacked);
			if (defender_goblin->combat.hp <= 0)
			{
				defender_goblin->combat.hp = 0;
				printf("You killed goblin #%i \n\n", goblin_attacked);
				alive_goblins - 1;
			}
			else
			{
				printf("The goblin #%i has %i hp left \n\n", goblin_attacked, defender_goblin->combat.hp);
			}

			for (int i = 0; i < alive_goblins; i++)
			{
				monster_data* active_goblin = goblins + i;
				if (active_goblin->combat.hp = 0)
					unsigned int goblin_attack;

				int goblin_attack = active_goblin->combat.attack_min + rand() % active_goblin->combat.attack_max;
				hero->combat.hp = damage_calculator(goblin_attack, hero->combat.armor, hero->combat.hp);
				
			}
			printf("The goblins have attacked you, and left you with %i hp left \n\n", hero->combat.hp);

		}
	}
}










