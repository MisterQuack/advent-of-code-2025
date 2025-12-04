#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const char kPaperRoll = '@';
const char kEmpty = '.';

bool isOutOfBounds(int value, int max) {
    return value < 0 || value >= max;
}

bool isAccessible(int rowIndex, int positionIndex, std::vector<std::string>& grid) {
    int numberOfAdjacantRolls = 0;

    for (int rowShift = -1; rowShift <= 1; rowShift++) {
        int checkingRow = rowIndex + rowShift;

        if (!isOutOfBounds(checkingRow, grid.size())) {
            for (int posShift = -1; posShift <= 1; posShift++) {
                int checkingPos = positionIndex + posShift;
            
                if (!isOutOfBounds(checkingPos, grid[checkingRow].size()) && grid[checkingRow][checkingPos] == kPaperRoll) 
                    numberOfAdjacantRolls++;
            }
        }
    }

    return numberOfAdjacantRolls <= 4;
}

int main() {
    std::ifstream infile("./input.txt");

    std::vector<std::string> grid;
    std::string row;
    while (std::getline(infile, row)) grid.push_back(row);

    int totalAccessibleRollsCount = 0;
    int accessibleRollsInIterationCount = 0;
    do {
        std::vector<std::string> iterationGrid(grid);
        accessibleRollsInIterationCount = 0;
        for(int rowIndex = 0; rowIndex < grid.size(); rowIndex++) {
            std::string& row = grid[rowIndex];

            for (int position = 0; position <= row.length(); position++)
                if (row[position] == kPaperRoll && isAccessible(rowIndex, position, iterationGrid)) {
                    accessibleRollsInIterationCount++;
                    row[position] = kEmpty;
                }
        }

        totalAccessibleRollsCount += accessibleRollsInIterationCount;
    }
    while(accessibleRollsInIterationCount > 0);

    std::string answer = std::to_string(totalAccessibleRollsCount);
    std::cout << "Amount of accessible rolls for all iterations: " << answer << std::endl;
    return 0;
}
