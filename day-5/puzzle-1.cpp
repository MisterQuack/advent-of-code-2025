#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const char kRangeDelimiter = '-';

typedef struct {
    long long min; 
    long long max;
} RANGE;

bool inRange(long long num, RANGE range) {
    return range.min <= num && num <= range.max;
}

bool inAnyRange(long long num, std::vector<RANGE> ranges) {
    for (int i = 0; i < ranges.size(); i++) 
        if (inRange(num, ranges[i])) return true;
    return false;
}

RANGE createRange(std::string& line, long long delimiterPos) {
    RANGE range;
    range.min = std::stoll(line.substr(0, delimiterPos));
    range.max = std::stoll(line.substr(delimiterPos + 1, line.length()));
    return range; 
}

int main() {
    std::ifstream infile("./input.txt");
    int numberOfFreshItems = 0;
    
    std::string line;
    std::vector<RANGE> ranges;

    while(std::getline(infile, line)) {
        int delimiterPos = line.find(kRangeDelimiter);
        if (delimiterPos > 0) ranges.push_back(createRange(line, delimiterPos));
        else if (line != "") {
            if (inAnyRange(std::stoll(line), ranges)) numberOfFreshItems++;
        }
    }

    std::string answer = std::to_string(numberOfFreshItems);
    std::cout << "Number of fresh ingredients: " + answer << std::endl;

    return 0;
}
