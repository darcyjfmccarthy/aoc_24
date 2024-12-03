#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

long long calculateTotalDistance(vector<int>& left, vector<int>& right) {

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    
    long long totalDistance = 0;
    
    for (size_t i = 0; i < left.size(); i++) {
        totalDistance += abs(left[i] - right[i]);
    }
    
    return totalDistance;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file.txt>" << endl;
        return 1;
    }

    ifstream inFile(argv[1]);
    if (!inFile) {
        cout << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }

    vector<int> leftList, rightList;
    string line;
    
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        
        istringstream iss(line);
        int left, right;
        
        if (iss >> left >> right) {
            leftList.push_back(left);
            rightList.push_back(right);
        }
    }
    
    inFile.close();

    
    long long result = calculateTotalDistance(leftList, rightList);
    cout << result << endl;
    
    return 0;
}