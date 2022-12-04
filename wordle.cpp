// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
		std::string word, 
		std::string floating, 
		const std::set<std::string>& dict, 
		size_t index,
		std::set<std::string>& final);

// std::string convertVecToString(vector<std::char> vec);

char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
										'h', 'i', 'j', 'k', 'l', 'm', 'n', 
										'o', 'p', 'q', 'r', 's', 't', 'u', 
										'v', 'w', 'x', 'y', 'z'};

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		std::set<std::string> final;
		size_t index = 0;
		wordleHelper(in, floating, dict, index, final);
		return final;
}

// Define any helper functions here
// std::string convertVecToString(vector<std::char> vec) {
// 		//maybe add base case
// 	  std::string s;
//     for (unsigned i = 0; i < vec.size(); i++) {
//         s.insert(i, 1, vec[i]);
//     }
// 		return s;
// }

void wordleHelper(std::string word, std::string floating, const std::set<std::string>& dict, size_t index, std::set<std::string>& final) {
	
	int dashCount = 0;
	//update dashes count
	for (size_t i = 0; i < word.size(); i++) {
		if (word[i] == '-') dashCount++;
	}

	//base case
	//if at end of string and no floating letters remain and in dictionary
	if (index == word.size() && floating.empty()) 
	{
		//cout << "HERE HERE" << endl;
		if (dict.find(word) != dict.end()) {
			final.insert(word);
			//cout << word << endl;
			//cout << final.size() << endl;
		}
		return;
	}

	//if we are not at a dash recurse to the next letter
	if (word[index] != '-') {
		wordleHelper(word, floating, dict, index+1, final);
		return;
	}

	//create vector of chars with the floating letters
	// vector<char> floatingLetters; 
	// std::string test;
	// for (unsigned int i = 0; i < (int)floating.size(); i++) {
	// 	std::string test;
	// 	test.push_back(floating[i]);
	// 	floatingLetters.push_back(floating[i]);
	// 	test = "";
	// }

	//if more dashes than floating letters
	if (dashCount > (int)floating.size()) {
		//loop thru all letters
		//iterate thru floating
		for (char c = 'a'; c <= 'z'; c++) {
			//cout << "HERE 1" << endl;
			//if float letter found in alphabet, remove float letter and recurse
			char curr = floating.find(c);
			if (curr != string::npos) {
				std::string floatingTemp = floating;
				word[index] = c;
				floatingTemp.erase(curr, 1);
				wordleHelper(word, floatingTemp, dict, index+1, final);
			}
			//else recurse to next index
			else {
				//cout << "TEST" << endl;
				word[index] = c;
				wordleHelper(word, floating, dict, index+1, final);
			}
		}
	}

	//if equal dashes and floating letters
	else if (dashCount == (int)floating.size()) {
		for (size_t s = 0; s < floating.size(); s++) {
			//cout << "HERE 2" << endl;
			std::string floatingTemp = floating;
			word[index] = floating[s];
			floatingTemp.erase(s, 1);
			wordleHelper(word, floatingTemp, dict, index+1, final);
		}
	}

	//if more floating letters than dashes
	else if (dashCount < (int)floating.size()) {
		for (size_t s = 0; s < floating.size(); s++) {
			//cout << "HERE 3" << endl;
			std::string floatingTemp = floating;
			word[index] = floating[s];
			floatingTemp.erase(s, 1);
			wordleHelper(word, floatingTemp, dict, index+1, final);
		}
	}
}
