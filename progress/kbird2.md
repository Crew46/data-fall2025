=Weekly Progress=
Week 1
Enemy single linked list.
appendEnemyA(headEnemyA); and deleteEnemyA(headEnemyA); functions are currently up and running.
insertEnemyA works.




Week 2
lasers have been added.
collision has been added between lasers and enemies.
collision has been added between enemies and the player.
The game will end if the player is deactivated (by getting hit by an enemy)
bitmasking is being used to spawn enemies and to make a bigger max enemy limit. 
Respawning enemies have been added.



Week 3
Edge cases have been added for the head node and tail node. Addition of rmnode(). Addition of mknode(). The doubly linked list has been added. Restructured and changed 
a lot of names to make it more clear such as headEnemyA turning into enemyList. Fixed bugs that skipped an extra node.
head and tail now hold information and can be deleted and made again.



Week 4
EnemyB created and spawning. Randomized spawning for enemies with srand() and rand() being used to select which enemy is spawned. 
hp is now used to detect when an enemy is to be deactivated. Background was updated. New headers have been added for visuals, functions, and the Object struct.
Fixed append not actually appending to the end of the list.


Week 5
This week I added the general list functions that we agreed on. Which added mkList(), deleteList(), and clearList(). I also updated my previous obtain function to use double pointers to properly use the function! I modified the existing code to make use of these new functions. My Obtain function no longer uses rmnode inside of it. I also made sure that there are proper return values as well. Added some new checks.


Week 6
Stack is almost done. Most of the functions have been made. Push currently works, but needs some tweaks and pop needs to be ironed out a bit. Queues are still a WIP though. mkQueue and enqueue functions have been made, but they have not been tested. I did a little more organization such as moving node and list functions to node.h and linkedlist.h. There is also now a functions.h file for functions that have general uses that are not tied to specific thing.
