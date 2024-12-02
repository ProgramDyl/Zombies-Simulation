#include <chrono>
#include <thread>
#include "../inc/City.h"

int main() {
    City city;
    for (int i = 0; i < 100; ++i) { // Initialize 100 humans
        int x, y;
        do {
            x = rand() % 20;
            y = rand() % 20;
        } while (city.getOrganism(x, y) != nullptr);
        city.addHuman(x, y);
    }
    for (int i = 0; i < 5; ++i) { // Initialize 5 zombies
        int x, y;
        do {
            x = rand() % 20;
            y = rand() % 20;
        } while (city.getOrganism(x, y) != nullptr);
        city.addZombie(x, y);
    }

    city.printRules();
    std::cout << city;
    city.printStats();

    // Simulation loop for at least 100 iterations or until extinction event
    for (int i = 0; i < 100; ++i) {
        std::cout << "Starting generation " << i + 1 << std::endl;
        city.runFromZombies();
        city.zombieChaseHuman();
        city.randomMove();
        city.recruitHumans();
        city.convertHumans();
        city.starveZombies();
        city.incrementGeneration();

        std::cout << city;
        city.printStats();
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (city.getHumanCount() == 0 || city.getZombieCount() == 0) {
            std::cout << "Extinction event occurred." << std::endl;
            break;
        }
    }

    std::cout << "Simulation ended after " << city.getGeneration() << " generations." << std::endl;

    return 0;
}
