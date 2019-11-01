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

    	//Need a map to store <string word, int number of times the word appears>
    	map<string,int> wMap;

    	//Need a position for next non alphabet
    	size_t posOfNonAlphabet = paragraph.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

    	//Need a position for next alphabet
    	size_t posOfAlphabet = 0;

    	//Need a string to hold the substring to process over and over again
    	string shorterParagraph;

    	//Return value
    	string maxWord = "\0";

    	cout << "Position of non alphabet: " << posOfNonAlphabet << endl;
    	while(0 != posOfNonAlphabet) {
    		//Newer shorter string to process
    		posOfAlphabet = paragraph.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    		if(posOfAlphabet == std::string::npos) {
    			break;
    		}
    		shorterParagraph = paragraph.substr(posOfAlphabet);
    		cout << "Shorter paragraph: " << shorterParagraph << endl;
    		//Find where the first word in shorterParagraph ends
    		posOfNonAlphabet = shorterParagraph.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    		//Storage for the word
    		string word;
    		//Find the last word - posOfNonAlphabet is not found.
    		if(posOfNonAlphabet == std::string::npos) {
    			posOfNonAlphabet = 0;
    			word = shorterParagraph.substr(0);
    		} else {
    			word = shorterParagraph.substr(0, posOfNonAlphabet);
    		}
    		cout << "Word: " << word << endl;
    		//if ((word != "\0") || (word != " ")) what the heck is that last word now
    		for (std::string::size_type i=0; i< word.length(); ++i)
    			word[i] = tolower(word[i]);
    		cout << "Word: " << word << endl;
    		wMap[word] += 1;
    		paragraph = paragraph.substr(posOfNonAlphabet + 1);
    	}

    	//Banned list goes to a set, cos unique entries and the find operation becomes O(1)
    	set<string> bannedSet(banned.begin(), banned.end());

    	int maxTimes = INT_MIN;
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

	const int testCaseCount = 3;
	TestCase* testCases[testCaseCount] = {
			new TestCase { "Bob hit a ball, the hit BALL flew far after it was hit.", {"hit"}, "ball" },
			new TestCase { "a, a, a, a, b,b,b,c, c", {"a"}, "b" },
			new TestCase { "L, P! X! C; u! P? w! P. G, S? l? X? D. w? m? f? v, x? i. z; x' m! U' M! j? V; l. S! j? r, K. O? k? p? p, H! t! z' X! v. u; F, h; s? X? K. y, Y! L; q! y? j, o? D' y? F' Z; E? W; W' W! n! p' U. N; w? V' y! Q; J, o! T? g? o! N' M? X? w! V. w? o' k. W. y, k; o' m! r; i, n. k, w; U? S? t; O' g' z. V. N? z, W? j! m? W! h; t! V' T! Z? R' w, w? y? y; O' w; r? q. G, V. x? n, Y; Q. s? S. G. f, s! U? l. o! i. L; Z' X! u. y, Q. q; Q, D; V. m. q. s? Y, U; p? u! q? h? O. W' y? Z! x! r. E, R, r' X' V, b. z, x! Q; y, g' j; j. q; W; v' X! J' H? i' o? n, Y. X! x? h? u; T? l! o? z. K' z' s; L? p? V' r. L? Y; V! V' S. t? Z' T' Y. s? i? Y! G? r; Y; T! h! K; M. k. U; A! V? R? C' x! X. M; z' V! w. N. T? Y' w? n, Z, Z? Y' R; V' f; V' I; t? X? Z; l? R, Q! Z. R. R, O. S! w; p' T. u? U! n, V, M. p? Q, O? q' t. B, k. u. H' T; T? S; Y! S! i? q! K' z' S! v; L. x; q; W? m? y, Z! x. y. j? N' R' I? r? V! Z; s, O? s; V, I, e? U' w! T? T! u; U! e? w? z; t! C! z? U, p' p! r. x; U! Z; u! j; T! X! N' F? n! P' t, X. s; q'",
			{"m","i","s","w","y","d","q","l","a","p","n","t","u","b","o","e","f","g","c","x"}, "z"}
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
