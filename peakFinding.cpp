/*
	Peak finding
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
	vector<int> list;
	int num, input;
	cin >> num;

	for (int j = 0; j < num; j++) {
		cin >> input;
		list.push_back(input);
	}

	int a = list.size() - 1;
	bool found = false;
	int maxSum = 0;

	while (!found) {
		int b = a/2;
		if (b == 0 || b == list.size() - 1) {
			maxSum = list[b];
			break;
		}

		unsigned long long curSum = list[b];
		unsigned long long beforeSum = list[b-1];
		unsigned long long afterSum = list[b+1];

		if ( curSum >= beforeSum && curSum >= afterSum){
			found = true;
			maxSum = curSum;
		} else if (curSum < afterSum) {
			a = b + list.size();
		} else if (curSum < beforeSum) {
			a = b;
		}
	}
	cout << maxSum << endl;
}
