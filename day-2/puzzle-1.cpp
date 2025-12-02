#include <iostream>
#include <fstream>
#include <string>


int main() {
    std::ifstream infile("./input.txt");

    char delimiter = ',';
    std::string range;
    
    long long answer = 0;
    while (std::getline(infile, range, delimiter)) {
        int seperatorPos = range.find('-');
        
        long long start = std::stoll(range.substr(0, seperatorPos));
        long long end = std::stoll(range.substr(seperatorPos + 1));

        for (long long currentId = start; currentId <= end; currentId++) {
            std::string currentIdString = std::to_string(currentId);
            if (currentIdString.length() % 2 != 0) continue;

            int half = currentIdString.length() / 2;            

            std::string firstPart = currentIdString.substr(0, half);
            std::string secondPart = currentIdString.substr(half, currentIdString.length());

            if (firstPart == secondPart) answer += currentId;
        }
    }

    std::cout << "All invalid ID's added up: " + std::to_string(answer) << std::endl;
    return 0;
}
