#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

const char kRangeDelimiter = '-';

typedef struct {
    long long min; 
    long long max;
} RANGE;

RANGE createRange(std::string& line, long long delimiterPos) {
    RANGE range;
    range.min = std::stoll(line.substr(0, delimiterPos));
    range.max = std::stoll(line.substr(delimiterPos + 1, line.length()));
    return range;
}

int main() {
    std::ifstream infile("./input.txt");
    long long numberOfFreshIds = 0;
    
    std::string line;
    std::vector<RANGE> ranges;

    while(std::getline(infile, line)) {
        int delimiterPos = line.find(kRangeDelimiter);
        if (delimiterPos > 0) ranges.push_back(createRange(line, delimiterPos));
    }
    
    std::sort(ranges.begin(), ranges.end(), [](const RANGE& a, const RANGE& b) {
        return a.min < b.min;
    });

    std::vector<RANGE> merged;
    for (const RANGE& range : ranges) {
        if (merged.empty() || range.min > merged.back().max) merged.push_back(range);
        else if (range.max > merged.back().max) merged.back().max = range.max;
    }

    for (int i = 0; i < merged.size(); i++)
        numberOfFreshIds += 1ULL + merged[i].max - merged[i].min;
    
    std::string answer = std::to_string(numberOfFreshIds);
    std::cout << "Number of fresh ingredients ID's: " + answer << std::endl;

    return 0;
}
