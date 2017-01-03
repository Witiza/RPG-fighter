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
	hero->coins = 0;
	hero->xp = 0;
}

void goblinstats_generator(monster_data * goblins, int numof)
{
	for (int i = 1; i <= numof; i++)
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


int damage_calculator(int attacker_mindmg, int attacker_maxdmg, int defender_armor, int defender_hp)
{
	int attacker_dmg = attacker_mindmg + rand() % attacker_maxdmg;
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

void combat_loop(hero_data * hero, monster_data* goblins, int numofgoblins)
{
	int alive_goblins = numofgoblins;
	while (alive_goblins > 0)
	{
		int goblin_attacked = 1 + rand() % numofgoblins;
		monster_data* defender_goblin = &goblins[goblin_attacked];
		if (defender_goblin->combat.hp != 0)
		{
			printf("You attack goblin #%i \n\n", goblin_attacked);
			defender_goblin->combat.hp = damage_calculator(hero->combat.attack_min, hero->combat.attack_max, defender_goblin->combat.armor, defender_goblin->combat.hp);

			if (defender_goblin->combat.hp <= 0)
			{
				defender_goblin->combat.hp = 0;
				hero->coins += defender_goblin->coins;
				hero->xp += defender_goblin->xp;
				printf("You killed goblin #%i and received %i coins and %i exp point from him\n\n", goblin_attacked, defender_goblin->coins, defender_goblin->xp);
				getchar();
				alive_goblins -= 1;
			}
			else
			{
				printf("The goblin #%i has %i hp left \n\n", goblin_attacked, defender_goblin->combat.hp);
				getchar();
			}

			for (int i = 0; i < alive_goblins; i++)
			{
				monster_data* active_goblin = goblins + i;
				if (active_goblin->combat.hp != 0)
				{
					hero->combat.hp = damage_calculator(active_goblin->combat.attack_min, active_goblin->combat.attack_max, hero->combat.armor, hero->combat.hp);
				}
			}
			if (hero->combat.hp <= 0)
			{
				hero->combat.hp = 0;
				printf("The goblins have finally killed you. You died with %i coins in the bag and %i points of exp in wherever they are stored. Good luck in the afterlife %s \n\n", hero->coins, hero->xp, hero->name);
				getchar();
				return;
			}
			else if (hero->combat.hp > 0 && alive_goblins > 0)
			{
				printf("The goblins have attacked you, and left you with %i hp left \n\n", hero->combat.hp);
				getchar();
			}
			else if (hero->combat.hp > 0 && alive_goblins <= 0)
			{
				printf("You killed all the goblins, prepare for the next assault\n\n");
				getchar();
				return;
			}
		}
	}
}

