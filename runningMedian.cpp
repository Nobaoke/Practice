#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

class RunningMedian {
public:
    void addValue(int input) {
        if (maxHeap.empty() || input < maxHeap.front()){
            pushMax(input);
        } else if (minHeap.empty() || input > minHeap.front()) {
            pushMin(input);
        } else {
            if (maxHeap.size() > minHeap.size()){
                pushMin(input);
            } else {
                pushMax(input);
            }
        }
        
        if (maxHeap.size() > minHeap.size() + 1){
            pushMin(popMax());
        } else if (minHeap.size() > maxHeap.size() + 1){
            pushMax(popMin());
        }
    }
    
    double getMedian() {
        double median;
        if (maxHeap.size() > minHeap.size()){
            median = maxHeap.front();
        } else if (minHeap.size() > maxHeap.size()){
            median = minHeap.front();
        } else {
            median = double(maxHeap.front() + minHeap.front()) / 2;
        }
        
        return median;
    }
    
private:
    vector<int> minHeap;
    vector<int> maxHeap;
    
    void pushMin(int val) {
        minHeap.push_back(val);
        push_heap(minHeap.begin(), minHeap.end(), greater<int>());
    }
    void pushMax(int val){
        maxHeap.push_back(val);
        push_heap(maxHeap.begin(), maxHeap.end());
    }
        
    int popMin(){
        pop_heap(minHeap.begin(), minHeap.end(), greater<int>());
        int popped = minHeap.back();
        minHeap.pop_back();
        
        return popped;
    }
    
    int popMax(){
        pop_heap(maxHeap.begin(), maxHeap.end());
        int popped = maxHeap.back();
        maxHeap.pop_back();
        
        return popped;
    }
};

int main(){
    int n;
    cin >> n;
    int input;
    RunningMedian rm;
    for(int a_i = 0;a_i < n;a_i++){
        cin >> input;
        
        rm.addValue(input);
        
        cout << std::fixed;
        cout << std::setprecision(1); 
        cout << rm.getMedian() << endl;
    }
    return 0;
}
