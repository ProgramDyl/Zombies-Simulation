#include <iostream>
#include <chrono>
#include <thread>
#include "../inc/City.h"
#include "../inc/GameSpecs.h"

using namespace std;

void ClearScreen() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int main() {
    const auto city = new City();
    const chrono::milliseconds interval(INTERVAL);

    while (city->hasDiversity()) {
        this_thread::sleep_for(interval);
        ClearScreen();
        city->step();
        city->reset();
        cout << *city;
        cout << "GENERATION " << city->getGeneration() << endl;
        cout << "HUMANS: " << city->countType(HUMAN_CH) << endl;
        cout << "ZOMBIES: " << city->countType(ZOMBIE_CH) << endl;
    }

    delete city;
    return 0;
}
