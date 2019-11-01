/*
 * common.cpp
 *
 *  Created on: Oct 22, 2019
 *      Author: poorie
 */

#include <stdio.h>
#include <ctype.h>
#include <climits>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <set>

using namespace std;

class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
    	//Sanitize the input paragraph
    	string sanitizedParagraph = "\0";
    	for(size_t i = 0; i < paragraph.length(); i++) {
    		if((isalpha(paragraph[i]) != 0) || (isspace(paragraph[i]) != 0)) {
    			sanitizedParagraph += tolower(paragraph[i]);
    		}
    	}
    	cout << "Sanitized Input: " << sanitizedParagraph << endl;

    	//Special boolean if we found the last word i.e. no more spaces
    	bool lastWord = false;
    	//pointer to the paragraph starting at 0
    	unsigned int startIndex = 0;
    	size_t posOfSpace = sanitizedParagraph.find(" ");
    	// A map to store <string, number of times it appears>
    	map<string, int> wMap;
    	//Travel the length of the paragraph until the end of line is reached
    	while(0 != posOfSpace) {
    		string input = sanitizedParagraph.substr(startIndex);
    		//cout << "Input: " << input << endl;
    		posOfSpace = input.find(" ");
    		string substring;
    		if(posOfSpace == std::string::npos) {
    			posOfSpace = 0;
    			substring = input.substr(0);
    			lastWord = true;
    		} else {
        		//cout << "Position of next space: " << posOfSpace << endl;
        		substring = input.substr(0, posOfSpace);
    		}
    		cout << substring << endl;
  			wMap[substring] += 1;
  			startIndex += posOfSpace + 1;
  			//cout << "Start index: " << startIndex << endl;

  			if(lastWord)
  				break;
    	}

    	//banned list goes to a set
    	set<string> bannedSet(banned.begin(), banned.end());

    	int maxTimes = INT_MIN;
    	string maxWord = "\0";
    	for(auto i = wMap.begin(); i != wMap.end(); i++){
    		if((i->second > maxTimes) && (bannedSet.find(i->first) == bannedSet.end())) {
    			maxTimes = i->second;
    			maxWord = i->first;
    		}
    	}

    	return maxWord;
    }
};

struct TestCase {
	string paragraphInput;
	vector<string> bannedInput;
	string expectedOutput;
};

int main() {

	const int testCaseCount = 1;
	TestCase* testCases[testCaseCount] = {
			new TestCase { "Bob hit a ball, the hit BALL flew far after it was hit.", {"hit"}, "ball" }
	};

	//Solution
	Solution result;
	for (int i = 0; i < testCaseCount; i++) {
		cout << "Test #: " << i+1  << endl;
		cout << "Input string: " << testCases[i]->paragraphInput << endl;
		string output = result.mostCommonWord(testCases[i]->paragraphInput, testCases[i]->bannedInput);
		cout << "Output string: " << output << endl;
		cout << "Test: " << ((output.compare(testCases[i]->expectedOutput) == 0) ? "PASS" : "FAIL") << endl << endl;
	}

	return 0;
}
