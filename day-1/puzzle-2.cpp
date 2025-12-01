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

        int offset = currentPosition + steps;
        if (offset <= 0) offset = ((-offset) + (currentPosition == 0 ? 0 : 100));

        zeroCount += (offset / 100);

        currentPosition = (currentPosition + steps) % 100;
        if (currentPosition < 0) currentPosition = 100 + currentPosition;
    }

    std::cout << "Amount of times the dial pointed or passed zero: " + std::to_string(zeroCount) << std::endl;
    return 0;
}
