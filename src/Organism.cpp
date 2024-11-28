#include "../inc/Organism.h"
#include "../inc/City.h"

Organism::Organism() : x(0), y(0), size(GRIDSIZE), moved(false), city(nullptr) {}

Organism::Organism(City* city, int size) : x(0), y(0), size(size), moved(false), city(city) {}

Organism::~Organism() {}

ostream& operator<<(ostream& output, Organism* organism) {
    output << organism->getChar();
    return output;
}
