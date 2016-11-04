/*
	Given coin types and number M output the number of ways
	we can make change for M
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

typedef vector<int> CoinTypes;
typedef map<int, unsigned long long> CoinChangeMap;
typedef vector<CoinChangeMap *> CoinChangeMaps;

unsigned long long coinChange(int n, const CoinTypes &cTypes, CoinChangeMaps maps) {
	unsigned long long numWays = 0;

	if(cTypes.size() == 0){
		numWays = 0;
	} else if(cTypes.size() == 1) {
		if (n % cTypes[0] == 0) {
			numWays = 1;
		} else {
			numWays = 0;
		}
	} else {
		CoinChangeMap *temp = maps[0];
		if (temp->find(n) != temp->end()) {
			numWays = (*temp)[n];
		} else {
			for (int i = 0; i < cTypes.size(); i++) {
				int left = n - cTypes[i];
				if (left < 0) {
					numWays += coinChange(n, CoinTypes(cTypes.begin()+i+1, cTypes.end()),
						                     CoinChangeMaps(maps.begin()+i+1, maps.end()));
					break;
				} else {
					numWays += coinChange(left, CoinTypes(cTypes.begin()+i, cTypes.end()),
						                        CoinChangeMaps(maps.begin()+i, maps.end()));
				}
			}
			(*(maps[0]))[n] = numWays;
		}
	}

	return numWays;
}

int main() {
	int n, m;
	CoinTypes cTypes;
	unsigned long long numWays = 0;
	CoinChangeMaps maps;

	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int input;
		cin >> input;

		cTypes.push_back(input);
	}

	sort(cTypes.begin(), cTypes.end(), greater<int>());

	for (int i= 0; i < cTypes.size() ; i++) {
		CoinChangeMap *map = new CoinChangeMap();
		(*map)[0] = 1;
		maps.push_back(map);
	}

	numWays = coinChange(n, cTypes, maps);

	cout << numWays << endl;

	for (int i= 0; i < maps.size() ; i++) {
		delete(maps[i]);
	}
    
    return 0;
}
