#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
    string capital;
    string country;
} info;


bool CompareFunction(info s1, info s2) {
    return s1.country < s2.country;
}


int main(){
	FILE *f, *fr ;
	f = fopen("file.txt", "w");
    
    vector<info> v;

	if(f) {
        cout << "Enter n" << endl;
		int n;
		cin >> n;
        cout << "Enter country, capital name" << endl;
		for(int i = 0; i < n; i++){
			info s;
            cin >> s.country >> s.capital;
            v.push_back(s);
		}
        sort(v.begin(), v.end(), CompareFunction);
        for(int i = 0; i < v.size(); ++i) {
            cout << v[i].country << ' ' << v[i].capital << endl;
            fwrite(&v[i], sizeof(info), 1, f);
        }
	}
	else {
		cout << "Cannot open file " << endl;
        return 0;
	}
    
    cout << "Enter country, capital to add" << endl;
    info s1;
    cin >> s1.country >> s1.capital;
    v.push_back(s1);
    fwrite(&v[v.size() - 1], sizeof(info), 1, f);
    sort(v.begin(), v.end(), CompareFunction);
    cout << "All countries and capitals" << endl;
    for(int i = 0; i < v.size(); ++i) {
            cout << v[i].country << ' ' << v[i].capital << endl;
    } 
    string ss;
    cout << "Get capital from country" << endl;
    cin >> ss;
    for(int i = 0; i < v.size(); i++) {
        if(v[i].country == ss) {
            cout << v[i].country << ' ' << v[i].capital << endl;
            break;
        }
    }
    return 0;
} 
