#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const char kPaperRoll = '@';

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

    int accessibleRollsCount = 0;

    for(int rowIndex = 0; rowIndex < grid.size(); rowIndex++) {
        std::string& row = grid[rowIndex];

        for (int position = 0; position <= row.length(); position++)
            if (row[position] == kPaperRoll && isAccessible(rowIndex, position, grid)) accessibleRollsCount++;
    }

    std::string answer = std::to_string(accessibleRollsCount);
    std::cout << "Amount of accessible rolls: " << answer << std::endl;
    return 0;
}
