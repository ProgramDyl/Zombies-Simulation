#include "../inc/City.h"

int main() {
    City city;
    city.addHuman(5, 5);
    city.addZombie(10, 10);
    city.addHuman(15, 15);
    city.addZombie(1, 1);

    // Print initial state
    city.print();
    city.printStats();

    //NOTE: set num of generations here
    for (int i = 0; i < 10; ++i) {
        city.runFromZombies();
        city.zombieChaseHuman();
        city.randomMove();
        city.recruitHumans();
        city.convertHumans();
        city.starveZombies();
        city.incrementGeneration();
        city.print(); // Print updated state after each step
        city.printStats(); // Print statistics after each step
    }

    return 0;
}
