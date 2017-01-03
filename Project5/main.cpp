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
	srand(time(NULL));

	hero_data hero;

	monster_data goblins[1000];

	printf("Enter the name of your hero: ");

	name_selector(&hero);
	
	capitalize(hero.name);
	
	printf("\nEnter combat stats for %s:", hero.name);
	
	herostats_selector(&hero);
	while (hero.combat.hp > 0)
	{
		srand(time(NULL));
		int num_goblins = 1 + rand() % 10;
		goblinstats_generator(goblins, num_goblins);
		printf("You fight aganist an horde of %i goblins!!!\n\n", num_goblins);
		combat_loop(&hero, goblins, num_goblins);
	}
	printf("finish");

	
	


	
	
	
	
	

	getchar();
	getchar();
	return 0;
}