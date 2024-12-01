#include "../inc/City.h"
#include "../inc/Human.h"
#include "../inc/Zombie.h"
#include <cstdlib>
#include <ctime>

// constructor: initializes the city grid with default values
// Constructor: initializes the city grid with default values
#include <cstdlib> // Include necessary header for rand()
#include <ctime> // Include header for time()

City::City() : generation(0), humanCount(0), zombieCount(0) {
    srand(time(0)); // Seed the random number generator with current time
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            grid[i][j] = '-'; // initialize all cells to empty
            starvationCounter[i][j] = 0; // initialize starvation counters to 0
            organismGrid[i][j] = nullptr; // initialize organism grid to null
        }
    }

    // Add initial humans and zombies only once
    for (int i = 0; i < 2; ++i) {
        int x, y;
        do {
            x = rand() % 20;
            y = rand() % 20;
        } while (grid[x][y] != '-');
        addHuman(x, y);
    }

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

// print: prints the current state of the city grid
void City::print() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "GENERATION " << generation << endl;
}

// method to add human at specific position
void City::addHuman(int x, int y) {
    if (isWithinBounds(x, y)) {
        grid[x][y] = 'H';
        organismGrid[x][y] = new Human(this, GRIDSIZE);
        humanCount++;
        // debug: print message when a human is added
        cout << "Human added at (" << x << ", " << y << ")\n";
    }
}

// method to add zombie at specific position
void City::addZombie(int x, int y) {
    if (isWithinBounds(x, y)) {
        grid[x][y] = 'Z';
        organismGrid[x][y] = new Zombie(this, GRIDSIZE);
        starvationCounter[x][y] = 0; // reset starvation counter for new zombie
        zombieCount++;
        // debug: print message when a zombie is added
        cout << "Zombie added at (" << x << ", " << y << ")\n";
    }
}

// move human from old position to new position
void City::moveHuman(int oldX, int oldY, int newX, int newY) {
    if (isWithinBounds(newX, newY) && grid[oldX][oldY] == 'H' && grid[newX][newY] == '-') {
        grid[newX][newY] = 'H';
        grid[oldX][oldY] = '-';
        organismGrid[newX][newY] = organismGrid[oldX][oldY];
        organismGrid[oldX][oldY] = nullptr;
    }
}

// move zombie from old position to new position
void City::moveZombie(int oldX, int oldY, int newX, int newY) {
    if (isWithinBounds(newX, newY) && grid[oldX][oldY] == 'Z' && grid[newX][newY] == '-') {
        grid[newX][newY] = 'Z';
        grid[oldX][oldY] = '-';
        starvationCounter[newX][newY] = starvationCounter[oldX][oldY]; // transfer starvation counter
        starvationCounter[oldX][oldY] = 0; // reset old position counter
        organismGrid[newX][newY] = organismGrid[oldX][oldY];
        organismGrid[oldX][oldY] = nullptr;
    }
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
            if (grid[i][j] == 'H') {
                bool nearZombie = false;
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        int checkX = i + x;
                        int checkY = j + y;
                        if (isWithinBounds(checkX, checkY) && grid[checkX][checkY] == 'Z') {
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
            if (grid[i][j] == 'Z') {
                bool nearHuman = false;
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        int checkX = i + x;
                        int checkY = j + y;
                        if (isWithinBounds(checkX, checkY) && grid[checkX][checkY] == 'H') {
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
            if (grid[i][j] == 'H') {
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
            if (grid[i][j] == 'Z') {
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        int newX = i + x;
                        int newY = j + y;
                        if (isWithinBounds(newX, newY) && grid[newX][newY] == 'H') {
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

// Perform starvation check for all zombies
void City::starveZombies() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (grid[i][j] == 'Z') {
                starvationCounter[i][j]++;
                if (starvationCounter[i][j] >= 5) { // if zombie hasn't eaten for 5 turns
                    grid[i][j] = '-'; // remove zombie
                    starvationCounter[i][j] = 0; // reset starvation counter
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
            if (grid[i][j] == 'H') humanCount++;
            if (grid[i][j] == 'Z') zombieCount++;
        }
    }
    if (humanCount == 0 || zombieCount == 0) {
        cout << "Extinction Level Event detected!" << endl;
    }
    printStats(); // print the statistics
}

// increment generation count
void City::incrementGeneration() {
    generation++;
}

// print statistics
void City::printStats() {
    cout << "Generation: " << generation << " | Humans: " << humanCount << " | Zombies: " << zombieCount << endl;
}

// print basic rules
void City::printRules() {
    cout << "Welcome to the Zombie Simulation!\n";
    cout << "Basic Rules:\n";
    cout << "1. Zombies and Humans move randomly around the grid.\n";
    cout << "2. Zombies will chase and try to convert Humans.\n";
    cout << "3. Humans will try to flee from Zombies.\n";
    cout << "4. If a zombie doesn't eat for 3 turns, it will die.\n";
    cout << "5. The simulation ends if either Humans or Zombies go extinct.\n";
    cout << "Enjoy the simulation!\n\n";
}

// simulation loop
void City::simulate() {
    printRules();

    while (humanCount > 0 && zombieCount > 0) {
        turnActions();
        resetMoveCounters();
        countEntitiesAndCheckELE();
        displayGrid();
        incrementGeneration();
    }

    cout << "Simulation ended after " << generation << " generations.\n";
}




// perform all actions each entity is capable of in the turn
void City::turnActions() {
    randomMove();
    runFromZombies();
    zombieChaseHuman();
    recruitHumans();
    convertHumans();
    starveZombies();
}

// reset all move counters to moved = false
void City::resetMoveCounters() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            Organism* organism = getOrganism(i, j);
            if (organism != nullptr) {
                organism->setMoved(false);
            }
        }
    }
}

// display the grid
void City::displayGrid() {
    print();
}
