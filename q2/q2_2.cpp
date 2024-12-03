#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

bool safeReport(const vector<int>& levels) {
    if (levels.size() < 2) return true;

    bool increasing = levels[1] > levels[0];

    for (size_t i = 1; i < levels.size(); i++) {
        int diff = levels[i] - levels[i-1];

        if (abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }

        if (increasing && diff < 0) {
            return false;
        }

        if (!increasing && diff > 0) {
            return false;
        }
    }

    return true;
}

bool checkSmallerReports(const vector<int>& levels) {
    if (safeReport(levels)) return true;
    

    for (size_t i = 0; i < levels.size(); i++) {
        vector<int> modified = levels;
        modified.erase(modified.begin() + i);
        
        if (safeReport(modified)) return true;
    }
    
    return false;
}

int main(int argc, char* argv[]) {
    ifstream inFile(argv[1]);

    string line;
    int safeCount = 0;
    int totalReports = 0;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        vector<int> levels;
        istringstream iss(line);
        int(level);

        while (iss >> level) {
            levels.push_back(level);
        }
        
        if (checkSmallerReports(levels)) {
            safeCount++;
        }
    }

    inFile.close();

    cout << safeCount << endl;
}