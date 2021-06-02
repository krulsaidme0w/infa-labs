#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Node {

	public:

	char data;
	Node* pNext;
	Node* pPrev;

	Node(char data = '-', Node *pNext = nullptr, Node *pPrev = nullptr) {
		this->data = data;
		this->pNext = pNext;
		this->pPrev = pPrev;
	}

};

class DList {
                
public:
    
	Node* Head;
    Node* Tail; 

    DList() {
     	Head = nullptr;
     	Tail = nullptr;
    };    
     
    // ~DList() {

    //  	while(Head != nullptr) {
    //  		Tail = Head->pNext;
    //  		delete Head;
    //  		Head = Tail;
    //  	}
    // }                
     
    void Add(char data) {

    	Node* temp = new Node(data, nullptr, nullptr);

    	if(Head == nullptr) {
    		Head = temp;
    		Tail = temp;
    	}
    	else {
    		Tail->pNext = temp;
    		temp->pPrev = Tail;
    		Tail = temp;
    	}

    	return;
    }

    void ShowFromTail() {

    	Node* temp = Tail;

    	while(temp != nullptr) {
    		cout << temp->data;
    		temp = temp->pPrev;
    	}
    	cout << endl;

    }

    void ShowFromHead() {
    	Node* temp = Head;

    	while(temp != nullptr) {
    		cout << temp->data;
    		temp = temp->pNext;
    	}
    	cout << endl;
    }    

    string GetString() {

    	string s = "";

    	Node* temp = Head;

    	while(temp != nullptr) {
    		s += temp->data;
    		temp = temp->pNext;
    	}

    	return s;
    }
 
};



void writeFile(string fileName, vector<DList> vlst) {

	ofstream o(fileName);

	for(int i = 0; i < vlst.size(); ++i) {

		string s = vlst[i].GetString();    	
		o << s;
		if(i != vlst.size() - 1) {
			o << endl;
		}
    }

	return;
}

vector<DList> readFile(string fileName) {

	ifstream i(fileName);
	
	vector<DList> vlst;

	string s;
	
	while(i >> s) {

        DList temp;
        
        for(int i = 0; i < s.size(); ++i) {
        	char c = s[i];
        	temp.Add(c);
        }

        vlst.push_back(temp);

	}
    
    for(DList i : vlst) {
    	i.ShowFromHead();
    }


	return vlst;
}


void makeRightArray(vector<DList> rlst, vector<DList> flst) {

	for(int i = 0; i < rlst.size(); ++i) {
	
		Node* rtemp = rlst[i].Head;
		string rs = "";

		while(rtemp != nullptr) {
			rs += rtemp[i]->data;
			rtemp = rtemp->pNext;
		}

		
		




    	// while(rtemp != nullptr) {
    		
    	// 	if(rtemp->data != ftemp->data) {
    	// 		ftemp->data = rtemp->data;
    	// 	}

    	// 	rtemp = rtemp->pNext;
    	// 	ftemp = ftemp->pNext;
    	// }

    }

}


int main() {

	cout << "right" << endl << endl;
	vector<DList> rlst = readFile("right.txt");
	cout << endl << "wrong" << endl << endl;
	vector<DList> flst = readFile("false.txt");
	cout << endl;

	makeRightArray(rlst, flst);

	writeFile("false.txt", rlst);

	cout << "right" << endl << endl;
	readFile("right.txt");
	cout << endl << "correct" << endl << endl;
	readFile("false.txt");
	cout << endl;

}