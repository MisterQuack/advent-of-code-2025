#include <iostream>
#include <fstream>
#include <string>


int main() {
    std::ifstream infile("./input.txt");

    int totalJoltageOutput = 0;

    std::string bank;
    while (std::getline(infile, bank)) {
        int firstHighestNumber = 0;
        int secondHighestNumber = 0;
        
        for (int index = 0; index < bank.length(); index++) {
            int currentNumber = bank[index] - '0';
            int nextIndex = index + 1;

            if (currentNumber > secondHighestNumber) {
                secondHighestNumber = currentNumber;
            }

            if (currentNumber > firstHighestNumber && nextIndex < bank.length()) {
                firstHighestNumber = currentNumber;
                secondHighestNumber = bank[nextIndex] - '0';
            }
        }

        int maxJoltage = (firstHighestNumber * 10) + secondHighestNumber;
        totalJoltageOutput += maxJoltage;
    }

    std::string answer = std::to_string(totalJoltageOutput);
    std::cout << "The total output joltage is: " + answer << std::endl;

    return 0;
}

