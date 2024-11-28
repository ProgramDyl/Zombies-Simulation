#ifndef _HUMAN_H
#define _HUMAN_H

#include "../inc/Organism.h"
#include "../inc/GameSpecs.h"

class Human : public Organism
{
private:
    int recruitCounter;

public:
    Human();
    Human(City *city, int size);
    virtual ~Human();

    void turn() override; // Implement Human's turn logic
    void move();
    void recruit();

    char getType() const override { return HUMAN_CH; }
    char getChar() const override { return HUMAN_CH; }
};

#endif
