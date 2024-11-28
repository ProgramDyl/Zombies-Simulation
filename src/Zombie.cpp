#include "../inc/Zombie.h"
#include "../inc/City.h"

Zombie::Zombie() : Organism(), starveCounter(0) {}

Zombie::Zombie(City* city, int size) : Organism(city, size), starveCounter(0) {}

Zombie::~Zombie() {}

void Zombie::turn() {
    move();
    starve();
}

void Zombie::move() {
    // Example move logic: Move to an empty adjacent cell or towards a human if adjacent
    int newX = x + (rand() % 3) - 1;
    int newY = y + (rand() % 3) - 1;

    if (newX >= 0 && newX < GRIDSIZE && newY >= 0 && newY < GRIDSIZE && city->getOrganism(newX, newY) == nullptr) {
        city->setOrganism(this, newX, newY);
        city->setOrganism(nullptr, x, y);
        x = newX;
        y = newY;
        moved = true;
    }
}

void Zombie::starve() {
    // Example starve logic
    starveCounter++;
    if (starveCounter >= 3) {
        // Logic to remove the Zombie if it starves
        city->setOrganism(nullptr, x, y);
        delete this;
    }
}
