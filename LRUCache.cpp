#include <iostream>
#include <map>
#include <list>

using namespace std;

template<typename K, typename V> 
class LRUCache {
public:
	LRUCache(unsigned int capacity) : capacity(capacity){}
	void insert(K key, V val);
	V getValue(K key);
	void printState();

private:
	void updateLRU(K key);

	unsigned int capacity;
	map<K, V> cache;
	list<K> lruList;
};

template<typename K, typename V> 
void LRUCache<K,V>::printState(){
	cout << "Cache state:" << endl;
	for(typename map<K, V>::iterator it = cache.begin(); it != cache.end(); it++){
		cout << it->first << "," << *(it->second) << endl;
	}

	cout << "LRU state:" << endl;
	for(typename list<K>::iterator it = lruList.begin(); it != lruList.end(); it++){
		cout << *it << " ";
	}
	cout << endl << endl;
}

template<typename K, typename V>
void LRUCache<K,V>::updateLRU(K key){
	typename list<K>::iterator pos = lruList.end();
	for(typename list<K>::iterator it = lruList.begin(); it != lruList.end(); it++){
		if (*it == key){
			pos = it;
			break;
		}
	}

	if (pos != lruList.end()){
		lruList.erase(pos);
	} else if (lruList.size() == capacity){
		cache.erase(lruList.front());
		lruList.pop_front();
	}

	lruList.push_back(key);
}

template<typename K, typename V>
void LRUCache<K,V>::insert(K key, V val){
	if (capacity == 0) {
		return;
	}
	cache[key] = val;
	updateLRU(key);
}

template<typename K, typename V> 
V LRUCache<K,V>::getValue(K key){
	if (cache.find(key) != cache.end()){
		updateLRU(key);
		return cache[key];
	} else {
		return NULL;
	}
}

int main() {
	LRUCache<int, int *> myCache(3);
	int * myVal = new int(8383);
	myCache.insert(1, myVal);
	myCache.printState();
	myCache.insert(2, myVal);
	myCache.printState();
	myCache.insert(3, myVal);
	myCache.printState();
	myCache.insert(4, myVal);
	myCache.printState();
	myCache.insert(1, myVal);
	myCache.printState();

	myCache.getValue(5);
	myCache.printState();

	myCache.getValue(2);
	myCache.printState();

	myCache.getValue(4);
	myCache.printState();

	myCache.getValue(3);
	myCache.printState();

	myCache.insert(1, myVal);
	myCache.printState();
	myCache.getValue(1);
	myCache.printState();
	
	return 0;
}