#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

long long calculateSimilarityScore(const vector<int>& left, const vector<int>& right) {

    unordered_map<int, int> rightFreq;
    for (int num : right) {
        rightFreq[num]++;
    }
    
    long long totalScore = 0;
    for (int num : left) {
        totalScore += (long long)num * rightFreq[num];
    }
    
    return totalScore;
}

int main(int argc, char* argv[]) {

    ifstream inFile(argv[1]);

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
    
    long long score = calculateSimilarityScore(leftList, rightList);
    cout << score << endl;

    
    return 0;
}