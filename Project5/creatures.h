#ifndef __CREATURES_H__
#define __CREATURES_H__

// find here the manin data structure for the game
// feel free to expand it to suit your improvements

struct combat_data
{
	int hp;
	int attack_min;
	int attack_max;
	int armor;
};

struct hero_data
{
	char name[20];
	struct combat_data combat;
	int coins;
	int xp;
};

struct monster_data
{
	struct combat_data combat;
	int coins;
	int xp;
};

void name_selector(hero_data*);
void herostats_selector(hero_data*);
void goblinstats_generator(monster_data*, int);
int combat_calculator(hero_data*, monster_data, int numof);
int damage_calculator(int, int, int);



#endif // __CREATURES_H__