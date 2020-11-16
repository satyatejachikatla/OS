//g++ lru.cpp && ./a.out 1 2 3 4 1 3 6 7

#include <iostream>
#include <unordered_map>
#include <list>
#include <stdlib.h>

using namespace std;

class LRUCache {

private:
	list<int> q;
	unordered_map<int,list<int>::iterator> m;

	int max_size;

public:
	LRUCache(int size) {
		max_size = size;
	}

	bool refer(int page_number) {
		if(m.find(page_number) == m.end()) {
			if(q.size() == max_size)
				q.pop_back();
			q.push_front(page_number);
			m[page_number] = q.begin();
			return true;
		} else {
			q.erase(m[page_number]);
			q.push_front(page_number);
			return false;
		}
	}

	void display() {
		for(list<int>::iterator it=q.begin(); it != q.end(); it++) {
			cout << *it << " " ;
		}
		cout <<endl;
	}

};

int main(int argc , char** argv ) {
	LRUCache my_c(5);

	for(int i=1;i<argc;i++) {
		my_c.refer(atoi(argv[i]));
		my_c.display();
	}

	return 0;
}
