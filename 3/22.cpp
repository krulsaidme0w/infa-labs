#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstring>

using namespace std;

typedef struct {
    string capital;
    string country;
} info;



bool Compare(info s1, info s2) {
    return s1.country > s2.country;
}


void printArray(info* array, size_t n) {

	for(size_t i = 0; i < n; i++){
		cout << array[i].country << ' ' << array[i].capital << endl;
	}

	return;
}


void fillArray(info* array, size_t n) {
	
	for(size_t i = 0; i < n; i++){
		info temp;
        cin >> temp.country >> temp.capital;
        array[i] = temp;
	}

	return;
}



bool writeArray(info* array, size_t n) {

	FILE *f;
	f = fopen("file.txt", "ab+");

	for(size_t i = 0; i < n; ++i) {

		if(!(fwrite(&array[i], sizeof(info), 1, f) == 1)) {
			return false;
		}
	}

	fclose(f);

	return true;
}


void readArray(info* array, size_t n) {

	delete[] array;

	FILE *f;
	f = fopen("file.txt", "rb+");

	array = new info[n];


	for(size_t i = 0; i < n; ++i) {

		if(!(fread(&array[i], sizeof(info), 1, f) == 1)) {
			return;
		}

	}

	fclose(f);


}


void sortArray(info* array, size_t n) {


	for(size_t i = 0; i < n; ++i) {

		for(size_t j = i + 1; j < n; ++j) {

			if(Compare(array[i], array[j])) {
				swap(array[i], array[j]);
			}


		}

	}


}

void addElement(info* array, size_t &n, info element) {

	size_t newSize = n + 1;
    
    info* newArray = new info[newSize];

    for(size_t i = 0; i < n; ++i)
    	newArray[i] = array[i];

    n = newSize;

   	delete[] array;
   	array = newArray;

   	array[n - 1] = element;

}


info getCapital(info* array, size_t n, string country) {

	info el;
	el.country = "NULL";
	el.capital = "NULL";

	for(size_t i = 0; i < n; i++){

		if(array[i].country == country) {
			el = array[i];
			break;
		}
	
	}

	return el;

}

info getElement() {
	info element;
	cin >> element.country >> element.capital;
	return element;
}


void printInfo(info el) {
	cout << el.country << ' ' << el.capital << endl;
}


int main() {

	FILE *f;
	f = fopen("file.txt", "w+");


	size_t n = 0;
	cout << "cin n ";
	cin >> n;	

	info* array = new info[n];

	fillArray(array, n);

	writeArray(array, n);
	
	readArray(array, n);

	printArray(array, n);

	string s;
	cin >> s;

	info t = getCapital(array, n, s);
	printInfo(t);

	

	return 0;

}