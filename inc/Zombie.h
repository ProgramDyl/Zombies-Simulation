#ifndef _ZOMBIE_H
#define _ZOMBIE_H

#include "../inc/Organism.h"
#include "../inc/GameSpecs.h"

class Zombie : public Organism
{
private:
    int starveCounter;

public:
    Zombie();
    Zombie(City *city, int size);
    virtual ~Zombie();

    void turn() override; // Implement Zombie's turn logic
    void move();
    void starve();

    char getType() const override { return ZOMBIE_CH; }
    char getChar() const override { return ZOMBIE_CH; }
};

#endif
