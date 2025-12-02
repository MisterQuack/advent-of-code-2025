#include <iostream>
#include <fstream>
#include <string>
#include <vector> 


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
            bool isNormalId = true;

            // This is shit, but I'm super tired right now so fuck it
            for (int divisions = 2; divisions <= currentIdString.length(); divisions++) {
                if (currentIdString.length() % divisions != 0) continue;
                int partSize = currentIdString.length() / divisions;

                std::string currentPart = currentIdString.substr(0, partSize);
                bool normalId = false;

                for (int block = 1; block < divisions; block++) {                    
                    int partStart = partSize * block;
                    std::string nextPart = currentIdString.substr(partStart, partSize);

                    if (currentPart != nextPart) normalId = true;
                    currentPart = nextPart;
                }

                if (!normalId) isNormalId = false;
            }

            if (!isNormalId) answer += currentId;
        }
    }

    std::cout << "All invalid ID's added up: " + std::to_string(answer) << std::endl;
    return 0;
}
