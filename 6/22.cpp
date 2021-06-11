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

    bool operator==(const Node &l) {
        if(this->data != l.data) {
            return 0;
        }

        return 1;
    }

};

class DList {
                
public:
    
	Node* Head;
    Node* Tail; 

    int size;

    DList() {
     	Head = nullptr;
     	Tail = nullptr;
        size = 0;
    };    
     
    // ~DList() {

    //  	while(Head != nullptr) {
    //  		Tail = Head->pNext;
    //  		delete Head;
    //  		Head = Tail;
    //  	}
    // }                
    
    int GetSize() {
        return size;
    }

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

        size++;

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

    bool operator==(DList &l) {
        
        if(this->GetSize() != l.GetSize()) {
            return 0;
        }

        Node* node1 = this->Head;
        Node* node2 = l.Head;

        while(node1 != nullptr) {
            if(node1 != node2) {
                return 0;
            }
            node1 = node1->pNext;
            node2 = node2->pNext;
        }

        return 1;

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


DList findWord(DList rightWrd, vector<DList> flst) {


    
    int kmax = -1;
    DList wrd;

    for(auto falseWrd : flst) {

        Node* rtemp = rightWrd.Head;
        Node* ftemp = falseWrd.Head;
        int k = 0;

        if(falseWrd.GetSize() == rightWrd.GetSize()) { 
            while(rtemp != nullptr) {
            
                if(rtemp->data == ftemp->data) {
                    k++;
                }

                rtemp = rtemp->pNext;
                ftemp = ftemp->pNext;
            }
        }

        else {

            if(falseWrd.GetSize() > rightWrd.GetSize()) {
                while(rtemp != nullptr) {
            
                    if(rtemp->data == ftemp->data) {
                        k++;
                    }

                    rtemp = rtemp->pNext;
                    ftemp = ftemp->pNext;
                }

            }
            else {
                while(ftemp != nullptr) {
            
                    if(rtemp->data == ftemp->data) {
                        k++;
                    }

                    rtemp = rtemp->pNext;
                    ftemp = ftemp->pNext;
                }
            }
        }

        if(k > kmax) {
            kmax = k;
            wrd = falseWrd;
        }
    }

    return wrd;

}


void makeRightArray(vector<DList> rlst, vector<DList> flst) {

	for(auto rightWrd : rlst) {


        DList word = findWord(rightWrd, flst);
        //word.ShowFromHead();
        


        for(auto falseWrd : flst) {

            if(falseWrd == word) {
                Node* rtemp = rightWrd.Head;
                Node* ftemp = falseWrd.Head;

                while(rtemp != nullptr) {
                    
                    if(ftemp == nullptr) {
                        falseWrd.Add(rtemp->data);
                    }

                    else if(rtemp->data != ftemp->data) {
                        ftemp->data = rtemp->data;
                    }

                    rtemp = rtemp->pNext;
                    
                    if(ftemp != nullptr)
                        ftemp = ftemp->pNext;
                }
                break;
            }
        }

        // for(auto falseWrd : flst) {
        //     falseWrd.ShowFromHead();
        // }
        // cout << endl;

    }

}

/*
spske
coo
meew
nyyu
*/

int main() {

	cout << "right" << endl << endl;
	vector<DList> rlst = readFile("right.txt");
	cout << endl << "wrong" << endl << endl;
	vector<DList> flst = readFile("false.txt");
	cout << endl;

	makeRightArray(rlst, flst);

	writeFile("false.txt", flst);

	cout << "right" << endl << endl;
	readFile("right.txt");
	cout << endl << "correct" << endl << endl;
	readFile("false.txt");
	cout << endl;

}
