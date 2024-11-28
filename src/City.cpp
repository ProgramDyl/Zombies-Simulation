#include "../inc/City.h"
#include "../inc/Human.h"
#include "../inc/Zombie.h"
#include "../inc/GameSpecs.h"

// Constructor: initializes the city grid and generation counter
City::City() : generation(0) {
    // Set all grid positions to nullptr (empty)
    for (int i = 0; i < GRIDSIZE; ++i) {
        for (int j = 0; j < GRIDSIZE; ++j) {
            grid[i][j] = nullptr;
        }
    }
}

// Destructor: deallocates memory used by the grid organisms
City::~City() {
    // Delete all organisms in the grid
    for (int i = 0; i < GRIDSIZE; ++i) {
        for (int j = 0; j < GRIDSIZE; ++j) {
            delete grid[i][j];
        }
    }
}

// Returns the organism at position (x, y) if within bounds, else nullptr
Organism* City::getOrganism(int x, int y) {
    if (x >= 0 && x < GRIDSIZE && y >= 0 && y < GRIDSIZE) {
        return grid[x][y];
    }
    return nullptr;
}

// Sets an organism at position (x, y) if within bounds
void City::setOrganism(Organism* organism, int x, int y) {
    if (x >= 0 && x < GRIDSIZE && y >= 0 && y < GRIDSIZE) {
        grid[x][y] = organism;
    }
}

// Executes a step in the simulation, updating all organisms' states
void City::step() {
    // Iterate through the grid and update each organism that hasn't moved
    for (int i = 0; i < GRIDSIZE; ++i) {
        for (int j = 0; j < GRIDSIZE; ++j) {
            if (grid[i][j] != nullptr && !grid[i][j]->getMoved()) {
                grid[i][j]->turn();
            }
        }
    }
    generation++; // Increment generation count
}

// Resets the moved status of all organisms in the grid
void City::reset() {
    // Iterate through the grid and reset each organism's moved status
    for (int i = 0; i < GRIDSIZE; ++i) {
        for (int j = 0; j < GRIDSIZE; ++j) {
            if (grid[i][j] != nullptr) {
                grid[i][j]->setMoved(false);
            }
        }
    }
}

// Counts the number of organisms of a specific type in the grid
int City::countType(char type) {
    int count = 0;
    // Iterate through the grid and count organisms of the specified type
    for (int i = 0; i < GRIDSIZE; ++i) {
        for (int j = 0; j < GRIDSIZE; ++j) {
            if (grid[i][j] != nullptr && grid[i][j]->getType() == type) {
                ++count;
            }
        }
    }
    return count;
}

// Checks if there is both human and zombie diversity in the city
bool City::hasDiversity() {
    return (countType(HUMAN_CH) > 0) && (countType(ZOMBIE_CH) > 0);
}

// Overloads the << operator to print the city grid
ostream& operator<<(ostream& output, City& city) {
    // Iterate through the grid and output each position
    for (int i = 0; i < GRIDSIZE; ++i) {
        for (int j = 0; j < GRIDSIZE; ++j) {
            if (city.grid[i][j] != nullptr) {
                output << city.grid[i][j]->getChar() << ' ';
            } else {
                output << "- ";
            }
        }
        output << endl;
    }
    return output;
}

// Placeholder for color logic in the future
void City::col(int c) {
    // TODO: Implement color logic for printing
}
