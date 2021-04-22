#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


typedef struct {
	
	int k;
	int s;

} info;  




class List {

public:
	 
	 List() {
	 	Size = 0;
		head = nullptr;
	 }

	~List() {
		clear();
	}

	void pop_front() {
		
		Node *temp = head;
		head = head->pNext;
		delete temp;
		Size--;

	}
	
	void push_back(info data) {
		
		if (head == nullptr) {
			head = new Node(data);
		}
		else {
			Node *current = this->head;

			while (current->pNext != nullptr) {
				current = current->pNext;
			}

			current->pNext = new Node(data);
		}

		Size++;
	}

	
	void clear() {
		
		while (Size) {
			pop_front();
		}
	}

	
	int GetSize() { 
		return Size; 
	}

	info operator[](const int index) {

		int counter = 0;

		Node *current = this->head;

		while(current != nullptr) {

			if(counter == index) {
				return current->data;
			}

			current = current->pNext;
			++counter;
		}


	}
	
	void push_front(info data) {

		head = new Node(data, head);
		Size++;

	}

	void insert(info data, int index) {

		if (index == 0)	{
			push_front(data);
		}
		
		else {
		
			Node *previous = this->head;

			for (int i = 0; i < index - 1; i++) {
				previous = previous->pNext;
			}

			Node *newNode = new Node(data, previous->pNext);
			previous->pNext = newNode;

			Size++;
		}
	}

	
	void removeAt(int index) {

		if(index == 0) {
			pop_front();
		}

		else {
			Node *previous = this->head;
			
			for (int i = 0; i < index - 1; i++) {
				previous = previous->pNext;
			}


			Node *toDelete = previous->pNext;
			previous->pNext = toDelete->pNext;
			delete toDelete;

			Size--;
		}


	}
	
	void pop_back() {
		removeAt(Size - 1);
	}

	void printList() {

		int counter = 0;

		Node *current = this->head;

		while(current != nullptr) {

			if(counter == 0)
				cout << current->data.k << "x^" << current->data.s;

			else
				cout << " + " << current->data.k << "x^" << current->data.s;

			current = current->pNext;
			++counter;
		}
	}


	int getNumber(int number) {

		int counter = 0, res = 0;

		Node *current = this->head;

		while(current != nullptr) {

			res += current->data.k * pow(number, current->data.s);

			current = current->pNext;
			++counter;
		}

		return res;

	}


	void getDif() {

		int counter = 0;
		vector<int> v;

		Node *current = this->head;

		while(current != nullptr) {

			current->data.k *= current->data.s;
			
			if(current->data.s != 0)
				--current->data.s;
			else
				v.push_back(counter);



			current = current->pNext;
			++counter;
		}

		int k = 0;
		for(int i = 0; i < v.size(); ++i) {
			removeAt(v[i] - k);
			++k;
		}


	}


private:

	class Node {

	public:
		Node* pNext;
		info data;

		Node(info data = info(), Node *pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
	};

	int Size;
	Node *head;
};




int main() {

	List lst;

	int n, k, s;
	cout << "cin n ";
	cin >> n;

	for(int i = 0; i < n; ++i) {
		cin >> k >> s;
		info temp;
		temp.k = k;
		temp.s = s;

		if(k != 0)
			lst.push_front(temp);
	}


	int res = lst.getNumber(5);

	lst.printList();
	cout << " = " << res << endl;

	lst.getDif();
	lst.printList();

}