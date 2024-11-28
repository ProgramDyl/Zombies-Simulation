#include <iostream>
#include "../inc/City.h"
#include "../inc/Human.h"
#include "../inc/GameSpecs.h"
#include <cassert> // for assert function

void testHumanMovement() {
    City city;
    Human* human = new Human(&city, GRIDSIZE);
    city.setOrganism(human, 10, 10);

    // Store original position
    int originalX = 10;
    int originalY = 10;

    // Move the human
    human->turn();

    // Check new position is within grid and different from original if move was made
    int newX = human->x;
    int newY = human->y;
    assert(newX >= 0 && newX < GRIDSIZE);
    assert(newY >= 0 && newY < GRIDSIZE);
    assert(newX != originalX || newY != originalY);

    std::cout << "Human movement test passed.\n";
}

void testHumanRecruit() {
    City city;
    Human* human = new Human(&city, GRIDSIZE);
    city.setOrganism(human, 10, 10);

    // Simulate turns to trigger recruitment
    for (int i = 0; i < 3; ++i) {
        human->turn();
        human->setMoved(false); // Reset move flag for manual turn call
    }

    // Check if new human is recruited
    bool recruited = false;
    for (int i = 9; i <= 11; ++i) {
        for (int j = 9; j <= 11; ++j) {
            if (i == 10 && j == 10) continue;
            if (city.getOrganism(i, j) != nullptr && city.getOrganism(i, j)->getType() == HUMAN_CH) {
                recruited = true;
                break;
            }
        }
    }
    assert(recruited);

    std::cout << "Human recruit test passed.\n";
}

int main() {
    testHumanMovement();
    testHumanRecruit();
    return 0;
}
