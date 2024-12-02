#include <chrono>
#include <thread>
#include "../inc/City.h"

int main() {
    City city;
    city.addHuman(5, 5);
    city.addZombie(10, 10);
    city.addHuman(15, 15);
    city.addZombie(1, 1);

    city.printRules();

    // Print initial state
    std::cout << city;
    city.printStats();

    // NOTE: set number of generations here
    for (int i = 0; i < 30; ++i) {
        std::cout << "Starting generation " << i + 1 << std::endl;
        city.runFromZombies();
        city.zombieChaseHuman();
        city.randomMove();
        city.recruitHumans();
        city.convertHumans();
        city.starveZombies();
        city.incrementGeneration();

        std::cout << city; // Print city using overloaded operator
        city.printStats();

        // pause execution to simulate time passage
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
