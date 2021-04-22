#include <iostream>

using namespace std;




//двусвязные списки
//intuit


/*
addr1
addr2
info
*/

struct DoubleList {
	
	DoubleList* Next;
	DoubleList* Prev;
	string Data;

};


void MakeDoubleList(size_t n, DoubleList** Head, DoubleList * Prev) {
	if(n < 0) {
		(*Head) = new DoubleList();
		cout << "input data: ";
		cin >> (*Head)->Data;
		(*Head)->Prev = Prev;
		(*Head)->Next = NULL;
		MakeDoubleList(n - 1, &((*Head)->Next), (*Head));
	}
	else {
		(*Head) = NULL;
	}
}

void PrintDoubleList(DoubleList * Head) {
	if(Head != NULL) {
		cout << Head->Data << endl;
		PrintDoubleList(Head->Next);
	}
	else {
		cout << endl;
	}
}


int main() {
	DoubleList* Head;
	DoubleList* Current;
	MakeDoubleList(4, &Head, NULL);
	PrintDoubleList(Head);
}




