=Weekly Progress=
**Week 1** - Worked on everything in main until we start to modularize our code. I Added a doublylinkedlist that holds nodes which hold objects. I made a bunch of helper functions for the linked list, nodes, and objects. I created functions to detect when an enemy exceeds bounds so we can deallocate the memory. I created a function that takes two objects and checks if they collide. In the collision function I added padding so the collision detection is less sensitive.

**Week 2** Still working in the main.c file for now. I reworked linked list functions so you can now append and insert anywhere in the list rather than just at the beginning and end.

**Week 3** Refactored code so that there are substructs that hold object pointers rather than keeping everything in object.

**Week 4** Added player ability shoot and added collision between the bullets and enemies. I also cleaned up my main function by separating all my game logic functions into an updateGame() function and all my rendering functions into a renderGame() function and then calling those two functions in main.

**Week 6** Added in Queue and Stack on top of list with functions. The stack and queue aren't used yet, but they compile. I also separated my main file into a bunch of separate header files to clean things up.

**Week 8** Added in status flags, I only added the ISACTIVE flag for now but it is a start. I also moved all of the deletion of objects to the update functions and in the other functions where an object was deleted, I set its ISACTIVE flag off.
