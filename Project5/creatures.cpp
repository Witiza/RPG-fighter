#include"creatures.h"
#include "String.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

typedef struct hero_data hero_data;
typedef struct combat_data combat_data;
typedef struct monster_data monster_data;


void name_selector(hero_data* hero)	 /*this function works by creating a temporal array, scanf the player's name on it, and then copy it into the hero.name. 
									We do it this way because hero.name is a pointer, so we can't scanf an entire word on it.*/
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
void herostats_selector(hero_data* hero)//This function works by just printing the stat desired and then scanf the player's stat. Althoug it recommends values, the final ones can be whatever the player puts, for testing purposes.
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
	hero->level = 1;
	hero->coins = 0;
	hero->xp = 0;
}

void goblinstats_generator(monster_data * goblins, int numof)//We add 1 to each result to avoid goblins from dropping 0 coins or exp, or having goblins that insta-die.
{
	for (int i = 1; i <= numof; i++)
	{
		monster_data* active_goblin = goblins + i; //our first generated goblin will be the goblins[0]. In the main combat loop it's explained.
		active_goblin->combat.hp = 1 + rand() % 100;
		active_goblin->combat.attack_min = 1 + rand() % 14;
		active_goblin->combat.attack_max = 15 + rand() % 16;
		active_goblin->combat.armor = 1 + rand() % 5;
		active_goblin->coins = 1 + rand() % 20;
		active_goblin->xp = 1 + rand() % 10;
	}
}


/*int damage_calculator(int attacker_mindmg, int attacker_maxdmg, int defender_armor, int defender_hp) //just a function that given an attacker's max dmg and min dmg, and a defender's armor and hp
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

}*/

void combat_loop(hero_data * hero, monster_data* goblins, int numofgoblins)
{
	int alive_goblins = numofgoblins;
	while (alive_goblins > 0)
	{
		int goblin_attacked = 1 + rand() % numofgoblins; //we decide which goblin we are going to attack. Since our first goblin declared is goblins[1], we add 1 to the random result.
		monster_data* defender_goblin = &goblins[goblin_attacked];
		if (defender_goblin->combat.hp != 0) //we check if the goblin attacked is alive (hp>0). If not, we just restart the cycle.
		{
			printf("You attacked goblin #%i", goblin_attacked);
			int hero_dmg = (hero->combat.attack_min + rand() % hero->combat.attack_max) - defender_goblin->combat.armor;//we calculate the damage we are going to deal to the defender goblin and then substract it. if its negative or zero, due to the armor, we change it to one, cuz the gameplay.
			if (hero_dmg < hero->combat.attack_min + (hero->combat.attack_max / 4) && hero->class_choosen == 2)
			{
				hero_dmg = hero->combat.attack_min + (hero->combat.attack_max / 4);
			}
			int hero_crit_chance = 1 + rand() % 100;
			if (hero_crit_chance <= 5 && hero->class_choosen != 3)
			{
				hero_dmg += defender_goblin->combat.armor;
				hero_dmg *= 3;
			}
			else if (hero_crit_chance <= 10 && hero->class_choosen == 3)
			{
				hero_dmg += defender_goblin->combat.armor;
				hero_dmg *= 3;
			}
			if (hero_dmg <= 0)
			{
				hero_dmg = 1;
			}
			if (hero_crit_chance <= 5)
			{
				printf(" with a critical hit");
			}
			
			printf(" and dealt %i dmg to him\n\n", hero_dmg);
			defender_goblin->combat.hp -= hero_dmg;

			//Now we check the different options. If the goblin's hp is o or below, we kill it and their coins and xp are added to the hero struct. If not, we just print a message.
			if (defender_goblin->combat.hp <= 0)
			{
				defender_goblin->combat.hp = 0;
				hero->coins += defender_goblin->coins;
				hero->xp += defender_goblin->xp;
				printf("You killed goblin #%i and received %i coins and %i exp point from him\n\n", goblin_attacked, defender_goblin->coins, defender_goblin->xp);
				if (hero->class_choosen == 3)
				{
					alive_goblins = ranger_hability(hero, goblins, numofgoblins, alive_goblins);
				}
				if (hero->xp >= hero->level * 100)
				{
					goblins_level_up(hero, goblins);
					hero_level_up(hero);
					printf("Your hero has leveled up and is now level %i!!! It's stats have increased, but watch out, the new goblins are thoughter than the previous ones.\nYour new hero stats are:\n\n", hero->level);
					getchar();
					printf("hp: %i\nattack_min: %i\nattack_max: %i\narmor: %i\n", hero->combat.hp, hero->combat.attack_min, hero->combat.attack_max, hero->combat.armor);
				}
				getchar();
				alive_goblins -= 1;
			}
			else
			{
				printf("The goblin #%i has %i hp left \n\n", goblin_attacked, defender_goblin->combat.hp);
				getchar();
			}
			
			//Here starts the goblins attack. We do a loop for each goblin, and if the active goblin is alive, we calculate the damage that deals to the hero, the same way we did with the hero attacking.
			int goblin_dmg = 0;
			int total_dmg = 0;
			for (int i = 0; i < alive_goblins; i++)
			{
				monster_data* active_goblin = goblins + i;
				if (active_goblin->combat.hp > 0)
				{
				goblin_dmg += ((active_goblin->combat.attack_min + rand() % active_goblin->combat.attack_max) - hero->combat.armor);
					int goblin_crit_chance = 1 + rand() % 100;
					if (goblin_crit_chance <= 5)
					{
						goblin_dmg += hero->combat.armor;
						goblin_dmg *= 3;
					}
					if (goblin_dmg <= 0)
					{
						goblin_dmg = 1;
					}
					total_dmg += goblin_dmg;
				}
			}
			hero->combat.hp -= total_dmg;
			
			//Now we check the different options. If the hero's hp is 0 or below, we print a message of his/her death, the coins and xp earned, and exit the loop. If its alive but there are alive goblins, we print a message and reestart the loop. If its alive but there are no goblins, it exits the loop.
			if (hero->combat.hp <= 0)
			{
				hero->combat.hp = 0;
				printf("The goblins have dealt %i dmg and finally killed you. You died with %i coins in the bag and %i points of exp (level %i) in wherever they are stored. Good luck in the afterlife %s \n\n", goblin_dmg, hero->coins, hero->xp, hero->level, hero->name);
				getchar();
				return;
			}
			else if (hero->combat.hp > 0 && alive_goblins > 0)
			{
				printf("The goblins have attacked you, dealing %i dmg, and leaving you with %i hp left \n\n", total_dmg, hero->combat.hp);
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

void hero_level_up(hero_data* hero)
{
	hero->combat.hp += 10 * hero->level;
	hero->combat.attack_min += 4 * hero->level;
	hero->combat.attack_max += 4 * hero->level;
	hero->level += 1;
}

void goblins_level_up(hero_data* hero, monster_data* goblins)
{
	goblins->combat.hp += 20 * hero->level;
	goblins->combat.attack_min += 10 * hero->level;
	goblins->combat.attack_max += 10 * hero->level;
	goblins->combat.armor += 1 * hero->level;
	goblins->coins += 10 * hero->level;
	goblins->xp += 2 * hero->level;
}

int ranger_hability(hero_data* hero, monster_data* goblins, int numofgoblins, int alive_goblins)
{
	int goblin_attacked = 1 + rand() % numofgoblins; //we decide which goblin we are going to attack. Since our first goblin declared is goblins[1], we add 1 to the random result.
	monster_data* defender_goblin = &goblins[goblin_attacked];
	if (defender_goblin->combat.hp != 0) //we check if the goblin attacked is alive (hp>0). If not, we just restart the cycle.
	{
		printf("Your hablilty targets the goblin #%i", goblin_attacked);
		int hero_dmg = (hero->combat.attack_min + rand() % hero->combat.attack_max);//we calculate the damage we are going to deal to the defender goblin and then substract it. if its negative or zero, due to the armor, we change it to one, cuz the gameplay.
		int hero_crit_chance = 1 + rand() % 100;
		if (hero_crit_chance <= 10)
		{
			hero_dmg += defender_goblin->combat.armor;
			hero_dmg *= 3;
		}
		if (hero_dmg <= 0)
		{
			hero_dmg = 1;
		}
		if (hero_crit_chance <= 5)
		{
			printf(" and your arrow finds its head ");
		}

		printf(" dealing %i dmg to him\n\n", hero_dmg);
		defender_goblin->combat.hp -= hero_dmg;

		if (defender_goblin->combat.hp <= 0)
		{
			defender_goblin->combat.hp = 0;
			hero->coins += defender_goblin->coins;
			hero->xp += defender_goblin->xp;
			printf("You killed goblin #%i and received %i coins and %i exp point from him\n\n", goblin_attacked, defender_goblin->coins, defender_goblin->xp);
			if (hero->xp >= hero->level * 100)
			{
				goblins_level_up(hero, goblins);
				hero_level_up(hero);
				printf("Your hero has leveled up and is now level %i!!! It's stats have increased, but watch out, the new goblins are thoughter than the previous ones.\nYour new hero stats are:\n\n", hero->level);
				getchar();
				printf("hp: %i\nattack_min: %i\nattack_max: %i\narmor: %i\n", hero->combat.hp, hero->combat.attack_min, hero->combat.attack_max, hero->combat.armor);
			}
			getchar();
			alive_goblins -= 1;
			return alive_goblins;

		}
		else
		{
			printf("The goblin #%i has %i hp left \n\n", goblin_attacked, defender_goblin->combat.hp);
			getchar();
			return alive_goblins;
		}

	}
}