#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "creatures.h"
#include "String.h"
#define _CRT_SECURE_NO_WARNINGS


int main()
{
	// Use this file to add the main flow of code. 
	// Keep it clean using creatures.cpp to create utility functions
	// Remember to free all allocated memory with malloc
	

	hero_data hero; 
	monster_data goblins[1000]; //The maximum number of monster_data structs is initialized and named (I use this syntax instead of malloc)
	//Below, the whole hero struct is given a name and stats by the player
	printf("Enter the name of your hero: ");
	name_selector(&hero);
	capitalize(hero.name);
	printf("\nEnter combat stats for %s:", hero.name);
	herostats_selector(&hero);
	printf("Now select a class:\n\nWarrior: No stats changed, no special habilities = 1\nPaladin: hp up, damage down, Divine Guidance = 2\nRanger: armor down, crit chance up, Piercing Shot = 3\n\n");
	printf("Introduce the number of the class choosen: ");
	scanf("%i", &hero.class_choosen);


	//Here starts the game loop that will last until the hero is dead. For each "round", we generate a random number of goblins with random stats
	while (hero.combat.hp > 0)
	{
		srand(time(NULL));
		int num_goblins = 2 + rand() % (8 + 1*hero.level); //we add a 1 to the result because a normal rand 10 would go from 0 to 9, and the player might be confused when he is attacked by 0 goblins.
		goblinstats_generator(goblins, num_goblins);
		if (hero.level > 1)
		{
			goblins_level_up(&hero, goblins);
		}
		printf("\nYou fight aganist an horde of %i goblins!!!\n\n", num_goblins);
		combat_loop(&hero, goblins, num_goblins);
		hero.xp += (hero.level * 10);
	}
	
	printf("Game finished, thanks for playing");
	
	getchar();
	getchar();
	return 0;
}