#include"creatures.h"
#include<stdio.h>

typedef struct hero_data hero_data;
typedef struct combat_data combat_data;
typedef struct monster_data monster_data;


void name_selector()
{
	char temp_char[20];
	hero_data hero;
	fflush(stdin);
	scanf("%s", temp_char);
	hero.name = temp_char;
}
