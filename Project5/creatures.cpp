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
	hero->combat.crit_chance = 5;
	hero->level = 1;
	hero->coins = 0;
	hero->total_xp = 0; //there are two types of experience. It is made this way because if not, using the leveling up system, the player can arrive to a point where he levels up five times in a row, and he becomes invincible. 
	hero->level_xp = 0; //The level xp is used to calculate the next level, and the total xp is used to tell the player how much xp has earned.
}

void goblinstats_generator(monster_data * goblins, int numof)//We add 1 to each result to avoid goblins from dropping 0 coins or exp, or having goblins that insta-die.
{
	for (int i = 1; i <= numof; i++)
	{
		monster_data* active_goblin = goblins + i; //our first generated goblin will be the goblins[1], instead of goblins[0] because "You attack goblin #0" may sound strange to the player.
		active_goblin->combat.hp = 1 + rand() % 100;
		active_goblin->combat.attack_min = 1 + rand() % 9;
		active_goblin->combat.attack_max = 10 + rand() % 10;
		active_goblin->combat.armor = 1 + rand() % 5;
		active_goblin->combat.crit_chance = 5;
		active_goblin->coins = 1 + rand() % 20;
		active_goblin->xp = 1 + rand() % 10;
	}
}


void combat_loop(hero_data * hero, monster_data* goblins, int numofgoblins)
{
	int alive_goblins = numofgoblins;
	while (alive_goblins > 0)
	{
		int goblin_attacked = 1 + rand() % numofgoblins; //we decide which goblin we are going to attack. Since our first goblin declared is goblins[1], we add 1 to the random result.
		monster_data* defender_goblin = &goblins[goblin_attacked];
		if (defender_goblin->combat.hp != 0) //we check if the goblin attacked is alive (hp>0). If not, we just restart the cycle.
		{
			int paladin_hability = 0;
			int hero_crit_chance = 1 + rand() % 100;
			int hero_dmg = (hero->combat.attack_min + rand() % hero->combat.attack_max) - defender_goblin->combat.armor;//we calculate the damage we are going to deal to the defender goblin and then substract it. if its negative or zero, due to the armor, we change it to one, cuz the gameplay.
			
			if (hero_dmg < hero->combat.attack_min + (hero->combat.attack_max / 4) && hero->class_choosen == 2) //Check to see if the paladin hability triggers (Readme)
			{
				hero_dmg = hero->combat.attack_min + (hero->combat.attack_max / 4);
				int palandin_hability = 1;

			}
			if (hero_crit_chance <= hero->combat.crit_chance)
			{
				hero_dmg += defender_goblin->combat.armor; //The armor is ignored
				hero_dmg *= 3;
			}
			if (hero_dmg <= 0) //The attacks always will deal minimum 1 dmg.
			{
				hero_dmg = 1;
			}

			defender_goblin->combat.hp -= hero_dmg;

			printf("You attacked goblin #%i", goblin_attacked); //here we do the various printfs, including the special text if a critic or an hability is triggered.
			if (hero_crit_chance <= hero->combat.crit_chance)
			{
				printf(" with a critical hit");
			}
			if (paladin_hability == 1)
			{
				printf(", with the blessing of God,");
			}
			printf(" and dealt %i dmg to him\n\n", hero_dmg);
			
			//Now we check the different options. If the goblin's hp is o or below, we kill it and their coins and xp are added to the hero struct. If not, we just print a message.
			if (defender_goblin->combat.hp <= 0)
			{
				defender_goblin->combat.hp = 0;
				hero->coins += defender_goblin->coins;
				hero->level_xp += defender_goblin->xp;
				hero->total_xp += defender_goblin->xp;
				printf("You killed goblin #%i and received %i coins and %i exp point from him\n\n", goblin_attacked, defender_goblin->coins, defender_goblin->xp);
				if (hero->class_choosen == 3) //if the player is a Ranger, the hability triggers
				{
					alive_goblins = ranger_hability(hero, goblins, numofgoblins, alive_goblins);
					alive_goblins += 1;//This is what we could call a "chapuza". In order to make the hability work, we do a alive_goblins -=1 inside the hability funcion. Because there is another -=1 in the combat function, we need to counter the first -=1 with this.
				}
				if (hero->level_xp >= hero->level * 50)
				{
					hero->level_xp = 0;
					goblins_level_up(hero, goblins, numofgoblins);
					hero_level_up(hero);
					printf("Your hero has leveled up and is now level %i!!! It's stats have increased, but watch out, the new goblins are thoughter than the previous ones.\nYour new hero stats are:\n\n", hero->level);
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
			for (int i = 1; i <= numofgoblins; i++)
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
				printf("The goblins have dealt %i dmg and finally killed you. You died with %i coins in the bag and %i points of exp (level %i) in wherever they are stored. Good luck in the afterlife %s \n\n", total_dmg, hero->coins, hero->total_xp, hero->level, hero->name);
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

void goblins_level_up(hero_data* hero, monster_data* goblins, int numofgobs)
{
	for(int i = 1; i <= numofgobs; i++)
	{
		monster_data* active_goblin = goblins + i; 
		active_goblin->combat.hp += 15 * hero->level;
		active_goblin->combat.attack_min += 8 * hero->level;
		active_goblin->combat.attack_max += 8 * hero->level;
		active_goblin->combat.armor += 1 * hero->level;
	
		active_goblin->coins += 10 * hero->level;
		active_goblin->xp += 2 * hero->level;
	}
	
}

void class_stats_modifier(hero_data* hero) 
{
	switch (hero->class_choosen)
	{
	case 2:
		hero->combat.hp *= 1.25;
		hero->combat.attack_min *= 0.90;
		hero->combat.attack_max *= 0.90;
		break;
	case 3:
		hero->combat.armor *= 0.75;
		hero->combat.crit_chance += 5;
		break;
	default:
		break;
	}
}

int ranger_hability(hero_data* hero, monster_data* goblins, int numofgoblins, int alive_goblins) //This function makes the player attack again (ignoring armor, Readme), and returns the number of alive goblins, that may change if the hability kills another goblin.
{
	alive_goblins -= 1;
	while (alive_goblins > 0)
	{
		int goblin_attacked = 1 + rand() % numofgoblins; 
		monster_data* defender_goblin = &goblins[goblin_attacked];
		if (defender_goblin->combat.hp != 0) 
		{
			printf("Your hability targets the goblin #%i", goblin_attacked);
			int hero_dmg = (hero->combat.attack_min + rand() % hero->combat.attack_max);
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
				hero->level_xp += defender_goblin->xp;
				hero->total_xp += defender_goblin->xp;
				printf("You killed goblin #%i and received %i coins and %i exp point from him\n\n", goblin_attacked, defender_goblin->coins, defender_goblin->xp);
				if (hero->level_xp >= hero->level * 100)
				{
					hero->level_xp = 0;
					goblins_level_up(hero, goblins, numofgoblins);
					hero_level_up(hero);
					printf("Your hero has leveled up and is now level %i!!! It's stats have increased, but watch out, the new goblins are thoughter than the previous ones.\nYour new hero stats are:\n\n", hero->level);
					getchar();
					printf("hp: %i\nattack_min: %i\nattack_max: %i\narmor: %i\n", hero->combat.hp, hero->combat.attack_min, hero->combat.attack_max, hero->combat.armor);
				}
				alive_goblins -= 1;
				return alive_goblins;

			}
			else
			{
				printf("The goblin #%i has %i hp left \n\n", goblin_attacked, defender_goblin->combat.hp);
				return alive_goblins;
			}

		}
	}
}