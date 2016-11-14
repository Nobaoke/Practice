// TODO: need to fix permutation to only output unique strings
//       combination should only be on unique characters
// 		 - will have to build unique character string as member
// 	     extending this class to do permuation on vectors instead of just strings

#include <iostream>
#include <cmath>

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

	void printAllCombUtil(string prefix, int start);
	void printAllCombUtil2(string *prefix, int start);
	void printAllCombUtil3();
	void printAllCombUtil4();

	void printAllPermUtil(string *prefix, bool *used);

	void printCombUtil(string *prefix, int size, int start);
};

Combinatorics::Combinatorics(string str) : mStr(str) {}
Combinatorics::~Combinatorics(){}

void Combinatorics::printAllCombUtil(string prefix, int start) {
	for (int i = start; i < mStr.length(); i++){
		string toPrint = prefix + mStr[i];
		cout << toPrint << endl;
		if (i+1 < mStr.length()){
			printAllCombUtil(toPrint, i+1);
		}
	}
	return;
}

void Combinatorics::printAllCombUtil2(string *prefix, int start) {
	for (int i = start; i < mStr.length(); i++){
		*prefix += mStr[i];
		cout << *prefix << endl;
		if (i+1 < mStr.length()) {
			printAllCombUtil2(prefix, i+1);
		}
		*prefix = prefix->substr(0, prefix->length() - 1);
	}

	return;
}

void Combinatorics::printAllCombUtil3() {
	for (int i = 1; i <= mStr.length(); i++){
		printCombinations(i);
	}

	return;
}

void Combinatorics::printAllCombUtil4() {
	for (int i = 1; i < pow(2,mStr.length()); i++){
		int mask = 1;
		int selectionBits = i;
		int index = 0;
		string toPrint;
		while (selectionBits != 0){
			int select = selectionBits & mask;
			if (select) {
				toPrint += mStr[index];
			}
			selectionBits = selectionBits >> 1;
			index += 1;
		}
		cout << toPrint << endl;
	}

	return;
}

// print all combinations of letters in mStr, no empty combination
void Combinatorics::printAllCombinations() {
	string *buffer = new string();

	printAllCombUtil2(buffer, 0);

	delete buffer;

	return;
} 

void Combinatorics::printAllPermUtil(string *prefix, bool *used) {
	for (int i = 0; i < mStr.length(); i++){
		if (!used[i]) {
			*prefix += mStr[i];
			used[i] = true;
			if (prefix->length() == mStr.length()) {
				cout << *prefix << endl;
			} else {
				printAllPermUtil(prefix, used);
			}
			used[i] = false;
			*prefix = prefix->substr(0, prefix->length() - 1);
		}
	}
	return;
}

void Combinatorics::printAllPermutations() {
	bool *used = new bool[mStr.length()];
	string *buffer = new string();

	printAllPermUtil(buffer, used);

	delete[] used;
	delete buffer;

	return;
} 

void Combinatorics::printCombUtil(string *prefix, int size, int start) {
	for (int i = start; i < mStr.length() && (mStr.length() - i >= size - prefix->length()); i++){
		*prefix += mStr[i];
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
	if (size > mStr.length()){
		return;
	}

	string *buffer = new string();

	printCombUtil(buffer, size, 0);

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