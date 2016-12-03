#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// no idea why there should be no Q
const char alphArray[] = {'A','B','C','D','E','F','G','H','I','J','K','L',
			  	 		  'M','N','O','P','R','S','T','U','V','W','X',
			     		  'Y'};

class TelephoneWords {
public:
	TelephoneWords(string input);
	~TelephoneWords();

	void printWords();
	char getCharKey(int teleKey, int index);

private:
	vector<int> teleNum;
	char *buffer;

	void recursivePrintWords(unsigned int index);
	void iterativePrintWords();
};

TelephoneWords::TelephoneWords(string input) {
	int num = 0;

	for (int i = 0; i < input.length(); i++) {
		teleNum.push_back(input[i] - '0');
	}

	buffer = new char(teleNum.size());
}

TelephoneWords::~TelephoneWords() {
	delete buffer;
}

void TelephoneWords::printWords() {
	recursivePrintWords(0);
	//iterativePrintWords();
}

// recursive algorithm
void TelephoneWords::recursivePrintWords(unsigned int index){
	for(int i = 0; i < 3; i++) {
		buffer[index] = getCharKey(teleNum[index],i);
		if (index < teleNum.size() - 1) {
			recursivePrintWords(index + 1);
		} else {
			cout << buffer << endl;
		}
		if (teleNum[index] == 0 ||
			teleNum[index] == 1) {
			return;
		}
	}
}

// iterative algorithm
void TelephoneWords::iterativePrintWords(){
	// init the first telephone alphabet
	for(int i = 0; i < teleNum.size(); i++) {
		buffer[i] = getCharKey(teleNum[i], 0);
	}

	while(true) {
		cout << buffer << endl;
		for (int i = teleNum.size() - 1; i >= 0; i--) {
			if (buffer[i] == getCharKey(teleNum[i], 2)) {
				if (i == 0) {
					return;
				} else {
					buffer[i] = getCharKey(teleNum[i], 0);
				}
			} else if (buffer[i] == getCharKey(teleNum[i], 0)) {
				buffer[i] = getCharKey(teleNum[i], 1);
				break;
			} else {
				buffer[i] = getCharKey(teleNum[i], 2);
				break;
			}
		}

	}
}

char TelephoneWords::getCharKey(int teleKey, int index){
	char result = ' ';

	if (index < 0 || index > 2) {
		return result;
	}

	switch (teleKey) {
		case 0:
			result = '0';
			break;
		case 1:
			result = '1';
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			result = alphArray[(teleKey-2)*3+index];
			break;
		default:
			break;
	}

	return result;
}

int main() {
	TelephoneWords *telWords = new TelephoneWords("345");

	telWords->printWords();

	delete telWords;

	return 0;
}