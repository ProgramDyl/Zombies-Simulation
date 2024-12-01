#include "../inc/Zombie.h"
#include "../inc/City.h"
#include "../inc/Human.h"
#include <vector>
#include <cstdlib>

// default constructor: initializes a zombie with default values and resets starve counter
Zombie::Zombie() : Organism(), starveCounter(0) {}

// parameterized constructor: initializes a zombie with given city and size, resets starve counter
Zombie::Zombie(City* city, const int size) : Organism(city, size), starveCounter(0) {}

// destructor: cleans up resources used by zombie
Zombie::~Zombie() {}

// turn: defines what actions the zombie takes during its turn
void Zombie::turn() {
    if (!moved) move(); // move if not already moved
    if (!moved) breed(); // attempt to breed if not moved
    starve(); // check if the zombie should starve and be removed
    moved = true; // mark as moved
}

// move: logic to move the zombie to an adjacent human or empty cell
void Zombie::move() {
    std::vector<std::pair<int, int>> adjacentCells;

    // find all valid adjacent cells
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // skip the current cell
            int newX = x + i;
            int newY = y + j;
            if (newX >= 0 && newX < GRIDSIZE && newY >= 0 && newY < GRIDSIZE) {
                adjacentCells.push_back(std::make_pair(newX, newY));
            }
        }
    }

    std::vector<std::pair<int, int>> humanCells;
    for (const auto& cell : adjacentCells) {
        if (city->getOrganism(cell.first, cell.second) != nullptr && city->getOrganism(cell.first, cell.second)->getType() == HUMAN_CH) {
            humanCells.push_back(cell); // collect cells with humans
        }
    }

    if (!humanCells.empty()) {
        std::pair<int, int> target = humanCells[rand() % humanCells.size()];
        city->setOrganism(this, target.first, target.second); // move to human cell and eat the human
        city->setOrganism(nullptr, x, y);
        x = target.first;
        y = target.second;
        starveCounter = 0; // reset starve counter after eating
    } else {
        std::vector<std::pair<int, int>> emptyCells;
        for (const auto& cell : adjacentCells) {
            if (city->getOrganism(cell.first, cell.second) == nullptr) {
                emptyCells.push_back(cell); // collect empty cells
            }
        }

        if (!emptyCells.empty()) {
            std::pair<int, int> target = emptyCells[rand() % emptyCells.size()];
            city->setOrganism(this, target.first, target.second); // move to an empty cell
            city->setOrganism(nullptr, x, y);
            x = target.first;
            y = target.second;
        }
    }

    moved = true; // mark as moved after moving
}

// breed: logic for converting humans into zombies
void Zombie::breed() {
    static int breedCounter = 0;
    breedCounter++;
    if (breedCounter >= 8) {
        breedCounter = 0;
        std::vector<std::pair<int, int>> humanCells;

        // find cells with humans around the zombie
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue; // skip the current cell
                int newX = x + i;
                int newY = y + j;
                if (newX >= 0 && newX < GRIDSIZE && newY >= 0 && newY < GRIDSIZE) {
                    if (city->getOrganism(newX, newY) != nullptr && city->getOrganism(newX, newY)->getType() == HUMAN_CH) {
                        humanCells.push_back(std::make_pair(newX, newY));
                    }
                }
            }
        }

        if (!humanCells.empty()) {
            std::pair<int, int> target = humanCells[rand() % humanCells.size()];
            city->setOrganism(new Zombie(city, GRIDSIZE), target.first, target.second); // convert human to zombie
        }
    }
}

// starve: logic for removing starving zombies
void Zombie::starve() {
    starveCounter++;
    if (starveCounter >= 5) { //5 humans until extinct
        city->setOrganism(nullptr, x, y); // remove starving zombie
    }
}
