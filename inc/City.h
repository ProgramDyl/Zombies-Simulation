#ifndef _CITY_H
#define _CITY_H

#include <iostream>
#include "../inc/GameSpecs.h"
using namespace std;

class Organism;

class City
{
protected:
    Organism *grid[GRIDSIZE][GRIDSIZE];
    int generation;

public:
    City();
    virtual ~City();

    Organism *getOrganism(int x, int y);
    void setOrganism(Organism *organism, int x, int y);

    void step();
    void reset();
    int countType(char type);
    bool hasDiversity();

    int getGeneration() const { return generation; }

    friend ostream& operator<<(ostream &output, City &city);

    void col(int c); // For colors
};

#endif
