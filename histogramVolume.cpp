#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void recurseLeft(int rightBar, int rightBarPos,
				 const vector<int> &historgram, 
				 const vector<int> &leftMax,
				 int *area) {
	if (rightBar == 0 || rightBarPos == 0) {
		return;
	}

	int leftBar = leftMax[rightBarPos - 1];
	int waterLevel = min(leftBar, rightBar);
	int i = rightBarPos - 1;
	while (historgram[i] != leftBar){
		*area += waterLevel - historgram[i];
		i--;
	}
	recurseLeft(leftBar, i, historgram, leftMax, area);
}

void recurseRight(int leftBar, int leftBarPos,
				 const vector<int> &historgram, 
				 const vector<int> &rightMax,
				 int *area) {
	if(leftBar == 0 || leftBarPos == historgram.size() - 1){
		return;
	}

	int rightBar = rightMax[leftBarPos + 1];
	int waterLevel = min(leftBar, rightBar);
	int i = leftBarPos + 1;
	while(historgram[i] != rightBar) {
		*area += waterLevel - historgram[i];
		i++;
	}
	recurseRight(rightBar, i, historgram, rightMax, area);
}

void iterateLeft(int rightBar, int rightBarPos,
				 const vector<int> &historgram, 
				 const vector<int> &leftMax,
				 int *area){
	// left area count
	if (rightBarPos == 0) {
		return;
	}

	int leftBar = leftMax[rightBarPos-1];
	int waterLevel = min(leftBar, rightBar);
	while (leftBar != 0){
		int i = rightBarPos - 1;
		while (historgram[i] != leftBar){
			*area += waterLevel - historgram[i];
			i--;
		}
		rightBarPos = i;
		rightBar = historgram[rightBarPos];

		if (rightBarPos <= 0){
			leftBar = 0;
		} else {
			leftBar = leftMax[rightBarPos-1];
		}
		waterLevel = min(leftBar, rightBar);
	}

	return;
}

void iterateRight(int leftBar, int leftBarPos,
				 const vector<int> &historgram, 
				 const vector<int> &rightMax,
				 int *area){
	// right area count
	if (leftBarPos == historgram.size() - 1) {
		return;
	}
	
	int rightBar = rightMax[leftBarPos+1];
	int waterLevel = min(leftBar, rightBar);
	while (rightBar != 0){
		int i = leftBarPos + 1;
		while (historgram[i] != rightBar){
			*area += waterLevel - historgram[i];
			i++;
		}
		leftBarPos = i;
		leftBar = historgram[leftBarPos];

		if (leftBarPos >= historgram.size()-1){
			rightBar = 0;
		} else {
			rightBar = rightMax[leftBarPos+1];
		}
		waterLevel = min(leftBar, rightBar);
	}

	return;
}

int onePass(const vector<int> &historgram,
	 		 const vector<int> &leftMax,
	 		 const vector<int> &rightMax) {
	int area = 0;
	for (int i = 1; i < historgram.size() - 1; i++){
		int sidesMin = min(leftMax[i - 1], rightMax[i + 1]);

		if (sidesMin > historgram[i]) {
			area += sidesMin - historgram[i];
		}
	}

	return area;
}

int histogramVolume(const vector<int>& historgram){
	vector<int> leftMax(historgram.size());
	vector<int> rightMax(historgram.size());
	int localMax = -1;
	int max = -1;
	int maxPos = 0;

	int area = 0;

	for (int i = 0; i < historgram.size(); i++){
		if (historgram[i] > max){
			max = historgram[i];
			maxPos = i;
		}
		localMax = std::max(localMax, historgram[i]);
		leftMax[i] = localMax;
	}

	localMax = -1;
	for (int i = historgram.size() - 1; i >= 0; i--){
		localMax = std::max(localMax, historgram[i]);
		rightMax[i] = localMax;
	}

	// recurseLeft(max, maxPos, historgram, leftMax, &area);
	// recurseRight(max, maxPos, historgram, rightMax, &area);

	// iterateLeft(max, maxPos, historgram, leftMax, &area);
	// iterateRight(max, maxPos, historgram, rightMax, &area);

	area = onePass(historgram, leftMax, rightMax);

	return area;
}

int main(int argc, char * argv[]) {
	vector<int> historgram;
	int input = 0;

	while(cin >> input){
		historgram.push_back(input);
	}

	int area = histogramVolume(historgram);

	cout << "The area of the histogram is: " << area << endl;
	return 0;
}