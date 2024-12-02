#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "../inc/Organism.h"
#include "../inc/GameSpecs.h"

class Zombie : public Organism
{
private:
    int starveCounter;

public:
    Zombie();
    Zombie(City *city, int size);
    ~Zombie() override;

    void turn() override; // inherited from pure virtual func. in Organism

    void move();
    void breed() const;
    void starve();

    char getType() const override { return ZOMBIE_CH; }
    char getChar() const override { return ZOMBIE_CH; }
};

#endif
