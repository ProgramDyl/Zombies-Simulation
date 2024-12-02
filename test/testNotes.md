# TEST RESULTS:


## TEST 1
#### (10 generations)

--------------------------------------RESULTS:--------------------------------------

    // - The humans and zombies interact, but both populations dwindle too fast.
    // - Neither H or Z is dispersing adequately, movement tuning required.





## TEST 2
#### (15 generations)


 **WHAT CHANGED**
 - set init addHumans to random 
 - same with zombies.
 - They both start in random places


--------------------------------------RESULTS:--------------------------------------

     1. random placement of Z and H is better. They start a
       little more evenly distributed.

     2. Humans still gathering in the top left corner too much.
     3. Zombies are barely converting humans, which makes too many humans.

     4. **_ELE:_** Zombies extinct by gen #5



## TEST 3

    **WHAT CHANGED:** 
 - When a zombie moves to space occupied by human, the human
   is converted to zombie or, "infected"
 - Increased threshold of the human recruit counter to 5. 
 - Increased threshold for zombie starvation

--------------------------------------RESULTS:--------------------------------------

    1. Humans and zombies interacting as intended. Humans still staying in
      place without moving. More constraints are required, so maybe humans
      can't stay in place for more than 3 turns. I also forgot to restrict 
      the human's movement to North South East West. So I will implement that
      for test #4. 
    2. Zombie needs to infect human, and needs to move in all 8 directions. 

## TEST 4
#### (15 generations)

     **WHAT CHANGED**
     - Zombie movement (8 directions)
     - zombie infects human (in zombie move method)
      - uses getType to collect all the cells with humans in it. 
        - if human cell is NOT empty,
          - uses get to remove human, places a new zombie. 
          - moves to target cell, leaves current cell. 
          - resets
      - Human recruit is slowed down to 5 
      - zombie survival increased (duration before starve)


--------------------------------------RESULTS:--------------------------------------

    1. 
    2.
    3. 