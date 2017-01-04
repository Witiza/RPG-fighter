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
	int level;
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
void combat_loop(hero_data*, monster_data*, int numof);
int damage_calculator(int, int, int, int);
void hero_level_up(hero_data*);
void goblins_level_up(hero_data*, monster_data*);


#endif 