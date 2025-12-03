#include <iostream>
#include <fstream>
#include <string>
#include <math.h>


int main() {
    std::ifstream infile("./input.txt");

    long long totalJoltageOutput = 0;
    const int maxBankSize = 12;

    std::string bank;
    while (std::getline(infile, bank)) {        
        int highestJoltageBatteries[maxBankSize] = {0};

        for (int index = 0; index < bank.length(); index++) {
            int currentNumber = bank[index] - '0';
            int numbersLeft = bank.length() - index;

            int earliestPositionInBank = maxBankSize - numbersLeft;
            if (earliestPositionInBank < 0) earliestPositionInBank = 0;

            int usedNumber = false;
            for (int bankIndex = earliestPositionInBank; bankIndex < maxBankSize; bankIndex++ ) {
                if (usedNumber) {
                    highestJoltageBatteries[bankIndex] = 1;
                }
                else if (currentNumber > highestJoltageBatteries[bankIndex]) {
                    highestJoltageBatteries[bankIndex] = currentNumber;
                    usedNumber = true;
                }
            }
        }

        long long maxJoltage = 0;
        for (int i = 0; i < maxBankSize; i++) {
            int exponent = maxBankSize - (i + 1);
            maxJoltage += highestJoltageBatteries[i] * pow(10, exponent);
        }

        totalJoltageOutput += maxJoltage;
    }

    std::string answer = std::to_string(totalJoltageOutput);
    std::cout << "The total output joltage is: " + answer << std::endl;

    return 0;
}
