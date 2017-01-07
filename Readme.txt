Own Rules of my RPG fighter.

This is a brief annotation of some mechanics that may not seem to obvious. This should be explained in a tutorial if the game had one.


How damage works: I just realized that my calculation of the damage (min_dmg + a random number of max_dmg), is a bit counterintuitive, due to the real max damage being (min_dmg+max_dmg).
		 It isn't really incorrect, but it can lead to misunderstanding to the player.

Both player and monsters have critical chance, that is included in the combat struct. Actually, it's initialized as 5% and deals x3 times the normal damage.
When a critic hits, it ignores the armor of the objective. This is done by adding to the normal damage calculated, the armor previously substracted.

The player gains xp when a round finishes.

There are two classes which have modified stats. These stats are modified after the player has selected its stats, and work by percentages.

Paladin (class no.2): Divine guidance: Once the damage is calculated, if it's too low (min_dmg + a quarter of the max dmg), its increased to (min_dmg + a quarter of the max dmg).

Ranger (Class no.3): Piercing shot: If the player kills an enemy, he has an extra attack to another random goblin. 
		This second attack, ignores armor, but cannot trigger the hability again (tested it, turned out to be too OP).
