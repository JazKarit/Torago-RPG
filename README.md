# Torago-RPG
Basic RPG where the player can level up, and equip and use items. 
Has a scrolling ASCII map and some a few different kinds of enemies.

Game Controls:

Use WASD or type North, South, East, or West to move.
Each move takes time based on the kind of tile you move on.
The passage of time wears down stamina and hydration, if either of these stats hits zero, you die.
Each tile also has different chances of meeting the different enemies.
Finally, you have a radius of visibility around you based on the tile you are on and the time of day.

Cities (+) can be visited to spend gold won from enemies.
You can buy armor for head, chest, and legs as well as a sword and shield.
You can also get food to boost stamina and water bottles to quench thirst (they can be refilled at the river).
You can also buy health potions.
You can sell stuff back to the shop for 80% of what you bought it for.
You also have a max carrying capacity that grows as you level up.

Battles happen when you encounter an enemy while traveling or resting.
You get the choice to attack, rest, or flee.
Attacking deals your attack stat plus the attack from your sword minus the defense of the enemy.
Resting heals a little hp and a good amount of stamina.
Fleeing is sometimes unsuccesful and can open you up to be attacked.
Attacking and fleeing both take stamina.

Things to Play With:

Change the map in maps.txt, or make a new map following the same format (See tiles.txt for the tile codes).
Change tile enemy encounter chances and add tiles in tiles.txt.
Change enemy stats or add enemies in enemies.txt.
Add items or edit existing items in items.txt.
Change starting player stats in player.txt.
Add any new items to some of the cities in cities.txt.
