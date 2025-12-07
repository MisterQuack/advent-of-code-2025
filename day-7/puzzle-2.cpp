#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


const std::string kStarter = "S";
const char kEmptySpace = '.';
const char kSplitter = '^';

bool is_numeric(const std::string& string) {
    return std::all_of(string.begin(), string.end(), ::isdigit);
}

std::string addTogether(std::string sValueOne, std::string sValueTwo) {
    long long valueOne = std::stoll(sValueOne);
    long long valueTwo = std::stoll(sValueTwo);
    return std::to_string(valueOne + valueTwo);
}

int main() {
    std::ifstream infile("./input.txt");
    long long totalSplits = 0;

    std::string line;
    std::vector<std::vector<std::string>> manifold;
    while(std::getline(infile, line)) {
        int currentRow = manifold.size();

        std::vector<std::string> newLine(line.size() , "0");
        for (int charIndex = 0; charIndex < line.size(); charIndex++) {            
            char character = line[charIndex];
            
            if (currentRow == 0) {
                if (character == 'S') newLine[charIndex] = std::string(1, character);
                continue;
            }

            std::string valueAbove = manifold[currentRow - 1][charIndex];
            switch(line[charIndex]) {
                case kEmptySpace:
                    if (is_numeric(valueAbove)) 
                        newLine[charIndex] = addTogether(valueAbove, newLine[charIndex]);
                    else if (valueAbove == kStarter) newLine[charIndex] = "1";
                    break;
                case kSplitter:
                    if (is_numeric(valueAbove)) {
                        newLine[charIndex] = "^";
                        newLine[charIndex - 1] = addTogether(valueAbove, newLine[charIndex - 1]);
                        newLine[charIndex + 1] = addTogether(valueAbove, newLine[charIndex + 1]);
                    }
                    break;
            }
        }
        manifold.push_back(newLine);
    }

    int lastRow = manifold.size() - 1;
    for (int charIndex = 0; charIndex < manifold[lastRow].size(); charIndex++) {
        totalSplits+= std::stoll(manifold[lastRow][charIndex]);
    }

    std::cout << "Amount of timelines: " + std::to_string(totalSplits) << std::endl;

    return 0;
}
