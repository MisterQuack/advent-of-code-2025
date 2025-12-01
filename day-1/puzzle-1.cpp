#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream infile("./input.txt");

    int currentPosition = 50;
    int zeroCount = 0;

    char direction;
    int steps;
    while (infile >> direction >> steps) {
        if (direction == 'L') steps = steps * -1;

        currentPosition = (currentPosition + steps) % 100;
        if (currentPosition < 0) currentPosition = 100 + currentPosition;

        if (currentPosition == 0) zeroCount++;
    }

    std::cout << "Amount of times the dial pointed at zero: " + std::to_string(zeroCount) << std::endl;
    return 0;
}
