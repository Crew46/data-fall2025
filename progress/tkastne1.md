=Weekly Progress=

***

**week 3** : 
Currently trying to fit things together into main. I have done some small changes to linked list, adding proper removal functions and checking edge cases. I also have made an effort to expand general functionality with the `object` struct, like a generic draw function. And I reintroduced a laser type to handle all of the projectiles. My next goal is to integrate weapons with players and lasers with weapons.

**week 4** :
I have been able to get weapons and lasers integrated into the player and working with the linked list structure. This week I've been fitting things together and fixing some bugs. The most important thing I added was a status for objects. This allows many different important flags about an object to be stored in a single value. Currently it only has a active flag, mark for deleting flag, and a couple bits for the team it is on. This will be the backbone of many different logical functions of the game, like collision/damage. The next thing I need to do add the ability for objects to be on 0 teams, including the different facing directions.