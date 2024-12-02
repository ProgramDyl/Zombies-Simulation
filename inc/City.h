#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <vector>
#include "Organism.h"

class City {
public:
    City();
    void simulate();
    void print();
    void addHuman(int x, int y);
    void addZombie(int x, int y);
    void moveHuman(int oldX, int oldY, int newX, int newY);
    void moveZombie(int oldX, int oldY, int newX, int newY);
    void randomMove();
    void runFromZombies();
    void zombieChaseHuman();
    void recruitHumans();
    void convertHumans();
    void starveZombies();

    void countEntitiesAndCheckELE();
    void incrementGeneration();
    void printStats();
    void printRules();
    void turnActions();
    void resetMoveCounters();
    void displayGrid();

    Organism* getOrganism(int x, int y);
    void setOrganism(Organism* organism, int x, int y);

    friend std::ostream& operator<<(std::ostream& os, const City& city);

private:
    char grid[20][20];
    Organism* organismGrid[20][20]; // To store Organism pointers
    int starvationCounter[20][20];
    int generation;
    int humanCount;
    int zombieCount;

    bool isWithinBounds(int x, int y);
};

#endif
