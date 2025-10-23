=Weekly Progress=

***

**week 3** : 
Currently trying to fit things together into main. I have done some small changes to linked list, adding proper removal functions and checking edge cases. I also have made an effort to expand general functionality with the `object` struct, like a generic draw function. And I reintroduced a laser type to handle all of the projectiles. My next goal is to integrate weapons with players and lasers with weapons.

**week 4** :
I have been able to get weapons and lasers integrated into the player and working with the linked list structure. This week I've been fitting things together and fixing some bugs. The most important thing I added was a status for objects. This allows many different important flags about an object to be stored in a single value. Currently it only has a active flag, mark for deleting flag, and a couple bits for the team it is on. This will be the backbone of many different logical functions of the game, like collision/damage. The next thing I need to do add the ability for objects to be on 0 teams, including the different facing directions.

**week 5** :
I have been working on team functionality. To make everything nice, I changed spites that might need to be rotated to have their hotspot in the center. As well as adding a offset to the Weapon relative to the player based on the direction. Now I am trying to get main ready for collisions and damage. I've made a simple collision check, which was also simplified by placing the hotspot in the center. I'm hoping on getting that together and functioning soon.

**week 6**
This week I mainly switched main over to use the new unified object, node, and list that was made. They still need some more features like a collision box and some more utility functions, but main does compile. Next week is were I plan to add back collision, which should be quicker now that I've done it before. I also want to add more features like picking up/dropping weapons. I will also be making my own implementation of stacks and queues.

**week 7**
I've have attempted to create queues and stacks, but I still need to test them. Currently I'm trying and failing to use queues so that the player can have multiple weapons at the same time. I've stumbled upon a weird major bug while doing this, and now I'm trying to find the root cause. Once I've done so I can start working on making main into more of a game and less of a demo, with enemies and a start screen.

**break week 1**
I've made some small progress this week, mainly updating the player/weapon system. I implemented queues to store weapons in the player, and fixed small bugs as they appeared. I also contributed to Haas' splitting of computation by separating out the rendering code from the object update functions and create a simple function to draw any desired list of objects

**week 8**
This week I added some simple enemy AI to the game, complimenting Haas' efforts to make a playable game. The AI currently is quite primitive; enemies lock onto the closest target and fire once in range. There are plenty of improvements left of make, like more natural targeting and movement, and changing it so they don't just fly downward into the endless void. A large portion of my time was spent debugging the C compiler to fix the most niche of and easily avoidable edge cases.