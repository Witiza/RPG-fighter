#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "creatures.h"
#define _CRT_SECURE_NO_WARNINGS


int main()
{
	// Use this file to add the main flow of code. 
	// Keep it clean using creatures.cpp to create utility functions
	// Remember to free all allocated memory with malloc
	hero_data hero;
	combat_data herostats;
	monster_data goblins[1000];
	printf("Enter the name of your hero: ");
	name_selector(&hero);
	printf("\nEnter combat stats for %s:", hero.name);
	herostats_selector(&herostats);
	
	printf()
	
	
	
	
	

	
	getchar();
	return 0;
}