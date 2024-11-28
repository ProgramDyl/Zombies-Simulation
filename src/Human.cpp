#include "../inc/Human.h"
#include "../inc/City.h"

// Default Constructor: Initializes a Human with default values and resets recruitCounter
Human::Human() : Organism(), recruitCounter(0) {}

// Parameterized Constructor: Initializes a Human with given city and size, resets recruitCounter
Human::Human(City* city, int size) : Organism(city, size), recruitCounter(0) {}

// Destructor: Cleans up resources used by Human
Human::~Human() {}

// Turn: Defines what actions the Human takes during its turn
void Human::turn() {
    move();
    recruit();
}

// Move: Logic to move the Human to an adjacent empty cell
void Human::move() {
    // Calculate new X position
    int newX = x + (rand() % 3) - 1;
    // Calculate new Y position
    int newY = y + (rand() % 3) - 1;

    // Check if new position is within grid bounds and empty
    if (newX >= 0 && newX < GRIDSIZE && newY >= 0 && newY < GRIDSIZE && city->getOrganism(newX, newY) == nullptr) {
        // Move Human to new position
        city->setOrganism(this, newX, newY);
        // Clear old position
        city->setOrganism(nullptr, x, y);

        //human's position
        x = newX;
        y = newY;
        moved = true;
    }
}

// Recruit: Logic for recruiting new Humans into the grid
void Human::recruit() {
    recruitCounter++;
    if (recruitCounter >= 3) {
        recruitCounter = 0;
        // Check surrounding cells for an empty position to place a new Human
        for (int i = x - 1; i <= x + 1; ++i) {
            for (int j = y - 1; j <= y + 1; ++j) {
                if (i >= 0 && i < GRIDSIZE && j >= 0 && j < GRIDSIZE && city->getOrganism(i, j) == nullptr) {
                    city->setOrganism(new Human(city, GRIDSIZE), i, j); // Place new Human
                    return; // Exit once a new Human is placed
                }
            }
        }
    }
}
