#include <vector>
#include <iostream>
#include <algorithm>
#include <exception>

using namespace std;

template <typename T, typename Compare = less<T> >
class Heap {
public:
	typedef Compare valueComp;

	class NestedComp {
		friend class Heap;
	protected:
		Compare comp;
		NestedComp(Compare c) : comp(c) {};
	public:
		bool operator()(T left, T right) {
			return comp(left, right);
		}
	};

	Heap(){};
	Heap(const vector<T> &vector);
	Heap(T array[], unsigned int size);

	void push(T val);
	T pop();
	vector<T> getData(){ return data; }
	valueComp getComp();
	NestedComp getNestedComp();

private:			
	int getParent(int index) const;
	int getLeftChild(int index) const;
	int getRightChild(int index) const;

	void bubbleUp(int index, Compare comp);
	void bubbleDown(int index, Compare comp);

	void swapVal(int x, int y);

	vector<T> data;
	Compare comp;
};

template <typename T, typename Compare>
Compare Heap<T, Compare>::getComp() {
	return comp;
}

template <typename T, typename Compare>
typename Heap<T, Compare>::NestedComp Heap<T, Compare>::getNestedComp() {
	NestedComp nComp(getComp()); 
	return nComp;
}

template <typename T, typename Compare>
Heap<T, Compare>::Heap(const vector<T> &vector) {
	data = vector;

	for (int i = data.size() - 1; i >= 0; i--){
		bubbleDown(i, comp);
	}
}

template <typename T, typename Compare>
Heap<T, Compare>::Heap(T array[], unsigned int size){
	data.empty();

	for (int i = 0; i < size; i++){
		data.push_back(array[i]);
	}

	for (int i = getParent(size - 1); i >= 0; i--) {
		bubbleDown(i, comp);
	}
}

template <typename T, typename Compare>
void Heap<T, Compare>::swapVal(int x, int y) {
	T temp = data[x];
	data[x] = data[y];
	data[y] = temp;

	return;
}

template <typename T, typename Compare>
void Heap<T, Compare>::push(T val) {
	data.push_back(val);
	bubbleUp(data.size() - 1, comp);
	return;
}

template <typename T, typename Compare>
T Heap<T, Compare>::pop() {
	if (data.size() == 0) {
		throw "Empty heap";
	}

	T result = data[0];
	swapVal(0, data.size() - 1);
	data.pop_back();

	if (data.size() > 1){
		bubbleDown(0, comp);
	}
	return result;
}

template <typename T, typename Compare>
int Heap<T, Compare>::getParent(int child) const {
	int parentIndex = (child - 1) / 2;

	if (parentIndex < 0 || parentIndex > data.size() - 1 || parentIndex == child) {
		return -1;
	} else {
		return parentIndex;
	}
}

template <typename T, typename Compare>
int Heap<T, Compare>::getLeftChild(int parent) const {
	int leftChildIndex = parent*2 + 1;
	if (leftChildIndex > data.size() - 1 || 
		leftChildIndex < 0) {
		return -1;
	} else {
		return leftChildIndex;
	}
}

template <typename T, typename Compare>
int Heap<T, Compare>::getRightChild(int parent) const {
	int rightChildIndex = parent*2 + 2;
	if ((rightChildIndex > data.size() - 1) || 
		(rightChildIndex < 0)) {
		return -1;
	} else {
		return rightChildIndex;
	}
}

template <typename T, typename Compare>
void Heap<T, Compare>::bubbleUp(int index, Compare comp){
	int parentIndex = getParent(index);
	if (parentIndex == -1){
		return;
	}
	if (!comp(data[index], data[parentIndex])){
		swapVal(index, parentIndex);
		bubbleUp(parentIndex, comp);
	}
	return;
}

template <typename T, typename Compare>
void Heap<T, Compare>::bubbleDown(int index, Compare comp){
	int leftChildIndex = getLeftChild(index);
	int rightChildIndex = getRightChild(index);
	int largest = index;

	if (leftChildIndex != -1 && comp(data[largest], data[leftChildIndex])) {
		largest = leftChildIndex;
	} 
	if (rightChildIndex != -1 && comp(data[largest], data[rightChildIndex])) {
		largest = rightChildIndex;
	}

	if (largest != index) {
		swapVal(largest, index);
		bubbleDown(largest, comp);
	}
	return;
}

void printVector(vector<int> vector){
	if (vector.size() == 0){
		return;
	}

	cout << vector[0];
	for(int i = 1; i < vector.size(); i++){
		cout << " " << vector[i];
	}
	cout << endl;
	return;
}

int main() {
	try {
		int array[] = {-4, 9, 4, 10, 29, 84, 291, 3};
		vector<int> control(array, array + sizeof(array)/sizeof(int));

		make_heap(control.begin(), control.end());

		for (int i = 0; i < sizeof(array)/sizeof(int); i++){
			cout << control.front() << " ";
			pop_heap(control.begin(), control.end());
			control.pop_back();
		}
		cout << endl;

		Heap<int, greater<int> > myHeap;

		for (int i = 0; i < sizeof(array)/sizeof(int); i++){
			myHeap.push(array[i]);
		}

		for (int i = 0; i < sizeof(array)/sizeof(int); i++){
			cout << myHeap.pop() << " ";
		}
		cout << endl;

		Heap<int, greater<int> > yourHeap(array, sizeof(array)/sizeof(int));

		for (int i = 0; i < sizeof(array)/sizeof(int); i++){
			cout << yourHeap.pop() << " ";
		}
		cout << endl;

		Heap<int, greater<int> >::NestedComp c = yourHeap.getNestedComp();
		cout << c(10, 9) << endl;

	} catch (const char *e){
		cout << e << endl;
	}


	return 0;
}