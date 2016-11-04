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

	for (int i = 0; i < mandras.size(); i++) {
		maxSum = max(maxSum, mandraSums[i]*(i+1));
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
