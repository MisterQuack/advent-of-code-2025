#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const char* kWhiteSpace = " \t\n\r\f\v";

std::string& trim(std::string& string) {
    string.erase(string.find_last_not_of(kWhiteSpace) + 1);
    return string.erase(0, string.find_first_not_of(kWhiteSpace));
}

void addValue(std::string& value, int column, std::vector<std::vector<std::string>>& columns) {
    if (columns.size() > column) columns[column].push_back(value);
    else columns.push_back({value});
}

long long collectionAdded(std::vector<std::string>& values) {
    long long total = 0;
    for (int i = 0; i < values.size(); i++) total += std::stoll(values[i]);
    return total;
}

long long collectionMultiplied(std::vector<std::string>& values) {
    long long total = std::stoll(values[0]);
    for (int i = 1; i < values.size(); i++) total *= std::stoll(values[i]);
    return total;
}

int main() {
    std::ifstream infile("./input.txt");
    long long grandTotal = 0;
    std::vector<std::vector<std::string>> columns;
    
    std::string line;
    while(std::getline(infile, line)) {
        int columnCount = 0;

        line = trim(line);
        while (line.size() > 0) {
            int firstWhiteSpace = line.find_first_of(kWhiteSpace);
            if (firstWhiteSpace < 0) firstWhiteSpace = line.size();

            std::string value = line.substr(0, firstWhiteSpace);
            line = trim(line.substr(firstWhiteSpace));

            switch(value[0]) {
                case '+': grandTotal += collectionAdded(columns[columnCount]); break;
                case '*': grandTotal += collectionMultiplied(columns[columnCount]); break;
                default: addValue(value, columnCount, columns); break;
            }

            columnCount++;
        };
    }

    std::cout << "The grand total: " + std::to_string(grandTotal) << std::endl;
    return 0;
}
