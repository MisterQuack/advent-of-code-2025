#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const char kSpace = ' ';

void addCharacter(char character, int index, int column, std::vector<std::vector<std::string>>& columns) {
    std::vector<std::string> columnGroup(index + 1, "");
    if (columns.size() <= column) {
        std::vector<std::string> newColumn(index + 1, "");
        newColumn[index] += character;
        columns.push_back(newColumn);
    } 
    else {
        std::vector<std::string>& existingColumn = columns[column];
        if (existingColumn.size() <= index) existingColumn.resize(index + 1, "");
        existingColumn[index] += character;
    }
}

long long collectionAdded(std::vector<std::string>& values) {
    long long total = 0;
    for (int i = 0; i < values.size(); i++) if (values[i].size() > 0) total += std::stoll(values[i]);
    return total;
}

long long collectionMultiplied(std::vector<std::string>& values) {
    long long total = 1;
    for (int i = 1; i < values.size(); i++) if (values[i].size() > 0) total *= std::stoll(values[i]);
    return total;
}

int main() {
    std::ifstream infile("./input.txt");
    long long grandTotal = 0;
    std::vector<std::vector<std::string>> columns;
    
    std::string line;
    while(std::getline(infile, line)) {
        int columnCount = 0;

        char previousCharacter = kSpace;
        for (int charIndex = 0; charIndex < line.size(); charIndex++) {
            char currentCharacter = line[charIndex];
            if (currentCharacter == kSpace && currentCharacter != previousCharacter) columnCount++;
                        
            switch(currentCharacter) {
                case kSpace: break;
                case '+': grandTotal += collectionAdded(columns[columnCount]); break;
                case '*': grandTotal += collectionMultiplied(columns[columnCount]); break;
                default: addCharacter(currentCharacter, charIndex, columnCount, columns); break;
            }

            previousCharacter = currentCharacter;
        };
    }

    std::cout << "The grand total: " + std::to_string(grandTotal) << std::endl;
    return 0;
}

//          |
//         -+-
//          A
//         /=\               /\  /\    ___  _ __  _ __ __    __
//       i/ O \i            /  \/  \  / _ \| '__|| '__|\ \  / /
//       /=====\           / /\  /\ \|  __/| |   | |    \ \/ /
//       /  i  \           \ \ \/ / / \___/|_|   |_|     \  /
//     i/ O * O \i                                       / /
//     /=========\        __  __                        /_/    _
//     /  *   *  \        \ \/ /        /\  /\    __ _  ____  | |
//   i/ O   i   O \i       \  /   __   /  \/  \  / _` |/ ___\ |_|
//   /=============\       /  \  |__| / /\  /\ \| (_| |\___ \  _
//   /  O   i   O  \      /_/\_\      \ \ \/ / / \__,_|\____/ |_|
// i/ *   O   O   * \i
// /=================\
//        |___|
