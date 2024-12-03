#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int processMatch(const string& match) {
    regex numPattern(R"(\d+)");
    
    vector<int> numbers;
    sregex_iterator numIter(match.begin(), match.end(), numPattern);
    sregex_iterator end;
    
    while (numIter != end) {
        numbers.push_back(stoi(numIter->str()));
        ++numIter;
    }
    
    if (numbers.size() == 2) {
        int result = numbers[0] * numbers[1];
        return result;
    }
    
    return 0;
}

int main(int argc, char* argv[]) {

    ifstream inFile(argv[1]);


    regex pattern(R"(mul\(\d{1,3},\d{1,3}\))");
    string line;
    int count = 0;
    long long totalSum = 0;
    

    int lineNum = 0;

    while (getline(inFile, line)) {
        lineNum++;
        sregex_iterator iter(line.begin(), line.end(), pattern);
        sregex_iterator end;
        
        while (iter != end) {
            count++;
            string match = iter->str();
            totalSum += processMatch(match);
            ++iter;
        }
    }
    
    inFile.close();
    
   
    if (count == 0) {
        cout << "No matches found." << endl;
    } else {
        cout << totalSum << endl;
    }
    
    return 0;
}