// Warning this implementation is extremely inefficient
// refer to hintedMarshes for fast version

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

typedef pair<int, int> Point;
typedef map<int, map<int, int> > SparseMatrix;

class Fence {
public:
    enum Side {
        TOP = 0,
        RIGHT, 
        BOT,
        LEFT,
        NONE
    };

	Fence(int originRow, int originCol,
		  int endRow, int endCol,
          int rows, int cols);

    bool isValidFence();

    // Return the first side that has a marsh, or NONE if not on marsh
    // Order of check -> TOP, RIGHT, BOT, LEFT
    Side isFenceOnMarsh(SparseMatrix &marshMap, Point *marsh);
    Fence shrinkFence(Side shrinkSide, Point point);
    int perimeter();

private:
	Point origin; 
	Point end;
    Point bounds;
};

Fence::Fence(int originRow, int originCol,
		  	 int endRow, int endCol,
             int rows, int cols) {
	origin.first = originRow;
	origin.second = originCol;
	end.first = endRow;
	end.second = endCol;
    bounds.first = rows;
    bounds.second = cols;
}

bool Fence::isValidFence() {
    return (origin.first < end.first) 
           && (origin.second < end.second) 
           && (origin.first >= 0)
           && (origin.first <= bounds.first)
           && (origin.second >= 0)
           && (origin.second <= bounds.second)
           && (end.first >= 0)
           && (end.first <= bounds.first)
           && (end.second >= 0)
           && (end.second <= bounds.second);
}

Fence::Side Fence::isFenceOnMarsh(SparseMatrix &marshMap, Point *marsh) {
    bool foundMarsh = false;

    // top side
    if (marshMap.find(origin.first) != marshMap.end()){
        for (int i = origin.second; i <= end.second; i++) {
            if (marshMap[origin.first].find(i) != marshMap[origin.first].end()) {
                marsh->first = origin.first;
                marsh->second = i;
                return TOP;
            }
        }
    }

    // right side
    for (int i = origin.first; i <= end.first; i++) {
        if (marshMap.find(i) != marshMap.end()){
            if (marshMap[i].find(end.second) != marshMap[i].end()) {
                marsh->first = i;
                marsh->second = end.second;
                return RIGHT;
            }
        }
    }

    // bot side
    if (marshMap.find(end.first) != marshMap.end()){
        for (int i = origin.second; i <= end.second; i++) {
            if (marshMap[end.first].find(i) != marshMap[end.first].end()) {
                marsh->first = end.first;
                marsh->second = i;
                return BOT;
            }
        }
    }

    // left side
    for (int i = origin.first; i <= end.first; i++) {
        if (marshMap.find(i) != marshMap.end()){
            if (marshMap[i].find(origin.second) != marshMap[i].end()) {
                marsh->first = i;
                marsh->second = origin.second;
                return LEFT;
            }
        }
    }

    return NONE;
}

Fence Fence::shrinkFence(Fence::Side shrinkSide, Point point) {
    Fence result = *this;
    switch (shrinkSide) {
        case TOP:
            result.origin.first = point.first + 1;
            break;
        case LEFT:
            result.origin.second = point.second + 1;
            break;
        case RIGHT:
            result.end.second = point.second - 1; 
            break;
        case BOT:
            result.end.first = point.first - 1;
            break;
        case NONE:
            break;
        default:
            cout << "what" << endl;
    }

    return result;
}

int Fence::perimeter() {
    if (this->isValidFence()) {
        return 2*(end.first - origin.first) + 2*(end.second - origin.second);
    }
    else {
        return 0;
    }
}

int maxFencePerimeter(int rows, int cols, SparseMatrix &marshMap) {
    int maxPerimeter = INT_MIN;
    queue<Fence> fenceQueue;

    fenceQueue.push(Fence(0, 0, rows - 1, cols - 1, rows - 1, cols - 1));

    while (!fenceQueue.empty()) {
        Fence fence = fenceQueue.front();
        fenceQueue.pop();

        Point offendingMarsh;
        Fence::Side side = fence.isFenceOnMarsh(marshMap, &offendingMarsh);

        switch (side) {
            case Fence::TOP:
                for (int i = 0; i < 4; i++) {
                    if (i != Fence::BOT) {
                        Fence newFence = fence.shrinkFence(static_cast<Fence::Side>(i), offendingMarsh);           
                        if (newFence.perimeter() < maxPerimeter) {
                            continue;
                        }
                        if (newFence.isValidFence()) {
                            fenceQueue.push(newFence);
                        }
                    }
                }
                break;
            case Fence::LEFT:
                for (int i = 0; i < 4; i++) {
                    if (i != Fence::RIGHT) {
                        Fence newFence = fence.shrinkFence(static_cast<Fence::Side>(i), offendingMarsh);
                        if (newFence.perimeter() < maxPerimeter) {
                            continue;
                        }
                        if (newFence.isValidFence()) {
                            fenceQueue.push(newFence);
                        }
                    }
                }
                break;
            case Fence::RIGHT:
                for (int i = 0; i < 4; i++) {
                    if (i != Fence::LEFT) {
                        Fence newFence = fence.shrinkFence(static_cast<Fence::Side>(i), offendingMarsh);
                        if (newFence.perimeter() < maxPerimeter) {
                            continue;
                        }
                        if (newFence.isValidFence()) {
                            fenceQueue.push(newFence);
                        }
                    }
                }
                break;
            case Fence::BOT:
                for (int i = 0; i < 4; i++) {
                    if (i != Fence::TOP) {
                        Fence newFence = fence.shrinkFence(static_cast<Fence::Side>(i), offendingMarsh);
                        if (newFence.perimeter() < maxPerimeter) {
                            continue;
                        }
                        if (newFence.isValidFence()) {
                            fenceQueue.push(newFence);
                        }
                    }
                }
                break;

            case Fence::NONE:
                if (fence.perimeter() > maxPerimeter) {
                    maxPerimeter = fence.perimeter();
                }
                break;
            default:
                cout << "what" << endl;
        }
    }

    return maxPerimeter;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int rows, cols;

    cin >> rows >> cols;
    string row;
    SparseMatrix marshMap; 

    for (int i = 0; i < rows; i++ ){
        cin >> row;

        if (row.length() != cols) {
            cout << "Columns does not equal expected Columns!" << endl;
            return 0;
        }

    	for (int j = 0; j < cols; j++){
    		if (row[j] == 'x') {
    			marshMap[i][j] = 1;
    		}
    	}
    }

    int maxPerimeter = maxFencePerimeter(rows, cols, marshMap);

    if (maxPerimeter == INT_MIN){
        cout << "impossible" << endl;
    } else {
        cout << maxPerimeter << endl;
    }

    return 0;
}