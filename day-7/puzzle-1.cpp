#include <iostream>
#include <fstream>
#include <string>
#include <vector>


const char kStarter = 'S';
const char kEmptySpace = '.';
const char kSplitter = '^';
const char kBeam = '|';

int main() {
    std::ifstream infile("./input.txt");
    long long totalSplits = 0;

    std::string line;
    std::vector<std::string> manifold;
    while(std::getline(infile, line)) {
        int currentRow = manifold.size();
        int previousRow = currentRow - 1;

        if (currentRow == 0) {
            manifold.push_back(line);
            continue;
        }
        
        for (int charIndex = 0; charIndex < line.size(); charIndex++) {
            char charAbove = manifold[previousRow][charIndex];
            switch(line[charIndex]) {
                case kEmptySpace:
                    if (charAbove == kBeam || charAbove == kStarter)
                        line[charIndex] = kBeam; 
                    break;
                case kSplitter:
                    if (charAbove == kBeam) {
                        line[charIndex - 1] = kBeam;
                        line[charIndex + 1] = kBeam;
                        totalSplits++;
                    } 
                    break;
            }
        }

        manifold.push_back(line);
    }

    std::cout << "Times the beam has been split: " + std::to_string(totalSplits) << std::endl;
    return 0;
}