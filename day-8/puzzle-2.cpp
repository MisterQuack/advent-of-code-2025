#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

const char kValueSeperator = ',';

std::vector<std::vector<std::string>> circuits;

typedef struct {
    std::string line;
    long long x;
    long long y;
    long long z;
} JUNCTION_BOX;

typedef struct {
    long long distance;
    JUNCTION_BOX pointA;
    JUNCTION_BOX pointB;
} EDGE;

JUNCTION_BOX createBox(std::string line) {
    JUNCTION_BOX box;
    box.line = line;
    box.x = std::stoll(line.substr(0, line.find(kValueSeperator)));

    std::string secondPart = line.substr(line.find(kValueSeperator) + 1);
    box.y = std::stoll(secondPart.substr(0, secondPart.find(kValueSeperator)));
    box.z = std::stoll(secondPart.substr(secondPart.find(kValueSeperator) + 1));
    return box;
}

long long getDistance(JUNCTION_BOX& box1, JUNCTION_BOX& box2) {
    return pow(box1.x - box2.x, 2) + pow(box1.y - box2.y, 2) + pow(box1.z - box2.z, 2);
}

EDGE createEdge(JUNCTION_BOX& boxA, JUNCTION_BOX& boxB) {
    EDGE edge;
    edge.pointA = boxA;
    edge.pointB = boxB;
    edge.distance = getDistance(boxA, boxB);
    return edge;
}

int getCircuitIndex(std::string line) {
    for (int i = 0; i < circuits.size(); i++)
        if(std::find(circuits[i].begin(), circuits[i].end(), line) != circuits[i].end())
            return i;
    return -1;
}

void joinCircuits(int index1, int index2) {
    circuits[index1].insert(circuits[index1].end(), circuits[index2].begin(), circuits[index2].end());
    circuits.erase(circuits.begin() + index2);
}

void createCircuit(std::string pointA, std::string pointB) {
    std::vector<std::string> newCircuit = { pointA, pointB };
    circuits.push_back(newCircuit);
}

int main() {
    std::ifstream infile("./input.txt");

    std::vector<JUNCTION_BOX> boxes;
    std::map<long long, EDGE> edges;
    long long answer = 0;

    std::string line;
    while(std::getline(infile, line)) boxes.push_back(createBox(line));

    for (int boxA = 0; boxA < boxes.size(); boxA++) {
        circuits.push_back({ boxes[boxA].line });
        for (int boxB = boxA + 1; boxB < boxes.size(); boxB++) {
            EDGE newEdge = createEdge(boxes[boxA], boxes[boxB]);
            edges[newEdge.distance] = newEdge; 
        }
    }

    for (auto& entry : edges) {
        EDGE& edge = entry.second;
        
        int circuitA = getCircuitIndex(edge.pointA.line);
        int circuitB = getCircuitIndex(edge.pointB.line);

        switch(circuitA) {
            case -1: 
                if (circuitB == -1) createCircuit(edge.pointA.line, edge.pointB.line);
                else circuits[circuitB].push_back(edge.pointA.line);
                break;
            default:
                if (circuitB == -1) circuits[circuitA].push_back(edge.pointB.line);
                else if(circuitA != circuitB) joinCircuits(circuitA, circuitB);
        }

        if (circuits.size() == 1 && circuits[0].size() == boxes.size()) {
            answer = edge.pointA.x * edge.pointB.x;
            break;
        }
    }

    std::cout << "Distance from the wall: " + std::to_string(answer) << std::endl;
    return 0;
}
