#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX_M_SIZE = 100;

struct info {
	string capital;
	string country;
};


int main(){
	FILE *f;
	f = fopen("file.txt", "wb");


	if(f) {
		int n;
		cin >> n;
		for(int i = 0; i < n; i++){
			string * m = new string[MAX_M_SIZE];
			string s;
			fwrite(&m, sizeof(string), 2, f);
			cout << m[0];
		}
	}
	else {
		cout << "Cannot open file " << endl;
	}

} 
