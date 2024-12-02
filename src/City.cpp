#include "../inc/City.h"
#include "../inc/Human.h"
#include "../inc/Zombie.h"
#include "../inc/GameSpecs.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

// constructor: initializes the city grid with default values
City::City() : generation(0), humanCount(0), zombieCount(0) {
    srand(time(0)); // Seed the random number generator with current time
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            grid[i][j] = '-'; // empty grid
            starvationCounter[i][j] = 0;
            organismGrid[i][j] = nullptr;
        }
    }

    // add init humans once
    for (int i = 0; i < 2; ++i) {
        int x, y;
        do {
            x = rand() % 20;
            y = rand() % 20;
        } while (grid[x][y] != '-');
        addHuman(x, y);
    }
    // add init zombies once
    for (int i = 0; i < 2; ++i) {
        int x, y;
        do {
            x = rand() % 20;
            y = rand() % 20;
        } while (grid[x][y] != '-');
        addZombie(x, y);
    }
}

// check if coordinates are within bounds
bool City::isWithinBounds(int x, int y) {
    return x >= 0 && x < 20 && y >= 0 && y < 20;
}

// get organism at specific position
Organism* City::getOrganism(int x, int y) {
    if (isWithinBounds(x, y)) {
        return organismGrid[x][y];
    }
    return nullptr;
}

// set organism at specific position
void City::setOrganism(Organism* organism, int x, int y) {
    if (isWithinBounds(x, y)) {
        organismGrid[x][y] = organism;
    }
}


// method to add human at specific position
void City::addHuman(int x, int y) {
    if (isWithinBounds(x, y)) {
        grid[x][y] = HUMAN_CH;
        organismGrid[x][y] = new Human(this, GRIDSIZE);
        humanCount++;
    }
}

// method to add zombie at specific position
void City::addZombie(int x, int y) {
    if (isWithinBounds(x, y)) {
        grid[x][y] = ZOMBIE_CH;
        organismGrid[x][y] = new Zombie(this, GRIDSIZE);
        starvationCounter[x][y] = 0; // reset starvation counter for new zombie
        zombieCount++;
    }
}

// move human from old position to new position
void City::moveHuman(int oldX, int oldY, int newX, int newY) {
    if (isWithinBounds(newX, newY) && grid[oldX][oldY] == HUMAN_CH && grid[newX][newY] == '-') {
        grid[newX][newY] = HUMAN_CH;
        grid[oldX][oldY] = '-';
        organismGrid[newX][newY] = organismGrid[oldX][oldY];
        organismGrid[oldX][oldY] = nullptr;
    }
}

// move zombie from old position to new position
void City::moveZombie(int oldX, int oldY, int newX, int newY) {
    if (isWithinBounds(newX, newY) && grid[oldX][oldY] == ZOMBIE_CH && grid[newX][newY] == '-') {
        grid[newX][newY] = ZOMBIE_CH;
        grid[oldX][oldY] = '-';
        starvationCounter[newX][newY] = starvationCounter[oldX][oldY]; // transfer
        starvationCounter[oldX][oldY] = 0; // reset old
        organismGrid[newX][newY] = organismGrid[oldX][oldY];
        organismGrid[oldX][oldY] = nullptr;
    }
}

// perform random movement for all humans and zombies
void City::randomMove() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            Organism* organism = getOrganism(i, j);
            if (organism != nullptr && !organism->getMoved()) {
                organism->turn();
            }
        }
    }
}

// move humans away from zombies
void City::runFromZombies() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (grid[i][j] == HUMAN_CH) {
                bool nearZombie = false;
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        int checkX = i + x;
                        int checkY = j + y;
                        if (isWithinBounds(checkX, checkY) && grid[checkX][checkY] == ZOMBIE_CH) {
                            nearZombie = true;
                        }
                    }
                }
                if (nearZombie) {
                    int newX = i + (rand() % 3) - 1;
                    int newY = j + (rand() % 3) - 1;
                    if (isWithinBounds(newX, newY) && grid[newX][newY] == '-') {
                        moveHuman(i, j, newX, newY);
                    }
                }
            }
        }
    }
}

// move zombies towards humans
void City::zombieChaseHuman() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (grid[i][j] == ZOMBIE_CH) {
                bool nearHuman = false;
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        int checkX = i + x;
                        int checkY = j + y;
                        if (isWithinBounds(checkX, checkY) && grid[checkX][checkY] == HUMAN_CH) {
                            nearHuman = true;
                        }
                    }
                }
                if (nearHuman) {
                    int newX = i + (rand() % 3) - 1;
                    int newY = j + (rand() % 3) - 1;
                    if (isWithinBounds(newX, newY) && grid[newX][newY] == '-') {
                        moveZombie(i, j, newX, newY);
                    }
                }
            }
        }
    }
}

// perform recruitment for all humans
void City::recruitHumans() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (grid[i][j] == HUMAN_CH) {
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        int newX = i + x;
                        int newY = j + y;
                        if (isWithinBounds(newX, newY) && grid[newX][newY] == '-') {
                            addHuman(newX, newY); // add new human
                            return; // only recruit one new human per turn
                        }
                    }
                }
            }
        }
    }
}

// perform conversion for all zombies
void City::convertHumans() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (grid[i][j] == ZOMBIE_CH) {
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        int newX = i + x;
                        int newY = j + y;
                        if (isWithinBounds(newX, newY) && grid[newX][newY] == HUMAN_CH) {
                            addZombie(newX, newY); // convert human to zombie
                            humanCount--;
                            return; // only convert one human per turn
                        }
                    }
                }
            }
        }
    }
}

// perform starvation check for all zombies
void City::starveZombies() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (grid[i][j] == ZOMBIE_CH) {
                starvationCounter[i][j]++;
                if (starvationCounter[i][j] >= 5) { // if zombie hasn't eaten for 5 turns
                    std::cout << "Zombie at (" << i << ", " << j << ") starved" << std::endl;
                    grid[i][j] = '-'; // remove zombie
                    starvationCounter[i][j] = 0; // reset starvation counter
                    delete organismGrid[i][j];
                    organismGrid[i][j] = nullptr;
                    zombieCount--;
                }
            }
        }
    }
}

// check the board, count humans and zombies, and check for extinction level event (ELE)
void City::countEntitiesAndCheckELE() {
    humanCount = 0;
    zombieCount = 0;
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (grid[i][j] == HUMAN_CH) humanCount++;
            if (grid[i][j] == ZOMBIE_CH) zombieCount++;
        }
    }
    if (humanCount == 0 || zombieCount == 0) {
        std::cout << "Extinction Level Event detected!" << std::endl;
    }
    printStats();
}

// increment generation count
void City::incrementGeneration() {
    generation++;
}

// print statistics
void City::printStats() {
    std::cout << "Generation: " << generation << " | Humans: " << humanCount << " | Zombies: " << zombieCount << std::endl;
}

// print the city grid with colors
std::ostream& operator<<(std::ostream& output, const City& city) {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (city.grid[i][j] == HUMAN_CH) {
                output << HUMAN_COLOR << HUMAN_CH << ' ';
            } else if (city.grid[i][j] == ZOMBIE_CH) {
                output << ZOMBIE_COLOR << ZOMBIE_CH << ' ';
            } else {
                output << DASH_COLOR << SPACE_CH << ' ';
            }
        }
        output << std::endl;
    }
    output << "GENERATION " << city.generation << std::endl;
    return output;
}

// print basic rules
void City::printRules() {
    std::cout << "Welcome to the Zombie Simulation!\n";
    std::cout << "Basic Rules:\n";
    std::cout << "1. Zombies and Humans move randomly around the grid.\n";
    std::cout << "2. Zombies will chase and try to convert Humans.\n";
    std::cout << "3. Humans will try to flee from Zombies.\n";
    std::cout << "4. If a zombie doesn't eat for 3 turns, it will die.\n";
    std::cout << "5. The simulation ends if either Humans or Zombies go extinct.\n";
    std::cout << "Enjoy the simulation!\n\n";
}

// simulation loop
void City::simulate() {
    printRules();

    while (true) { // change to infinite loop for debugging
        std::cout << "Generation " << generation << " - Humans: " << humanCount << " - Zombies: " << zombieCount << std::endl;

        turnActions();
        resetMoveCounters();
        countEntitiesAndCheckELE();
        displayGrid();
        incrementGeneration();

        std::cout << "After increment: Generation " << generation << " - Humans: " << humanCount << " - Zombies: " << zombieCount << std::endl;

        // Exit condition: ensure it's properly working
        if (humanCount == 0 || zombieCount == 0) {
            std::cout << "Exiting loop: Generation " << generation << " - Humans: " << humanCount << " - Zombies: " << zombieCount << std::endl;
            break;
        }

        // Pause execution to simulate time passage
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Simulation ended after " << generation << " generations.\n";
}

// perform all actions each entity is capable of in the turn
void City::turnActions() {
    std::cout << "Running turn actions" << std::endl;
    randomMove();
    runFromZombies();
    zombieChaseHuman();
    recruitHumans();
    convertHumans();
    starveZombies();
    std::cout << "Completed turn actions" << std::endl;
}

// display the grid
void City::displayGrid() {
    std::cout << *this;
}

// reset all move counters to moved = false
void City::resetMoveCounters() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            Organism* organism = getOrganism(i, j);
            if (organism != nullptr) {
                organism->setMoved(false); // reset moved flag to false
            }
        }
    }
}
