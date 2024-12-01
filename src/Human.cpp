#include "../inc/Human.h"
#include "../inc/City.h"
#include <vector>
#include <cstdlib>

// default constructor: initializes a human with default values and resets recruit counter
Human::Human() : Organism(), recruitCounter(0) {}

// parameterized constructor: initializes a human with given city and size, resets recruit counter
Human::Human(City* city, int size) : Organism(city, size), recruitCounter(0) {}

// destructor: cleans up resources used by human
Human::~Human() {}

// turn: defines what actions the human takes during its turn
void Human::turn() {
    if (!moved) move(); // move if not already moved
    if (!moved) recruit(); // attempt to recruit if not moved
    moved = true; // mark as moved
}

// move: logic to move the human to an adjacent empty cell
void Human::move() {
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

    std::vector<std::pair<int, int>> emptyCells;
    for (const auto& cell : adjacentCells) {
        if (city->getOrganism(cell.first, cell.second) == nullptr) {
            emptyCells.push_back(cell); // collect empty cells
        }
    }

    if (!emptyCells.empty()) {
        std::pair<int, int> target = emptyCells[rand() % emptyCells.size()];
        city->setOrganism(this, target.first, target.second);
        city->setOrganism(nullptr, x, y);
        x = target.first;
        y = target.second;
        moved = true; // mark as moved after moving
    }
}

// recruit: logic for recruiting new humans into the grid
void Human::recruit() {
    recruitCounter++;
    if (recruitCounter >= 3) {
        recruitCounter = 0;
        std::vector<std::pair<int, int>> emptyCells;

        // find empty cells around the human
        for (int i = x - 1; i <= x + 1; ++i) {
            for (int j = y - 1; j <= y + 1; ++j) {
                if (i >= 0 && i < GRIDSIZE && j >= 0 && j < GRIDSIZE && city->getOrganism(i, j) == nullptr) {
                    emptyCells.push_back(std::make_pair(i, j));
                }
            }
        }

        if (!emptyCells.empty()) {
            std::pair<int, int> target = emptyCells[rand() % emptyCells.size()];
            city->setOrganism(new Human(city, GRIDSIZE), target.first, target.second); // place new human
        }
    }
}
