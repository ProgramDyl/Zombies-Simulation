cmake_minimum_required(VERSION 3.10)
project(Zombies)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Add the executable for the main simulation
add_executable(Zombies src/City.cpp src/Human.cpp src/Zombie.cpp src/Organism.cpp src/main.cpp)

# Add the executables for the tests
add_executable(HumanTest test/HumanTest.cpp src/City.cpp src/Human.cpp src/Organism.cpp)
add_executable(ZombieTest test/ZombieTest.cpp src/City.cpp src/Zombie.cpp src/Human.cpp src/Organism.cpp)
