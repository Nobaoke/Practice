// TODO: need to fix permutation to only output unique strings
//       combination should only be on unique characters
// 	     extending this class to do permuation on vectors instead of just strings

#include <iostream>
#include <cmath>
#include <map>

using namespace std;

class Combinatorics {
public:
	Combinatorics(string str);
	virtual ~Combinatorics();

	void printAllCombinations();
	void printAllPermutations();
	void printCombinations(int size);

private:
	const string mStr;
	string mUniquStr;

	void printAllCombUtil(string prefix, int start);
	void printAllCombUtil2(string *prefix, int start);
	void printAllCombUtil3();
	void printAllCombUtil4();

	void printAllPermUtil(string *prefix, map<char, int> &strMap);

	void printCombUtil(string *prefix, int size, int start);
};

Combinatorics::Combinatorics(string str) : mStr(str) {
	map<char, int> uniqueCharMap;

	for(int i = 0; i < mStr.length(); i++){
		if (uniqueCharMap.find(mStr[i]) == uniqueCharMap.end()){
			uniqueCharMap[mStr[i]] = 1;
		}
	}

	for(map<char, int>::iterator it = uniqueCharMap.begin(); it != uniqueCharMap.end(); it++) {
		mUniquStr += it->first;
	}
}
Combinatorics::~Combinatorics(){}

void Combinatorics::printAllCombUtil(string prefix, int start) {
	for (int i = start; i < mUniquStr.length(); i++){
		string toPrint = prefix + mUniquStr[i];
		cout << toPrint << endl;
		if (i+1 < mUniquStr.length()){
			printAllCombUtil(toPrint, i+1);
		}
	}
	return;
}

void Combinatorics::printAllCombUtil2(string *prefix, int start) {
	for (int i = start; i < mUniquStr.length(); i++){
		*prefix += mUniquStr[i];
		cout << *prefix << endl;
		if (i+1 < mUniquStr.length()) {
			printAllCombUtil2(prefix, i+1);
		}
		*prefix = prefix->substr(0, prefix->length() - 1);
	}

	return;
}

void Combinatorics::printAllCombUtil3() {
	for (int i = 1; i <= mUniquStr.length(); i++){
		printCombinations(i);
	}

	return;
}

void Combinatorics::printAllCombUtil4() {
	for (int i = 1; i < pow(2,mUniquStr.length()); i++){
		int mask = 1;
		int selectionBits = i;
		int index = 0;
		string toPrint;
		while (selectionBits != 0){
			int select = selectionBits & mask;
			if (select) {
				toPrint += mUniquStr[index];
			}
			selectionBits = selectionBits >> 1;
			index += 1;
		}
		cout << toPrint << endl;
	}

	return;
}

// print all combinations of letters in mStr, no empty combination, nor repeated characters
void Combinatorics::printAllCombinations() {
	string *buffer = new string();

	printAllCombUtil2(buffer, 0);

	delete buffer;

	return;
} 

void Combinatorics::printCombUtil(string *prefix, int size, int start) {
	for (int i = start; i < mUniquStr.length() && (mUniquStr.length() - i >= size - prefix->length()); i++){
		*prefix += mUniquStr[i];
		if(prefix->length() == size){
			cout << *prefix << endl;
		} else {
			printCombUtil(prefix, size, i+1);
		}
		*prefix = prefix->substr(0, prefix->length() - 1);
	}

	return;
}

void Combinatorics::printCombinations(int size){
	if (size > mUniquStr.length()){
		return;
	}

	string *buffer = new string();

	printCombUtil(buffer, size, 0);

	delete buffer;

	return;
}

void Combinatorics::printAllPermUtil(string *prefix, map<char, int> &strMap) {
	for (map<char, int>::iterator it = strMap.begin(); it != strMap.end(); it++){
		char curChar = it->first;

		if (strMap[curChar] != 0) {
			*prefix += curChar;
			strMap[curChar] -= 1;
			if (prefix->length() == mStr.length()) {
				cout << *prefix << endl;
			} else {
				printAllPermUtil(prefix, strMap);
			}
			strMap[curChar] += 1;
			*prefix = prefix->substr(0, prefix->length() - 1);
		}
	}
	return;
}

void Combinatorics::printAllPermutations() {
	string *buffer = new string();
	map<char, int> strMap;

	for(int i = 0; i < mStr.length(); i++){
		if(strMap.find(mStr[i]) == strMap.end()){
			strMap[mStr[i]] = 1;
		} else {
			strMap[mStr[i]] += 1;
		}
	}

	printAllPermUtil(buffer, strMap);

	delete buffer;

	return;
} 

int main() {
	string input;
	int n;

	cin >> input >> n;

	Combinatorics *myUtil = new Combinatorics(input);

	cout << "Permutations:" << endl;

	myUtil->printAllPermutations();

	cout << "----------------------" << endl;
	cout << "Combinations:" << endl;

	myUtil->printAllCombinations();

	cout << "----------------------" << endl;
	cout << "Combinations of " << n << ":" << endl;

	myUtil->printCombinations(n);

	return 0;
}