#include "../inc/Organism.h"

#include "../inc/GameSpecs.h"

#include "../inc/City.h"

Organism::Organism() : x(0), y(0), size(GRIDSIZE), moved(false), city(nullptr) {}

Organism::Organism(City* city, const int size) : x(0), y(0), size(size), moved(false), city(city) {}

Organism::~Organism() = default;

ostream& operator<<(ostream& output, const Organism* organism) {
    output << organism->getChar();
    return output;
}
