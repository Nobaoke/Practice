#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <utility>
#include <queue>
#include <climits>

using namespace std;

int main() {
    int rows, cols;

    cin >> rows >> cols;
    char matrix[rows][cols];

    for (int i = 0; i < rows; i++){
        cin >> matrix[i];
    }

    int downMatrix[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 'x') {
                downMatrix[i][j] = INT_MIN;
            } else if (i == 0) {
                downMatrix[i][j] = 0;
            } else {
                downMatrix[i][j] = (downMatrix[i - 1][j] == INT_MIN) ? 0 : downMatrix[i - 1][j] + 1;
            }
        }
    }

    int rightMatrix[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 'x') {
                rightMatrix[i][j] = INT_MIN;
            } else if (j == 0) {
                rightMatrix[i][j] = 0;
            } else {
                rightMatrix[i][j] = (rightMatrix[i][j - 1] == INT_MIN) ? 0 : rightMatrix[i][j-1] + 1;
            }
        }
    }

    int maxPerimeter = INT_MIN;

    for(int i = 0; i < rows; i++) {
        for(int x = rows - 1; x > i; x--) {
            for (int j = 0; j < cols; j++) {
                bool rightFound = false;
                if (x - i == downMatrix[x][j] - downMatrix[i][j]){
                    for (int y = cols - 1; y > j; y--) {
                        if (x-i+y-j < maxPerimeter) {
                            break;
                        }
                        if (x - i == downMatrix[x][y] - downMatrix[i][y]) {
                            if ((y - j == rightMatrix[i][y] - rightMatrix[i][j]) &&
                                (y - j == rightMatrix[x][y] - rightMatrix[x][j])){
                                maxPerimeter = max(maxPerimeter, x-i+y-j);
                                rightFound = true;
                                break;
                            }
                        }
                    }
                }
                if (rightFound) {
                    break;
                }
            }
        }
    }

    if (maxPerimeter == INT_MIN) {
        cout << "impossible" << endl;
    } else { 
        cout << maxPerimeter*2 << endl;
    }

    return 0;
}