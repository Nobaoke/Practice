#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

typedef vector<unsigned long long> IntArray;
typedef IntArray MandraArray;


unsigned long long maxScore(MandraArray &mandras) {
	unsigned long long maxSum = 0;

	sort(mandras.begin(), mandras.end());

	IntArray mandraSums(mandras.size());

	unsigned long long runningSum = 0;

	for (int i = mandras.size()-1; i >= 0; i--) {
		runningSum += mandras[i];
		mandraSums[i] = runningSum;
	}

	int a = 0;
	int b = mandras.size() - 1;
	bool found = false;

	if(mandras.size() == 2) {
		return max(mandraSums[0],mandraSums[1]*(2));
	}

	while (!found) {
		int c = (a + b)/2;
		unsigned long long curSum = mandraSums[c]*(c+1);
		
		if (c == 0) {
			if (mandras.size() == 2) {
				maxSum = max(mandraSums[0],mandraSums[1]*(2));
			} else {
				maxSum = curSum;
			}
			found = true;
		} else if (c == mandras.size() - 1) {
			maxSum = curSum;
			found = true;
		} else {
			unsigned long long beforeSum = mandraSums[c-1]*(c);
			unsigned long long afterSum = mandraSums[c+1]*(c+2);

			if ( curSum >= beforeSum && curSum >= afterSum){
				maxSum = curSum;
				found = true;
			} else if (curSum < afterSum) {
				a = c + 1;
			} else if (curSum < beforeSum) {
				b = c - 1;
			}
		}
	}

	return maxSum;
}

int main() {

	unsigned long long testCases, mandraNum, mandraHealth;

	cin >> testCases;
	IntArray score;

	for (int i = 0; i < testCases; i++){
		MandraArray list;
		cin >> mandraNum;

		for (int j = 0; j < mandraNum; j++) {
			cin >> mandraHealth;
			list.push_back(mandraHealth);
		}

		score.push_back(maxScore(list));
	}

	for (IntArray::iterator it = score.begin(); it != score.end(); it++) {
		cout << *it << endl;
	}

    return 0;
}
