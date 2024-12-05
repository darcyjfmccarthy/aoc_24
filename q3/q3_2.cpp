#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

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


    string line;
    int count = 0;
    long long totalSum = 0;
    

    int lineNum = 0;
    while (getline(inFile, line)) {
        bool enabled = true;
        size_t pos = 0;
        
        while (pos < line.length()) {

            size_t doPos = line.find("do()", pos);
            size_t dontPos = line.find("don't()", pos);
            size_t mulPos = line.find("mul(", pos);
            
            // Find the earliest one
            size_t nextPos = string::npos;
            if (doPos != string::npos) nextPos = min(nextPos, doPos);
            if (dontPos != string::npos) nextPos = min(nextPos, dontPos);
            if (mulPos != string::npos) nextPos = min(nextPos, mulPos);
            
            if (nextPos == string::npos) break;
            
            if (nextPos == doPos) {
                enabled = true;
                pos = doPos + 4; 
            }
            else if (nextPos == dontPos) {
                enabled = false;
                pos = dontPos + 6; 
            }
            else if (nextPos == mulPos) {
            
                size_t closePos = line.find(')', mulPos);
                if (closePos != string::npos) {
                    string mulExpr = line.substr(mulPos, closePos - mulPos + 1);
                
                    regex mulPattern(R"(mul\(\d{1,3},\d{1,2}\))");
                    if (regex_match(mulExpr, mulPattern)) {
                        if (enabled) {
                            count++;
                            totalSum += processMatch(mulExpr);
                        } 
                    }
                    pos = closePos + 1;
                } else {
                    pos = mulPos + 1;
                }
            }
        }
    }
    
    
    inFile.close();
    
    if (count == 0) {
        cout << "No enabled multiplications found." << endl;
    } else {
        cout << totalSum << endl;
    }
    
    return 0;
}