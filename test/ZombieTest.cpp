#include <iostream>
#include "../inc/City.h"
#include "../inc/Human.h"
#include "../inc/Zombie.h"
#include "../inc/GameSpecs.h"
#include <cassert> // for assert function

void testZombieMovement() {
    City city;
    Zombie* zombie = new Zombie(&city, GRIDSIZE);
    city.setOrganism(zombie, 10, 10);

    // Store original position
    int originalX = 10;
    int originalY = 10;

    // Move the zombie
    zombie->turn();

    // Check new position is within grid and different from original if move was made
    int newX = zombie->x;
    int newY = zombie->y;
    assert(newX >= 0 && newX < GRIDSIZE);
    assert(newY >= 0 && newY < GRIDSIZE);
    assert(newX != originalX || newY != originalY);

    std::cout << "Zombie movement test passed.\n";
}

void testZombieFeeding() {
    City city;
    Zombie* zombie = new Zombie(&city, GRIDSIZE);
    Human* human = new Human(&city, GRIDSIZE);
    city.setOrganism(zombie, 10, 10);
    city.setOrganism(human, 9, 9);

    // Simulate turns to allow zombie to eat the human
    for (int i = 0; i < 3; ++i) {
        zombie->turn();
        zombie->setMoved(false); // Reset move flag for manual turn call
    }

    // Check if human has been eaten
    assert(city.getOrganism(9, 9) == nullptr || city.getOrganism(9, 9)->getType() == ZOMBIE_CH);

    std::cout << "Zombie feeding test passed.\n";
}

int main() {
    testZombieMovement();
    testZombieFeeding();
    return 0;
}
