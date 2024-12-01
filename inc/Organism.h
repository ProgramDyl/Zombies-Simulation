#ifndef _Organism_H
#define _Organism_H

#include <iostream>
using namespace std;

class City;

class Organism
{
public:
    int x;
    int y;
    int size;
    bool moved;
    City *city;

public:
    Organism();
    Organism(City *city, int size);
    virtual ~Organism();
    virtual void turn() = 0;

    bool getMoved() const { return moved; }
    void setMoved(const bool moved) { this->moved = moved; }

    friend ostream& operator<<(ostream &output, const Organism *organism);
    virtual char getType() const = 0; // Added pure virtual function to get organism type
    virtual char getChar() const = 0; // Added pure virtual function to get ASCII character
};

#endif
